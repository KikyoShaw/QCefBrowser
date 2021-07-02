#ifndef EVENTS_H
#define EVENTS_H

#include <QEvent>
#include <QImage>

class UpdateEvent : public QEvent
{
public:
    const static Type eventType = static_cast<Type>(QEvent::User+1);
    explicit UpdateEvent(const QImage &image);
    QImage m_image;
};

#endif // EVENTS_H
