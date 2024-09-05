// Tutorial.h
#ifndef TUTORIAL_H
#define TUTORIAL_H

#include <QGraphicsView>
#include <QMouseEvent>
#include <QPushButton>
#include <QLabel>
#include <QGraphicsScene>

class Tutorial : public QGraphicsView {
    Q_OBJECT  // Adicione esta macro para suportar slots

public:
    Tutorial();
    ~Tutorial();

private slots:
    void returnButtonClicked();     // Slot para o botão "Voltar"
signals:
    void returnToMenu();
private:
    QGraphicsScene *scene;
    QPushButton *returnButton;      // Botão "Voltar"
    QLabel *backgroundLabel;        // Rótulo para a imagem de fundo
};

#endif // TUTORIAL_H
