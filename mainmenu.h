#ifndef MAINMENU_H
#define MAINMENU_H

#include <QWidget>
#include <QPushButton>
#include <QLabel>
#include <QVBoxLayout>
#include "board.h"
#include "highscorewindow.h"

class MainMenu : public QWidget
{
    Q_OBJECT
public:
    explicit MainMenu(QWidget *parent = 0);

signals:
    /**
     * @brief playClicked signals that play was clicked
     */
    void playClicked();
    /**
     * @brief hsClicked signals that high score was clicked
     */
    void hsClicked();
    /**
     * @brief quitClicked signals that quit was clicked
     */
    void quitClicked();

public slots:
    void createBoard();
    void createHS();
    void quitAction();


private:
    QPushButton *start;
    QPushButton * high_scores;
    QPushButton * quit;
    QLabel *welcome;
    QVBoxLayout *menu_layout;
    HighScoreWindow* hs;

    int score;
};

#endif // MAINMENU_H
