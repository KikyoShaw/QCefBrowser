#ifndef CEF3_CLIENT_APP_RENDERER_H
#define CEF3_CLIENT_APP_RENDERER_H
#include "include/cef_app.h"
#include "include/cef_client.h"
#include <QObject>
class MyRenderProcessHandler :public CefApp,
    public CefRenderProcessHandler
{

public:
    MyRenderProcessHandler();
    CefRefPtr<CefRenderProcessHandler> GetRenderProcessHandler() OVERRIDE
    {
        return this;
    }

    void OnContextCreated(
        CefRefPtr<CefBrowser> browser,
        CefRefPtr<CefFrame> frame,
        CefRefPtr<CefV8Context> context);

private:

    IMPLEMENT_REFCOUNTING(MyRenderProcessHandler);
};
#endif
