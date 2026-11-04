#include "CefOsrHandlerImp.h"

#include <QCoreApplication>
#include <QMutexLocker>
#include <QString>
#include "include/base/cef_bind.h"
#include "include/wrapper/cef_closure_task.h"
#include "include/wrapper/cef_helpers.h"
#include "events.h"

CefOsrHandlerImp::CefOsrHandlerImp()
    : m_closeRequested(false), m_hwnd(nullptr), m_receiver(nullptr)
{
}

CefOsrHandlerImp::~CefOsrHandlerImp()
{
}

void CefOsrHandlerImp::setWinHandle(HWND hwnd)
{
    m_hwnd = hwnd;
}

void CefOsrHandlerImp::setReceiver(QObject* receiver)
{
    QMutexLocker lock(&m_receiverLock);
    m_receiver = receiver;
}

void CefOsrHandlerImp::postEvent(QEvent* event)
{
    QMutexLocker lock(&m_receiverLock);
    if (m_receiver) {
        QCoreApplication::postEvent(m_receiver, event);
    }
    else {
        delete event;
    }
}

void CefOsrHandlerImp::RunBrowserAction(const BrowserAction& action)
{
    if (!CefCurrentlyOn(TID_UI)) {
        CefPostTask(TID_UI, base::Bind(&CefOsrHandlerImp::RunBrowserAction,
            CefRefPtr<CefOsrHandlerImp>(this), action));
        return;
    }

    if (!m_closeRequested && !browser_list_.empty()) {
        action(browser_list_.front());
    }
}

bool CefOsrHandlerImp::OnBeforePopup(CefRefPtr<CefBrowser> browser,
    CefRefPtr<CefFrame> frame,
    const CefString& target_url,
    const CefString& target_frame_name,
    WindowOpenDisposition target_disposition,
    bool user_gesture,
    const CefPopupFeatures& popupFeatures,
    CefWindowInfo& windowInfo,
    CefRefPtr<CefClient>& client,
    CefBrowserSettings& settings,
    bool* no_javascript_access)
{
    CEF_REQUIRE_UI_THREAD();
    // Keep new-window links in this off-screen view.
    if (!m_closeRequested && !target_url.empty()) {
        browser->GetMainFrame()->LoadURL(target_url);
    }
    return true;
}

void CefOsrHandlerImp::OnAfterCreated(CefRefPtr<CefBrowser> browser)
{
    CEF_REQUIRE_UI_THREAD();
    browser_list_.push_back(browser);
    if (m_closeRequested) {
        browser->GetHost()->CloseBrowser(true);
        return;
    }
    browser->GetHost()->SetMouseCursorChangeDisabled(false);
    postEvent(new BrowserReadyEvent());
}

bool CefOsrHandlerImp::DoClose(CefRefPtr<CefBrowser> browser)
{
    CEF_REQUIRE_UI_THREAD();
    if (browser_list_.size() == 1) {
        m_closeRequested = true;
    }
    return false;
}

void CefOsrHandlerImp::OnBeforeClose(CefRefPtr<CefBrowser> browser)
{
    CEF_REQUIRE_UI_THREAD();
    for (auto it = browser_list_.begin(); it != browser_list_.end(); ++it) {
        if ((*it)->IsSame(browser)) {
            browser_list_.erase(it);
            break;
        }
    }
    if (browser_list_.empty()) {
        m_closeRequested = true;
        postEvent(new BrowserClosedEvent());
    }
}

void CefOsrHandlerImp::CloseAllBrowsers(bool force_close)
{
    if (!CefCurrentlyOn(TID_UI)) {
        CefPostTask(TID_UI, base::Bind(&CefOsrHandlerImp::CloseAllBrowsers,
            CefRefPtr<CefOsrHandlerImp>(this), force_close));
        return;
    }

    // Keep the request even when asynchronous creation has not completed yet.
    m_closeRequested = true;
    const auto browsers = browser_list_;
    for (const auto& browser : browsers) {
        browser->GetHost()->CloseBrowser(force_close);
    }
}

void CefOsrHandlerImp::OnLoadError(CefRefPtr<CefBrowser> browser,
    CefRefPtr<CefFrame> frame,
    ErrorCode errorCode,
    const CefString& errorText,
    const CefString& failedUrl)
{
    CEF_REQUIRE_UI_THREAD();
    if (errorCode == ERR_ABORTED || m_closeRequested) {
        return;
    }

    const QString html = QStringLiteral(
        "<html><body><h2>Failed to load URL</h2><p>%1</p><p>%2 (%3)</p></body></html>")
        .arg(QString::fromStdWString(failedUrl.ToWString()).toHtmlEscaped())
        .arg(QString::fromStdWString(errorText.ToWString()).toHtmlEscaped())
        .arg(static_cast<int>(errorCode));
    frame->LoadString(html.toStdWString(), failedUrl);
}

bool CefOsrHandlerImp::GetViewRect(CefRefPtr<CefBrowser> browser, CefRect& rect)
{
    RECT clientRect;
    if (!::GetClientRect(m_hwnd, &clientRect)) {
        return false;
    }
    rect = CefRect(0, 0, qMax(1L, clientRect.right - clientRect.left),
        qMax(1L, clientRect.bottom - clientRect.top));
    return true;
}

void CefOsrHandlerImp::OnPaint(CefRefPtr<CefBrowser> browser,
    PaintElementType type,
    const RectList& dirtyRects,
    const void* buffer,
    int width,
    int height)
{
    if (m_closeRequested || type != PET_VIEW || !buffer || width <= 0 || height <= 0) {
        return;
    }

    // The CEF buffer is valid only during this callback; Qt owns the copied frame.
    const QImage view(static_cast<const uchar*>(buffer), width, height,
        width * 4, QImage::Format_ARGB32_Premultiplied);
    const QImage image = view.copy();
    if (!image.isNull()) {
        postEvent(new UpdateEvent(image));
    }
}

void CefOsrHandlerImp::OnCursorChange(CefRefPtr<CefBrowser> browser,
    CefCursorHandle cursor,
    CursorType type,
    const CefCursorInfo& custom_cursor_info)
{
    if (!m_closeRequested) {
        postEvent(new ChangeCursorEvent(type));
    }
}

bool CefOsrHandlerImp::GetScreenPoint(CefRefPtr<CefBrowser> browser,
    int viewX, int viewY, int& screenX, int& screenY)
{
    POINT point = { viewX, viewY };
    if (!::ClientToScreen(m_hwnd, &point)) {
        return false;
    }
    screenX = point.x;
    screenY = point.y;
    return true;
}
