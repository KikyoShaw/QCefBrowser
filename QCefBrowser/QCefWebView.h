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

	//���������
	bool CreateBrowser(const QSize & size);

	//������ҳ
	void loadUrl(const QUrl& url);

	//������һҳ
	void back();

	//��һҳ
	void forward();

	//ˢ��
	void refresh();

	//ֹͣ����
	void stop();

	//��ҳ����
	void ModifyZoom(double delta);

	//������Ϣ��js��
    void SendMsgToPage(const QString& msg);

	//�ر������
	void closeBrowser(QCloseEvent* event);

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
	//cef����Ӧ���ڴ�С
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
