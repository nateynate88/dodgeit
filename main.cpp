#include "mainwindow.h"
#include "board.h"
#include "highscorewindow.h"
#include "gameoverwidget.h"
#include <QApplication>
#include <QPushButton>
#include <QVBoxLayout>
#include <QLabel>
#include <iostream>
/**
 Nathan Brucher
 November 13, 2014
 Dodgeit!
 The purpose of this game is to avoid the obstacles as the stickman. Touching the obstacles will result in death and game over.
 Obstacles will be telegraphed to you before they appear, so find a safe spot on the board.
 Try to survive as long as possible!
 */
int main(int argc, char *argv[])
{

    QApplication a(argc, argv);
    MainWindow* w = new MainWindow;
    w->show();
    QObject::connect(w,SIGNAL(quit_signal()),&a,SLOT(quit()));

    return a.exec();
}
