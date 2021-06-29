#include "MyRenderProcessHandler.h"
#include <Windows.h>
#include <tchar.h>
#include "myv8handler.h"

MyRenderProcessHandler::MyRenderProcessHandler()
{

}
void MyRenderProcessHandler::OnContextCreated(CefRefPtr<CefBrowser> browser,
    CefRefPtr<CefFrame> frame,
    CefRefPtr<CefV8Context> context)
{

    // Retrieve the context's window object.
     CefRefPtr<CefV8Value> object = context->GetGlobal();

     // Create an instance of my CefV8Handler object.
     CefRefPtr<MyV8Handler> handler = new MyV8Handler();
     // Create the "myfunc" function.
     CefRefPtr<CefV8Value> func = CefV8Value::CreateFunction("JsToCpp", handler);

     // Add the "myfunc" function to the "window" object.
     object->SetValue("ReceivedMsgFromJS", func, V8_PROPERTY_ATTRIBUTE_NONE);


}
