#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    resize(300, 600);

    auto motionTimer = new QTimer(this);
    _elapsed.start();
    motionTimer->start(1000 / 60); // 60 FPS

    connect(motionTimer, &QTimer::timeout, this, [this]() {
        auto randomGenerator = QRandomGenerator64::global();
        int windowHeight = height();
        const auto childrens = children();
        for (auto *object : childrens) {
            const auto &button = qobject_cast<QPushButton*>(object);
            if (!button || !button->isVisible()) {
                continue;
            }

            int speed = randomGenerator->bounded(MIN_SPEED, MAX_SPEED + 1);;
            if (button->geometry().contains(mapFromGlobal(QCursor::pos()))) {
                speed *= 2;
            }
            button->move(button->x(), button->y() + speed);

            bool isLose = (button->y() + button->height()) >= windowHeight;
            if (isLose) {
                setStyleSheet(QStringLiteral("QMainWindow { background-color: red; }"));
                setWindowTitle(QStringLiteral("Lose!"));
                button->deleteLater();
            }
        }

        if (_elapsed.elapsed() >= _creationInterval) {
            _elapsed.restart();
            _creationInterval = MIN_CREATION_INTERVAL +
                                randomGenerator->bounded(MAX_CREATION_INTERVAL - MIN_CREATION_INTERVAL);

            int windowWidth = width();
            auto button = new QPushButton(QStringLiteral("*"), this);
            auto randomX = randomGenerator->bounded(windowWidth);
            auto randomY = randomGenerator->bounded(100);

            button->move(randomX, randomY);
            connect(button, &QPushButton::clicked, this, [button]() {
                button->hide();
                button->deleteLater();
            }, Qt::DirectConnection);
            button->show();
        }
    });
}

MainWindow::~MainWindow()
{
}
