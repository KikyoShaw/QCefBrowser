#ifndef CEFOSRWIDGET_H
#define CEFOSRWIDGET_H

#include "CefOsrHandlerImp.h"

#include <QWidget>
#include "ui_CefOsrWidget.h"

class CefOsrWidget : public QWidget
{
	Q_OBJECT

public:
    CefOsrWidget(QWidget* parent = nullptr);
    ~CefOsrWidget() override;

protected:
    void resizeEvent(QResizeEvent* event) override;
    void paintEvent(QPaintEvent* event) override;
    bool event(QEvent* event) override;
    void wheelEvent(QWheelEvent* event) override;

    void mousePressEvent(QMouseEvent* event) override;
    void mouseReleaseEvent(QMouseEvent* event) override;
    void mouseDoubleClickEvent(QMouseEvent* event) override;
    void mouseMoveEvent(QMouseEvent* event) override;

    void keyPressEvent(QKeyEvent* event) override;

    CefRefPtr<CefBrowser> getBrowser();

private:
    //将Qt的鼠标按钮转换成Cef中的鼠标按键（鼠标左键、中键，右键）
    cef_mouse_button_type_t toCefMouseButton(Qt::MouseButton mouseButton);
	//将Qt的键盘事件转换成Cef中的键盘事件
    CefKeyEvent toCefKeyEvent(QKeyEvent* event);

private:
    Ui::vCefOsrWidget ui;

    CefRefPtr<CefOsrHandlerImp> m_browserHander;
    QImage m_image;
};

#endif // CEFOSRWIDGET_H
