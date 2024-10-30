#include "hp_clicker.h"

#include <QTimer>
#include <QDebug>
#include <QDir>

#ifdef CLICKER_DEBUD
#include "../logger.h"
#endif

/* 1920*1080
 * 949 118
 * 956 118
 * 963 118
 * 970 118
 */
/* 1024*768
 * 501 88
 * 508 88
 * 515 88
 * 522 88
 */

namespace
{
void log_debug(int timestamp, const QString& str)
{
#ifdef CLICKER_DEBUG
    Logger::instance() << "[" << timestamp << "] " << str;
    Logger::instance().endLine();
#endif
}
}

HPClicker::HPClicker(QObject *parent)
    : QObject{parent}
    , m_timer{new QTimer{this}}
{
    m_timer->setInterval(500);
    QObject::connect(m_timer, &QTimer::timeout, this, &HPClicker::onTimeout);
}

void HPClicker::start()
{
    if(m_hwnd)
    {
        m_timer->start();
    }
}

void HPClicker::stop()
{
    m_timer->stop();
    m_timestamp = 0u;
    m_lastSightUse = 0u;
}

void HPClicker::setInterval(int milliseconds)
{
    m_timer->setInterval(milliseconds);
}

void HPClicker::setCastCancelKey(SystemAPI::KeyCode code)
{
    m_castCancel = code;
}

void HPClicker::setHocusPocusKey(SystemAPI::KeyCode code)
{
    m_hocusPocus = code;
}

void HPClicker::setSightKey(SystemAPI::KeyCode code)
{
    m_sight = code;
}

void HPClicker::setWindowDescriptor(HWND hwnd)
{
    m_hwnd = hwnd;

    auto capture = SystemAPI::captureWindow(hwnd);
    generateCheckPoints(capture.size());

    {
        auto changePixelsColor = [](QImage& img, const QVector<QPoint>& points, const QColor& color)
        {
            for(const auto& p : points)
            {
                img.setPixelColor(p, color);
            }
        };

        changePixelsColor(capture, m_checkPoints, QColor(Qt::cyan));
        changePixelsColor(capture, m_excludedPoints, QColor(Qt::red));
        capture.save("debug.bmp", "BMP");
    }
}

void HPClicker::onTimeout()
{
    if(m_pauseFrames-- > 0)
    {
        return;
    }

    // log_debug(m_timestamp, "frame event");
    QImage capture = SystemAPI::captureWindow(m_hwnd);
    const auto& size = capture.size();

    // log_debug(m_timestamp, QString("Width: %1, Height: %2").arg(size.width()).arg(size.height()));

    if(compareWithRef(capture))
    {
        // log_debug(m_timestamp, "skill found");

        if(m_pauseFrames <= 0)
        {
            emit stopped();
            m_pauseFrames = 10;
        }
    }
    else
    {
        // log_debug(m_timestamp, "skill not found -> Press Key []");

        if((!m_lastSightUse || (m_timestamp - m_lastSightUse) >= (10000 / m_timer->interval() - 1)) && m_timestamp % 2 == 0)
        {
            m_lastSightUse = m_timestamp;
            if(!m_lastSightUse)
            {
                m_timestamp = 2u;
                m_lastSightUse = 2u;
            }

            // log_debug(m_timestamp, "Press Key [Sight]");
            SystemAPI::pushKeyEvent(m_hwnd, m_sight);
            return;
        }

        SystemAPI::pushKeyEvent(m_hwnd, m_timestamp % 2 == 0 ? m_hocusPocus : m_castCancel);
    }

    ++m_timestamp;
}

void HPClicker::generateCheckPoints(const QSize &size)
{
    m_checkPoints.clear();
    m_checkPoints.resize(4);

    m_excludedPoints.clear();
    m_excludedPoints.resize(4);

    QPoint refStartPoint;

    if(size == QSize(1920, 1080))
    {
        refStartPoint = QPoint{949, 118};
    }
    else if(size == QSize{1024, 768})
    {
        refStartPoint = QPoint{501, 88};
    }
    else
    {
        return;
    }

    int i = 0;
    std::generate(m_checkPoints.begin(), m_checkPoints.end(), [&]()
        {
            return QPoint{refStartPoint.x() + i++ * 7, refStartPoint.y()};
        });

    i = 0;
    std::generate(m_excludedPoints.begin(), m_excludedPoints.end(), [&]()
        {
            return QPoint{refStartPoint.x() + i++ * 7, refStartPoint.y() - 1};
        });
}

bool HPClicker::compareWithRef(const QImage &capture)
{
    bool checkRef = std::all_of(m_checkPoints.begin(), m_checkPoints.end(), [&](const QPoint& pt)
        {
            return capture.pixelColor(pt) == m_referenceColor;
        });

    bool checkExcl = std::all_of(m_excludedPoints.begin(), m_excludedPoints.end(), [&](const QPoint& pt)
        {
            return capture.pixelColor(pt) != m_referenceColor;
        });

    return checkRef && checkExcl;
}
