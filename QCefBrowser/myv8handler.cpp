#include "myv8handler.h"
#include "QDebug"
#include "QMessageBox"
#include "WinUser.h"

MyV8Handler::MyV8Handler()
{

}

bool MyV8Handler::Execute(const CefString &name, CefRefPtr<CefV8Value> object, const CefV8ValueList &arguments, CefRefPtr<CefV8Value> &retval, CefString &exception)
{
    if (name == "JsToCpp") {
        if (arguments.size() == 1) {
            CefString strfromweb = arguments.at(0)->GetStringValue();
            std::string stdstr = strfromweb.ToString();
            //QString str = QString::fromLocal8Bit(strfromweb.ToString().c_str()); //中文会乱码
			QString str = QString::fromStdWString(strfromweb.c_str());
			SendMsgToBrowser(strfromweb);
            QMessageBox::information(NULL, QStringLiteral("收到web页面消息") ,str);
            //::SendMessage((HWND)pMainWebForm->winId(), 501, (WPARAM)&stdstr, NULL);
            retval = CefV8Value::CreateString(strfromweb);

        }
        else {
            retval = CefV8Value::CreateInt(0);
        }
        return true;
    }

    // Function does not exist.
    return false;
}

void MyV8Handler::SendMsgToBrowser(CefString str)
{
    CefRefPtr<CefProcessMessage> msg = CefProcessMessage::Create("vvMsg");

    // Retrieve the argument list object.
    CefRefPtr<CefListValue> args = msg->GetArgumentList();

    // Populate the argument values.
    args->SetSize(1);
    args->SetString(0, str);

    // Send the process message to the browser process.
    CefV8Context::GetCurrentContext()->GetBrowser()->SendProcessMessage(PID_BROWSER, msg);
}

