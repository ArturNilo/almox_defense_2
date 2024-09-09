#include "AcidTower.h"

AcidTower::AcidTower(QGraphicsItem *parent) : Tower(parent) {
    // Definir parâmetros específicos para AcidTower
    setPixmap(QPixmap(":/images/tex/21.png"));  // Pixmap específico para AcidTower
    radius = 200;  // Exemplo de parâmetro específico
    attack_rate = 300;
    damage = 40;
    // Outros parâmetros e inicializações específicas
}
