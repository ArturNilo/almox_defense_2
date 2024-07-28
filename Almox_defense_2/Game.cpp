#include <QGraphicsScene>
#include "Game.h"
#include "Tower.h"
#include "Bullet.h"
#include "Enemy.h"


Game::Game(): QGraphicsView()
{
    // Create a scene
    scene = new QGraphicsScene(this);
    scene->setSceneRect(0,0,1280,720);

    setScene(scene);

    setFixedSize(1280,720);
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);


    // Criar torreta
    Tower * t = new Tower();

    scene->addItem(t);


    // Criar inimigo teste
    Enemy * enemy = new Enemy();
    scene->addItem(enemy);

}

void Game::mousePressEvent(QMouseEvent *event){

    Bullet * bullet = new Bullet();
    bullet->setPos(event->pos());
    scene->addItem(bullet);
}
