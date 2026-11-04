#ifndef CEFOSRWIDGET_H
#define CEFOSRWIDGET_H

#include "CefOsrHandlerImp.h"
#include <QWidget>
#include "ui_CefOsrWidget.h"

class CefOsrWidget : public QWidget
{
    Q_OBJECT

public:
    explicit CefOsrWidget(const QString& url = QString(), QWidget* parent = nullptr);
    ~CefOsrWidget() override;

protected:
    void closeEvent(QCloseEvent* event) override;
    void resizeEvent(QResizeEvent* event) override;
    void paintEvent(QPaintEvent* event) override;
    bool event(QEvent* event) override;
    void wheelEvent(QWheelEvent* event) override;
    void leaveEvent(QEvent* event) override;
    void focusInEvent(QFocusEvent* event) override;
    void focusOutEvent(QFocusEvent* event) override;

    void mousePressEvent(QMouseEvent* event) override;
    void mouseReleaseEvent(QMouseEvent* event) override;
    void mouseDoubleClickEvent(QMouseEvent* event) override;
    void mouseMoveEvent(QMouseEvent* event) override;
    void keyPressEvent(QKeyEvent* event) override;
    void keyReleaseEvent(QKeyEvent* event) override;

private:
    void runBrowserAction(const CefOsrHandlerImp::BrowserAction& action);
    int toCefModifiers(Qt::MouseButtons buttons, Qt::KeyboardModifiers modifiers) const;
    CefMouseEvent toCefMouseEvent(const QPoint& pos, Qt::MouseButtons buttons,
        Qt::KeyboardModifiers modifiers) const;
    cef_mouse_button_type_t toCefMouseButton(Qt::MouseButton button) const;
    CefKeyEvent toCefKeyEvent(QKeyEvent* event, bool keyUp) const;
    void sendMouseClick(QMouseEvent* event, bool mouseUp, int clickCount);

    Ui::vCefOsrWidget ui;
    CefRefPtr<CefOsrHandlerImp> m_browserHander;
    QImage m_image;
    bool m_closeRequested = false;
    bool m_browserClosed = false;
};

#endif // CEFOSRWIDGET_H
