#pragma once

#include <QWidget>
#include <qwindowdefs_win.h>

QT_BEGIN_NAMESPACE
class QComboBox;
class QPushButton;
QT_END_NAMESPACE

class WindowSelector : public QWidget
{
    Q_OBJECT
public:
    explicit WindowSelector(QWidget *parent = nullptr);
    void setEnabled(bool enabled);

private:
    void refresh();
    bool filter(const QString& title);

    void currentIndexChanged(int);
    void buttonClicked(bool checked);

signals:
    void onLocked(HWND);
    void onUnlocked();

    void onIndexChanged(HWND);

private:
    QComboBox* m_comboBox;
    QPushButton* m_confirmBtn;

    QVector<HWND> m_items;

    bool m_isLocked{false};
};
