#ifndef QPOINTEDIT_H
#define QPOINTEDIT_H

#include <QWidget>

QT_BEGIN_NAMESPACE
class QSpinBox;
QT_END_NAMESPACE

class QPointEdit : public QWidget
{
    Q_OBJECT

public:
    QPointEdit(QWidget *parent = nullptr);

    QPoint point() const;

    void setPoint(const QPoint &point);

signals:
    void pointChanged(const QPoint &point);

private:
    QSpinBox *m_xSpinBox;
    QSpinBox *m_ySpinBox;
};

#endif // QPOINTEDIT_H
