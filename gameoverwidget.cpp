#include "gameoverwidget.h"
/**
 * @brief GameOverWidget::GameOverWidget creates a widget that displays after you lose the game
 * @param parent is the parent widget
 */
GameOverWidget::GameOverWidget(QWidget *parent) :
    QWidget(parent)
{
   game_over_layout = new QVBoxLayout;
  //game_over_message = new QLabel("Game Over! Your score is " + score_string) ;//+ QString::number(parent->getScore()));
   message = "GAME OVER!";

   quit = new QPushButton("Quit");
   main_menu = new QPushButton("Main Menu");
   retry= new QPushButton("New Game");



   this->setLayout(game_over_layout);
   QWidget::connect(quit,SIGNAL(clicked()),this,SLOT(quit_the_game()));
   QWidget::connect(main_menu,SIGNAL(clicked()),this,SLOT(back_to_main()));
   QWidget::connect(retry,SIGNAL(clicked()), this, SLOT(new_game()));
   game_over_message= nullptr;
}
/**
 * @brief GameOverWidget::quit_the_game emits a signal that the application should quit
 */
void GameOverWidget::quit_the_game(){
    emit quitClicked();
    this->close();
}
/**
 * @brief GameOverWidget::back_to_main closes this widget and emits a signal that the game should go back to the main menu
 */
void GameOverWidget::back_to_main(){
    emit mainMenuClicked();
    this->close();
}
/**
 * @brief GameOverWidget::new_game closes this widget and emits a signal that the game should start a new game and create a new board
 */
void GameOverWidget::new_game(){
    emit retryClicked();

    this->close();
}
/**
 * @brief GameOverWidget::set_score sets the score in this widget to match the score achieved by the player
 * @param n is the value that the score should be set to
 */
void GameOverWidget::set_score(int n){

    score = n;
     qDebug() << "Score in game over widget:" << score << "THIS WAS CALLED";
    QString score_string= QString::number(score);
    message= "Game Over! Your score is: " + score_string;
    if (game_over_message == nullptr){
        game_over_message = new QLabel(message);
        game_over_layout->addWidget(game_over_message);
    }
    else {
        delete game_over_message;
        game_over_message= nullptr;
        game_over_message = new QLabel(message);
        game_over_layout->addWidget(game_over_message);

    }
    game_over_layout->addWidget(main_menu);
    game_over_layout->addWidget(retry);
    game_over_layout->addWidget(quit);

}
