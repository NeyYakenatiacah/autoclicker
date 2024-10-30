#ifndef LOGGER_H
#define LOGGER_H

#ifdef CLICKER_DEBUG

#include <QFile>
#include <QTextStream>
#include <QMutex>
#include <QDateTime>
#include <QString>
#include <QCoreApplication>
#include <QDebug>

class Logger {
public:
    static Logger& instance();

    // Перегрузка оператора << для записи строки в лог-файл
    Logger& operator<<(const QString& message);

    // Перегрузка оператора << для записи целого числа
    Logger& operator<<(int value);

    // Перегрузка оператора << для записи вещественного числа
    Logger& operator<<(float value);

    void endLine();

private:
    Logger();
    ~Logger();

    // Удаляем копирующие и перемещающие конструкторы для обеспечения синглтонности
    Logger(const Logger&) = delete;
    Logger& operator=(const Logger&) = delete;
    Logger(Logger&&) = delete;
    Logger& operator=(Logger&&) = delete;

private:
    QFile logFile;
    QMutex mutex;
    QString buffer;
};
#endif

#endif // LOGGER_H
