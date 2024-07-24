#include "Game.h"
#include "Tower.h"
#include <QGraphicsScene>



Game::Game()
{
    // Create a scene
    scene = new QGraphicsScene(this);

    setScene(scene);

    // Criar torreta
    Tower * t = new Tower();

    scene->addItem(t);

}
