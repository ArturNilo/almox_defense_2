#ifndef TOWER_H
#define TOWER_H

#include <QGraphicsPixmapItem>
#include <QGraphicsEllipseItem>
#include <QGraphicsItem>
#include <QPointF>
#include <QObject>

class Tower:public QObject, public QGraphicsPixmapItem{
    Q_OBJECT
public:
    Tower(QGraphicsItem * parent=0);
    double dist_to(QGraphicsItem * item);
    void fire();
public slots:
    void aquire_target();
private:
    float x;
    float y;
    float radius_mult;
    QGraphicsEllipseItem * attack_area;
    QPointF attack_dest;
    QPointF center_r;
    bool has_target;
};
#endif // TOWER_H
