#include "startwindow.h"
#include "ui_startwindow.h"

//Default Constructor
StartWindow::StartWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::StartWindow)
{
    ui->setupUi(this);
}

//Declare static variable
int StartWindow::nPlayers = 0;

//Destructor
StartWindow::~StartWindow()
{
    delete ui;
}

//Sets up the game for singleplayer
void StartWindow::singleplayerClick(){
    nPlayers = 1;
    this->hide();
    game.show();
    MainWindow::launch = true;
    game.aiShips();
}

//Sets up game for multiplayer
void StartWindow::multiplayerClick(){
    nPlayers = 2;
    this->hide();
    game.show();
    MainWindow::launch = true;
}
