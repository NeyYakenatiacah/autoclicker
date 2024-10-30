#ifndef AUTO_CLICKER_H
#define AUTO_CLICKER_H

#include <QObject>
#include <qwindowdefs_win.h>

#define CLICKER_DEBUG
#ifdef CLICKER_DEBUG
#include <QDebug>
#endif

typedef unsigned __int64 WPARAM;

QT_BEGIN_NAMESPACE
class QTimer;
QT_END_NAMESPACE

class AutoClicker : public QObject
{
    Q_OBJECT
public:
    using KeySequence = QVector<QChar>;

public:
    explicit AutoClicker(QObject *parent = nullptr);

    void start();
    void stop();

    std::chrono::milliseconds interval() const;
    void setInterval(std::chrono::milliseconds val);

    const KeySequence& keySequence() const;
    void setKeySequence(const KeySequence& seq);

signals:
    void started();
    void stopped();

private:
    void onTimeout();

private:
    QVector<QChar> m_keySequence;

    HWND m_hwnd{nullptr};

    QTimer* m_timer;

    uint64_t m_timestamp{0u};
};

#endif // AUTO_CLICKER_H

