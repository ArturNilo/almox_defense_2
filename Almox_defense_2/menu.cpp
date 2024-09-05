#include "menu.h"
#include "Game.h"
#include "Tutorial.h"
#include <QtWidgets>

Game *game;
Tutorial *tutorial;

Menu::Menu(QWidget *parent)
    : QMainWindow(parent)
{
    setFixedSize(1280, 720);
    showMenu();  // Chama a função para configurar o menu
}

Menu::~Menu()
{
}

void Menu::showMenu()
{
    // Criação do fundo como um QLabel
    backgroundLabel = new QLabel(this);
    backgroundLabel->setPixmap(QPixmap(":/images/tex/34.png"));
    backgroundLabel->setScaledContents(true);
    backgroundLabel->setFixedSize(1280, 720);

    // Configuração do botão "Jogar" com imagem
    playButton = new QPushButton(this);
    QPixmap playButtonPixmap(":/images/tex/28.png");
    playButton->setIcon(QIcon(playButtonPixmap));
    playButton->setIconSize(playButtonPixmap.size());
    playButton->setFixedSize(playButtonPixmap.size());
    playButton->setFlat(true);
    connect(playButton, &QPushButton::clicked, this, &Menu::onStartButtonClicked);

    // Configuração do botão "Tutorial" com imagem
    tutorialButton = new QPushButton(this);
    QPixmap tutorialButtonPixmap(":/images/tex/27.png");
    tutorialButton->setIcon(QIcon(tutorialButtonPixmap));
    tutorialButton->setIconSize(tutorialButtonPixmap.size());
    tutorialButton->setFixedSize(tutorialButtonPixmap.size());
    tutorialButton->setFlat(true);
    connect(tutorialButton, &QPushButton::clicked, this, &Menu::onTutorialButtonClicked);

    // Layout dos botões
    QVBoxLayout *buttonLayout = new QVBoxLayout;
    buttonLayout->addStretch(1);
    buttonLayout->addWidget(playButton, 0, Qt::AlignCenter);
    buttonLayout->addWidget(tutorialButton, 0, Qt::AlignCenter);
    buttonLayout->addStretch(1);

    QWidget *buttonContainer = new QWidget(this);
    buttonContainer->setLayout(buttonLayout);

    QGridLayout *layout = new QGridLayout;
    layout->addWidget(backgroundLabel, 0, 0);
    layout->addWidget(buttonContainer, 0, 0);

    QWidget *central = new QWidget(this);
    central->setLayout(layout);
    setCentralWidget(central);  // Aplica o layout ao widget central
}

void Menu::onStartButtonClicked()
{
    game = new Game();
    setCentralWidget(game);  // Substitui o menu pelo jogo
}

void Menu::onTutorialButtonClicked()
{
    tutorial = new Tutorial();
    setCentralWidget(tutorial);  // Substitui o menu pelo tutorial

    // Conecta o sinal "returnToMenu" do tutorial ao slot "showMenu"
    connect(tutorial, &Tutorial::returnToMenu, this, &Menu::showMenu);
}
