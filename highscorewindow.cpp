#include "highscorewindow.h"
#include <algorithm>
/**
 * @brief HighScoreWindow::HighScoreWindow creates a high score window widget that displays the top 10 high scores for the game
 * @param parent is the parent widget
 */
HighScoreWindow::HighScoreWindow(QWidget *parent) :
    QWidget(parent), counter(0)
{
    high_score = 0;
    high_score_label = new QLabel("No score yet!");
    overarching_layout = new QVBoxLayout;
    QHBoxLayout *connecting_layout = new QHBoxLayout;
    QVBoxLayout *layout_left = new QVBoxLayout;
    layout_right = new QVBoxLayout;
    QLabel *title = new QLabel("<h1> High Score <h1>");
    overarching_layout->addWidget(title);


    connecting_layout->addLayout(layout_left);
    connecting_layout->addLayout(layout_right);
    overarching_layout->addWidget(high_score_label);
    this->setLayout(overarching_layout);


}
/**
 * @brief HighScoreWindow::updateHighScores updates the high score
 * @param n is the value to change the high score to
 */
void HighScoreWindow::updateHighScores(int n){

    if( n> high_score){

        high_score= n;
        QString hs_string= QString::number(high_score);
        high_score_label->setText(hs_string);
        high_score_label->setAlignment(Qt::AlignCenter);
        overarching_layout->addWidget(high_score_label);
    }

}



