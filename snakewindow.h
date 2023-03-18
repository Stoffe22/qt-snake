#ifndef SNAKEWINDOW_H
#define SNAKEWINDOW_H

#include <QWidget>
#include <QVBoxLayout>
#include <QPushButton>
#include <QLCDNumber>
#include "snake.h"

class SnakeWindow : public QWidget
{
    Q_OBJECT

    static const int B_WIDTH = 300;
    static const int B_HEIGHT = 300;
    QVBoxLayout* mainLayout;
    QHBoxLayout* buttonLayout;
    QPushButton* startButton;
    QPushButton* stopButton;
    QLCDNumber* scoreLabel;
    Snake snake;
public:
    explicit SnakeWindow(QWidget *parent = nullptr);

signals:

private slots:
    void updateScoreLabel();

};

#endif // SNAKEWINDOW_H
