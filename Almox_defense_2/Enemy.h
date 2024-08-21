#ifndef ENEMY_H
#define ENEMY_H

#include <QGraphicsPixmapItem>
#include <QObject>
#include <QList>
#include <QPointF>


class Enemy: public QObject, public QGraphicsPixmapItem{
    Q_OBJECT
public:
    Enemy(QGraphicsItem *parent=0);
    void rotate_to_point(QPointF p);
    bool is_dead;
public slots:
    void move_forward();
    void take_damage(int dmg);
private:
    QList<QPointF> points;
    QPointF dest;
    QLineF dist_to;
    int point_index;
    int life;

};

#endif // ENEMY_H
