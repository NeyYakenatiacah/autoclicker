#ifndef QCOLOREDIT_H
#define QCOLOREDIT_H

#include <QPushButton>

class QColorEdit : public QPushButton
{
    Q_OBJECT
public:
    explicit QColorEdit(const QString& text, QWidget *parent = nullptr);

private:
    void onClicked();

signals:
    void colorChanged(const QColor&);

private:
    QString m_text;
};

#endif // QCOLOREDIT_H
