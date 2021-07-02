#include "events.h"

UpdateEvent::UpdateEvent(const QImage &image) :QEvent(eventType)
{
    m_image = image;
}
