#include <QGraphicsScene>
#include "Game.h"
#include "Tower.h"
#include "AcidTower.h"
#include "CapTower.h"
#include "ResTower.h"
#include "Bullet.h"
#include "Enemy.h"
#include <QTimer>

Game::Game() : QGraphicsView()
{
    // Create a scene
    scene = new QGraphicsScene(this);
    scene->setSceneRect(0, 0, 1280, 720);
    setScene(scene);

    setFixedSize(1280, 720);
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    setMouseTracking(true);
    mapGrid = QPixmap(":/images/tex/0.png");
    pathGrid1 = QPixmap(":/images/tex/1.png");
    pathGrid2 = QPixmap(":/images/tex/2.png");
    pathGrid3 = QPixmap(":/images/tex/3.png");
    gridPixelSize = 48;
    currentPathPixmapIndex = 1;
    selectedTower = nullptr;
    int tempGrid[10][20] =
        {
         {0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
         {0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1},
         {0, 0, 1, 0, 0, 0, 1, 1, 1, 1, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0},
         {0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0},
         {0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0},
         {0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0},
         {0, 0, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
         {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
         {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
         {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
         };
    // Copiar o conteúdo do tempGrid para o grid da classe
    for (int row = 0; row < 10; ++row) {
        for (int col = 0; col < 20; ++col) {
            grid[row][col] = tempGrid[row][col];
        }
    }
    generateMap();


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

    OptionsLabel->setAttribute(Qt::WA_TransparentForMouseEvents);
    bottomLabel->setAttribute(Qt::WA_TransparentForMouseEvents);

    QTimer * timer = new QTimer();
    connect(BuyCapTower, &QPushButton::clicked, this, &Game::buyCapTower);
    connect(BuyResTower, &QPushButton::clicked, this, &Game::buyResTower);
    connect(BuyAcidTower, &QPushButton::clicked, this, &Game::buyAcidTower);
    connect(timer, &QTimer::timeout, this, &Game::updatePathPixmap);
    timer->start(200);


    setRenderHint(QPainter::Antialiasing);
    setCacheMode(QGraphicsView::CacheBackground);
    setViewportUpdateMode(QGraphicsView::BoundingRectViewportUpdate);

    setFocus();

    // Criar inimigo teste
    Enemy *enemy = new Enemy(this);
    scene->addItem(enemy);

    Enemy *enemy1 = new Enemy(this);
    scene->addItem(enemy1);
}


void Game::buyCapTower() {
    qDebug() << "Cap Tower Button Clicked!";
    if (selectedTower) {
        delete selectedTower;  // Limpar torre anterior, se houver
    }
    selectedTower = new CapTower();
    scene->addItem(selectedTower);

    QPointF scenePos = mapToScene(QCursor::pos());
    selectedTower->setPos(scenePos - QPointF(selectedTower->boundingRect().width() / 2, selectedTower->boundingRect().height() / 2));
    selectedTower->setZValue(1);
}

void Game::buyResTower() {
    qDebug() << "Res Tower Button Clicked!";
    if (selectedTower) {
        delete selectedTower;
    }
    selectedTower = new ResTower();
    scene->addItem(selectedTower);
    QPointF scenePos = mapToScene(QCursor::pos());
    selectedTower->setPos(scenePos - QPointF(selectedTower->boundingRect().width() / 2, selectedTower->boundingRect().height() / 2));
}

void Game::buyAcidTower() {
    qDebug() << "Acid Tower Button Clicked!";
    if (selectedTower) {
        delete selectedTower;
    }
    selectedTower = new AcidTower();
    scene->addItem(selectedTower);
    QPointF scenePos = mapToScene(QCursor::pos());
    selectedTower->setPos(scenePos - QPointF(selectedTower->boundingRect().width() / 2, selectedTower->boundingRect().height() / 2));
}

void Game::mousePressEvent(QMouseEvent *event) {
    qDebug() << "Mouse pressed";
    if (event->button() == Qt::RightButton) {
        if (selectedTower) {
            delete selectedTower;  // Cancela a compra ao clicar com o botão direito
            selectedTower = nullptr;
            return;
        }
    }

    if (event->button() == Qt::LeftButton && selectedTower) {
        QPointF scenePos = mapToScene(event->pos());
        qDebug() << "Mouse Pressed at:" << scenePos;

        int row = scenePos.y() / gridPixelSize;
        int col = scenePos.x() / gridPixelSize;

        if (row >= 0 && row < 10 && col >= 0 && col < 20) {
            if (grid[row][col] != 1) {
                selectedTower->setPos(col * gridPixelSize, row * gridPixelSize);
                selectedTower = nullptr;  // Torre foi comprada
            }
        }
    }
}

void Game::mouseMoveEvent(QMouseEvent *event) {
    //qDebug() << "Mouse moved";
    if (selectedTower) {
        QPointF scenePos = mapToScene(event->pos());
        selectedTower->setPos(scenePos - QPointF(selectedTower->boundingRect().width() / 2, selectedTower->boundingRect().height() / 2));
        selectedTower->setZValue(2);
    }
}

void Game::generateMap() {
    pathPoints.clear();
    QPoint start(2, 0); // Ponto inicial do caminho (linha 0, coluna 2)

    // Algoritmo para rastrear o caminho na matriz e armazenar os pontos em ordem
    QPoint current = start;
    pathPoints.append(QPointF(current.x() * gridPixelSize, current.y() * gridPixelSize));

    while (true) {
        bool moved = false;

        // Cima
        if (current.y() > 0 && grid[current.y() - 1][current.x()] == 1 &&
            !pathPoints.contains(QPointF(current.x() * gridPixelSize, (current.y() - 1) * gridPixelSize))) {
            current.setY(current.y() - 1);
            moved = true;
        }
        // Baixo
        else if (current.y() < 9 && grid[current.y() + 1][current.x()] == 1 &&
                 !pathPoints.contains(QPointF(current.x() * gridPixelSize, (current.y() + 1) * gridPixelSize))) {
            current.setY(current.y() + 1);
            moved = true;
        }
        // Esquerda
        else if (current.x() > 0 && grid[current.y()][current.x() - 1] == 1 &&
                 !pathPoints.contains(QPointF((current.x() - 1) * gridPixelSize, current.y() * gridPixelSize))) {
            current.setX(current.x() - 1);
            moved = true;
        }
        // Direita
        else if (current.x() < 19 && grid[current.y()][current.x() + 1] == 1 &&
                 !pathPoints.contains(QPointF((current.x() + 1) * gridPixelSize, current.y() * gridPixelSize))) {
            current.setX(current.x() + 1);
            moved = true;
        }

        if (moved) {
            pathPoints.append(QPointF(current.x() * gridPixelSize, current.y() * gridPixelSize));
        } else {
            // Se não foi possível mover em nenhuma direção, significa que chegamos ao fim do caminho
            break;
        }
    }

    qDebug() << "Número de pontos no caminho:" << pathPoints.size();

    // Restante do código para desenhar o mapa
    for (int row = 0; row < 10; row++) {
        for (int col = 0; col < 20; col++) {
            QPixmap pixmap = (grid[row][col] == 1) ? pathGrid1 : mapGrid;
            QGraphicsPixmapItem* gridItem = new QGraphicsPixmapItem(pixmap);
            gridItem->setPos(col * gridPixelSize, row * gridPixelSize);
            gridItem->setZValue(-1);
            scene->addItem(gridItem);
            gridItems[row][col] = gridItem;
        }
    }
}



void Game::updatePathPixmap() {
    QPixmap newPixmap;
    switch (currentPathPixmapIndex) {
    case 1:
        newPixmap = pathGrid2;
        currentPathPixmapIndex = 2;
        break;
    case 2:
        newPixmap = pathGrid3;
        currentPathPixmapIndex = 3;
        break;
    case 3:
        newPixmap = pathGrid1;
        currentPathPixmapIndex = 1;
        break;
    }

    int index = 0;
    for (int row = 0; row < 10; ++row) {
        for (int col = 0; col < 20; ++col) {
            if (grid[row][col] == 1) {
                QPixmap pixmap = newPixmap;

                if (col < 19 && grid[row][col + 1] == 1) {
                    QTransform transform;
                    transform.rotate(-90);
                    pixmap = pixmap.transformed(transform);
                } else if (col > 0 && grid[row][col - 1] == 1) {
                    QTransform transform;
                    transform.rotate(90);
                    pixmap = pixmap.transformed(transform);
                }

                // Debug: Verifica a posição atualizada
                //qDebug() << "Updating path pixmap at position:" << row << "," << col;

                gridItems[row][col]->setPixmap(pixmap);
            }
        }
    }
}
