#ifndef HP_CLICKER_H
#define HP_CLICKER_H

#include <QObject>
#include "../system_api.h"

QT_BEGIN_NAMESPACE
class QTimer;
QT_END_NAMESPACE

class HPClicker : public QObject
{
    Q_OBJECT
public:
    explicit HPClicker(QObject *parent = nullptr);

    void start();
    void stop();

    void setInterval(int milliseconds);

    void setCastCancelKey(SystemAPI::KeyCode code);
    void setHocusPocusKey(SystemAPI::KeyCode code);
    void setSightKey(SystemAPI::KeyCode code);

    void setWindowDescriptor(HWND hwnd);

private:
    void onTimeout();

    void generateCheckPoints(const QSize &size);
    bool compareWithRef(const QImage& capture);

signals:
    void stopped();

private:
    SystemAPI::KeyCode m_castCancel{SystemAPI::KeyCode::F1};
    SystemAPI::KeyCode m_hocusPocus{SystemAPI::KeyCode::F1};
    SystemAPI::KeyCode m_sight{SystemAPI::KeyCode::F1};

    QVector<QPoint> m_checkPoints;
    QVector<QPoint> m_excludedPoints;

    QColor m_referenceColor{49, 255, 49};

    HWND m_hwnd{nullptr};

    QTimer* m_timer{nullptr};

    uint64_t m_timestamp{0u};
    uint64_t m_lastSightUse{0u};

    int m_pauseFrames{0u};
};

#endif // HP_CLICKER_H
