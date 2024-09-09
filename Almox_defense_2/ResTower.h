#ifndef RESTOWER_H
#define RESTOWER_H

#include "Tower.h"

class ResTower : public Tower {
    Q_OBJECT
public:
    ResTower(QGraphicsItem *parent = nullptr);
    // Adicione métodos específicos de ResTower, se necessário
};

#endif // RESTOWER_H
