#ifndef APPLICATION_WIDGET_H
#define APPLICATION_WIDGET_H

#include <QWidget>

class CaptureWidget;
class PreferencesWidget;

class ApplicationWidget : public QWidget
{
    Q_OBJECT
public:
    explicit ApplicationWidget(QWidget *parent = nullptr);

signals:

private:
    CaptureWidget* m_capture;
    PreferencesWidget* m_preferences;
};

#endif // APPLICATION_WIDGET_H
