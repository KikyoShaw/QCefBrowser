#pragma once
#include <QObject>
#include <list>

#pragma warning(disable:4100)
#include "include/cef_client.h"

class CefBrowserHandlerImp: public QObject,
	public CefClient,
	public CefDisplayHandler,
	public CefLifeSpanHandler,
	public CefFocusHandler,
	public CefLoadHandler,
	public CefRenderHandler  //¿Î∆¡‰÷»æ
{
	Q_OBJECT

public:
	CefBrowserHandlerImp();

	void setWinHandle(HWND hwnd);
	void setReceiver(QObject* receiver);

public:
	// CefClient methods:
	virtual CefRefPtr<CefDisplayHandler> GetDisplayHandler() OVERRIDE { return this;}
	virtual CefRefPtr<CefLifeSpanHandler> GetLifeSpanHandler() OVERRIDE { return this;}
	virtual CefRefPtr<CefLoadHandler> GetLoadHandler() OVERRIDE { return this; }
	virtual CefRefPtr<CefFocusHandler> GetFocusHandler() OVERRIDE { return this; }
	virtual CefRefPtr<CefRenderHandler> GetRenderHandler() OVERRIDE { return this; }

	// CefDisplayHandler methods:
	virtual void OnTitleChange(CefRefPtr<CefBrowser> browser, const CefString& title) OVERRIDE;
	virtual void OnAddressChange(CefRefPtr<CefBrowser> browser, CefRefPtr<CefFrame> frame, const CefString& url) OVERRIDE;

	// CefLifeSpanHandler methods:
	virtual void OnAfterCreated(CefRefPtr<CefBrowser> browser) OVERRIDE;
	virtual bool DoClose(CefRefPtr<CefBrowser> browser) OVERRIDE;
	virtual void OnBeforeClose(CefRefPtr<CefBrowser> browser) OVERRIDE;
	virtual bool OnBeforePopup(CefRefPtr<CefBrowser> browser,
		CefRefPtr<CefFrame> frame,
		const CefString& target_url,
		const CefString& target_frame_name,
		WindowOpenDisposition target_disposition,
		bool user_gesture,
		const CefPopupFeatures& popupFeatures,
		CefWindowInfo& windowInfo,
		CefRefPtr<CefClient>& client,
		CefBrowserSettings& settings,
		bool* no_javascript_access)OVERRIDE;

	// CefLoadHandler methods:
	virtual void OnLoadError(CefRefPtr<CefBrowser> browser,
		CefRefPtr<CefFrame> frame,
		ErrorCode errorCode,
		const CefString& errorText,
		const CefString& failedUrl) OVERRIDE;
	virtual void OnLoadingStateChange(CefRefPtr<CefBrowser> browser,bool isLoading,bool canGoBack,bool canGoForward) OVERRIDE;
	virtual void OnLoadStart(CefRefPtr<CefBrowser> browser, CefRefPtr<CefFrame> frame, TransitionType transition_type) OVERRIDE;
	virtual void OnLoadEnd(CefRefPtr<CefBrowser> browser, CefRefPtr<CefFrame> frame, int httpStatusCode) OVERRIDE;

	// CefFocusHandler methods:
	virtual void OnGotFocus(CefRefPtr<CefBrowser> browser) OVERRIDE;
    virtual bool OnProcessMessageReceived(CefRefPtr<CefBrowser> browser, CefProcessId source_process, CefRefPtr<CefProcessMessage> message);

	// CefRenderHandler methods:
	virtual bool GetViewRect(CefRefPtr<CefBrowser> browser, CefRect& rect) OVERRIDE;
	virtual void OnPaint(CefRefPtr<CefBrowser> browser,
		PaintElementType type,
		const RectList& dirtyRects,
		const void* buffer,
		int width,
		int height) OVERRIDE;

signals:
	void browserCreated();
	void urlChanged(const QString& url);
	void titleChanged(const QString& title);
	void loadingStateChanged(bool isLoading, bool canGoBack, bool canGoForward);
	void webViewGotFocus();
    void recvRenderMsg(const QString& msg);
	void loadStarted();
	void loadFinished(bool loadSuccess);

public:
	// Request that all existing browser windows close.
	void CloseAllBrowsers(bool forceClose);
	bool IsClosing() const { return _isClosing; }
	CefRefPtr<CefBrowser> GetBrowser(){	return _browser; }
	std::list<CefRefPtr<CefBrowser>> getCefBrowerList() { return _browserList; }

private:
	// List of existing browser windows. Only accessed on the CEF UI thread.
	typedef std::list<CefRefPtr<CefBrowser>> BrowserList;
	BrowserList _browserList;

	bool _isClosing;
	// child browser window
	CefRefPtr<CefBrowser> _browser;
	// The number of currently existing browser windows. The application will exit
	// when the number reaches 0.
	static int _browserCount;
	// The child browser id
	int _browserId;
	// The Qt hwnd
	HWND m_hwnd;
	// osr image
	QObject* m_receiver;

private:
	// Include the default reference counting implementation.
	IMPLEMENT_REFCOUNTING(CefBrowserHandlerImp);
};
