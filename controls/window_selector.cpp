#include "window_selector.h"
#include "../system_api.h"


#include <QComboBox>
#include <QHBoxLayout>
#include <QPushButton>


WindowSelector::WindowSelector(QWidget *parent)
    : QWidget{parent}
    , m_comboBox{new QComboBox}
    , m_confirmBtn{new QPushButton}
{

    m_confirmBtn->setText("Lock");

    auto* layout = new QHBoxLayout(this);
    layout->addWidget(m_comboBox);
    layout->addWidget(m_confirmBtn);

    refresh();

    QObject::connect(m_comboBox, &QComboBox::currentIndexChanged, this, &WindowSelector::currentIndexChanged);
    QObject::connect(m_confirmBtn, &QPushButton::clicked, this, [this](bool checked)
        {
            m_isLocked = !m_isLocked;
            m_comboBox->setDisabled(m_isLocked);

            m_confirmBtn->setText(m_isLocked ? "Unlock" : "Lock");

            if(m_isLocked)
            {
                const auto idx = m_comboBox->currentIndex();
                auto hwnd = m_comboBox->itemData(idx).value<HWND>();
                emit onLocked(hwnd);
            }
            else
            {
                emit onUnlocked();
            }
        });
}

void WindowSelector::setEnabled(bool enabled)
{
    m_confirmBtn->setEnabled(enabled);
}

void WindowSelector::refresh()
{
    m_comboBox->clear();

    for(const HWND& hwnd : SystemAPI::getWindows())
    {
        const auto title = SystemAPI::getWindowTitle(hwnd);
        if(filter(title))
        {
            QVariant itemData = QVariant::fromValue(hwnd);
            m_comboBox->addItem(title, itemData);
        }
    }
}

bool WindowSelector::filter(const QString &title)
{
    // list of excluded windows?
    return !title.isEmpty();
}

void WindowSelector::currentIndexChanged(int index)
{
    auto hwnd = m_comboBox->itemData(index).value<HWND>();
    emit onIndexChanged(hwnd);
}
