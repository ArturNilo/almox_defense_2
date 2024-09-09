#include "CapTower.h"

CapTower::CapTower(QGraphicsItem *parent) : Tower(parent) {
    // Definir parâmetros específicos para CapTower
    setPixmap(QPixmap(":/images/tex/17.png"));  // Pixmap específico para CapTower
    radius = 100;  // Exemplo de parâmetro específico
    attack_rate = 200;
    damage = 20;
    // Outros parâmetros e inicializações específicas
}
