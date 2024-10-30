#include "auto_clicker.h"
#include "../system_api.h"
#include <QTimer>
#include <QDebug>

AutoClicker::AutoClicker(QObject *parent)
    : QObject{parent}
    , m_timer{new QTimer{this}}
{
    QObject::connect(m_timer, &QTimer::timeout, this, &AutoClicker::onTimeout);
}

void AutoClicker::start()
{
    m_timer->start();
    emit started();
}

void AutoClicker::stop()
{
    m_timer->stop();
    emit stopped();
}

std::chrono::milliseconds AutoClicker::interval() const
{
    return m_timer->intervalAsDuration();
}

void AutoClicker::setInterval(std::chrono::milliseconds val)
{
    m_timer->setInterval(val);
}

const AutoClicker::KeySequence &AutoClicker::keySequence() const
{
    return m_keySequence;
}

void AutoClicker::setKeySequence(const KeySequence &seq)
{
    if(!m_timer->isActive())
    {
        m_keySequence = seq;
    }
}

void AutoClicker::onTimeout()
{
    if(!m_hwnd || m_keySequence.empty())
    {
        return;
    }

    for(auto key : m_keySequence)
    {
        qDebug() << "Post key [" << key << "]";
        // systemapi::pushKeyEvent(m_hwnd, reinterpret_cast<WPARAM>(key));
    }
}
