#ifndef CAPTURE_WIDGET_H
#define CAPTURE_WIDGET_H

#include <QLabel>
#include <qwindowdefs_win.h>

class CaptureWidget : public QLabel
{
    Q_OBJECT
public:
    explicit CaptureWidget(QWidget *parent = nullptr);

    void update(HWND hwnd);

signals:

private:
};

#endif // CAPTURE_WIDGET_H
