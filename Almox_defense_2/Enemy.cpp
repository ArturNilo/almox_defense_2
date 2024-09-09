#include "Enemy.h"
#include <QPixmap>
#include <QTimer>
#include <QLineF>
#include <QPen>
#include "Game.h"

extern Game* game;

// Enemy.cpp
#include "Enemy.h"
#include "Game.h"

Enemy::Enemy(Game *gameInstance, QGraphicsItem *parent) : QGraphicsPixmapItem(parent) {
    setPixmap(QPixmap(":/images/tex/7.png"));
    setTransformOriginPoint(boundingRect().width()/2, boundingRect().height()/2);

    life = 10;
    is_dead = false;

    if (gameInstance == nullptr) {
        qDebug() << "Erro: Ponteiro gameInstance é nullptr!";
        return;
    }

    if (!gameInstance->pathPoints.isEmpty()) {
        points = gameInstance->pathPoints;  // Acessa os pontos de caminho do jogo
        point_index = 0;
        dest = points[0];

        // Definir a posição inicial do inimigo
        setPos(dest);

        rotate_to_point(dest);
    } else {
        qDebug() << "pathPoints está vazia!";
        return;
    }

    QTimer* timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(move_forward()));
    timer->start(10);
}

void Enemy::rotate_to_point(QPointF p)
{
    QLineF ln(pos(), p);
    setRotation(-1 * ln.angle());
}

void Enemy::move_forward()
{
    qDebug() << "Move forward iniciado";  // Debug para rastrear execução

    if (points.isEmpty()) {
        return;  // Evite mover se não houver pontos
    }

    QLineF ln(pos(), dest);

    if (ln.length() < 5) {
        point_index++;
        if (point_index == points.size()) {
            qDebug() << "Inimigo chegou ao final do caminho";
            // Remover inimigo da cena
            scene()->removeItem(this);
            //implementar dano na base
            delete this;
            return;
        }
        dest = points[point_index];
        rotate_to_point(dest);
    }

    int STEP_SIZE = 1;
    int theta = rotation();

    double dx = STEP_SIZE * qCos(qDegreesToRadians(theta));
    double dy = STEP_SIZE * qSin(qDegreesToRadians(theta));

    setPos(x() + dx, y() + dy);

    qDebug() << "Move forward concluído";  // Debug para rastrear execução
}


void Enemy::take_damage(int dmg)
{
    life -= dmg;
    if (life <= 0) {
        is_dead = true;
    }
}
