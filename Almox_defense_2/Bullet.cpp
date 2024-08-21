#include "Bullet.h"
#include "Enemy.h"
#include <QPixmap>
#include <QTimer>
#include <qmath.h>

Bullet::Bullet(QGraphicsItem *parent): QObject(),QGraphicsPixmapItem(parent){
    setPixmap(QPixmap(":/images/tex/41.png"));

    setTransformOriginPoint(boundingRect().width()/2,boundingRect().height()/2);

    // Opcional: centralizar o objeto no ponto inicial

    QTimer * move_timer = new QTimer(this);
    connect(move_timer,SIGNAL(timeout()),this, SLOT(move()));
    move_timer->start(3);

    maxRange = 100;
    distanceTravelled = 0;
}

void Bullet::move(){
    int STEP_SIZE = 3;
    double theta = rotation(); // degrees

    double dy = STEP_SIZE * qSin(qDegreesToRadians(theta));
    double dx = STEP_SIZE * qCos(qDegreesToRadians(theta));

    setPos(x()+dx, y()+dy);
    distanceTravelled = distanceTravelled + STEP_SIZE;
    if (distanceTravelled > maxRange)
    {
        delete this;
    }
    QList<QGraphicsItem *> colliding_items = collidingItems();
    for (int i = 0; i < colliding_items.size(); ++i) {
        Enemy * enemy = dynamic_cast<Enemy *>(colliding_items[i]);
        if (enemy) {
            enemy->take_damage(damage);
            if (enemy->is_dead) {
                // Deleta ambos da memória
                delete enemy;
            }
            delete this;
            return;
        }
    }
}

double Bullet::getMaxRange(){
    return maxRange;
}

double Bullet::getDistanceTravelled(){
    return distanceTravelled;
}

void Bullet::setMaxRange(double rng){
    maxRange = rng;
}

void Bullet::setDistanceTravelled(double dist){
    distanceTravelled = dist;
}

void Bullet::setDamage(int dmg){
    damage = dmg;
}
