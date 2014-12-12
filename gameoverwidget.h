
#ifndef GAMEOVERWIDGET_H
#define GAMEOVERWIDGET_H

#include <QWidget>
#include <QLabel>
#include <QVBoxLayout>
#include <QPushButton>
#include "board.h"
#include<QDebug>

class Board;

class GameOverWidget : public QWidget
{
    Q_OBJECT
public:
    explicit GameOverWidget(QWidget *parent = 0);


signals:
    /**
     * @brief quitClicked signals quit was clicked
     */
    void quitClicked();
    /**
     * @brief mainMenuClicked signals main menu was clicked
     */
    void mainMenuClicked();
    /**
     * @brief retryClicked signals new game was clicked
     */
    void retryClicked();
    /**
     * @brief score_changed signals score changed
     * @param n is the integer value to pass
     */
    void score_changed(int n);

public slots:
    void quit_the_game();
    void back_to_main();
    void new_game();
    void set_score(int n);

private:
    QLabel* game_over_message;
    QPushButton* main_menu;
    QPushButton* quit;
    QPushButton* retry;
    QVBoxLayout* game_over_layout;
    int score;
    QString message;

    Board* board;
};

#endif // GAMEOVERWIDGET_H
