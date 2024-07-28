#include "Tower.h"
#include "Game.h"
#include <QPixmap>
#include <QVector>
#include <QPointF>
#include <QLineF>
#include <QTimer>
#include <QGraphicsEllipseItem>
#include "Bullet.h"
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
    connect(timer,SIGNAL(timeout()),this,SLOT(attack_target()));
    timer->start(1000);

    // set attack_dest
    attack_dest = QPointF(400,300);
}

void Tower::attack_target()
{
    Bullet * bullet = new Bullet();
    bullet->setPos(center_r.x(), center_r.y());

    QLineF ln(center_r, attack_dest);
    int angle = -1 * ln.angle();
    bullet->setRotation(angle);
    setRotation(angle);
    game->scene->addItem(bullet);
}
