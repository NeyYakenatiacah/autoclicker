#ifndef HP_WIDGET_H
#define HP_WIDGET_H

#include <QWidget>

QT_BEGIN_NAMESPACE
class QPushButton;
class QThread;
QT_END_NAMESPACE

class HPClicker;
class HPWidget : public QWidget
{
    Q_OBJECT
public:
    explicit HPWidget(QWidget *parent = nullptr);
    virtual ~HPWidget();

signals:

private:
    HPClicker *m_clicker{nullptr};
    QThread* m_clickerThread{nullptr};

    QPushButton* m_startButton;
    QPushButton* m_stopButton;

    bool m_playSound{true};
};

#endif // HP_WIDGET_H
