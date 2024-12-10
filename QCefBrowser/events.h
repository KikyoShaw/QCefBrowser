#ifndef EVENTS_H
#define EVENTS_H

#include <QEvent>
#include <QImage>
#include <internal/cef_types.h>

class UpdateEvent : public QEvent
{
public:
    const static Type eventType = static_cast<Type>(QEvent::User+1);
    explicit UpdateEvent(const QImage &image);
    QImage m_image;
};

class ChangeCursorEvent : public QEvent
{
public:
    const static Type eventType = static_cast<Type>(QEvent::User + 2);
    explicit ChangeCursorEvent(cef_cursor_type_t shape_);
    cef_cursor_type_t shape;
};

class ReloadBrowerEvent : public QEvent
{
public:
    const static Type eventType = static_cast<Type>(QEvent::User + 3);
    explicit ReloadBrowerEvent();
};

#endif // EVENTS_H
