#include "Tower.h"
#include <QPixmap>
#include <QVector>
#include <QPointF>
#include <QGraphicsEllipseItem>

Tower::Tower(QGraphicsItem *parent)
{
    setPixmap(QPixmap(":/images/tex/16.png"));

    radius_mult = 2.2;

    attack_area = new QGraphicsEllipseItem((25-radius_mult*25), (25-radius_mult*25), 50*radius_mult, 50*radius_mult, this);
}
