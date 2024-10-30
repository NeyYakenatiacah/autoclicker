#include "application_widget.h"

#include <QComboBox>
#include <QVBoxLayout>
#include <QPushButton>
// #include <QStackedWidget>

#include "controls/window_selector.h"
#include "controls/preferences_widget.h"
#include "controls/capture_widget.h"

#include "system_api.h"


ApplicationWidget::ApplicationWidget(QWidget *parent)
    : QWidget{parent}
    , m_capture{new CaptureWidget}
    , m_preferences{new PreferencesWidget}
{
    auto *layout = new QVBoxLayout(this);

    auto* selector = new WindowSelector(this);
    layout->addWidget(selector);

    QHBoxLayout* row = new QHBoxLayout(this);
    layout->addLayout(row);

    m_capture->setFixedSize(300, 300);
    setFixedHeight(300);

    row->addWidget(m_capture, 3);
    row->addWidget(m_preferences, 7);

    QObject::connect(selector, &WindowSelector::onIndexChanged, this, [this](HWND hwnd)
    {
        auto title = SystemAPI::getWindowTitle(hwnd);
        qDebug() << "WindowSelector::onIndexChanged(" << title << ")";

        m_capture->update(hwnd);
    });

    QObject::connect(selector, &WindowSelector::onLocked, this, [this](HWND hwnd)
    {
        auto title = SystemAPI::getWindowTitle(hwnd);
        qDebug() << "WindowSelector::onConfirmed(" << title << ")";

        SystemAPI::hideWindow(hwnd);
    });


}
