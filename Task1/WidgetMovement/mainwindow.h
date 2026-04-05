#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <vector>
#include <QTimer>
#include <QElapsedTimer>
#include <QPushButton>
#include <QRandomGenerator64>

class QTimer;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    static constexpr double MIN_CREATION_INTERVAL = 0.1;
    static constexpr double MAX_CREATION_INTERVAL = 1.0;
    static constexpr int SPEED = 3;

    double _creationInterval = MAX_CREATION_INTERVAL;
    std::unique_ptr<QElapsedTimer> _elapsedTimer;
    std::unique_ptr<QTimer> _motionTimer;
    std::vector<std::unique_ptr<QPushButton>> _buttons;
};
#endif // MAINWINDOW_H
