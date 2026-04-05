#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    resize(300, 600);

    _motionTimer = std::make_unique<QTimer>();
    auto elapsed = std::make_shared<QElapsedTimer>();
    elapsed->start();
    _motionTimer->start(1000 / 60); // 60 FPS

    connect(_motionTimer.get(), &QTimer::timeout, this, [this, elapsed]() {
        static size_t index = 0;
        int windowHeight = height();
        for (auto it = _buttons.begin(); it != _buttons.end();) {
            auto &button = *it;
            if (!button->isVisible()) {
                continue;
            }

            int speed = SPEED;
            if (button->geometry().contains(mapFromGlobal(QCursor::pos()))) {
                speed *= 2;
            }
            button->move(button->x(), button->y() + speed);

            bool isLose = (button->y() + button->height()) >= windowHeight;
            if (isLose) {
                setStyleSheet(QStringLiteral("QMainWindow { background-color: red; }"));
                setWindowTitle(QStringLiteral("Lose!"));
                (*it)->deleteLater();
                it = _buttons.erase(it);
            } else {
                ++it;
            }
        }

        if (elapsed->elapsed() >= _creationInterval) {
            elapsed->restart();
            _creationInterval = MIN_CREATION_INTERVAL +
                                QRandomGenerator64::global()->bounded(MAX_CREATION_INTERVAL - MIN_CREATION_INTERVAL);

            int windowWidth = width();
            auto button = std::make_unique<QPushButton>(QStringLiteral("*"), this);
            button->move(QRandomGenerator64::global()->bounded(windowWidth), 100);
            connect(button.get(), &QPushButton::clicked, this, [this, current = button.get()]() {
                current->hide();
                auto it = std::find_if(_buttons.begin(), _buttons.end(),
                                       [current](const auto &element) {
                                           return element.get() == current;
                });

                if (it != _buttons.end()) {
                    current->deleteLater();
                    _buttons.erase(it);
                }
            }, Qt::DirectConnection);
            button->show();
            _buttons.push_back(std::move(button));
        }
    }, Qt::QueuedConnection);
}

MainWindow::~MainWindow()
{
}
