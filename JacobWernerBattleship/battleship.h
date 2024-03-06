#ifndef BATTLESHIP
#define BATTLESHIP

#include <QColor>
#include <QObject>
#include <QtWidgets>
#include <QMainWindow>
#include <QGraphicsView>
#include <QGraphicsItem>
#include <QGraphicsScene>


enum class TileType {Empty, DCharge, Torpedo, Ship};

class Tile : public QObject, public QGraphicsItem{
    Q_OBJECT
    Q_INTERFACES(QGraphicsItem)
    public:
        Tile(int x, int y, int width, int height, int grid); //Default constructor
        int getX() const {return tx;}       //Getter for x variable
        void setX(int ix) {tx = ix;}        //Setter for x variable
        int getY() const {return ty;}       //Getter for y variable
        void setY(int iy) {ty = iy;}        //Setter for y variable
        int getW() {return tWidth;}         //Getter for width variable
        void setW(int iw) {tWidth = iw;}    //Setter for width variable
        int getH() {return tHeight;}        //Getter for height variable
        void setH(int ih) {tHeight = ih;}   //Setter for height variable
        int getStatus() {return tStatus;}                 //Setter for tile status
        void setStatus(int iStatus) {tStatus = iStatus;}  //Setter for tile status
        QColor getColor() {return tColor;}                //Getter for tile color
        void setColor(QColor iColor) {tColor = iColor;}   //Setter for tile color
        void paint(QPainter *p, const QStyleOptionGraphicsItem *i, QWidget *w) override; //Handles painting of tile
        QRectF boundingRect() const override;   //Creates outline for tile
        QPainterPath shape() const override;    //Creates shape for tile

        int grid;
        static int buttonClick;
        static int player1Score;
        static int player2Score;
        static int player1Torpedo;
        static int player2Torpedo;
        static int player1dCharge;
        static int player2dCharge;

        bool hit;
        static bool game1;
        static bool game2;
        static bool dChargeSelect;
        static bool torpedoSelect;

        TileType t;

    signals:
        void tIncrease();
        void tDecrease();
        void tScoreCheck();
        void yClick();
        void tTorpedo(Tile *t);
        void tdCharge(Tile *t);
        void tNeighbors(int x, int y);
        void tScoreBoard(Tile *t);

    protected:
        void mousePressEvent(QGraphicsSceneMouseEvent *e) override;

    private:
        int tx;
        int ty;
        int tWidth;
        int tHeight;
        int tStatus;
        QColor tColor;
};



class Graph : public QObject, public QGraphicsItem{
    Q_OBJECT
    Q_INTERFACES(QGraphicsItem)
    public:
        Graph(int x, int y, int h);
        int getX() {return gx;}
        void setX(int ix) {gx = ix;}
        int getY() {return gy;}
        void setY(int iy) {gy = iy;}
        static int getWidth() {return gWidth;}
        int getHeight(){return gHeight;}
        void setHeight(int h){gHeight = h;}
        void paint(QPainter *p, const QStyleOptionGraphicsItem *i, QWidget *w) override;
        QRectF boundingRect() const override;
        QPainterPath shape() const override;

    private:
        int gx;
        int gy;
        int gHeight;
        static const int gWidth = 30;
        QColor gColor;
};

class Player : public QObject{
    Q_OBJECT
    public:
        Player();
        int getTurn(){return pTurns;}
        void setTurn(int iTurn) {pTurns += iTurn;}
        int getMode(){return pMode;}
        void setMode(int im) {pMode = im;}
        int pTurns;
        int pMode;

};

class AI : public Player{
    Q_OBJECT
    public:
        AI();
        virtual void setTurn(int iTurn);
        TileType t;

    signals:
        void placeShip();
};

#endif // BATTLESHIP

