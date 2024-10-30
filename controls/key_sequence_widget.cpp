#include "key_sequence_widget.h"
#include "key_selector_widget.h"

#include <QScrollArea>
#include <QVBoxLayout>
#include <QPushButton>

KeySequenceWidget::KeySequenceWidget(QWidget *parent)
    : QWidget{parent}
{
    auto* layout = new QVBoxLayout{this};

    QScrollArea* scrollArea = new QScrollArea{this};
    QWidget* scrollWidget = new QWidget{};
    scrollArea->setWidget(scrollWidget);
    scrollArea->setWidgetResizable(true);

    m_scrollLayout = new QVBoxLayout{scrollWidget};
    m_scrollLayout->setAlignment(Qt::AlignTop);

    auto* addButton = new QPushButton("Add Key", this);

    layout->addWidget(scrollArea, 9);
    layout->addWidget(addButton, 1);

    QObject::connect(addButton, &QPushButton::clicked, this, &KeySequenceWidget::addItem);
}

SystemAPI::KeySequence KeySequenceWidget::asSequence() const
{
    SystemAPI::KeySequence sequence;

    for(const auto* selector : m_widgets)
    {
        sequence.append(selector->getKeyCode());
    }

    return std::move(sequence);
}

void KeySequenceWidget::addItem()
{
    auto* selector = new KeySelectorWidget(this);
    m_scrollLayout->addWidget(selector);
    m_widgets.append(selector);

    QObject::connect(selector, &KeySelectorWidget::deleted, this, &KeySequenceWidget::removeItem);
}

void KeySequenceWidget::removeItem(KeySelectorWidget *widget)
{
    m_scrollLayout->removeWidget(widget);
    m_widgets.removeOne(widget);
    widget->deleteLater();
}
