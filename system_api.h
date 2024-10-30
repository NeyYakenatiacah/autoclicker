#ifndef SYSTEM_API_H
#define SYSTEM_API_H
#include <Windows.h>

#include <QString>
#include <QStringList>
#include <QVector>
#include <QImage>

#include <qtmetamacros.h>
#include <QMetaEnum>

namespace SystemAPI
{
    Q_NAMESPACE

    enum KeyCode {
        // Функциональные клавиши F1-F9
        F1 = 0x70,
        F2 = 0x71,
        F3 = 0x72,
        F4 = 0x73,
        F5 = 0x74,
        F6 = 0x75,
        F7 = 0x76,
        F8 = 0x77,
        F9 = 0x78,

        // Клавиши A-Z
        A = 0x41,
        B = 0x42,
        C = 0x43,
        D = 0x44,
        E = 0x45,
        F = 0x46,
        G = 0x47,
        H = 0x48,
        I = 0x49,
        J = 0x4A,
        K = 0x4B,
        L = 0x4C,
        M = 0x4D,
        N = 0x4E,
        O = 0x4F,
        P = 0x50,
        Q = 0x51,
        R = 0x52,
        S = 0x53,
        T = 0x54,
        U = 0x55,
        V = 0x56,
        W = 0x57,
        X = 0x58,
        Y = 0x59,
        Z = 0x5A,

        // Цифровые клавиши 1-9
        Num1 = 0x31,
        Num2 = 0x32,
        Num3 = 0x33,
        Num4 = 0x34,
        Num5 = 0x35,
        Num6 = 0x36,
        Num7 = 0x37,
        Num8 = 0x38,
        Num9 = 0x39,

        // Модификаторы
        LeftShift = 0xA0,
        RightShift = 0xA1,
        LeftAlt = 0xA4,
        RightAlt = 0xA5
    };
    Q_ENUM_NS(KeyCode)

    using KeySequence = QVector<KeyCode>;

    QVector<HWND> getWindows();

    QString getWindowTitle(HWND hwnd);

    bool pushKeyEvent(HWND hwnd, WPARAM key);

    // Function to capture a window using Windows API
    QImage captureWindow(HWND hwnd);

    void showWindow(HWND hwnd);
    void hideWindow(HWND hwnd);
}
/*
BOOL CALLBACK speichereFenster(HWND hwnd, LPARAM substring){
    const DWORD TITLE_SIZE = 1024;
    TCHAR windowTitle[TITLE_SIZE];

    GetWindowText(hwnd, windowTitle, TITLE_SIZE);
    int length = ::GetWindowTextLength(hwnd);

    std::wstring temp(&windowTitle[0]);
    std::string title(temp.begin(), temp.end());

    if (!IsWindowVisible(hwnd) || length == 0 || title == "Program Manager") {
        return TRUE;
    }

    std::cout << title << std::endl;

    return TRUE;
}

void printWindows()
{
    EnumWindows(speichereFenster, NULL);
}
*/

#endif // SYSTEM_API_H
