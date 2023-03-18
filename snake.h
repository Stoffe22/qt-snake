#ifndef SNAKE_H
#define SNAKE_H

#include <QFrame>

class Snake : public QFrame
{
    Q_OBJECT

    QImage head;
    QImage dot;
    QImage apple;

    static const int DOT_SIZE = 10;
    static const int MAX_DOTS = 300;
    static const int DELAY = 100;

    int score;
    int timerId;

    int x[MAX_DOTS];
    int y[MAX_DOTS];
    int x_apple;
    int y_apple;
    int dots;

    int b_width;
    int b_height;

    bool inGame;
    bool gameOver;
    bool isStopped;

    bool leftDirection;
    bool rightDirection;
    bool upDirection;
    bool downDirection;

    void loadImages();

    void checkCollision();
    void checkApple();
    void locateApple();
    void move();
    void doDrawing();
    void gameOverMessage(QPainter& qp);


protected:
    void paintEvent(QPaintEvent* e);
    void timerEvent(QTimerEvent* e);
    void keyPressEvent(QKeyEvent* e);

public:
    explicit Snake(QWidget *parent = nullptr, int width = 100, int height = 100);

    void initGame();
    void stopGame();
    int applesEaten() { return score; }

signals:
    void appleEaten();

};

#endif // SNAKE_H
