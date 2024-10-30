#include "logger.h"
#ifdef CLICKER_DEBUG
Logger &Logger::instance() {
    static Logger instance;
    return instance;
}


Logger::Logger() {
    logFile.setFileName("log.txt");
    if (!logFile.open(QIODevice::WriteOnly | QIODevice::Text)) {  // Очищаем файл при каждом открытии
        qWarning() << "Could not open log file for writing!";
    }
}

Logger::~Logger() {
    if (logFile.isOpen()) {
        logFile.close();
    }
}

Logger &Logger::operator<<(int value) {
    buffer += QString::number(value);
    return *this;
}

void Logger::endLine() {
    QMutexLocker locker(&mutex);
    if (!logFile.isOpen()) {
        qWarning() << "Log file is not open!";
        return;
    }

    QTextStream out(&logFile);
    out << QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss") << " - " << buffer << "\n";
    out.flush();

    buffer.clear();  // Очистка буфера после записи
}

Logger &Logger::operator<<(float value) {
    buffer += QString::number(value, 'f', 6); // 6 знаков после запятой
    return *this;
}


Logger &Logger::operator<<(const QString &message) {
    buffer += message;
    return *this;
}
#endif
