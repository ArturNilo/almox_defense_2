#include <QGraphicsScene>
#include "Game.h"
#include "Tower.h"
#include "Bullet.h"
#include "Enemy.h"


Game::Game()
{
    // Create a scene
    scene = new QGraphicsScene(this);

    setScene(scene);

    // Criar torreta
    Tower * t = new Tower();

    scene->addItem(t);

    setFixedSize(1200,800);
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    // Criar inimigo teste
    Enemy * enemy = new Enemy();
    scene->addItem(enemy);

}

void Game::mousePressEvent(QMouseEvent *event){

    Bullet * bullet = new Bullet();
    bullet->setPos(event->pos());
    scene->addItem(bullet);
}
