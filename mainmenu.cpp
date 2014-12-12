#include "mainmenu.h"
/**
 * @brief MainMenu::MainMenu constructor for a main menu widget that has various options
 * @param parent
 */
MainMenu::MainMenu(QWidget *parent) :
    QWidget(parent)
{
    //pushbuttons
    welcome = new QLabel("<h1>Welcome to Dodgeit!</h1>");
    start= new QPushButton("Let's play");
    high_scores= new QPushButton("High Score");
    quit= new QPushButton("Quit");
    menu_layout= new QVBoxLayout;

    menu_layout->addWidget(welcome);
    menu_layout->addWidget(start);
    menu_layout->addWidget(high_scores);
    menu_layout->addWidget(quit);

    this->setLayout(menu_layout);
    //connect all the buttons to slots
    QWidget::connect(start, SIGNAL(clicked()), this, SLOT (createBoard()));
    QWidget::connect(high_scores,SIGNAL(clicked()), this, SLOT(createHS()));
    QWidget::connect(quit,SIGNAL(clicked()), this, SLOT(quitAction()));

    this->setFixedSize(300,200);

}
/**
 * @brief MainMenu::createBoard emits a signal that a board should be created
 */
void MainMenu::createBoard(){

    emit playClicked();
}
/**
 * @brief MainMenu::createHS creates a High score window widget and shows it
 */
void MainMenu::createHS(){
    emit hsClicked();
}
/**
 * @brief MainMenu::quitAction emits a signal that quit is clicked and the application should quit
 */
void MainMenu::quitAction(){
    emit quitClicked();
}



