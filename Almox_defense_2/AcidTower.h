#ifndef ACIDTOWER_H
#define ACIDTOWER_H

#include "Tower.h"

class AcidTower : public Tower {
    Q_OBJECT
public:
    AcidTower(QGraphicsItem *parent = nullptr);
    // Adicione métodos específicos de AcidTower, se necessário
};

#endif // ACIDTOWER_H
