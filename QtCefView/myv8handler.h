#ifndef MYV8HANDLER_H
#define MYV8HANDLER_H
#include <QObject>
#include "include/cef_v8.h"
class MyV8Handler :public CefV8Handler {

public:
  MyV8Handler();
  virtual bool Execute(const CefString& name,
                       CefRefPtr<CefV8Value> object,
                       const CefV8ValueList& arguments,
                       CefRefPtr<CefV8Value>& retval,
                       CefString& exception) OVERRIDE;


  void SendMsgToBrowser(CefString str);
public:

  // Provide the reference counting implementation for this class.
  IMPLEMENT_REFCOUNTING(MyV8Handler);
};
#endif // MYV8HANDLER_H
