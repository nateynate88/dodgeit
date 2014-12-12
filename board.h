#ifndef BOARD_H
#define BOARD_H

#include <QWidget>
#include <Qlabel>
#include <QGridLayout>
#include <QVBoxLayout>
#include <QPushButton>
#include <QPixmap>
#include <QTransform>
#include <QKeyEvent>
#include <QPoint>
#include <random>
#include <chrono>
#include <QTimer>
#include <QCoreApplication>
#include "gameoverwidget.h"
#include "mainwindow.h"
#include "highscorewindow.h"


class GameOverWidget;
class Board : public QWidget
{
    Q_OBJECT
public:
    explicit Board(QWidget *parent = 0);
    //~Board(){};


   void keyPressEvent(QKeyEvent *event);
   void paintEvent(QPaintEvent *e);
   //void closeEvent(QCloseEvent *e);
   void updateStickman(int px, int py, int nx, int ny);
   void gameOver();
   int getScore(){return score;};




signals:
   /**
    * @brief main_menu_clicked signal that main menu has been clicked
    */
   void main_menu_clicked();
   /**
    * @brief you_lost signal that the player died
    */
   void you_lost();
   /**
    * @brief score_signal signal that passes along the score
    * @param n is the integer value to pass
    */
   void score_signal(int n);

public slots:
   void updateLasers();
   bool checkIfDead();
   void laser_warning_update();
   void endLaser();
   void back_to_menu();
   void emit_signal();
   void score_slot(int n );

private:
    QWidget *Board_grid;
    const size_t board_size;
    QLabel** labels;
    QPixmap *up_arrow_image;
    QPixmap *down_arrow_image;
    QPixmap *right_arrow_image;
    QPixmap *left_arrow_image;
    QPixmap *stickman;
    QPixmap *bomb_image;
    QPixmap *anvil_image;
    QPoint *stickman_position;
    QPoint *laser_position_up;
    QPoint *laser_position_down;
    QPoint *laser_position_right;
    QPoint *laser_position_left;
    QPoint *bomb_position;
    QPoint* anvil_position;
    QPoint* warning_signal_right;
    QPoint* warning_signal_up;
    QPoint* warning_signal_left;
    QPoint* warning_signal_down;


    QTimer* timer;
    QTimer* checking_timer;
    QTimer* warning_timer;

    QLabel* score_label;
    QLabel* level_label;

    GameOverWidget* game_over;


    int score;

    QPushButton* menu;
    int level;

};

#endif // BOARD_H
