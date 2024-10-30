#include "qpointedit.h"

#include <QSpinBox>
#include <QHBoxLayout>
#include <QLabel>
#include <QPoint>

QPointEdit::QPointEdit(QWidget *parent)
    : QWidget{parent}
{
    // Создаем QSpinBox для x и y
    m_xSpinBox = new QSpinBox(this);
    m_ySpinBox = new QSpinBox(this);

    // Устанавливаем диапазон значений, например, от -5000 до 5000
    m_xSpinBox->setRange(-5000, 5000);
    m_ySpinBox->setRange(-5000, 5000);

    // Создаем разметку для виджета
    QHBoxLayout *layout = new QHBoxLayout(this);

    // Добавляем метки и спинбоксы для x и y
    layout->addWidget(new QLabel("X:", this));
    layout->addWidget(m_xSpinBox);
    layout->addWidget(new QLabel("Y:", this));
    layout->addWidget(m_ySpinBox);

    // Настраиваем сигналы на изменение значений
    const auto onChanged = [this]()
    {
        emit pointChanged(point());
    };

    connect(m_xSpinBox, QOverload<int>::of(&QSpinBox::valueChanged), this, onChanged);
    connect(m_ySpinBox, QOverload<int>::of(&QSpinBox::valueChanged), this, onChanged);
}

QPoint QPointEdit::point() const
{
    return QPoint(m_xSpinBox->value(), m_ySpinBox->value());
}

void QPointEdit::setPoint(const QPoint &point)
{
    m_xSpinBox->setValue(point.x());
    m_ySpinBox->setValue(point.y());
}
