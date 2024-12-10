#include "CefOsrHandlerImp.h"

#include <sstream>
#include <string>
#include <QDebug>
#include <QDateTime>
#include <QBuffer>
#include <QPixmap>
#include <QtWin>

#include <QCoreApplication>

#include "include/base/cef_bind.h"
#include "include/cef_app.h"
#include "include/views/cef_browser_view.h"
#include "include/views/cef_window.h"
#include "include/wrapper/cef_closure_task.h"
#include "include/wrapper/cef_helpers.h"
#include "events.h"

namespace {

    CefOsrHandlerImp* g_instance = NULL;

}  // namespace

CefOsrHandlerImp::CefOsrHandlerImp(bool use_views)
    : use_views_(use_views), is_closing_(false) {
    DCHECK(!g_instance);
    g_instance = this;

    m_bMouseCursorChangeDisabled = false;

    m_receiver = nullptr;
}

CefOsrHandlerImp::~CefOsrHandlerImp() {
    g_instance = nullptr;
}

void CefOsrHandlerImp::setWinHandle(HWND hwnd)
{
    m_hwnd = hwnd;
}

void CefOsrHandlerImp::setReceiver(QObject* receiver)
{
    m_receiver = receiver;
}

// static
CefOsrHandlerImp* CefOsrHandlerImp::GetInstance() {
    return g_instance;
}

void CefOsrHandlerImp::OnAfterCreated(CefRefPtr<CefBrowser> browser) {
    CEF_REQUIRE_UI_THREAD()

        if (m_bMouseCursorChangeDisabled)
            browser->GetHost()->SetMouseCursorChangeDisabled(true);
        else
            browser->GetHost()->SetMouseCursorChangeDisabled(false);

    // Add to the list of existing browsers.
    browser_list_.push_back(browser);
}

bool CefOsrHandlerImp::DoClose(CefRefPtr<CefBrowser> browser) {
    CEF_REQUIRE_UI_THREAD()

        // Closing the main window requires special handling. See the DoClose()
        // documentation in the CEF header for a detailed destription of this
        // process.
        if (browser_list_.size() == 1) {
            // Set a flag to indicate that the window close should be allowed.
            is_closing_ = true;
        }

    // Allow the close. For windowed browsers this will result in the OS close
    // event being sent.
    return false;
}

void CefOsrHandlerImp::OnBeforeClose(CefRefPtr<CefBrowser> browser) {
    CEF_REQUIRE_UI_THREAD()

        // Remove from the list of existing browsers.
        BrowserList::iterator bit = browser_list_.begin();
    for (; bit != browser_list_.end(); ++bit) {
        if ((*bit)->IsSame(browser)) {
            browser_list_.erase(bit);
            break;
        }
    }

    if (browser_list_.empty()) {
        // All browser windows have closed. Quit the application message loop.
        CefQuitMessageLoop();
    }
}

void CefOsrHandlerImp::OnLoadError(CefRefPtr<CefBrowser> browser,
    CefRefPtr<CefFrame> frame,
    ErrorCode errorCode,
    const CefString& errorText,
    const CefString& failedUrl) {
    CEF_REQUIRE_UI_THREAD()

        qDebug() << "errorCode: " << errorCode;

    // Don't display an error for downloaded files.
    if (errorCode == ERR_ABORTED)
        return;

    // Display a load error message.
    std::stringstream ss;
    ss << "<html><body bgcolor=\"white\">"
        "<h2>Failed to load URL "
        << std::string(failedUrl) << " with error " << std::string(errorText)
        << " (" << errorCode << ").</h2></body></html>";
    frame->LoadString(ss.str(), failedUrl);
}

void CefOsrHandlerImp::CloseAllBrowsers(bool force_close) {
    if (!CefCurrentlyOn(TID_UI)) {
        // Execute on the UI thread.
        CefPostTask(TID_UI, base::Bind(&CefOsrHandlerImp::CloseAllBrowsers, this,
            force_close));
        return;
    }

    if (browser_list_.empty())
        return;

    BrowserList::const_iterator it = browser_list_.begin();
    for (; it != browser_list_.end(); ++it)
        (*it)->GetHost()->CloseBrowser(force_close);
}

std::list<CefRefPtr<CefBrowser> > CefOsrHandlerImp::getCefBrowerList()
{
    return browser_list_;
}

bool CefOsrHandlerImp::GetViewRect(CefRefPtr<CefBrowser> browser, CefRect& rect)
{
    RECT clientRect;
    if (!::GetClientRect(m_hwnd, &clientRect))
        return false;

    rect.x = rect.y = 0;
    rect.width = clientRect.right;
    rect.height = clientRect.bottom;

    return true;
}

void CefOsrHandlerImp::OnPaint(CefRefPtr<CefBrowser> browser,
    CefRenderHandler::PaintElementType type,
    const CefRenderHandler::RectList& dirtyRects,
    const void* buffer,
    int width,
    int height)
{
    HBITMAP bitmap = CreateBitmap(width, height, 1, 32, buffer);
    QImage image = QtWin::imageFromHBITMAP(bitmap);

    if (image.isNull())
    {
        qDebug() << "image is null";
        return;
    }

    //以下为测试代码，将图片写到文件中去
    //QString fileName = QString("D:/1/%1.png").arg(QDateTime::currentMSecsSinceEpoch());
    //image.save(fileName, "PNG");

    UpdateEvent* updateEvent = new UpdateEvent(image);
    QCoreApplication::postEvent(m_receiver, updateEvent);
}

void CefOsrHandlerImp::OnCursorChange(CefRefPtr<CefBrowser> browser, CefCursorHandle cursor, CefRenderHandler::CursorType type, const CefCursorInfo& custom_cursor_info)
{
    ChangeCursorEvent* changeCursorEvent = new ChangeCursorEvent(type);
    QCoreApplication::postEvent(m_receiver, changeCursorEvent);

    //    ::SetCursor(cursor);
}

bool CefOsrHandlerImp::GetScreenPoint(CefRefPtr<CefBrowser> browser, int viewX, int viewY, int& screenX, int& screenY)
{
    RECT clientRect;
    if (!::GetWindowRect(m_hwnd, &clientRect))
        return false;

    screenX = clientRect.left + viewX;
    screenY = clientRect.top + viewY;
    return true;
}