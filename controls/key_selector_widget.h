#ifndef KEY_SELECTOR_WIDGET_H
#define KEY_SELECTOR_WIDGET_H

#include <QWidget>
#include "../system_api.h"

QT_BEGIN_NAMESPACE
class QComboBox;
QT_END_NAMESPACE

class KeySelectorWidget : public QWidget
{
    Q_OBJECT
public:
    explicit KeySelectorWidget(QWidget *parent = nullptr, bool removable = false);

    SystemAPI::KeyCode getKeyCode() const;

signals:
    void changed(SystemAPI::KeyCode);
    void deleted(KeySelectorWidget*);

private:
    QComboBox *m_comboBox;
};

#endif // KEY_SELECTOR_WIDGET_H
