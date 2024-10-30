#include "key_selector_widget.h"

#include <QComboBox>
#include <QHBoxLayout>
#include <QPushButton>

namespace
{
void fillKeys(QComboBox* comboBox)
{
    QMetaEnum metaEnum = QMetaEnum::fromType<SystemAPI::KeyCode>();

    for(int idx = 0; idx < metaEnum.keyCount(); ++idx)
    {
        const auto name = QString{metaEnum.key(idx)};
        const auto code = metaEnum.value(idx);

        comboBox->addItem(name, QVariant::fromValue(code));
    }
}
}

KeySelectorWidget::KeySelectorWidget(QWidget *parent, bool removable)
    : QWidget{parent}
    , m_comboBox{new QComboBox}
{
    fillKeys(m_comboBox);

    auto* layout = new QHBoxLayout{this};
    layout->addWidget(m_comboBox, 9);

    QObject::connect(m_comboBox, &QComboBox::currentIndexChanged, this, [this](int idx)
    {
        const auto code = m_comboBox->itemData(idx).value<SystemAPI::KeyCode>();
        qDebug() << "Key CHanged";
        emit changed(code);
    });

    if(removable)
    {
        auto* delBtn = new QPushButton{"U", this};
        layout->addWidget(delBtn, 1);

        QObject::connect(delBtn, &QPushButton::clicked, this, [this](bool)
        {
            emit deleted(this);
        });
    }
}

SystemAPI::KeyCode KeySelectorWidget::getKeyCode() const
{
    const auto idx = m_comboBox->currentIndex();
    return m_comboBox->itemData(idx).value<SystemAPI::KeyCode>();
}
