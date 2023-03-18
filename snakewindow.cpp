#include "snakewindow.h"

SnakeWindow::SnakeWindow(QWidget *parent)
    : QWidget{parent}, snake{parent, B_WIDTH, B_HEIGHT}
{
    buttonLayout = new QHBoxLayout(parent);
    startButton = new QPushButton("Start");
    stopButton = new QPushButton("Stop");
    scoreLabel = new QLCDNumber();
    buttonLayout->addWidget(startButton);
    buttonLayout->addWidget(stopButton);
    buttonLayout->addWidget(scoreLabel);

    mainLayout = new QVBoxLayout(parent);
    mainLayout->addLayout(buttonLayout);
    mainLayout->addWidget(&snake);
    setLayout(mainLayout);

    connect(startButton, &QPushButton::clicked, &snake, &Snake::initGame);
    connect(stopButton, &QPushButton::clicked, &snake, &Snake::stopGame);
    connect(&snake, &Snake::appleEaten, this, &SnakeWindow::updateScoreLabel);
}

void SnakeWindow::updateScoreLabel()
{
    scoreLabel->display(snake.applesEaten());
}
