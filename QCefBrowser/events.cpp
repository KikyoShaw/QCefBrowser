#include "events.h"

UpdateEvent::UpdateEvent(const QImage &image) :QEvent(eventType)
{
    m_image = image;
}

ChangeCursorEvent::ChangeCursorEvent(cef_cursor_type_t shape_) :QEvent(eventType)
{
    shape = shape_;
}

ReloadBrowerEvent::ReloadBrowerEvent() :QEvent(eventType)
{
    //TODO 目前不需要啥操作，有业务自己写就行
}
