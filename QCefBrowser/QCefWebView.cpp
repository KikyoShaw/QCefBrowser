#include "qcefwebview.h"
#include <QCloseEvent>
#include <QDebug>
#include "CefBrowserHandlerImp.h"
#include "QCefWebView.h"
#include <QtWidgets/QApplication>
#include "include/wrapper/cef_helpers.h"
#include "include/base/cef_bind.h"

#define DEFAULT_URL "http://43.138.196.60/"

static int s_browserHandlercount=0;
static std::map<int,CefRefPtr<CefBrowserHandlerImp>> smap_browserHandlers=std::map<int,CefRefPtr<CefBrowserHandlerImp>>();
CefRefPtr<CefBrowserHandlerImp> GetBrowserHandler(int index){
    std::map<int,CefRefPtr<CefBrowserHandlerImp>>::iterator itr=smap_browserHandlers.find(index);
    if(itr!=smap_browserHandlers.end()){
        return itr->second;
    }
    return NULL;
}
CefRefPtr<CefBrowser> GetBrowser(int index)
{
    CefRefPtr<CefBrowser> browser = nullptr;
    CefRefPtr<CefBrowserHandlerImp> browserHandler=GetBrowserHandler(index);
    if (browserHandler.get()) {
        browser = browserHandler->GetBrowser();
    }
    return browser;
}

QCefWebView::QCefWebView(QWidget *parent) :
    QWidget(parent),
    _browserState(None),
    _needResize(false),
    _needLoad(false),
    _url(DEFAULT_URL)
{
    setAttribute(Qt::WA_NativeWindow);
    setAttribute(Qt::WA_DontCreateNativeAncestors);
    browserHandlerIndex=s_browserHandlercount++;
    CefRefPtr<CefBrowserHandlerImp> s_browserHandler=NULL;
    if (!s_browserHandler) {
        s_browserHandler = new CefBrowserHandlerImp();
        smap_browserHandlers[browserHandlerIndex]=s_browserHandler;
        connect(s_browserHandler, &CefBrowserHandlerImp::browserCreated, this, &QCefWebView::sltBrowserCreated, Qt::QueuedConnection);
        connect(s_browserHandler, &CefBrowserHandlerImp::urlChanged, this, &QCefWebView::urlChanged, Qt::QueuedConnection);
        connect(s_browserHandler, &CefBrowserHandlerImp::titleChanged, this, &QCefWebView::titleChanged, Qt::QueuedConnection);
        connect(s_browserHandler, &CefBrowserHandlerImp::loadingStateChanged, this, &QCefWebView::loadStateChanged, Qt::QueuedConnection);
		connect(s_browserHandler, &CefBrowserHandlerImp::loadStarted, this, &QCefWebView::loadStarted, Qt::QueuedConnection);
		connect(s_browserHandler, &CefBrowserHandlerImp::loadFinished, this, &QCefWebView::loadFinished, Qt::QueuedConnection);
        connect(s_browserHandler, &CefBrowserHandlerImp::webViewGotFocus, this, &QCefWebView::webViewGotFocus, Qt::QueuedConnection);
        connect(s_browserHandler, &CefBrowserHandlerImp::recvRenderMsg, this, &QCefWebView::recvRenderMsg, Qt::QueuedConnection);
    }
}

QCefWebView::~QCefWebView()
{
}

void QCefWebView::closeBrowser(QCloseEvent* event)
{
    qDebug() << "-->>" << __FUNCTION__;
    CefRefPtr<CefBrowserHandlerImp> browserHandler=GetBrowserHandler(browserHandlerIndex);
    if (browserHandler && !browserHandler->IsClosing()) {
        auto browser = browserHandler->GetBrowser();
        if (browser.get()) {
            browser->GetHost()->CloseBrowser(false);
        }
        event->ignore();
    }
    else {
        event->accept();
    }
}

void QCefWebView::loadUrl(const QUrl& url)
{
    _url = url;
    switch (_browserState) {
    case None:
        CreateBrowser(size());
        break;

    case Creating:
        _needLoad = true;
        break;

    default:
        BrowserLoadUrl(url);
    }
}

void QCefWebView::back()
{
    auto browser = GetBrowser(browserHandlerIndex);
    if (browser.get()) {
        browser->GoBack();
    }
}

void QCefWebView::forward()
{
    auto browser = GetBrowser(browserHandlerIndex);
    if (browser.get()) {
        browser->GoForward();
    }
}

void QCefWebView::refresh()
{
    auto browser = GetBrowser(browserHandlerIndex);
    if (browser.get()) {
        browser->Reload();
    }
}

void QCefWebView::stop()
{
    auto browser = GetBrowser(browserHandlerIndex);
    if (browser.get()) {
        browser->StopLoad();
    }
}

void QCefWebView::sltBrowserCreated()
{
    _browserState = Created;
    if (_needResize) {
        ResizeBrowser(size());
        _needResize = false;
    }
}

void QCefWebView::resizeEvent(QResizeEvent* event)
{
    switch (_browserState) {
    case None:
        CreateBrowser(event->size());
        break;

    case Creating:
        _needResize = true;
        break;

    default:
        ResizeBrowser(event->size());
    }
	QWidget::resizeEvent(event);
}

bool QCefWebView::CreateBrowser(const QSize& size)
{
    if (_browserState != None || size.isEmpty()) {
        return false;
    }

    if (_browserState != None) {
        return false;
    }



// 	CefWindowInfo windowInfo;
// 	CefBrowserSettings browserSettings;

// #ifdef _WIN32
// 	RECT rect;
// 	rect.left = 0;
// 	rect.top = 0;
// 	rect.right = size.width();
// 	rect.bottom = size.height();
// 	windowInfo.SetAsChild(reinterpret_cast<HWND>(this->winId()), rect);
// #endif

    CefWindowHandle hWnd = (CefWindowHandle)this->winId();

    CefWindowInfo info;
    CefBrowserSettings _settings;
    _settings.file_access_from_file_urls = STATE_ENABLED;
    _settings.universal_access_from_file_urls = STATE_ENABLED;
    _settings.javascript_access_clipboard = STATE_ENABLED;

    _settings.plugins = STATE_DISABLED;

    // Initialize window info to the defaults for a child window.

#ifdef Q_OS_WIN
    RECT rect;
    rect.left = 0;
    rect.top = 0;
    rect.right = this->width()*qApp->devicePixelRatio();
    rect.bottom = this->height()*qApp->devicePixelRatio();
    info.SetAsChild(hWnd, rect);
#endif

#if defined(_LINUX) && !defined(_MAC)
    CefRect rect;
    rect.x = 0;
    rect.y = 0;
    rect.width = 10;
    rect.height = 10;
    info.SetAsChild(hWnd, rect);
#endif

#ifdef Q_OS_MAC
    info.SetAsChild(hWnd, 0, 0, this->width(), this->height());
#endif

    QString url = _url.isEmpty() ? (DEFAULT_URL) : _url.toString();
    CefRefPtr<CefBrowserHandlerImp> browserHandler=GetBrowserHandler(browserHandlerIndex);
    CefBrowserHost::CreateBrowser(info, browserHandler.get(), CefString(url.toStdWString()), _settings, NULL);
    _browserState = Creating;

    return true;
}

void QCefWebView::SendMsgToPage(const QString &msg)
{
    CefRefPtr<CefFrame> frame =GetBrowser(browserHandlerIndex)->GetMainFrame();
    QString datastr;
    datastr="CppToJs('";
    datastr+=msg;
    datastr+="')";
    CefString code;
   // code.FromString(std::string(datastr.toLocal8Bit().data()));
    code.FromString(datastr.toStdString());

    frame->ExecuteJavaScript(code, frame->GetURL(), 0);

}

void QCefWebView::ModifyZoom(double delta)
{
	auto browser = GetBrowser(browserHandlerIndex);
	if (browser.get()) {
		//在UI线程上执行
		if (!CefCurrentlyOn(TID_UI)) {
			//CefPostTask(TID_UI, base::Bind(&ModifyZoom, this, delta));
			return;
		}
		browser->GetHost()->SetZoomLevel(browser->GetHost()->GetZoomLevel() + delta);
	}
}

double QCefWebView::getBrowserZoomLevel()
{
	double zoomLevel = 0;
	auto browser = GetBrowser(browserHandlerIndex);
	if (browser.get()) {
		zoomLevel = browser->GetHost()->GetZoomLevel();
	}
	return zoomLevel;
}


void QCefWebView::ResizeBrowser(const QSize& size)
{
    CefRefPtr<CefBrowserHandlerImp> browserHandler=GetBrowserHandler(browserHandlerIndex);
    if (browserHandler.get() && browserHandler->GetBrowser()) {
        auto windowHandle = browserHandler->GetBrowser()->GetHost()->GetWindowHandle();

        if (windowHandle) {
#ifdef _WIN32
            auto hdwp = BeginDeferWindowPos(1);
            hdwp = DeferWindowPos(hdwp, windowHandle, nullptr, 0, 0,
                qApp->devicePixelRatio()*size.width(), qApp->devicePixelRatio()*size.height(), SWP_NOZORDER);
            EndDeferWindowPos(hdwp);
#endif
        }
    }
}

bool QCefWebView::BrowserLoadUrl(const QUrl& url)
{
    if (!url.isEmpty() && GetBrowser(browserHandlerIndex)) {
        CefString cefurl(url.toString().toStdWString());
        GetBrowser(browserHandlerIndex)->GetMainFrame()->LoadURL(cefurl);
        return true;
    }
    return false;
}
