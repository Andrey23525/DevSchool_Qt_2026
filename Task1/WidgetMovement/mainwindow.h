#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
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

    static constexpr int MIN_SPEED = 1;
    static constexpr int MAX_SPEED = 3;

    double _creationInterval = MAX_CREATION_INTERVAL;
    QElapsedTimer _elapsed;
};
#endif // MAINWINDOW_H
