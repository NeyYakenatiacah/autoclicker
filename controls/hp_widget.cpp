#include "hp_widget.h"

#include "hp_clicker.h"
#include "capture_widget.h"
#include "window_selector.h"
#include "key_selector_widget.h"

#include <QApplication>
#include <QLabel>
#include <QGridLayout>
#include <QPushButton>
#include <QSpinBox>
#include <QThread>
#include <QVBoxLayout>
#include <QTimeEdit>

HPWidget::HPWidget(QWidget *parent)
    : QWidget{parent}
    , m_clicker{new HPClicker{this}}
    , m_clickerThread{new QThread{this}}
    , m_startButton{new QPushButton{"start", this}}
    , m_stopButton{new QPushButton{"stop", this}}
{
    m_startButton->setEnabled(false);
    m_stopButton->setEnabled(false);

    m_clicker->moveToThread(m_clickerThread);

    auto* windowSelector = new WindowSelector{this};
    QObject::connect(windowSelector, &WindowSelector::onLocked, m_clicker, &HPClicker::setWindowDescriptor);
    QObject::connect(windowSelector, &WindowSelector::onLocked, this, [this](HWND)
        {
            m_startButton->setEnabled(true);
            m_stopButton->setEnabled(true);
        });
    QObject::connect(windowSelector, &WindowSelector::onUnlocked, this, [this]()
        {
            m_startButton->setEnabled(false);
            m_stopButton->setEnabled(false);
        });

    auto* captureWidget = new CaptureWidget(this);
    captureWidget->setFixedHeight(300);
    QObject::connect(windowSelector, &WindowSelector::onIndexChanged, captureWidget, &CaptureWidget::update);

    auto* intervalEdit = new QSpinBox(this);
    intervalEdit->setRange(100, 1000);
    intervalEdit->setValue(500);
    QObject::connect(intervalEdit, QOverload<int>::of(&QSpinBox::valueChanged), m_clicker, &HPClicker::setInterval);

    auto* hpEdit = new KeySelectorWidget(this, false);
    QObject::connect(hpEdit, &KeySelectorWidget::changed, m_clicker, &HPClicker::setHocusPocusKey);

    auto* ccEdit = new KeySelectorWidget(this, false);
    QObject::connect(ccEdit, &KeySelectorWidget::changed, m_clicker, &HPClicker::setCastCancelKey);

    auto* sightEdit = new KeySelectorWidget(this, false);
    QObject::connect(sightEdit, &KeySelectorWidget::changed, m_clicker, &HPClicker::setSightKey);

    QObject::connect(m_startButton, &QPushButton::clicked, m_clicker, &HPClicker::start);

    QObject::connect(m_stopButton, &QPushButton::clicked, m_clicker, &HPClicker::stop);

    QObject::connect(m_clicker, &HPClicker::stopped, this, [this]()
        {
            qDebug() << "HPClicker::stopped";
            QApplication::beep();
            QApplication::alert(this, 15);
        });

    auto* layout = new QVBoxLayout(this);

    layout->addWidget(windowSelector, 1);
    layout->addWidget(captureWidget, 5);
    layout->addWidget(intervalEdit, 1);
    layout->addWidget(hpEdit, 1);
    layout->addWidget(ccEdit, 1);
    layout->addWidget(sightEdit, 1);
    layout->addWidget(m_startButton, 1);
    layout->addWidget(m_stopButton, 1);

    m_clickerThread->start();
}

HPWidget::~HPWidget()
{
    m_clickerThread->quit();
    m_clickerThread->wait();
}
