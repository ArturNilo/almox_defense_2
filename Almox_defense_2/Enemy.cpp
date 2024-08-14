#include "Enemy.h"
#include <QPixmap>
#include <QTimer>
#include <QLineF>
#include <QPen>
#include "Game.h"

extern Game * game;

Enemy::Enemy(QGraphicsItem *parent)
{
    setPixmap(QPixmap(":/images/tex/7.png"));
    // Define a origem de transformação para o centro do pixmap
    setTransformOriginPoint(boundingRect().width()/2, boundingRect().height()/2);

    // Opcional: centralizar o objeto no ponto inicial

    points << QPoint(200,200) << QPoint(200,400) << QPoint(400,400) << QPoint(400,200);
    point_index = 0;
    dest = points[0];
    rotate_to_point(dest);

    QTimer * timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(move_forward()));
    timer->start(10);
}

void Enemy::rotate_to_point(QPointF p)
{
    QLineF ln(pos(), p);
    setRotation(-1 * ln.angle());
}

void Enemy::move_forward()
{
    QLineF ln(pos(), dest);
    if (ln.length() < 5){
        point_index++;
        if (point_index >= points.size()){
            point_index = 0;
        }
        dest = points[point_index];
        rotate_to_point(dest);
    }

    int STEP_SIZE = 1;
    int theta = rotation();

    double dx = STEP_SIZE * qCos(qDegreesToRadians(theta));
    double dy = STEP_SIZE * qSin(qDegreesToRadians(theta));


    setPos(x() + dx, y() + dy);
}
