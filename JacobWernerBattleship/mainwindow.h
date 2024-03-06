#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QDebug>
#include <QtWidgets>
#include <QMainWindow>
#include <QGraphicsItem>
#include <QGraphicsView>
#include <QGraphicsScene>
#include "battleship.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT
    public:
        explicit MainWindow(QWidget *parent = nullptr);
        ~MainWindow();
        void aiTurn();
        void aiShips();
        static bool launch;

    private slots:
        void click();
        void scoreChangeSlot();
        void restartButtonSlot();
        void TorpedoSlot(Tile *t);
        void DepthChargeSlot(Tile *t);

        void p1CruClick();  //Player 1 Cruiser mouse click
        void p2CruClick();  //Player 2 Cruiser mouse click
        void p1BtlClick();  //Player 1 Battleship mouse click
        void p2BtlClick();  //Player 2 Battleship mouse click
        void p1SubClick();  //Player 1 Submarine mouse click
        void p2SubClick();  //Player 2 Submarine mouse click
        void p1DestClick(); //Player 1 Destroyer mouse click
        void p2DestClick(); //Player 2 Destroyer mouse click
        void p1CarrClick(); //Player 1 Carrier mouse click
        void p2CarrClick(); //Player 2 Carrier mouse click
        void p1TorpClick(); //Player 1 Torpedo mouse click
        void p2TorpClick(); //Player 2 Torpedo mouse click
        void p1DcgeClick(); //Player 1 Depth Charge mouse click
        void p2DcgeClick(); //Player 2 Depth Charge mouse click
        void p1EndSetup();  //Player 1 End Setup button mouse click
        void p2EndSetup();  //Player 2 End Setup button mouse click

    private:
        Ui::MainWindow *ui;
        Player *p1;
        Player *p2;
        AI *ai;

        int score1 = 0;
        int score2 = 0;
        int turnCount = 0;
        int tileWidth;
        int tileHeight;
        int graphH = 0;
        int graphY = 0;
        int graphWidth;
        //int p1TorpCount = 0;
        //int p2TorpCount = 0;
        double graphHeight;
        bool p1Hidden = false;
        bool p2Hidden = false;
        bool p1Torpedo = false;
        bool p2Torpedo = false;
        bool p1dCharge = false;
        bool p2dCharge = false;
        bool torpedoSelect = false;
        bool dChargeSelect = false;

        std::vector<Graph*> graphs;
        Tile *p1Tiles[10][10];
        Tile *p2Tiles[10][10];
        QGraphicsScene *p1Grid;
        QGraphicsScene *p2Grid;
        QGraphicsScene *graphUI;

        void hidep1();
        void hidep2();
        void winCount();
};

#endif // MAINWINDOW_H
