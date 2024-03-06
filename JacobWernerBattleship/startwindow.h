#ifndef STARTWINDOW_H
#define STARTWINDOW_H

#include <QMainWindow>
#include "mainwindow.h"

QT_BEGIN_NAMESPACE
namespace Ui { class StartWindow; }
QT_END_NAMESPACE

class StartWindow : public QMainWindow
{
    Q_OBJECT
    public:
        explicit StartWindow(QWidget *parent = nullptr);
        ~StartWindow();
        //int getPlayerCount(){return nPlayers;}      //Getter for nPlayers
        //void setPlayerCount(int in){nPlayers = in;} //Setter for nPlayers
        static int nPlayers; //Holds the number of players

    private slots:
        void singleplayerClick(); //Slot for if 1 player button is selected
        void multiplayerClick(); //Slot for if 2 players button is selected

    private:
        Ui::StartWindow *ui; 
        MainWindow game;
};

#endif // STARTWINDOW_H
