#include "Enemy.h"
#include <QPixmap>
#include <QTimer>
#include <QLineF>

Enemy::Enemy(QGraphicsItem *parent)
{
    setPixmap(QPixmap(":/images/tex/7.png"));

    points << QPoint(200,200) << QPoint(400,200);
    point_index = 0;
    dest = points[0];
    rotate_to_point(dest);

    QTimer * timer = new QTimer(this);
    connect(timer,SIGNAL(timeout()),this,SLOT(move_forward()));
    timer->start(150);
}

void Enemy::rotate_to_point(QPointF p)
{
    QLineF ln(pos(), p);
    setRotation(-1 * ln.angle());
}

void Enemy::move_forward()
{
    QLineF ln(pos(),dest);
    if (ln.length() < 5){
        point_index++;
        if (point_index >= points.size()){
            return;
        }
        dest = points[point_index];
        rotate_to_point(dest);
    }

    int STEP_SIZE = 5;
    int theta = rotation();

    double dx = STEP_SIZE * qSin(qDegreesToRadians(theta));
    double dy = STEP_SIZE * qCos(qDegreesToRadians(theta));

    setPos(x()+dx, y()+dy);
}
