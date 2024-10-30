#include "main_window.h"
//#include "application_widget.h"
#include "controls/hp_widget.h"

#include <QImage>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    // auto* widget = new ApplicationWidget(this);
    auto* widget = new HPWidget(this);
    this->setCentralWidget(widget);

    QImage img;
    img.load("D:/qwe.jpg");
    qDebug() << img.size();
    auto color = img.pixelColor(501, 87);
    qDebug() << "COLOR: {" << color.red() << ":" << color.green() << ":" << color.blue();
}

MainWindow::~MainWindow()
{
}

