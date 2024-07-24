#ifndef TOWER_H
#define TOWER_H

#include <QGraphicsPixmapItem>
#include <QGraphicsEllipseItem>
#include <QGraphicsItem>

class Tower: public QGraphicsPixmapItem{
public:
    Tower(QGraphicsItem * parent=0);
private:
    float x;
    float y;
    float radius_mult;
    QGraphicsEllipseItem * attack_area;

};
#endif // TOWER_H
