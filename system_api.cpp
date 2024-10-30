#include "system_api.h"
#include "WinUser.h"
#include <QDebug>
namespace SystemAPI
{
namespace
{
BOOL windowCallback(HWND hwnd, LPARAM lParam)
{
    auto* windows = reinterpret_cast<QVector<HWND>*>(lParam);

    if(IsWindowVisible(hwnd))
    {
        windows->append(hwnd);
    }

    return TRUE;
}
}

QVector<HWND> getWindows()
{
    QVector<HWND> windows;

    EnumWindows(windowCallback, (LPARAM)&windows);

    return windows;
}

// namespace

QString getWindowTitle(HWND hwnd) {
    char windowTitle[1024];

    int length = GetWindowTextA(hwnd, windowTitle, sizeof(windowTitle));

    if (length > 0) {
        return QString::fromLocal8Bit(windowTitle);
    }

    return QString{};
}

bool pushKeyEvent(HWND hwnd, WPARAM key)
{
    auto r1 = SendMessageA(hwnd, WM_KEYDOWN, key, NULL);
    auto r2 = SendMessageA(hwnd, WM_KEYUP, key, NULL);
    return !(r1 && r2);
}

QImage captureWindow(HWND hwnd)
{
    HDC hdcWindow = GetDC(hwnd);
    HDC hdcMemDC = CreateCompatibleDC(hdcWindow);

    RECT rcClient;
    GetClientRect(hwnd, &rcClient);
    int width = rcClient.right - rcClient.left;
    int height = rcClient.bottom - rcClient.top;

    HBITMAP hbmScreen = CreateCompatibleBitmap(hdcWindow, width, height);
    SelectObject(hdcMemDC, hbmScreen);

    // Bit block transfer into our compatible memory DC
    BitBlt(hdcMemDC, 0, 0, width, height, hdcWindow, 0, 0, SRCCOPY);

    // Convert HBITMAP to QPixmap

    QImage im = QImage::fromHBITMAP(hbmScreen);

    // Clean up
    DeleteObject(hbmScreen);
    DeleteDC(hdcMemDC);
    ReleaseDC(hwnd, hdcWindow);

    return im;
}

void showWindow(HWND hwnd)
{

}

void hideWindow(HWND hWnd)
{
    qDebug() << "HIDEWINDOW";
    long style= GetWindowLong(hWnd, GWL_STYLE);
    style &= ~(WS_VISIBLE);    // this works - window become invisible


    style |= WS_EX_TOOLWINDOW;   // flags don't work - windows remains in taskbar
    style |= WS_DISABLED;
    style &= ~(WS_EX_APPWINDOW);

    ShowWindow(hWnd, SW_HIDE); // hide the window
    SetWindowLong(hWnd, GWL_STYLE, style); // set the style
    ShowWindow(hWnd, SW_SHOW); // show the window for the new style to come into effect
    ShowWindow(hWnd, SW_HIDE); // hide the window so we can't see it
}

} // namespace systemapi
