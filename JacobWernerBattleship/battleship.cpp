#include <QDebug>
#include <QtWidgets>
#include <QGraphicsView>
#include <QGraphicsItem>
#include <QGraphicsScene>
#include "mainwindow.cpp"
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "battleship.h"

//-----------------------------------------------------------
//---------------------TILE----------------------------------

//Default constructor
Tile::Tile(int x, int y, int width, int height, int iGrid){
    QColor color(77, 166, 255);
    setColor(color);
    setX(x * width);
    setY(y * height);
    setW(width);
    setH(height);
    grid = iGrid;
    int p = rand() % 100 + 1;
    if(p > 0 && p <=5){
        t = TileType::DCharge;
    }
    else if(p > 0 && p <= 15){
        t = TileType::Torpedo;
    }
    else{
        t = TileType::Empty;
    }
}

//Declare static variables
int Tile::buttonClick = 0;
int Tile::player1Score = 0;
int Tile::player2Score = 0;
int Tile::player1Torpedo = 0;
int Tile::player2Torpedo = 0;
int Tile::player1dCharge = 0;
int Tile::player2dCharge = 0;

bool Tile::game1 = false;
bool Tile::game2 = false;
bool Tile::dChargeSelect = false;
bool Tile::torpedoSelect = false;

//Paints the tile to the according color
void Tile::paint(QPainter *p, const QStyleOptionGraphicsItem *i, QWidget *w){
    Q_UNUSED(w)
    Q_UNUSED(i)
    QBrush brush = p->brush();
    p->setBrush(QBrush(getColor()));
    p->drawRect(QRect(this->tx, this->ty, this->tWidth, this->tHeight));;
    p->setBrush(brush);
}

//Draws the outline of the tile
QRectF Tile::boundingRect() const{
    return QRectF(tx, ty, tWidth, tHeight);
}

//Draws the shape of the tile
QPainterPath Tile::shape() const{
    QPainterPath p;
    p.addRect(tx, ty, tWidth, tHeight);
    return p;
}

//Determines the action to be taken when a left or right mouse click is registered
void Tile::mousePressEvent(QGraphicsSceneMouseEvent *e){
    //If the game is not in setup stage
    if(game1 == true && game2 == true){
        emit yClick();
    }
    //Check if a ship selection button was selected (which increased buttonClick value)
    if(Tile::buttonClick > 0){
        //If the game is in setup stage
        if(e->button() == Qt::LeftButton && (game1 == false || game2 == false)){
            //Check if the tile is empty, if not then ignore
            if(getColor() == QColor(77, 166, 255)){
                setColor(QColor(240, 20, 130));
                t = TileType::Ship;
                update();
            }
        }
    }
    //If the game is past the setup stage
    if(e->button() == Qt::LeftButton && game1 == true && game2 == true){
        if(t == TileType::Ship){
            setColor(QColor(255, 0, 0));
            hit = true;
            update();
            if(grid == 1){
                player1Score++;
                grid = 2;
            }
            else{
                player2Score++;
                grid = 1;
            }
        }
        //Check if the user hit a dCharge, meaning that they get it as a powerup
        if(t == TileType::DCharge){
            if(grid == 1){
                setColor(QColor(255, 255, 255));
                player1dCharge++;
                grid = 2;
                update();
            }
            else{
                setColor(QColor(255, 255, 255));
                player2dCharge++;
                grid = 1;
                update();
            }
        }
        //Check if the user hit a torpedo, meaning that they get it as a powerup
        if(t == TileType::Torpedo){
            if(grid == 1){
                setColor(QColor(255, 255, 255));
                player1Torpedo++;
                grid = 2;
                update();
            }
            else{
                setColor(QColor(255, 255, 255));
                player2Torpedo++;
                grid = 1;
                update();
            }
        }

        //If the user is trying to use a depth charge
        if(dChargeSelect){
            if(grid == 1){
                if(player1dCharge < 1){
                    return;
                }
                else{
                    this->tdCharge(this);
                    player1dCharge--;
                    dChargeSelect = false;
                    update();
                }
            }
            else{
                if(player2dCharge < 1){
                    return;
                }
                else{
                    this->tdCharge(this);
                    player2dCharge--;
                    dChargeSelect = false;
                    update();
                }
            }
        }
        //If a player is trying to use a torpedo
        if(torpedoSelect){
            if(grid == 1){
                if(player1Torpedo < 1){
                    return;
                }
                else{
                    emit this->tTorpedo(this);
                    player1Torpedo--;
                    torpedoSelect = false;
                    update();
                }
            }
            else{
                if(player2Torpedo < 1){
                    return;
                }
                else{
                    emit this->tTorpedo(this);
                    player2Torpedo--;
                    torpedoSelect = false;
                    update();
                }
            }
        }
        //If the user misses
        else if(t == TileType::Empty){
            setColor(QColor(255, 255, 255));
            if(grid == 1){grid = 2;}
            else{grid = 1;}
            update();
        }
    }
    update();
    emit tScoreBoard(this);
    buttonClick--;
}

//-----------------------------------------------------------
//---------------------GRAPH---------------------------------

//Default constructor
Graph::Graph(int x, int y, int h){
    setX(x);
    setY(y);
    setHeight(h);
    gColor = "white";
}

//Paints the graph cells the  according color
void Graph::paint(QPainter *p, const QStyleOptionGraphicsItem *i, QWidget *w){
    Q_UNUSED(w)
    QBrush brush = p->brush();
    p->setBrush(QBrush(gColor.dark(i->state & QStyle::State_Sunken ? 120 : 100)));
    p->drawRect(this->gx, this->gy, this->gWidth, this->gHeight);
    p->setBrush(brush);
}

//Draws the outline of the graph cell
QRectF Graph::boundingRect() const{
    return QRectF(gx, gy, gWidth, gHeight);
}

//Draws the shape of the graph cell
QPainterPath Graph::shape() const{
    QPainterPath p;
    p.addRect(gx, gy, gWidth, gHeight);
    return p;
}
//--------------------------------------------------------
//----------------------PLAYER----------------------------

Player::Player(){
    pMode = 1;
    pTurns = 0;
}
//--------------------------------------------------------
//-------------------------AI-----------------------------

AI::AI(){
    pMode = 2;
    pTurns = 0;
}
void AI::setTurn(int i){
    if((i == 1 || i == -1) && getTurn() < 2){
        setTurn(getTurn() + i);
    }
}
