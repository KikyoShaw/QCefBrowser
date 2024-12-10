

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
	//CefEnableHighDPISupport();
	// Provide CEF with command-line arguments.
	HINSTANCE hInstance = static_cast<HINSTANCE>(GetModuleHandle(nullptr));
	CefMainArgs mainArgs(hInstance);

	void* sandbox_info = NULL;

	// CEF applications have multiple sub-processes (render, plugin, GPU, etc)
	// that share the same executable. This function checks the command-line and,
	// if this is a sub-process, executes the appropriate logic.
	CefRefPtr<MyRenderProcessHandler> app_r(new MyRenderProcessHandler);
    int exit_code_app_r = CefExecuteProcess(mainArgs, app_r.get(), sandbox_info);
    if (exit_code_app_r >= 0) {
        // The sub-process has completed so return here.
        return exit_code_app_r;
    }
	//
	// Specify CEF global settings here.
	CefSettings settings;
	settings.no_sandbox = false; //关闭沙盒 

#ifdef Q_OS_WIN
	settings.multi_threaded_message_loop = true;  //多线程消息循环
#endif

	settings.windowless_rendering_enabled = true; //开启离屏渲染
	// CefAppImp implements application-level callbacks for the browser process.
	// It will create the first browser instance in OnContextInitialized() after
	// CEF has initialized.
	CefRefPtr<CefAppImp> app(new CefAppImp);
	int exit_code_app = CefExecuteProcess(mainArgs, app.get(), nullptr);
	if (exit_code_app >= 0) {
		return exit_code_app;
	}
	// Initialize CEF.
    CefInitialize(mainArgs, settings, app_r, sandbox_info);
	//CefInitialize(mainArgs, settings, app, sandbox_info);
    return 0;
}

int QCefProcessStartOsr() 
{
	HINSTANCE hInstance = static_cast<HINSTANCE>(GetModuleHandle(nullptr));

	CefMainArgs mainArgs(hInstance);
	CefRefPtr<CefAppImp> app(new CefAppImp); //CefApp实现，用于处理进程相关的回调。

	int exit_code = CefExecuteProcess(mainArgs, app.get(), nullptr);
	if (exit_code >= 0) {
		return exit_code;
	}

	CefSettings settings;
	//std::string cache_path = AppGetWorkingDirectory().toStdString() + "/.cache";//缓存地址
	// CefString(&settings.cache_path) = CefString(cache_path);
	settings.multi_threaded_message_loop = true;//多线程消息循环
	settings.log_severity = LOGSEVERITY_DISABLE;//日志
	settings.windowless_rendering_enabled = true;
	settings.no_sandbox = false;//沙盒
	CefInitialize(mainArgs, settings, app, nullptr);

	return -1;
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

