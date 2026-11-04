#include "CefOsrWidget.h"

#include <QCoreApplication>
#include <QCloseEvent>
#include <QCursor>
#include <QFocusEvent>
#include <QGuiApplication>
#include <QKeyEvent>
#include <QMessageBox>
#include <QMouseEvent>
#include <QPainter>
#include <QTimer>
#include <QUrl>
#include <QWheelEvent>
#include "events.h"

CefOsrWidget::CefOsrWidget(const QString& url, QWidget* parent)
    : QWidget(parent)
{
    ui.setupUi(this);
    setWindowTitle(QStringLiteral("OSR (off-screen)"));
    resize(1200, 800);
    setMouseTracking(true);
    setFocusPolicy(Qt::StrongFocus);

    const HWND wnd = reinterpret_cast<HWND>(winId());
    CefWindowInfo windowInfo;
    windowInfo.SetAsWindowless(wnd);

    CefBrowserSettings browserSettings;
    browserSettings.windowless_frame_rate = 60;
    browserSettings.background_color = CefColorSetARGB(255, 255, 255, 255);

    m_browserHander = new CefOsrHandlerImp();
    m_browserHander->setWinHandle(wnd);
    m_browserHander->setReceiver(this);

    const QString pageUrl = url.isEmpty()
        ? QUrl::fromLocalFile(QCoreApplication::applicationDirPath() + "/test.html").toString(QUrl::FullyEncoded)
        : url;
    const bool created = CefBrowserHost::CreateBrowser(windowInfo, m_browserHander,
        CefString(pageUrl.toStdWString()), browserSettings, nullptr);
    if (!created) {
        m_browserClosed = true;
        QTimer::singleShot(0, this, [this]() {
            if (!m_closeRequested) {
                QMessageBox::information(this, QStringLiteral("Browser"),
                    QStringLiteral("Failed to create the off-screen browser."));
                close();
            }
        });
    }
}

CefOsrWidget::~CefOsrWidget()
{
    if (m_browserHander) {
        m_browserHander->setReceiver(nullptr);
        if (!m_browserClosed) {
            m_browserHander->CloseAllBrowsers(true);
        }
    }
}

void CefOsrWidget::runBrowserAction(const CefOsrHandlerImp::BrowserAction& action)
{
    if (!m_closeRequested && !m_browserClosed && m_browserHander) {
        m_browserHander->RunBrowserAction(action);
    }
}

void CefOsrWidget::closeEvent(QCloseEvent* event)
{
    if (m_browserClosed) {
        event->accept();
        return;
    }

    // Keep the native owner and event receiver alive until CEF confirms closure.
    event->ignore();
    if (!m_closeRequested) {
        m_closeRequested = true;
        hide();
        m_browserHander->CloseAllBrowsers(true);
    }
}

void CefOsrWidget::resizeEvent(QResizeEvent* event)
{
    QWidget::resizeEvent(event);
    runBrowserAction([](CefRefPtr<CefBrowser> browser) {
        browser->GetHost()->WasResized();
    });
}

void CefOsrWidget::paintEvent(QPaintEvent* event)
{
    Q_UNUSED(event);
    QPainter painter(this);
    painter.fillRect(rect(), Qt::white);
    if (!m_image.isNull()) {
        painter.drawImage(rect(), m_image, m_image.rect());
    }
}

bool CefOsrWidget::event(QEvent* event)
{
    if (event->type() == UpdateEvent::eventType) {
        if (!m_closeRequested) {
            m_image = static_cast<UpdateEvent*>(event)->m_image;
            update();
        }
        return true;
    }
    if (event->type() == BrowserReadyEvent::eventType) {
        const bool focused = hasFocus();
        runBrowserAction([focused](CefRefPtr<CefBrowser> browser) {
            browser->GetHost()->WasResized();
            browser->GetHost()->SendFocusEvent(focused);
        });
        return true;
    }
    if (event->type() == BrowserClosedEvent::eventType) {
        m_browserClosed = true;
        m_closeRequested = true;
        close();
        return true;
    }
    if (event->type() == ChangeCursorEvent::eventType) {
        if (!m_closeRequested) {
            const auto shape = static_cast<ChangeCursorEvent*>(event)->shape;
            Qt::CursorShape cursor = Qt::ArrowCursor;
            switch (shape) {
            case CT_CROSS: cursor = Qt::CrossCursor; break;
            case CT_HAND: cursor = Qt::PointingHandCursor; break;
            case CT_IBEAM: cursor = Qt::IBeamCursor; break;
            case CT_WAIT: cursor = Qt::WaitCursor; break;
            case CT_HELP: cursor = Qt::WhatsThisCursor; break;
            default: break;
            }
            setCursor(cursor);
        }
        return true;
    }
    if (event->type() == ReloadBrowerEvent::eventType) {
        runBrowserAction([](CefRefPtr<CefBrowser> browser) { browser->Reload(); });
        return true;
    }
    if (event->type() == QEvent::ShortcutOverride) {
        event->accept();
        return true;
    }
    // QWidget otherwise consumes Tab for its own focus traversal.
    if (event->type() == QEvent::KeyPress || event->type() == QEvent::KeyRelease) {
        auto keyEvent = static_cast<QKeyEvent*>(event);
        if (keyEvent->key() == Qt::Key_Tab || keyEvent->key() == Qt::Key_Backtab) {
            if (event->type() == QEvent::KeyPress) {
                keyPressEvent(keyEvent);
            }
            else {
                keyReleaseEvent(keyEvent);
            }
            return true;
        }
    }
    return QWidget::event(event);
}

int CefOsrWidget::toCefModifiers(Qt::MouseButtons buttons, Qt::KeyboardModifiers modifiers) const
{
    int flags = 0;
    if (buttons & Qt::LeftButton) flags |= EVENTFLAG_LEFT_MOUSE_BUTTON;
    if (buttons & Qt::RightButton) flags |= EVENTFLAG_RIGHT_MOUSE_BUTTON;
    if (buttons & Qt::MiddleButton) flags |= EVENTFLAG_MIDDLE_MOUSE_BUTTON;
    if (modifiers & Qt::ShiftModifier) flags |= EVENTFLAG_SHIFT_DOWN;
    if (modifiers & Qt::ControlModifier) flags |= EVENTFLAG_CONTROL_DOWN;
    if (modifiers & Qt::AltModifier) flags |= EVENTFLAG_ALT_DOWN;
    if (modifiers & Qt::KeypadModifier) flags |= EVENTFLAG_IS_KEY_PAD;
    if (::GetKeyState(VK_CAPITAL) & 1) flags |= EVENTFLAG_CAPS_LOCK_ON;
    if (::GetKeyState(VK_NUMLOCK) & 1) flags |= EVENTFLAG_NUM_LOCK_ON;
    return flags;
}

CefMouseEvent CefOsrWidget::toCefMouseEvent(const QPoint& pos,
    Qt::MouseButtons buttons, Qt::KeyboardModifiers modifiers) const
{
    CefMouseEvent result;
    result.x = pos.x();
    result.y = pos.y();
    result.modifiers = toCefModifiers(buttons, modifiers);
    return result;
}

void CefOsrWidget::wheelEvent(QWheelEvent* event)
{
    const CefMouseEvent mouse = toCefMouseEvent(event->pos(), event->buttons(), event->modifiers());
    const QPoint delta = event->angleDelta();
    runBrowserAction([mouse, delta](CefRefPtr<CefBrowser> browser) {
        browser->GetHost()->SendMouseWheelEvent(mouse, delta.x(), delta.y());
    });
    event->accept();
}

void CefOsrWidget::leaveEvent(QEvent* event)
{
    const CefMouseEvent mouse = toCefMouseEvent(mapFromGlobal(QCursor::pos()),
        QGuiApplication::mouseButtons(), QGuiApplication::keyboardModifiers());
    runBrowserAction([mouse](CefRefPtr<CefBrowser> browser) {
        browser->GetHost()->SendMouseMoveEvent(mouse, true);
    });
    QWidget::leaveEvent(event);
}

void CefOsrWidget::focusInEvent(QFocusEvent* event)
{
    QWidget::focusInEvent(event);
    runBrowserAction([](CefRefPtr<CefBrowser> browser) {
        browser->GetHost()->SendFocusEvent(true);
    });
}

void CefOsrWidget::focusOutEvent(QFocusEvent* event)
{
    runBrowserAction([](CefRefPtr<CefBrowser> browser) {
        browser->GetHost()->SendFocusEvent(false);
    });
    QWidget::focusOutEvent(event);
}

cef_mouse_button_type_t CefOsrWidget::toCefMouseButton(Qt::MouseButton button) const
{
    if (button == Qt::RightButton) return MBT_RIGHT;
    if (button == Qt::MiddleButton) return MBT_MIDDLE;
    return MBT_LEFT;
}

void CefOsrWidget::sendMouseClick(QMouseEvent* event, bool mouseUp, int clickCount)
{
    if (event->button() != Qt::LeftButton && event->button() != Qt::RightButton &&
        event->button() != Qt::MiddleButton) {
        event->ignore();
        return;
    }
    const CefMouseEvent mouse = toCefMouseEvent(event->pos(), event->buttons(), event->modifiers());
    const auto button = toCefMouseButton(event->button());
    runBrowserAction([mouse, button, mouseUp, clickCount](CefRefPtr<CefBrowser> browser) {
        browser->GetHost()->SendMouseClickEvent(mouse, button, mouseUp, clickCount);
    });
    event->accept();
}

void CefOsrWidget::mousePressEvent(QMouseEvent* event)
{
    setFocus(Qt::MouseFocusReason);
    sendMouseClick(event, false, 1);
}

void CefOsrWidget::mouseReleaseEvent(QMouseEvent* event)
{
    sendMouseClick(event, true, 1);
}

void CefOsrWidget::mouseDoubleClickEvent(QMouseEvent* event)
{
    sendMouseClick(event, false, 2);
}

void CefOsrWidget::mouseMoveEvent(QMouseEvent* event)
{
    const CefMouseEvent mouse = toCefMouseEvent(event->pos(), event->buttons(), event->modifiers());
    runBrowserAction([mouse](CefRefPtr<CefBrowser> browser) {
        browser->GetHost()->SendMouseMoveEvent(mouse, false);
    });
    event->accept();
}

CefKeyEvent CefOsrWidget::toCefKeyEvent(QKeyEvent* event, bool keyUp) const
{
    CefKeyEvent key;
    key.type = keyUp ? KEYEVENT_KEYUP : KEYEVENT_RAWKEYDOWN;
    key.windows_key_code = static_cast<int>(event->nativeVirtualKey());
    key.modifiers = toCefModifiers(Qt::NoButton, event->modifiers());
    key.is_system_key = (event->modifiers() & Qt::AltModifier) &&
        !(event->modifiers() & Qt::ControlModifier);

    const quint32 scanCode = event->nativeScanCode();
    quint32 nativeCode = 1u | ((scanCode & 0xffu) << 16);
    const int virtualKey = key.windows_key_code;
    const bool extended = (scanCode & 0x100u) || virtualKey == VK_RCONTROL ||
        virtualKey == VK_RMENU || virtualKey == VK_LWIN || virtualKey == VK_RWIN ||
        virtualKey == VK_APPS || virtualKey == VK_DIVIDE ||
        (virtualKey == VK_RETURN && (event->modifiers() & Qt::KeypadModifier)) ||
        (!(event->modifiers() & Qt::KeypadModifier) &&
            (virtualKey == VK_INSERT || virtualKey == VK_DELETE || virtualKey == VK_HOME ||
             virtualKey == VK_END || virtualKey == VK_PRIOR || virtualKey == VK_NEXT ||
             virtualKey == VK_LEFT || virtualKey == VK_RIGHT || virtualKey == VK_UP || virtualKey == VK_DOWN));
    if (extended) nativeCode |= 1u << 24;
    if (key.is_system_key) nativeCode |= 1u << 29;
    if (event->isAutoRepeat() || keyUp) nativeCode |= 1u << 30;
    if (keyUp) nativeCode |= 1u << 31;
    key.native_key_code = static_cast<int>(nativeCode);
    return key;
}

void CefOsrWidget::keyPressEvent(QKeyEvent* event)
{
    if (event->key() == Qt::Key_F5) {
        runBrowserAction([](CefRefPtr<CefBrowser> browser) { browser->Reload(); });
        event->accept();
        return;
    }

    const CefKeyEvent key = toCefKeyEvent(event, false);
    const QString text = event->text();
    runBrowserAction([key, text](CefRefPtr<CefBrowser> browser) {
        browser->GetHost()->SendKeyEvent(key);
        for (const QChar character : text) {
            CefKeyEvent typed = key;
            typed.type = KEYEVENT_CHAR;
            typed.windows_key_code = character.unicode();
            typed.character = character.unicode();
            typed.unmodified_character = character.unicode();
            browser->GetHost()->SendKeyEvent(typed);
        }
    });
    event->accept();
}

void CefOsrWidget::keyReleaseEvent(QKeyEvent* event)
{
    const CefKeyEvent key = toCefKeyEvent(event, true);
    runBrowserAction([key](CefRefPtr<CefBrowser> browser) {
        browser->GetHost()->SendKeyEvent(key);
    });
    event->accept();
}
