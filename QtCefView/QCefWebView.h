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


    void closeBrowser(QCloseEvent* event);

    bool CreateBrowser(const QSize & size);
    //CefRefPtr<CefBrowserHandlerImp> s_browserHandler = NULL;
    //CefRefPtr<CefBrowser> GetBrowser();

    void SendMsgToPage(const QString& msg);

    int browserHandlerIndex;

public slots:
    void loadUrl(const QUrl& url);
    void back();
    void forward();
    void refresh();
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
    void onBrowserCreated();

protected:
    virtual void resizeEvent(QResizeEvent* event) override;

private:
    //CefRefPtr<CefBrowser> GetBrowser() const;
    void ResizeBrowser(const QSize & size);
    bool BrowserLoadUrl(const QUrl & url);

private:

    BrowserState _browserState;
    bool _needResize;
    bool _needLoad;
    QUrl _url;
};
#endif // QCEFWEBVIEW_H
