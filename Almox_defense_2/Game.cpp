#include <QGraphicsScene>
#include "Game.h"
#include "Tower.h"
#include "Bullet.h"
#include "Enemy.h"

Game::Game() : QGraphicsView()
{
    generateMap();
    // Create a scene
    scene = new QGraphicsScene(this);
    scene->setSceneRect(0, 0, 1280, 720);

    setScene(scene);

    setFixedSize(1280, 720);
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    // Criação do fundo como um QLabel (OptionsLabel já configurado antes)
    OptionsLabel = new QLabel(this);
    OptionsLabel->setPixmap(QPixmap(":/images/tex/33.png"));
    OptionsLabel->setScaledContents(true);
    // Ajustar a posição da OptionsLabel para que sua borda direita encoste na borda direita da janela
    int labelWidth = OptionsLabel->pixmap().size().width();
    int windowWidth = this->width();
    int xPosition = windowWidth - labelWidth;
    OptionsLabel->move(xPosition, 0);

    // Novo QLabel para alinhar a imagem à parte inferior
    QLabel *bottomLabel = new QLabel(this);
    bottomLabel->setPixmap(QPixmap(":/images/tex/32.png"));
    bottomLabel->setScaledContents(true);  // Faz com que a imagem se ajuste ao QLabel
    // Alinhar a borda inferior do bottomLabel com a borda inferior da janela, mantendo x = 0
    int labelHeight = bottomLabel->pixmap().size().height();  // Altura da imagem do QPixmap
    int windowHeight = this->height();  // Altura da janela
    // Calcular a posição Y para mover o bottomLabel para que a borda inferior encoste na borda inferior da janela
    int yPosition = windowHeight - labelHeight;
    bottomLabel->move(0, yPosition);  // Manter x = 0 e ajustar a posição y

    BuyCapTower = new QPushButton(this);
    QPixmap BuyCapTowerPixmap(":/images/tex/25.png");
    BuyCapTower->setIcon(QIcon(BuyCapTowerPixmap));
    BuyCapTower->setIconSize(BuyCapTowerPixmap.size());
    BuyCapTower->setFixedSize(BuyCapTowerPixmap.size());
    BuyCapTower->setFlat(true);
    BuyCapTower->move(20, 500);

    BuyResTower = new QPushButton(this);
    QPixmap BuyResTowerPixmap(":/images/tex/31.png");
    BuyResTower->setIcon(QIcon(BuyResTowerPixmap));
    BuyResTower->setIconSize(BuyResTowerPixmap.size());
    BuyResTower->setFixedSize(BuyResTowerPixmap.size());
    BuyResTower->setFlat(true);
    BuyResTower->move(240, 500);

    BuyAcidTower = new QPushButton(this);
    QPixmap BuyAcidTowerPixmap(":/images/tex/24.png");
    BuyAcidTower->setIcon(QIcon(BuyAcidTowerPixmap));
    BuyAcidTower->setIconSize(BuyAcidTowerPixmap.size());
    BuyAcidTower->setFixedSize(BuyAcidTowerPixmap.size());
    BuyAcidTower->setFlat(true);
    BuyAcidTower->move(460, 500);


    // Criar torreta
    Tower *t = new Tower();
    scene->addItem(t);
    t->setPos(200, 200);

    Tower *t1 = new Tower();
    scene->addItem(t1);
    t1->setPos(400, 400);

    // Criar inimigo teste
    Enemy *enemy = new Enemy();
    scene->addItem(enemy);
    enemy->setPos(120, 120);

    Enemy *enemy1 = new Enemy();
    scene->addItem(enemy1);
    enemy1->setPos(10, 10);
}

void Game::mousePressEvent(QMouseEvent *event)
{
    Bullet *bullet = new Bullet();
    bullet->setPos(event->pos());
    scene->addItem(bullet);
}

void Game::generateMap()
{
    QPixmap mapGrid(":/images/tex/0.png");
    QPixmap pathGrid1(":/images/tex/1.png");
    QPixmap pathGrid2(":/images/tex/2.png");
    QPixmap pathGrid3(":/images/tex/3.png");

    int gridPixelSize = 48; //tamanho de cada parte do grid em pixels

    int grid[10][20] = {
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1},
        {0, 0, 1, 0, 0, 0, 1, 1, 1, 1, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0},
        {0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0},
        {0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0},
        {0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0},
        {0, 0, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    };

    for (int row = 0; row < 10; ++row) {
        for (int col = 0; col < 20; ++col) {
            QLabel *gridLabel = new QLabel(this);
            QPixmap pixmap;

            switch (grid[row][col]) {
            case 1:
                pixmap = pathGrid1;
                break;
            default:
                pixmap = mapGrid;
                break;
            }
            if (grid[row][col+1])
            {
                QTransform transform;
                transform.rotate(90);
                pixmap = pixmap.transformed(transform);
            }
            gridLabel->setPixmap(pixmap);
            gridLabel->setScaledContents(true);
            gridLabel->setFixedSize(gridPixelSize, gridPixelSize);
            gridLabel->move(col * gridPixelSize, row * gridPixelSize);
            gridLabel->show();
        }
    }

}
