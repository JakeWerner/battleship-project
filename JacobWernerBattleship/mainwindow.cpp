#include <QDebug>
#include <QtWidgets>
#include <QGraphicsItem>
#include <QGraphicsView>
#include <QGraphicsScene>
#include "mainwindow.h"
#include "startwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    srand(time(NULL));
    p1Grid = new QGraphicsScene;
    p2Grid = new QGraphicsScene;
    QGraphicsView *p1GridV = ui->p1UI;  //CHECK THIS
    QGraphicsView *p2GridV = ui->p2UI;  //CHECK THIS

    //Set up player 1 grid variables
    tileWidth = p1GridV->frameSize().width();
    int tileWidth2 = tileWidth/10;
    tileHeight = p1GridV->frameSize().height();
    int tileHeight2 = tileHeight/10;
    p1GridV->setScene(p1Grid);
    p1GridV->setSceneRect(0, 0, tileWidth, tileHeight);

    //Set up player 1 grid
    for(int i = 0; i < 10; i++){
        for(int j = 0; j < 10; j++){
            Tile *nTile = new Tile(j, i, tileWidth2, tileHeight2, 1);
            p1Tiles[i][j] = nTile;
            p1Grid->addItem(nTile);
            connect(nTile, &Tile::tScoreBoard, this, &MainWindow::scoreChangeSlot);
            connect(nTile, &Tile::tTorpedo, this, &MainWindow::TorpedoSlot);
            connect(nTile, &Tile::tdCharge, this, &MainWindow::DepthChargeSlot);
            connect(nTile, &Tile::yClick, this, &MainWindow::click);
        }
    }

    //Set up player 2 grid variables
    tileWidth = p2GridV->frameSize().width();
    tileWidth2 = tileWidth/10;
    tileHeight = p2GridV->frameSize().height();
    tileHeight2 = tileHeight/10;
    p2GridV->setScene(p2Grid);
    p2GridV->setSceneRect(0, 0, tileWidth, tileHeight);

    //Set up player 2 grid
    for(int i = 0; i < 10; i++){
        for(int j = 0; j < 10; j++){
            Tile *nTile = new Tile(j, i, tileWidth2, tileHeight2, 2);
            p2Tiles[i][j] = nTile;
            p2Grid->addItem(nTile);
            connect(nTile, &Tile::tScoreBoard, this, &MainWindow::scoreChangeSlot);
            connect(nTile, &Tile::tTorpedo, this, &MainWindow::TorpedoSlot);
            connect(nTile, &Tile::tdCharge, this, &MainWindow::DepthChargeSlot);
            connect(nTile, &Tile::yClick, this, &MainWindow::click);
        }
    }

    graphUI = new QGraphicsScene;
    QGraphicsView *graphV = ui->scorebar;       //CHECK THIS
    graphV->setScene(graphUI);
    graphV->setSceneRect(0, 0, graphV->frameSize().width(), graphV->frameSize().height());
    graphH = graphV->frameSize().height();
    graphY = graphH-2;

}

bool MainWindow::launch = false;

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::p1CruClick(){
    Tile::buttonClick = 2;
    ui->p1Cru->setEnabled(false);
}

void MainWindow::p2CruClick(){
    Tile::buttonClick = 2;
    ui->p2Cru->setEnabled(false);
}

void MainWindow::p1BtlClick(){
    Tile::buttonClick = 4;
    ui->p1Btl->setEnabled(false);
}

void MainWindow::p2BtlClick(){
    Tile::buttonClick = 4;
    ui->p2Btl->setEnabled(false);
}

void MainWindow::p1SubClick(){
    Tile::buttonClick = 3;
    ui->p1Sub->setEnabled(false); //CHECK THIS
}

void MainWindow::p2SubClick(){
    Tile::buttonClick = 3;
    ui->p2Sub->setEnabled(false); //CHECK THIS
}

void MainWindow::p1DestClick(){
    Tile::buttonClick = 3;
    ui->p1Dest->setEnabled(false); //CHECK THIS
}

void MainWindow::p2DestClick(){
    Tile::buttonClick = 3;
    ui->p2Dest->setEnabled(false); //CHECK THIS
}

void MainWindow::p1CarrClick(){
    Tile::buttonClick = 5;
    ui->p1Carrier->setEnabled(false);
}

void MainWindow::p2CarrClick(){
    Tile::buttonClick = 5;
    ui->p2Carrier->setEnabled(false);
}

void MainWindow::p1EndSetup(){
    hidep1();
    p1Hidden = true;
    ui->p1Done->setEnabled(false);  //CHECK THIS
}

void MainWindow::p2EndSetup(){
    int i = 0;
    int i2 = 0;
    if(MainWindow::launch){
        if(StartWindow::nPlayers == 1){
            p1 = new Player();
            ai = new AI();
        }
        else if(StartWindow::nPlayers ==  2){
            p1 = new Player();
            p2 = new Player();
        }
        MainWindow::launch = false;
    }
    if(StartWindow::nPlayers == 2){
        p1->Player::setTurn(1);
        i = p1->getTurn();
        ui->turn1->setText("Turns: " + QString::number(i));
    }
    else{
        p2->Player::setTurn(1);
        ai->AI::setTurn(0);
        i = p2->getTurn();
        i2 = ai->getTurn();
        ui->turn2->setText("Turns: " + QString::number(i));
        ui->turn1->setText("Turns: " + QString::number(i2));
    }

    hidep2();
    p2Hidden = true;
    ui->p2Done->setEnabled(false);   //CHECK THIS
}

void MainWindow::hidep1(){
    qDebug() << "hidep1";
    QColor color(77, 166, 255);
    for(int i = 0; i < 10; i++){
        for(int j = 0; j < 10; j++){
            p1Tiles[i][j]->setColor(color);
        }
    }
    //ui->p1UI->setScene(p1Grid);
    Tile::game1 = true;
    ui->p1UI->update();
}

void MainWindow::hidep2(){
    qDebug() << "hidep2";
    QColor color(77, 166, 255);
    for(int i = 0; i < 10; i++){
        for(int j = 0; j < 10; j++){
            p2Tiles[i][j]->setColor(color);
        }
    }
    //ui->p2UI->setScene(p2Grid);
    Tile::game2 = true;
    ui->p2UI->update();
}

void MainWindow::p1TorpClick(){
    Tile::torpedoSelect = true;
}

void MainWindow::p2TorpClick(){
    Tile::torpedoSelect = true;
}

void MainWindow::p1DcgeClick(){
    Tile::dChargeSelect = true;
}

void MainWindow::p2DcgeClick(){
    Tile::dChargeSelect = true;
}

void MainWindow::scoreChangeSlot(){
    qDebug() << "scoreChangeslot";
    ui->p1Score->setText(QString::number(Tile::player2Score));
    ui->p2Score->setText(QString::number(Tile::player1Score));
    ui->p1TorpedoCount->setText(QString::number(Tile::player2Torpedo));
    ui->p2TorpedoCount->setText(QString::number(Tile::player1Torpedo));
    ui->p1dChargeCount->setText(QString::number(Tile::player2dCharge));
    ui->p2dChargeCount->setText(QString::number(Tile::player1dCharge));
    winCount();
}

void MainWindow::winCount(){
    qDebug() << "winCount";
    if(Tile::player1Score == 17){
        score1 += 1;
        Graph *nGraph = new Graph(100, graphY, score1);
        QMessageBox::information(this, tr("Game Over"), tr("Player 2 Wins!"));
        graphs.push_back(nGraph);
        graphUI->addItem(nGraph);
        ui->p1WinCount->setText("Player 2: " + QString::number(score1));
        if(StartWindow::nPlayers == 1){
            ui->p2WinCount->setText("AI: " + QString::number(score2));
        }
        else{
            ui->p2WinCount->setText("Player 1: " + QString::number(score2));
        }
    }

    else if(Tile::player2Score == 17){
        score2 += 1;
        Graph *nGraph = new Graph(50, graphY, score2);
        graphs.push_back(nGraph);
        graphUI->addItem(nGraph);
        if(StartWindow::nPlayers == 1){
            ui->p2WinCount->setText("AI: " + QString::number(score2));
            QMessageBox::information(this, tr("Game Over"),tr("AI Wins!"));
        }
        else{
            ui->p2WinCount->setText("Player 1: " + QString::number(score2));
            QMessageBox::information(this, tr("Game Over"), tr("Player 1 Wins!"));
        }

    }
}

void MainWindow::restartButtonSlot(){
    int tileWidth2 = tileWidth/10;
    int tileHeight2 = tileHeight/10;
    //If multiplayer game
    if(StartWindow::nPlayers == 2){
        p1Grid->clear();
        p2Grid->clear();

        //Reset player 1
        Tile::player1Score = 0;
        Tile::player1Torpedo = 0;
        Tile::player1dCharge = 0;
        Tile::game1 = false;
        for(int i = 0; i < 10; i++){
            for(int j = 0; j < 10; j++){
                Tile *nTile = new Tile(j, i, tileWidth2, tileHeight2, 1);
                p1Tiles[i][j] = nTile;
                p1Grid->addItem(nTile);
                connect(nTile, &Tile::tScoreBoard, this, &MainWindow::scoreChangeSlot);
                connect(nTile, &Tile::tTorpedo, this, &MainWindow::TorpedoSlot);
                connect(nTile, &Tile::tdCharge, this, &MainWindow::DepthChargeSlot);
                connect(nTile, &Tile::yClick, this, &MainWindow::click);
            }
        }
        ui->turn1->setText("Turns: "+ QString::number(0));

        //Reset player 2
        Tile::player1Score = 0;
        Tile::player2Torpedo = 0;
        Tile::player2dCharge = 0;
        Tile::game2 = false;
        ui->turn2->setText("Turns: "+ QString::number(0));
        for(int i = 0; i < 10; i++){
            for(int j = 0; j < 10; j++){
                Tile *nTile = new Tile(j, i, tileWidth2, tileHeight2, 2);
                p2Tiles[i][j] = nTile;
                p2Grid->addItem(nTile);
                connect(nTile, &Tile::tScoreBoard, this, &MainWindow::scoreChangeSlot);
                connect(nTile, &Tile::tTorpedo, this, &MainWindow::TorpedoSlot);
                connect(nTile, &Tile::tdCharge, this, &MainWindow::DepthChargeSlot);
                connect(nTile, &Tile::yClick, this, &MainWindow::click);
            }
        }
        ui->p1Sub->setEnabled(true);
        ui->p2Sub->setEnabled(true);
        ui->p1Dest->setEnabled(true);
        ui->p2Dest->setEnabled(true);
        ui->p1Carrier->setEnabled(true);
        ui->p2Carrier->setEnabled(true);
        ui->p1Cru->setEnabled(true);
        ui->p2Cru->setEnabled(true);
        ui->p1Btl->setEnabled(true);
        ui->p2Btl->setEnabled(true);
        ui->p1Done->setEnabled(true);
        ui->p2Done->setEnabled(true);
    }
    //If singleplayer game
    else{
        p1Grid->clear();
        aiShips();
        Tile::player1Score = 0;
        Tile::player2Score = 0;
        Tile::player1Torpedo = 0;
        Tile::player2Torpedo = 0;
        Tile::player1dCharge = 0;
        Tile::player2dCharge = 0;
        Tile::game1 = true;
        Tile::game2 = false;
        ui->turn1->setText("Turns: " + QString::number(0));
        ui->turn2->setText("Turns: " + QString::number(0));

        for(int i = 0; i < 10; i++){
            for(int j = 0; j < 10; j++){
                Tile *nTile = new Tile(j, i, tileWidth2, tileHeight2, 1);
                p1Tiles[i][j] = nTile;
                p1Grid->addItem(nTile);
                connect(nTile, &Tile::tScoreBoard, this, &MainWindow::scoreChangeSlot);
                connect(nTile, &Tile::tTorpedo, this, &MainWindow::TorpedoSlot);
                connect(nTile, &Tile::tdCharge, this, &MainWindow::DepthChargeSlot);
                connect(nTile, &Tile::yClick, this, &MainWindow::click);
            }
        }
        ui->p1Sub->setEnabled(true);
        ui->p1Dest->setEnabled(true);
        ui->p1Carrier->setEnabled(true);
        ui->p1Cru->setEnabled(true);
        ui->p1Btl->setEnabled(true);
        ui->p1Done->setEnabled(true);
    }
    update();
}

void MainWindow::click(){
    qDebug() << "click()";
    int i = 0;
    int i1 = 0;

    //If multiplayer
    if(StartWindow::nPlayers == 2){
        //Turn for player 1
        if(p1->getTurn() > 0){
            p1->Player::setTurn(-1);
            i = p1->getTurn();
            if(i == 0){
                p2->Player::setTurn(1);
                i1 = p2->getTurn();
                ui->turn2->setText("Turns: " + QString::number(i1));
            }
            ui->turn1->setText("Turns: " + QString::number(i));
        }
        //Turn for player 2
        else if(p2->getTurn() > 0){
            p2->Player::setTurn(-1);
            i = p2->getTurn();
            if(i == 0){
                p1->Player::setTurn(1);
                i1 = p1->getTurn();
                ui->turn1->setText("Turns: " + QString::number(i1));
            }
            ui->turn2->setText("Turns: " + QString::number(i));
        }
    }

    //Else singleplayer
    else{
        //If AI turn
        if(ai->getTurn() > 0){
            this->aiTurn();
            ai->AI::setTurn(-1);
            i = ai->getTurn();
            p1->Player::setTurn(1);
            i1 = p1->getTurn();
            ui->turn1->setText("Turns: " + QString::number(i));
            ui->turn2->setText("Turns: " + QString::number(i1));
        }
        //Else if player turn
        else if(p1->getTurn() > 0){
            p1->Player::setTurn(-1);
            i = p1->getTurn();
            if(i == 0){
                ai->Player::setTurn(1);
                i1 = ai->getTurn();
                ui->turn1->setText("Turns: " + QString::number(i1));
            }
            ui->turn2->setText("Turns: " + QString::number(i));
            this->update();
            this->aiTurn();
        }
    }
    this->update();
}

void MainWindow::aiShips(){
    qDebug() << "AI ships func";
    ui->label_2->setText("AI");
    ui->p2WinCount->setText("AI: ");

    //Carrier Setup
    int rand1 = rand() % 10;
    int rand2 = rand() % 10;
    int tmp = rand2;
    p2Tiles[rand2][rand1]->t = TileType::Ship;
    if(rand2 >= 4){
        p2Tiles[rand2-1][rand1]->t = TileType::Ship;
        p2Tiles[rand2-2][rand1]->t = TileType::Ship;
        p2Tiles[rand2-3][rand1]->t = TileType::Ship;
        p2Tiles[rand2-4][rand1]->t = TileType::Ship;
    }

    else{
        p2Tiles[rand2+1][rand1]->t = TileType::Ship;
        p2Tiles[rand2+2][rand1]->t = TileType::Ship;
        p2Tiles[rand2+3][rand1]->t = TileType::Ship;
        p2Tiles[rand2+4][rand1]->t = TileType::Ship;
    }

    //Submarine Setup

    //Check to ensure coordinate is empty, if not then continue to randomly generate tiles
    while(p2Tiles[rand2][rand1]->t == TileType::Ship){
        rand1 = rand() % 10;
        rand2 = rand() % 10;
    }

    //If the coordinate is in the left most column
    if(rand1 <= 2){
        //If there is a boat to the right of the coordinate already
        if(p2Tiles[rand2][rand2+1]->t != TileType::Ship && p2Tiles[rand2][rand2 + 2]->t != TileType::Ship){
            p2Tiles[rand2][rand2+1]->t = TileType::Ship;
            p2Tiles[rand2][rand2+2]->t = TileType::Ship;
        }
        //If the coordinate's row is less than 7, place the ship in increasing order
        else if(tmp <= 7){
            p2Tiles[rand2 + 1][rand1]->t = TileType::Ship;
            p2Tiles[rand2 + 2][rand1]->t = TileType::Ship;
        }
        //If the coordinate's row is more than 7, place the ship in decreasing order
        else{
            p2Tiles[rand2 - 1][rand1]->t = TileType::Ship;
            p2Tiles[rand2 - 2][rand1]->t = TileType::Ship;
        }
    }

    //If not in the left most column
    else{
        //If there is a boat to the left of the coordinate already
        if(p2Tiles[rand2][rand1-1]->t != TileType::Ship && p2Tiles[rand2][rand1]->t != TileType::Ship){
            p2Tiles[rand2][rand1-1]->t = TileType::Ship;
            p2Tiles[rand2][rand1-2]->t = TileType::Ship;
        }

        else if(tmp <= 7){
            p2Tiles[rand2+1][rand1]->t = TileType::Ship;
            p2Tiles[rand2+2][rand1]->t = TileType::Ship;
        }

        else{
            p2Tiles[rand2-1][rand1]->t = TileType::Ship;
            p2Tiles[rand2-2][rand1]->t = TileType::Ship;
        }
    }

    //Destroyer Setup
    while(p2Tiles[rand2][rand1]->t == TileType::Ship){
        rand1 = rand() % 10;
        rand2 = rand() % 10;
    }

    if(rand1 <= 2){
        //If there is a boat to the right of the coordinate already
        if(p2Tiles[rand2][rand2+1]->t != TileType::Ship && p2Tiles[rand2][rand2 + 2]->t != TileType::Ship){
            p2Tiles[rand2][rand2+1]->t = TileType::Ship;
            p2Tiles[rand2][rand2+2]->t = TileType::Ship;
        }
        //If the coordinate's row is less than 7, place the ship in increasing order
        else if(tmp <= 7){
            p2Tiles[rand2 + 1][rand1]->t = TileType::Ship;
            p2Tiles[rand2 + 2][rand1]->t = TileType::Ship;
        }
        //If the coordinate's row is more than 7, place the ship in decreasing order
        else{
            p2Tiles[rand2 - 1][rand1]->t = TileType::Ship;
            p2Tiles[rand2 - 2][rand1]->t = TileType::Ship;
        }
    }

    //If not in the left most column
    else{
        //If there is a boat to the left of the coordinate already
        if(p2Tiles[rand2][rand1-1]->t != TileType::Ship && p2Tiles[rand2][rand1]->t != TileType::Ship){
            p2Tiles[rand2][rand1-1]->t = TileType::Ship;
            p2Tiles[rand2][rand1-2]->t = TileType::Ship;
        }

        else if(tmp <= 7){
            p2Tiles[rand2+1][rand1]->t = TileType::Ship;
            p2Tiles[rand2+2][rand1]->t = TileType::Ship;
        }

        else{
            p2Tiles[rand2-1][rand1]->t = TileType::Ship;
            p2Tiles[rand2-2][rand1]->t = TileType::Ship;
        }
    }

    Tile::game2 = true;
    hidep2();
    p2Hidden = true;
    ui->p2Done->setEnabled(false);
}

void MainWindow::aiTurn(){
    int rand1 = rand() % 10;
    int rand2 = rand() % 10;
    while(p1Tiles[rand2][rand1]->getColor() == QColor(77, 166, 255) || p1Tiles[rand2][rand1]->getColor() == QColor(255, 0, 0)){
        rand1 = rand() % 10;
        rand2 = rand() % 10;
    }
    //If the AI lands a hit
    if(p1Tiles[rand2][rand1]->t == TileType::Ship){
        p1Tiles[rand2][rand1]->setColor(QColor(255, 0, 0));
        p1Tiles[rand2][rand1]->hit = true;
        Tile::player2Score++;
        this->update();
        this->scoreChangeSlot();
    }
    //If the AI hits a depth charge powerup
    if(p1Tiles[rand2][rand1]->t == TileType::DCharge){
        p1Tiles[rand2][rand1]->setColor(QColor(77, 166, 255));
        this->DepthChargeSlot(p1Tiles[rand2][rand1]);
        this->update();
    }
    //If the AI hits a torpedo powerup
    if(p1Tiles[rand2][rand1]->t == TileType::Torpedo){
        p1Tiles[rand2][rand1]->setColor(QColor(77, 166, 255));
        this->TorpedoSlot(p1Tiles[rand2][rand1]);
        this->update();
    }
    //Else if the AI misses
    else if(p1Tiles[rand2][rand1]->t == TileType::Empty){
        p1Tiles[rand2][rand1]->setColor(QColor(77, 166, 255));
        this->update();
    }
    ai->setTurn(-1);
    int i = ai->getTurn();
    ui->turn2->setText("Turns: " + QString::number(i));
    p1->setTurn(1);
    int i1 = p1->getTurn();
    ui->turn1->setText("Turns: " + QString::number(i1));
    this->update();
}

void MainWindow::TorpedoSlot(Tile *ti){
    qDebug() << "TorpedoSlot";
    int x = ti->getX();
    int y = ti->getY();
    int w = ti->getW();
    int h = ti->getH();
    x = x/w;
    y = y/h;

    Tile *tmp = new Tile(0, 0, w/10, h/10, 1);
    //If the selected tile is on the last row
    if(y == 9){
        //If the grid is set to player1
        if(ti->grid == 1){
            //If miss
            if(ti->t != TileType::Ship){
                ti->setColor(QColor(255, 255, 255));
            }
            //If hit
            else{
                ti->setColor(QColor(255, 0, 0));
                Tile::player1Score++;
            }
        }
        //If the grid is set to player 2
        else{
            //If miss
            if(ti->t != TileType::Ship){
                ti->setColor(QColor(255, 255, 255));
            }
            //If hit
            else{
                ti->setColor(QColor(255, 0, 0));
                Tile::player2Score++;
            }
        }
    }

    else{
        //If grid is set to player 1
        if(ti->grid == 1){
            //If miss
            if(ti->t != TileType::Ship){
                ti->setColor(QColor(255, 255, 255));
            }
            //If hit
            else{
                ti->setColor(QColor(255, 0, 0));
                Tile::player1Score++;
            }
            //Get the next tile (since the torpedo hits two tiles
            tmp = p1Tiles[y-1][x];
            //If the next tile is a miss
            if(tmp->t != TileType::Ship){
                tmp->setColor(QColor(255, 255, 255));
            }
            //If the next tile is a hit
            else{
                //If the tile isnt already painted as hit
                if(tmp->getColor() != QColor(255, 0, 0)){
                    tmp->setColor(QColor(255, 0, 0));
                    Tile::player1Score++;
                }
            }
        }
        else{
            //If miss
            if(ti->t != TileType::Ship){
                ti->setColor(QColor(255, 255, 255));
            }
            //If hit
            else{
                ti->setColor(QColor(255, 0, 0));
                Tile::player2Score++;
            }
            //Get the next tile (since the torpedo hits two tiles
            tmp = p2Tiles[y-1][x];
            //If the next tile is a miss
            if(tmp->t != TileType::Ship){
                tmp->setColor(QColor(255, 255, 255));
            }
            //If the next tile is a hit
            else{
                //If the tile isnt already painted as hit
                if(tmp->getColor() != QColor(255, 0, 0)){
                    tmp->setColor(QColor(255, 0, 0));
                    Tile::player2Score++;
                }
            }
        }
    }
    torpedoSelect = false;
    scoreChangeSlot();
    delete tmp;
    qDebug() << "End Torpedo Slot";
}

void MainWindow::DepthChargeSlot(Tile *it){
    qDebug() << "DepthChargeSlot";
    int x = it->getX();
    int y = it->getY();
    int w = it->getW();
    int h = it->getH();
    x = x/w;
    y = y/h;
    Tile *tmp = new Tile(0, 0, w/10, h/10, 1);
    //Check if the tile is not in the corner or the edge
    if(x > 0 && x < 9 && y > 0 && y < 9){
        //Check if the grid is set to player 1
        if(it->grid == 1){
            //Check if there is a ship at the designated tile
            if(it->t != TileType::Ship){
                it->setColor(QColor(255, 255, 255));
            }
            else{
                it->setColor(QColor(255, 0, 0));
                Tile::player1Score++;
            }
            //Check the tile below the coordinate
            tmp = p1Tiles[y][x-1];
            if(tmp->t != TileType::Ship){
                tmp->setColor(QColor(255,255,255));
            }
            else{
                if(tmp->getColor()!= QColor(255, 0, 0)){
                    tmp->setColor(QColor(255,0,0));
                    Tile::player1Score++;
                }
            }
            //Check the tile above the coordinate
            tmp = p1Tiles[y][x+1];
            if(tmp->t != TileType::Ship){
                tmp->setColor(QColor(255,255,255));
            }
            else{
                if(tmp->getColor()!= QColor(255, 0, 0)){
                    tmp->setColor(QColor(255,0,0));
                    Tile::player1Score++;
                }
            }

            //Check the tile to the left of the coordinate
            tmp = p1Tiles[y-1][x];
            if(tmp->t != TileType::Ship){
                tmp->setColor(QColor(255,255,255));
            }
            else{
                if(tmp->getColor()!= QColor(255, 0, 0)){
                    tmp->setColor(QColor(255,0,0));
                    Tile::player1Score++;
                }
            }

            //Check the tile to the right of the coordinate
            tmp = p1Tiles[y+1][x];
            if(tmp->t != TileType::Ship){
                tmp->setColor(QColor(255,255,255));
            }
            else{
                if(tmp->getColor()!= QColor(255, 0, 0)){
                    tmp->setColor(QColor(255,0,0));
                    Tile::player1Score++;
                }
            }
            //2;
        }

        //If the grid is set to player 2
        else{
            //Check if there is a ship at the designated tile
            if(it->t != TileType::Ship){
                it->setColor(QColor(255, 255, 255));
            }
            else{
                it->setColor(QColor(255, 0, 0));
                Tile::player2Score++;
            }
            //Check the tile below the coordinate
            tmp = p1Tiles[y][x-1];
            if(tmp->t != TileType::Ship){
                tmp->setColor(QColor(255,255,255));
            }
            else{
                if(tmp->getColor() != QColor(255, 0, 0)){
                    tmp->setColor(QColor(255,0,0));
                    Tile::player2Score++;
                }
            }
            //Check the tile above the coordinate
            tmp = p1Tiles[y][x+1];
            if(tmp->t != TileType::Ship){
                tmp->setColor(QColor(255,255,255));
            }
            else{
                if(tmp->getColor()!= QColor(255, 0, 0)){
                    tmp->setColor(QColor(255,0,0));
                    Tile::player2Score++;
                }
            }

            //Check the tile to the left of the coordinate
            tmp = p1Tiles[y-1][x];
            if(tmp->t != TileType::Ship){
                tmp->setColor(QColor(255,255,255));
            }
            else{
                if(tmp->getColor()!= QColor(255, 0, 0)){
                    tmp->setColor(QColor(255,0,0));
                    Tile::player2Score++;
                }
            }

            //Check the tile to the right of the coordinate
            tmp = p1Tiles[y+1][x];
            if(tmp->t != TileType::Ship){
                tmp->setColor(QColor(255,255,255));
            }
            else{
                if(tmp->getColor()!= QColor(255, 0, 0)){
                    tmp->setColor(QColor(255,0,0));
                    Tile::player2Score++;
                }
            }
            //1;
        }
    }

    //Corner case 1
    else if(x == 0 && y == 9){
        //If the grid is set to player 1
        if(it->grid == 1){
            //Check if the selected tile is a hit
            if(tmp->t != TileType::Ship){
                tmp->setColor(QColor(255,255,255));
            }
            else{
                if(tmp->getColor()!= QColor(255, 0, 0)){
                    tmp->setColor(QColor(255,0,0));
                    Tile::player1Score++;
                }
            }
            //Check if the tile to the left is a hit
            tmp = p1Tiles[y-1][x];
            if(tmp->t != TileType::Ship){
                tmp->setColor(QColor(255,255,255));
            }
            else{
                if(tmp->getColor()!= QColor(255, 0, 0)){
                    tmp->setColor(QColor(255,0,0));
                    Tile::player1Score++;
                }
            }

            //Check the tile above the coordinate
            tmp = p1Tiles[y][x+1];
            if(tmp->t != TileType::Ship){
                tmp->setColor(QColor(255,255,255));
            }
            else{
                if(tmp->getColor()!= QColor(255, 0, 0)){
                    tmp->setColor(QColor(255,0,0));
                    Tile::player1Score++;
                }
            }
            //2;
        }
        //If the grid is set to player 2
        else{
            //Check if the selected tile is a hit
            if(tmp->t != TileType::Ship){
                tmp->setColor(QColor(255,255,255));
            }
            else{
                if(tmp->getColor()!= QColor(255, 0, 0)){
                    tmp->setColor(QColor(255,0,0));
                    Tile::player2Score++;
                }
            }
            //Check if the tile to the left is a hit
            tmp = p1Tiles[y-1][x];
            if(tmp->t != TileType::Ship){
                tmp->setColor(QColor(255,255,255));
            }
            else{
                if(tmp->getColor()!= QColor(255, 0, 0)){
                    tmp->setColor(QColor(255,0,0));
                    Tile::player2Score++;
                }
            }

            //Check the tile above the coordinate
            tmp = p1Tiles[y][x+1];
            if(tmp->t != TileType::Ship){
                tmp->setColor(QColor(255,255,255));
            }
            else{
                if(tmp->getColor()!= QColor(255, 0, 0)){
                    tmp->setColor(QColor(255,0,0));
                    Tile::player2Score++;
                }
            }
            //1;
        }
    }

    //Corner Case 2
    else if(x == 0 && y == 9){
        //If the grid is set to player 1
        if(it->grid == 1){
            //Check if the selected tile is a hit
            if(tmp->t != TileType::Ship){
                tmp->setColor(QColor(255,255,255));
            }
            else{
                if(tmp->getColor()!= QColor(255, 0, 0)){
                    tmp->setColor(QColor(255,0,0));
                    Tile::player1Score++;
                }
            }
            //Check if the tile to the right is a hit
            tmp = p1Tiles[y+1][x];
            if(tmp->t != TileType::Ship){
                tmp->setColor(QColor(255,255,255));
            }
            else{
                if(tmp->getColor()!= QColor(255, 0, 0)){
                    tmp->setColor(QColor(255,0,0));
                    Tile::player1Score++;
                }
            }

            //Check the tile above the coordinate
            tmp = p1Tiles[y][x+1];
            if(tmp->t != TileType::Ship){
                tmp->setColor(QColor(255,255,255));
            }
            else{
                if(tmp->getColor()!= QColor(255, 0, 0)){
                    tmp->setColor(QColor(255,0,0));
                    Tile::player1Score++;
                }
            }
            //2;
        }
        //If the grid is set to player 2
        else{
            //Check if the selected tile is a hit
            if(tmp->t != TileType::Ship){
                tmp->setColor(QColor(255,255,255));
            }
            else{
                if(tmp->getColor()!= QColor(255, 0, 0)){
                    tmp->setColor(QColor(255,0,0));
                    Tile::player2Score++;
                }
            }
            //Check if the tile to the right is a hit
            tmp = p1Tiles[y+1][x];
            if(tmp->t != TileType::Ship){
                tmp->setColor(QColor(255,255,255));
            }
            else{
                if(tmp->getColor()!= QColor(255, 0, 0)){
                    tmp->setColor(QColor(255,0,0));
                    Tile::player2Score++;
                }
            }

            //Check the tile above the coordinate
            tmp = p1Tiles[y][x+1];
            if(tmp->t != TileType::Ship){
                tmp->setColor(QColor(255,255,255));
            }
            else{
                if(tmp->getColor()!= QColor(255, 0, 0)){
                    tmp->setColor(QColor(255,0,0));
                    Tile::player2Score++;
                }
            }
            //1;
        }
    }

    //Corner Case 3
    else if(x == 9 && y == 0){
        //If the grid is set to player 1
        if(it->grid == 1){
            //Check if the selected tile is a hit
            if(tmp->t != TileType::Ship){
                tmp->setColor(QColor(255,255,255));
            }
            else{
                if(tmp->getColor()!= QColor(255, 0, 0)){
                    tmp->setColor(QColor(255,0,0));
                    Tile::player1Score++;
                }
            }
            //Check if the tile to the right is a hit
            tmp = p1Tiles[y+1][x];
            if(tmp->t != TileType::Ship){
                tmp->setColor(QColor(255,255,255));
            }
            else{
                if(tmp->getColor()!= QColor(255, 0, 0)){
                    tmp->setColor(QColor(255,0,0));
                    Tile::player1Score++;
                }
            }

            //Check the tile below the coordinate
            tmp = p1Tiles[y][x-1];
            if(tmp->t != TileType::Ship){
                tmp->setColor(QColor(255,255,255));
            }
            else{
                if(tmp->getColor()!= QColor(255, 0, 0)){
                    tmp->setColor(QColor(255,0,0));
                    Tile::player1Score++;
                }
            }
            //2;
        }
        //If the grid is set to player 2
        else{
            //Check if the selected tile is a hit
            if(tmp->t != TileType::Ship){
                tmp->setColor(QColor(255,255,255));
            }
            else{
                if(tmp->getColor()!= QColor(255, 0, 0)){
                    tmp->setColor(QColor(255,0,0));
                    Tile::player2Score++;
                }
            }
            //Check if the tile to the right is a hit
            tmp = p1Tiles[y+1][x];
            if(tmp->t != TileType::Ship){
                tmp->setColor(QColor(255,255,255));
            }
            else{
                if(tmp->getColor()!= QColor(255, 0, 0)){
                    tmp->setColor(QColor(255,0,0));
                    Tile::player2Score++;
                }
            }

            //Check the tile below the coordinate
            tmp = p1Tiles[y][x-1];
            if(tmp->t != TileType::Ship){
                tmp->setColor(QColor(255,255,255));
            }
            else{
                if(tmp->getColor()!= QColor(255, 0, 0)){
                    tmp->setColor(QColor(255,0,0));
                    Tile::player2Score++;
                }
            }
            //1;
        }
    }

    //Corner Case 4
    else if(x == 9 && y == 9){
        //If the grid is set to player 1
        if(it->grid == 1){
            //Check if the selected tile is a hit
            if(tmp->t != TileType::Ship){
                tmp->setColor(QColor(255,255,255));
            }
            else{
                if(tmp->getColor()!= QColor(255, 0, 0)){
                    tmp->setColor(QColor(255,0,0));
                    Tile::player1Score++;
                }
            }
            //Check if the tile to the left is a hit
            tmp = p1Tiles[y-1][x];
            if(tmp->t != TileType::Ship){
                tmp->setColor(QColor(255,255,255));
            }
            else{
                if(tmp->getColor()!= QColor(255, 0, 0)){
                    tmp->setColor(QColor(255,0,0));
                    Tile::player1Score++;
                }
            }

            //Check the tile below the coordinate
            tmp = p1Tiles[y][x-1];
            if(tmp->t != TileType::Ship){
                tmp->setColor(QColor(255,255,255));
            }
            else{
                if(tmp->getColor()!= QColor(255, 0, 0)){
                    tmp->setColor(QColor(255,0,0));
                    Tile::player1Score++;
                }
            }
            //2;
        }
        //If the grid is set to player 2
        else{
            //Check if the selected tile is a hit
            if(tmp->t != TileType::Ship){
                tmp->setColor(QColor(255,255,255));
            }
            else{
                if(tmp->getColor()!= QColor(255, 0, 0)){
                    tmp->setColor(QColor(255,0,0));
                    Tile::player2Score++;
                }
            }
            //Check if the tile to the left is a hit
            tmp = p1Tiles[y-1][x];
            if(tmp->t != TileType::Ship){
                tmp->setColor(QColor(255,255,255));
            }
            else{
                if(tmp->getColor()!= QColor(255, 0, 0)){
                    tmp->setColor(QColor(255,0,0));
                    Tile::player2Score++;
                }
            }

            //Check the tile below the coordinate
            tmp = p1Tiles[y][x-1];
            if(tmp->t != TileType::Ship){
                tmp->setColor(QColor(255,255,255));
            }
            else{
                if(tmp->getColor()!= QColor(255, 0, 0)){
                    tmp->setColor(QColor(255,0,0));
                    Tile::player2Score++;
                }
            }
            //1;
        }
    }

    //Edge Case 1
    else if(x == 0){
        if(it->grid == 1){
            //Check if the selected tile is a hit
            if(tmp->t != TileType::Ship){
                tmp->setColor(QColor(255,255,255));
            }
            else{
                if(tmp->getColor()!= QColor(255, 0, 0)){
                    tmp->setColor(QColor(255,0,0));
                    Tile::player1Score++;
                }
            }
            //Check if the tile to the left is a hit
            tmp = p1Tiles[y-1][x];
            if(tmp->t != TileType::Ship){
                tmp->setColor(QColor(255,255,255));
            }
            else{
                if(tmp->getColor()!= QColor(255, 0, 0)){
                    tmp->setColor(QColor(255,0,0));
                    Tile::player1Score++;
                }
            }

            //Check the tile below the coordinate
            tmp = p1Tiles[y][x+1];
            if(tmp->t != TileType::Ship){
                tmp->setColor(QColor(255,255,255));
            }
            else{
                if(tmp->getColor()!= QColor(255, 0, 0)){
                    tmp->setColor(QColor(255,0,0));
                    Tile::player1Score++;
                }
            }
            //Check the tile to the right of the coordinate
            tmp = p1Tiles[y+1][x];
            if(tmp->t != TileType::Ship){
                tmp->setColor(QColor(255,255,255));
            }
            else{
                if(tmp->getColor()!= QColor(255, 0, 0)){
                    tmp->setColor(QColor(255,0,0));
                    Tile::player1Score++;
                }
            }
            //2;
        }
        //If the grid is set to player 2
        else{
            //Check if the selected tile is a hit
            if(tmp->t != TileType::Ship){
                tmp->setColor(QColor(255,255,255));
            }
            else{
                if(tmp->getColor()!= QColor(255, 0, 0)){
                    tmp->setColor(QColor(255,0,0));
                    Tile::player2Score++;
                }
            }
            //Check if the tile to the left is a hit
            tmp = p1Tiles[y-1][x];
            if(tmp->t != TileType::Ship){
                tmp->setColor(QColor(255,255,255));
            }
            else{
                if(tmp->getColor()!= QColor(255, 0, 0)){
                    tmp->setColor(QColor(255,0,0));
                    Tile::player2Score++;
                }
            }

            //Check the tile below the coordinate
            tmp = p1Tiles[y][x+1];
            if(tmp->t != TileType::Ship){
                tmp->setColor(QColor(255,255,255));
            }
            else{
                if(tmp->getColor()!= QColor(255, 0, 0)){
                    tmp->setColor(QColor(255,0,0));
                    Tile::player2Score++;
                }
            }
            //Check the tile to the right of the coordinate
            tmp = p1Tiles[y+1][x];
            if(tmp->t != TileType::Ship){
                tmp->setColor(QColor(255,255,255));
            }
            else{
                if(tmp->getColor()!= QColor(255, 0, 0)){
                    tmp->setColor(QColor(255,0,0));
                    Tile::player2Score++;
                }
            }
            //1;
        }
    }

    //Edge case 2
    else if(y == 0){
        if(it->grid == 1){
            //Check if the selected tile is a hit
            if(tmp->t != TileType::Ship){
                tmp->setColor(QColor(255,255,255));
            }
            else{
                if(tmp->getColor()!= QColor(255, 0, 0)){
                    tmp->setColor(QColor(255,0,0));
                    Tile::player1Score++;
                }
            }
            //Check if the tile below is a hit
            tmp = p1Tiles[y][x-1];
            if(tmp->t != TileType::Ship){
                tmp->setColor(QColor(255,255,255));
            }
            else{
                if(tmp->getColor()!= QColor(255, 0, 0)){
                    tmp->setColor(QColor(255,0,0));
                    Tile::player1Score++;
                }
            }

            //Check the tile below the coordinate
            tmp = p1Tiles[y][x+1];
            if(tmp->t != TileType::Ship){
                tmp->setColor(QColor(255,255,255));
            }
            else{
                if(tmp->getColor()!= QColor(255, 0, 0)){
                    tmp->setColor(QColor(255,0,0));
                    Tile::player1Score++;
                }
            }
            //Check the tile to the right of the coordinate
            tmp = p1Tiles[y+1][x];
            if(tmp->t != TileType::Ship){
                tmp->setColor(QColor(255,255,255));
            }
            else{
                if(tmp->getColor()!= QColor(255, 0, 0)){
                    tmp->setColor(QColor(255,0,0));
                    Tile::player1Score++;
                }
            }
            //2;
        }
        //If the grid is set to player 2
        else{
            //Check if the selected tile is a hit
            if(tmp->t != TileType::Ship){
                tmp->setColor(QColor(255,255,255));
            }
            else{
                if(tmp->getColor()!= QColor(255, 0, 0)){
                    tmp->setColor(QColor(255,0,0));
                    Tile::player2Score++;
                }
            }
            //Check if the tile below is a hit
            tmp = p1Tiles[y][x-1];
            if(tmp->t != TileType::Ship){
                tmp->setColor(QColor(255,255,255));
            }
            else{
                if(tmp->getColor()!= QColor(255, 0, 0)){
                    tmp->setColor(QColor(255,0,0));
                    Tile::player2Score++;
                }
            }

            //Check the tile above the coordinate
            tmp = p1Tiles[y][x+1];
            if(tmp->t != TileType::Ship){
                tmp->setColor(QColor(255,255,255));
            }
            else{
                if(tmp->getColor()!= QColor(255, 0, 0)){
                    tmp->setColor(QColor(255,0,0));
                    Tile::player2Score++;
                }
            }
            //Check the tile to the right of the coordinate
            tmp = p1Tiles[y+1][x];
            if(tmp->t != TileType::Ship){
                tmp->setColor(QColor(255,255,255));
            }
            else{
                if(tmp->getColor()!= QColor(255, 0, 0)){
                    tmp->setColor(QColor(255,0,0));
                    Tile::player2Score++;
                }
            }
            //1;
        }
    }

    //Edge Case 3
    else if(y == 9){
        //If the grid is set to player 1
        if(it->grid == 1){
            //Check if the selected tile is a hit
            if(tmp->t != TileType::Ship){
                tmp->setColor(QColor(255,255,255));
            }
            else{
                if(tmp->getColor()!= QColor(255, 0, 0)){
                    tmp->setColor(QColor(255,0,0));
                    Tile::player1Score++;
                }
            }
            //Check if the tile below is a hit
            tmp = p1Tiles[y][x-1];
            if(tmp->t != TileType::Ship){
                tmp->setColor(QColor(255,255,255));
            }
            else{
                if(tmp->getColor()!= QColor(255, 0, 0)){
                    tmp->setColor(QColor(255,0,0));
                    Tile::player1Score++;
                }
            }

            //Check the tile below the coordinate
            tmp = p1Tiles[y][x+1];
            if(tmp->t != TileType::Ship){
                tmp->setColor(QColor(255,255,255));
            }
            else{
                if(tmp->getColor()!= QColor(255, 0, 0)){
                    tmp->setColor(QColor(255,0,0));
                    Tile::player1Score++;
                }
            }
            //Check the tile to the left of the coordinate
            tmp = p1Tiles[y-1][x];
            if(tmp->t != TileType::Ship){
                tmp->setColor(QColor(255,255,255));
            }
            else{
                if(tmp->getColor()!= QColor(255, 0, 0)){
                    tmp->setColor(QColor(255,0,0));
                    Tile::player1Score++;
                }
            }
            //2;
        }
        //If the grid is set to player 2
        else{
            //Check if the selected tile is a hit
            if(tmp->t != TileType::Ship){
                tmp->setColor(QColor(255,255,255));
            }
            else{
                if(tmp->getColor()!= QColor(255, 0, 0)){
                    tmp->setColor(QColor(255,0,0));
                    Tile::player2Score++;
                }
            }
            //Check if the tile below is a hit
            tmp = p1Tiles[y][x-1];
            if(tmp->t != TileType::Ship){
                tmp->setColor(QColor(255,255,255));
            }
            else{
                if(tmp->getColor()!= QColor(255, 0, 0)){
                    tmp->setColor(QColor(255,0,0));
                    Tile::player2Score++;
                }
            }

            //Check the tile above the coordinate
            tmp = p1Tiles[y][x+1];
            if(tmp->t != TileType::Ship){
                tmp->setColor(QColor(255,255,255));
            }
            else{
                if(tmp->getColor()!= QColor(255, 0, 0)){
                    tmp->setColor(QColor(255,0,0));
                    Tile::player2Score++;
                }
            }
            //Check the tile to the left of the coordinate
            tmp = p1Tiles[y-1][x];
            if(tmp->t != TileType::Ship){
                tmp->setColor(QColor(255,255,255));
            }
            else{
                if(tmp->getColor()!= QColor(255, 0, 0)){
                    tmp->setColor(QColor(255,0,0));
                    Tile::player2Score++;
                }
            }
            //1;
        }
    }

    //Edge Case 4
    else{
        if(it->grid == 1){
            //Check if the selected tile is a hit
            if(tmp->t != TileType::Ship){
                tmp->setColor(QColor(255,255,255));
            }
            else{
                if(tmp->getColor()!= QColor(255, 0, 0)){
                    tmp->setColor(QColor(255,0,0));
                    Tile::player1Score++;
                }
            }
            //Check if the tile below is a hit
            tmp = p1Tiles[y][x-1];
            if(tmp->t != TileType::Ship){
                tmp->setColor(QColor(255,255,255));
            }
            else{
                if(tmp->getColor()!= QColor(255, 0, 0)){
                    tmp->setColor(QColor(255,0,0));
                    Tile::player1Score++;
                }
            }

            //Check the tile to the left of the coordinate
            tmp = p1Tiles[y-1][x];
            if(tmp->t != TileType::Ship){
                tmp->setColor(QColor(255,255,255));
            }
            else{
                if(tmp->getColor()!= QColor(255, 0, 0)){
                    tmp->setColor(QColor(255,0,0));
                    Tile::player1Score++;
                }
            }
            //Check the tile to the right of the coordinate
            tmp = p1Tiles[y+1][x];
            if(tmp->t != TileType::Ship){
                tmp->setColor(QColor(255,255,255));
            }
            else{
                if(tmp->getColor()!= QColor(255, 0, 0)){
                    tmp->setColor(QColor(255,0,0));
                    Tile::player1Score++;
                }
            }
            //2;
        }
        //If the grid is set to player 2
        else{
            //Check if the selected tile is a hit
            if(tmp->t != TileType::Ship){
                tmp->setColor(QColor(255,255,255));
            }
            else{
                if(tmp->getColor()!= QColor(255, 0, 0)){
                    tmp->setColor(QColor(255,0,0));
                    Tile::player2Score++;
                }
            }
            //Check if the tile below is a hit
            tmp = p1Tiles[y][x-1];
            if(tmp->t != TileType::Ship){
                tmp->setColor(QColor(255,255,255));
            }
            else{
                if(tmp->getColor()!= QColor(255, 0, 0)){
                    tmp->setColor(QColor(255,0,0));
                    Tile::player2Score++;
                }
            }

            //Check the tile to the left of the coordinate
            tmp = p1Tiles[y-1][x];
            if(tmp->t != TileType::Ship){
                tmp->setColor(QColor(255,255,255));
            }
            else{
                if(tmp->getColor()!= QColor(255, 0, 0)){
                    tmp->setColor(QColor(255,0,0));
                    Tile::player2Score++;
                }
            }
            //Check the tile to the right of the coordinate
            tmp = p1Tiles[y+1][x];
            if(tmp->t != TileType::Ship){
                tmp->setColor(QColor(255,255,255));
            }
            else{
                if(tmp->getColor()!= QColor(255, 0, 0)){
                    tmp->setColor(QColor(255,0,0));
                    Tile::player2Score++;
                }
            }
            //1;
        }
    }

    dChargeSelect = false;
    update();
    scoreChangeSlot();
    qDebug() << "End DepthChargeSlot";
}
