#ifndef SYSTEM_WINDOW_MANAGER_H
#define SYSTEM_WINDOW_MANAGER_H

#include <QObject>

class SystemWindowManager : public QObject
{
    Q_OBJECT
public:
    explicit SystemWindowManager(QObject *parent = nullptr);

signals:
};

#endif // SYSTEM_WINDOW_MANAGER_H
