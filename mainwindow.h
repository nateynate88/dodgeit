#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "board.h"
//#include "mainmenu.h"
#include "gameoverwidget.h"
#include "highscorewindow.h"

class Board;
class MainMenu;
class GameOverWidget;
class HighScoreWindow;

/*namespace Ui {
}*/

class MainWindow : public QMainWindow
{
    Q_OBJECT
public slots:
    void createBoard();
    void back_to_main_menu_gameOver();
    void back_to_main_menu_board();
    void quit_the_game();
    void createQuit();
    void createBoard_gameOver();
    void createHS();
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void keyPressEvent(QKeyEvent *event);
signals:
    void quit_signal();


private:
    //Ui::MainWindow *ui;
    Board* gameBoard;
    QWidget* central;
    QPushButton *start;
    QPushButton * high_scores;
    QPushButton * quit;
    QLabel *welcome;
    QVBoxLayout *menu_layout;
    MainMenu* menu_widget;
    QWidget* central_copy;
    GameOverWidget* game_over;
    HighScoreWindow* hs;



};

#endif // MAINWINDOW_H
