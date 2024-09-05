#ifndef MENU_H
#define MENU_H

#include <QMainWindow>
#include <QPushButton>
#include <QLabel>
#include <QVBoxLayout>

class Menu : public QMainWindow
{
    Q_OBJECT

public:
    explicit Menu(QWidget *parent = nullptr);
    ~Menu();

private slots:
    void onStartButtonClicked();     // Slot para o botão "Jogar"
    void onTutorialButtonClicked();  // Slot para o botão "Tutorial"
    void showMenu();

private:
    QPushButton *playButton;         // Botão "Jogar"
    QPushButton *tutorialButton;     // Botão "Tutorial"
    QLabel *backgroundLabel;         // Rótulo para a imagem de fundo
    QVBoxLayout *buttonLayout;       // Layout vertical para os botões
};

#endif // MENU_H
