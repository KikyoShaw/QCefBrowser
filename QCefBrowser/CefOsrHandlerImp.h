#ifndef CEFOSRHANDLERIMP_H
#define CEFOSRHANDLERIMP_H

#include "include/cef_client.h"
#include <QMutex>

#include <functional>
#include <list>
#include <QEvent>
#include <QImage>
#include <QObject>
#include <WinUser.h>

class CefOsrHandlerImp : public CefClient,
    public CefLifeSpanHandler,
    public CefLoadHandler,
    public CefRenderHandler
{
public:
    typedef std::function<void(CefRefPtr<CefBrowser>)> BrowserAction;

    CefOsrHandlerImp();
    ~CefOsrHandlerImp() OVERRIDE;

    void setWinHandle(HWND hwnd);
    void setReceiver(QObject* receiver);
    void RunBrowserAction(const BrowserAction& action);
    void CloseAllBrowsers(bool force_close);

    CefRefPtr<CefLifeSpanHandler> GetLifeSpanHandler() OVERRIDE { return this; }
    CefRefPtr<CefLoadHandler> GetLoadHandler() OVERRIDE { return this; }
    CefRefPtr<CefRenderHandler> GetRenderHandler() OVERRIDE { return this; }

    void OnAfterCreated(CefRefPtr<CefBrowser> browser) OVERRIDE;
    bool DoClose(CefRefPtr<CefBrowser> browser) OVERRIDE;
    void OnBeforeClose(CefRefPtr<CefBrowser> browser) OVERRIDE;
    void OnLoadError(CefRefPtr<CefBrowser> browser,
        CefRefPtr<CefFrame> frame,
        ErrorCode errorCode,
        const CefString& errorText,
        const CefString& failedUrl) OVERRIDE;

    bool GetViewRect(CefRefPtr<CefBrowser> browser, CefRect& rect) OVERRIDE;
    void OnPaint(CefRefPtr<CefBrowser> browser,
        PaintElementType type,
        const RectList& dirtyRects,
        const void* buffer,
        int width,
        int height) OVERRIDE;
    void OnCursorChange(CefRefPtr<CefBrowser> browser,
        CefCursorHandle cursor,
        CursorType type,
        const CefCursorInfo& custom_cursor_info) OVERRIDE;
    bool GetScreenPoint(CefRefPtr<CefBrowser> browser,
        int viewX, int viewY, int& screenX, int& screenY) OVERRIDE;

private:
    void postEvent(QEvent* event);

    // Browser state is accessed only on the CEF UI thread.
    std::list<CefRefPtr<CefBrowser>> browser_list_;
    bool m_closeRequested;
    HWND m_hwnd;

    // Detaching and posting share a lock so the receiver cannot be deleted mid-post.
    QMutex m_receiverLock;
    QObject* m_receiver;

    IMPLEMENT_REFCOUNTING(CefOsrHandlerImp);
};

#endif // CEFOSRHANDLERIMP_H
