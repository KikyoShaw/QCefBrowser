#pragma once

#pragma warning(disable:4100)
#include "include/cef_app.h"


class CefAppImp:public CefApp,
    public CefBrowserProcessHandler//,
    //public CefRenderProcessHandler
{
public:
	CefAppImp();

public:
    // CefApp methods:
    virtual CefRefPtr<CefBrowserProcessHandler> GetBrowserProcessHandler() OVERRIDE {
        return this;
    }

	// CefBrowserProcessHandler methods:
    virtual void OnContextInitialized() OVERRIDE;


private:
	// Include the default reference counting implementation.
	IMPLEMENT_REFCOUNTING(CefAppImp);
};

