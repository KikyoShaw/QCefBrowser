

//#pragma comment(lib,"libcef")
//#ifdef NDEBUG
//#pragma comment(lib,"libcef_dll_wrapper")
//#else
//#pragma comment(lib,"libcef_dll_wrapper_d")
//#endif

#include "CefBrowser.h"
#include "CefAppImp.h"
#include "MyRenderProcessHandler.h"

int QCefProcessStart()
{
	CefEnableHighDPISupport();
	// Provide CEF with command-line arguments.
	CefMainArgs main_args;

	void* sandbox_info = NULL;

	// CEF applications have multiple sub-processes (render, plugin, GPU, etc)
	// that share the same executable. This function checks the command-line and,
	// if this is a sub-process, executes the appropriate logic.
    MyRenderProcessHandler* app_r=new MyRenderProcessHandler();
//    int exit_code = CefExecuteProcess(main_args, app_r, sandbox_info);
//    if (exit_code >= 0) {
//        // The sub-process has completed so return here.
//        return exit_code;
//    }
	//
	// Specify CEF global settings here.
	CefSettings settings;
	settings.no_sandbox = true; //关闭沙盒 
#ifdef Q_OS_WIN
	settings.multi_threaded_message_loop = true;  //多线程消息循环
#endif

	//settings.windowless_rendering_enabled = true; //开启离屏渲染
	// CefAppImp implements application-level callbacks for the browser process.
	// It will create the first browser instance in OnContextInitialized() after
	// CEF has initialized.
    //CefRefPtr<CefAppImp> app(new CefAppImp);
	// Initialize CEF.
    CefInitialize(main_args, settings, app_r, sandbox_info);
    return 0;
}

void QCefMessageLoop()
{
#ifndef Q_OS_WIN
	CefRunMessageLoop();
#endif
}


void QCefProcessExit()
{
	// Shut down CEF.
	CefShutdown();
}

