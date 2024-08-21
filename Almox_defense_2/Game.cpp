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
    t->setPos(200,200);

    Tower * t1 = new Tower();

    scene->addItem(t1);
    t1->setPos(400,400);



    // Criar inimigo teste
    Enemy * enemy = new Enemy();
    scene->addItem(enemy);
    enemy->setPos(120, 120);

    Enemy * enemy1 = new Enemy();
    scene->addItem(enemy1);
    enemy1->setPos(10, 10);

}

void Game::mousePressEvent(QMouseEvent *event){

    Bullet * bullet = new Bullet();
    bullet->setPos(event->pos());
    scene->addItem(bullet);
}
