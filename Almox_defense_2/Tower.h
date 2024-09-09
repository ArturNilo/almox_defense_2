#ifndef TOWER_H
#define TOWER_H

#include <QGraphicsPixmapItem>
#include <QGraphicsEllipseItem>
#include <QGraphicsItem>
#include <QObject>
#include <QPointF>

class Tower : public QObject, public QGraphicsPixmapItem {
    Q_OBJECT
public:
    Tower(QGraphicsItem *parent = nullptr);

    // Métodos públicos
    double dist_to(QGraphicsItem *item) const;
    void fire();
    void setRadius(float r);
    void setAttackRate(int rate);
    void setDamage(int dmg);

public slots:



protected:
    // Membros protegidos acessíveis pelas subclasses
    float x;
    float y;
    float radius;
    int attack_rate;
    int damage;
    QTimer *attackTimer;
    QGraphicsEllipseItem *attack_area;
    QPointF attack_dest;
    QPointF center_pixmap;
    QPointF center_r;
    bool has_target;

    // Métodos protegidos
    void rotate_to_point(QPointF p);
    double dist_to(QGraphicsItem *item);
    void acquire_target();

private:
         // Membros privados (não acessíveis diretamente pelas subclasses)
};

#endif // TOWER_H
