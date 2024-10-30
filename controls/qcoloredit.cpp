#include "qcoloredit.h"
#include <QColorDialog>

QColorEdit::QColorEdit(const QString &text, QWidget *parent)
    : QPushButton(text, parent)
    , m_text(text)
{
    QObject::connect(this, &QColorEdit::clicked, this, &QColorEdit::onClicked);
}

void QColorEdit::onClicked()
{
    QColor selectedColor = QColorDialog::getColor(Qt::white, this, "Choose Color");
    setText(m_text + ": " + QString::number(selectedColor.rgb()));
    emit colorChanged(selectedColor);
}
