#ifndef GAME_H
#define GAME_H

#include <QGraphicsView>
#include <QMouseEvent>
#include <QPushButton>
#include <Qlabel.h>
#include "Tower.h"

class Game: public QGraphicsView{
    Q_OBJECT
public:
    Game();
    QGraphicsScene * scene;
protected:
    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;

private:
    QPushButton *BuyCapTower;
    QPushButton *BuyResTower;
    QPushButton *BuyAcidTower;
    QLabel *OptionsLabel;
    QLabel *BottomLabel;
    QGraphicsPixmapItem* gridItems[10][20];
    int grid[10][20];
    int gridPixelSize;
    int pathSize;
    int currentPathPixmapIndex;  // Índice para controlar qual pixmap está sendo exibido
    int initColumn;
    int finalRow;
    QPointF pathPoints[10][20];
    Tower *selectedTower;

    QPixmap mapGrid;
    QPixmap pathGrid1;
    QPixmap pathGrid2;
    QPixmap pathGrid3;
private slots:
    void generateMap();
    void updatePathPixmap();
    void buyCapTower();
    void buyResTower();
    void buyAcidTower();

};

#endif // GAME_H
