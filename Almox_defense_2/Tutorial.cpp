// Tutorial.cpp
#include "Tutorial.h"

Tutorial::Tutorial() : QGraphicsView() {
    scene = new QGraphicsScene(this);
    scene->setSceneRect(0, 0, 1280, 720);

    setScene(scene);
    setFixedSize(1280, 720);

    // Criação do fundo como um QLabel
    backgroundLabel = new QLabel(this);
    backgroundLabel->setPixmap(QPixmap(":/images/tex/46.png"));
    backgroundLabel->setScaledContents(true);
    backgroundLabel->setFixedSize(1280, 720);  // Tamanho do fundo igual ao da janela

    // Configuração do botão "Voltar" com imagem
    returnButton = new QPushButton(this);
    QPixmap returnButtonPixmap(":/images/tex/43.png");
    returnButton->setIcon(QIcon(returnButtonPixmap));
    returnButton->setIconSize(returnButtonPixmap.size());
    returnButton->setFixedSize(returnButtonPixmap.size());
    returnButton->setFlat(true);

    // Posicione o botão no centro ou em qualquer outro lugar desejado
    returnButton->move(1160, 600);  // Exemplo: mover para a posição (100, 100)

    // Conectar o sinal do botão ao slot
    connect(returnButton, &QPushButton::clicked, this, &Tutorial::returnButtonClicked);
}

Tutorial::~Tutorial()
{
}

void Tutorial::returnButtonClicked() {
    emit returnToMenu();  // Emite o sinal para retornar ao menu
}
