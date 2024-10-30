#ifndef KEY_SEQUENCE_WIDGET_H
#define KEY_SEQUENCE_WIDGET_H

#include <QWidget>
#include "../system_api.h"

QT_BEGIN_NAMESPACE
class QVBoxLayout;
QT_END_NAMESPACE

class KeySelectorWidget;
class KeySequenceWidget : public QWidget
{
    Q_OBJECT
public:
    explicit KeySequenceWidget(QWidget *parent = nullptr);

    SystemAPI::KeySequence asSequence() const;

private:
    void addItem();
    void removeItem(KeySelectorWidget* widget);

private:
    QList<KeySelectorWidget*> m_widgets;
    QVBoxLayout* m_scrollLayout;
};

#endif // KEY_SEQUENCE_WIDGET_H
