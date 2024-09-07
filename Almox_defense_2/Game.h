#ifndef GAME_H
#define GAME_H

#include <QGraphicsView>
#include <QMouseEvent>
#include <QPushButton>
#include <Qlabel.h>

class Game: public QGraphicsView{
public:
    Game();
    void mousePressEvent(QMouseEvent *event);

    QGraphicsScene * scene;
private:
    QPushButton *BuyCapTower;
    QPushButton *BuyResTower;
    QPushButton *BuyAcidTower;
    QLabel *OptionsLabel;
    QLabel *BottomLabel;
};

#endif // GAME_H
