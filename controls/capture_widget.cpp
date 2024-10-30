#include "capture_widget.h"
#include "../system_api.h"

#include <QPixmap>

CaptureWidget::CaptureWidget(QWidget *parent)
    : QLabel{parent}
{
}

void CaptureWidget::update(HWND hwnd)
{
    auto image = SystemAPI::captureWindow(hwnd);
    this->setPixmap(QPixmap::fromImage(image.scaled(this->size(), Qt::KeepAspectRatio)));
}
