#ifndef QCEFWEBVIEW_H
#define QCEFWEBVIEW_H
#include <QWidget>
#include <QUrl>
#include "QCefWebView_global.h"


class QCefWebView :public QWidget
{
    Q_OBJECT

public:
    enum BrowserState {
        None,
        Creating,
        Created
    };

public:
    QCefWebView(QWidget *parent = 0);
    ~QCefWebView();

    //CefRefPtr<CefBrowserHandlerImp> s_browserHandler = NULL;
    //CefRefPtr<CefBrowser> GetBrowser();

	//创建浏览器
	bool CreateBrowser(const QSize & size);

	//网页缩放
	void ModifyZoom(double delta);

	//获取浏览器当前尺寸
	double getBrowserZoomLevel();

	//发送消息到js端
	void SendMsgToPage(const QString& msg);

	//关闭浏览器
	void closeBrowser(QCloseEvent* event);


public slots :
	//加载网页
	void loadUrl(const QUrl& url);
	//返回上一页
	void back();
	//下一页
	void forward();
	//刷新
	void refresh();
	//停止加载
	void stop();

signals:
    void titleChanged(const QString& title);
    void urlChanged(const QString& url);
    void loadStateChanged(bool isLoading, bool canGoBack, bool canGoForward);
    void webViewGotFocus();
    void recvRenderMsg(const QString& msg);
    void loadStarted();
    void loadFinished(bool loadSuccess);

private slots:
    void sltBrowserCreated();

protected:
    virtual void resizeEvent(QResizeEvent* event) override;

private:
    //CefRefPtr<CefBrowser> GetBrowser() const;
	//cef自适应窗口大小
    void ResizeBrowser(const QSize & size);
    bool BrowserLoadUrl(const QUrl & url);

private:
    BrowserState _browserState;
    bool _needResize;
    bool _needLoad;
    QUrl _url;
	int browserHandlerIndex;
};
#endif // QCEFWEBVIEW_H
