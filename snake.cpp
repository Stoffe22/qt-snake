#include <QTime>
#include <QPainter>
#include <QDebug>
#include <QKeyEvent>
#include "snake.h"

Snake::Snake(QWidget *parent, int width, int height)
    : QFrame{parent}, b_width(width), b_height(height)
{
    setStyleSheet("background-color:black");
    setFixedSize(width, height);
    loadImages();
    setFocusPolicy(Qt::StrongFocus);
    inGame = false;
    gameOver = false;
    isStopped = false;
}


void Snake::loadImages()
{
    QPixmap apple_pm;
    QPixmap head_pm;
    QPixmap dot_pm;

    apple_pm.load("/Users/jonason/Documents/code/projects/qt/snake/dot.png");
    head_pm.load("/Users/jonason/Documents/code/projects/qt/snake/dot.png");
    dot_pm.load("/Users/jonason/Documents/code/projects/qt/snake/dot.png");

    apple_pm = apple_pm.scaled(10, 10, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
    head_pm = head_pm.scaled(10, 10, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
    dot_pm = dot_pm.scaled(10, 10, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);

    apple = apple_pm.toImage();
    head = head_pm.toImage();
    dot = dot_pm.toImage();
}

void Snake::initGame()
{
    if (isStopped)
    {
        timerId = startTimer(DELAY);
        return;
    }

    leftDirection = false;
    rightDirection = true;
    upDirection = false;
    downDirection = false;
    score = 0;

    dots = 3;
    for (int i = 0; i < dots; i++)
    {
        x[i] = 100 - DOT_SIZE * i;
        y[i] = 100;
    }
    locateApple();
    timerId = startTimer(DELAY);
    inGame = true;
    gameOver = false;
    isStopped = false;
}

void Snake::stopGame()
{
    killTimer(timerId);
    isStopped = true;
}


void Snake::locateApple()
{
    QTime time = QTime::currentTime();
    srand((uint) time.msec());

    int r = arc4random() % 29;
    x_apple = r * DOT_SIZE;

    r = arc4random() % 29;
    y_apple = r * DOT_SIZE;
}

void Snake::paintEvent(QPaintEvent* e)
{
    Q_UNUSED(e);
    doDrawing();
}

void Snake::move()
{
    for (int i = dots; i > 0; i--)
    {
        x[i] = x[i - 1];
        y[i] = y[i - 1];
    }

    if (leftDirection) {
        x[0] -= DOT_SIZE;
    }

    if (rightDirection) {
        x[0] += DOT_SIZE;
    }

    if (upDirection) {
        y[0] -= DOT_SIZE;
    }

    if (downDirection) {
        y[0] += DOT_SIZE;
    }
}

void Snake::timerEvent(QTimerEvent* e)
{
    if (inGame)
    {
        checkCollision();
        checkApple();
        move();
    }
    repaint();
}

void Snake::checkCollision()
{
    if (x[0] < 0 || x[0] >= b_width || y[0] < 0 || y[0] >= b_height)
    {
        inGame = false;
        gameOver = true;
        isStopped = false;
    }
    for (int i = 1; i < dots; i++)
    {
        if (x[i] == x[0] && y[i] == y[0])
        {
            inGame = false;
            gameOver = true;
            isStopped = false;
        }
    }

    if(!inGame) {
        killTimer(timerId);
    }
}

void Snake::checkApple()
{
    if (x[0] == x_apple && y[0] == y_apple)
    {
        dots++;
        locateApple();
        score++;
        emit appleEaten();
    }
}

void Snake::keyPressEvent(QKeyEvent* e)
{
    if (e->key() == Qt::Key_Up)
    {
        upDirection = true;
        downDirection = false;
        leftDirection = false;
        rightDirection = false;
    }
    if (e->key() == Qt::Key_Down)
    {
        upDirection = false;
        downDirection = true;
        leftDirection = false;
        rightDirection = false;
    }
    if (e->key() == Qt::Key_Right)
    {
        upDirection = false;
        downDirection = false;
        leftDirection = false;
        rightDirection = true;
    }
    if (e->key() == Qt::Key_Left)
    {
        upDirection = false;
        downDirection = false;
        leftDirection = true;
        rightDirection = false;
    }

    QWidget::keyPressEvent(e);
}

void Snake::doDrawing()
{
    QPainter qp(this);
    if (inGame)
    {
        for (int i = dots; i > 0; i--)
        {
            qp.drawImage(x[i], y[i], dot);
        }
        qp.drawImage(x[0], y[0], head);
        qp.drawImage(x_apple, y_apple, apple);
    }
    else
    {
        gameOverMessage(qp);
    }
}

void Snake::gameOverMessage(QPainter& qp)
{
    if (!gameOver)
        return;
    QString message = "Game over";
    QFont font("Courier", 15, QFont::DemiBold);
    QFontMetrics fm(font);
    int textWidth = fm.horizontalAdvance(message);

    qp.setFont(font);
    int h = height();
    int w = width();

    qp.translate(QPoint(w/2, h/2));
    qp.drawText(-textWidth/2, 0 , message);
}
