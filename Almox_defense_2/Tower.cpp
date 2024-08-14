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

    radius = 400;
    attack_rate = 1000;

    // Calcula o centro do pixmap
    center_pixmap = QPointF(boundingRect().width()/2, boundingRect().height()/2);

    // Define o ponto de origem da transformação no centro do pixmap
    setTransformOriginPoint(center_pixmap);

    // Define a área de ataque centralizada no centro do pixmap
    attack_area = new QGraphicsEllipseItem(-radius/2, -radius/2, radius, radius, this);
    attack_area->setPos(center_pixmap);
    attack_area->setPen(QPen(Qt::DotLine));

    // Conectar um temporizador para atacar o alvo
    QTimer * timer = new QTimer();
    connect(timer, SIGNAL(timeout()), this, SLOT(aquire_target()));

    timer->start(attack_rate);

    // Define o destino de ataque
    //attack_dest = QPointF(400, 300);
}

void Tower::fire()
{
    // Cria o projétil
    Bullet * bullet = new Bullet();

    // Converte a posição central do QPixmap para as coordenadas globais da cena
    //QPointF tower_center_scene = mapToScene(center_pixmap);

    bullet->setPos(pos());
    QLineF ln(pos(), attack_dest);
    int angle = -1 * ln.angle();
    bullet->setRotation(angle);

    // Ajusta a rotação da torre em torno de seu centro
    setRotation(angle);

    game->scene->addItem(bullet);
}

double Tower::dist_to(QGraphicsItem *item)
{
    QLineF ln(pos(), item->pos());
    return ln.length();
}

void Tower::aquire_target()
{
    QList<QGraphicsItem *> colliding_items = attack_area->collidingItems();

    if (colliding_items.size() == 1)
    {
        has_target = false;
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
                attack_dest = closest_pt;
                has_target = true;
                fire();
            }
        }
        else{has_target = false;}

    }
}
