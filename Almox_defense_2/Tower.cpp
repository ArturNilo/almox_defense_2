#include "Tower.h"
#include "Game.h"
#include "Bullet.h"
#include "Enemy.h"
#include <QPixmap>
#include <QVector>
#include <QPointF>
#include <QLineF>
#include <QTimer>
#include <QGraphicsEllipseItem>
#include <qmath.h>

extern Game * game;

Tower::Tower(QGraphicsItem *parent): QObject(), QGraphicsPixmapItem(parent){
    setPixmap(QPixmap(":/images/tex/16.png"));

    radius_mult = 4;

    QPointF center_r(25-radius_mult*25, 25-radius_mult*25);

    // Deifine real pixmap center based on radius multiplier
    attack_area = new QGraphicsEllipseItem(center_r.x(), center_r.y(), 50*radius_mult, 50*radius_mult, this);

    //connect a timer to attack_target
    QTimer * timer = new QTimer();
    connect(timer,SIGNAL(timeout()),this,SLOT(aquire_target()));
    timer->start(1000);

    // set attack_dest
    attack_dest = QPointF(400,300);
}

double Tower::dist_to(QGraphicsItem *item)
{
    QLineF ln(pos(), item->pos());
    return ln.length();
}

void Tower::fire()
{
    Bullet * bullet = new Bullet();
    bullet->setPos(center_r.x(), center_r.y());

    QLineF ln(center_r, attack_dest);
    int angle = -1 * ln.angle();
    bullet->setRotation(angle);
    setRotation(angle);
    game->scene->addItem(bullet);
}

void Tower::aquire_target()
{
    QList<QGraphicsItem *> colliding_items = attack_area->collidingItems();

    if (colliding_items.size() == 1)
    {
        has_target = false;
        return;
    }

    double closest_dist = 300;
    QPointF closest_pt = QPointF(0,0);

    for (size_t i = 0, n = colliding_items.size(); i<n; i++)
    {
        Enemy * enemy =  dynamic_cast<Enemy *>(colliding_items[i]);
        if (enemy){
            double dist = dist_to(enemy);
            if(dist < closest_dist)
            {
                closest_dist = dist;
                closest_pt = colliding_items[i]->pos();
                has_target = true;
            }
        }
    }
    attack_dest = closest_pt;
    fire();
}
