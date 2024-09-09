#include "ResTower.h"

ResTower::ResTower(QGraphicsItem *parent) : Tower(parent) {
    // Definir parâmetros específicos para ResTower
    setPixmap(QPixmap(":/images/tex/13.png"));  // Pixmap específico para ResTower
    radius = 150;  // Exemplo de parâmetro específico
    attack_rate = 100;
    damage = 30;
    // Outros parâmetros e inicializações específicas
}
