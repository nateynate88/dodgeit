#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "mainmenu.h"


/**
 * @brief MainWindow::MainWindow constructor for the main window
 * @param parent is the parent widget
 */
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent)
    //ui(new Ui::MainWindow)
{

    gameBoard = nullptr;
    hs = new HighScoreWindow;
    menu_widget= new MainMenu;
    game_over = new GameOverWidget;
    this->setCentralWidget(menu_widget);

    QWidget::connect(menu_widget,SIGNAL(playClicked()),this, SLOT(createBoard()));
    QWidget::connect(menu_widget,SIGNAL(quitClicked()),this,SLOT(quit_the_game()));
    QWidget::connect(menu_widget,SIGNAL(hsClicked()), this, SLOT(createHS()));

}
/**
 * @brief MainWindow::~MainWindow deconstructor for the Main Window
 */
MainWindow::~MainWindow()
{
    //delete ui;
}

/**
 * @brief MainWindow::createBoard slot that creates the gameBoard and sets it as the central widget
 */
void MainWindow::createBoard(){

    if (centralWidget()){
        centralWidget()->setParent(0);
    }
    gameBoard = new Board;
    this->setCentralWidget(gameBoard);
    QObject::connect(gameBoard,SIGNAL(main_menu_clicked()),this,SLOT(back_to_main_menu_board()));
    QObject::connect(gameBoard,SIGNAL(you_lost()),this, SLOT(createQuit()));
    QWidget::connect(gameBoard,SIGNAL(score_signal(int)),game_over,SLOT(set_score(int)));
    QWidget::connect(gameBoard, SIGNAL(score_signal(int)),hs,SLOT(updateHighScores(int)));


}
/**
 * @brief MainWindow::createBoard_gameOver slot that creates a gameBoard from the gameOver window
 */
void MainWindow::createBoard_gameOver(){

    if (centralWidget()){
        centralWidget()->setParent(0);
    }
    delete gameBoard;
    gameBoard = new Board;
    this->setCentralWidget(gameBoard);
    QObject::connect(gameBoard,SIGNAL(main_menu_clicked()),this,SLOT(back_to_main_menu_board()));
    QObject::connect(gameBoard,SIGNAL(you_lost()),this, SLOT(createQuit()));
    QWidget::connect(gameBoard,SIGNAL(score_signal(int)),game_over,SLOT(set_score(int)));


}
/**
 * @brief MainWindow::back_to_main_menu_gameOver slot that returns to the main menu from the gameOVer menu
 */
void MainWindow::back_to_main_menu_gameOver(){
    this->resize(300,200);
    if(centralWidget()){
        centralWidget()->setParent(0);
    }
    this->setCentralWidget(menu_widget);
    this->resize(300,200);
    this->adjustSize();
    //this->setCentralWidget(central);
}
/**
 * @brief MainWindow::back_to_main_menu_board slot that returns to main menu from the Board
 */
void MainWindow::back_to_main_menu_board(){

    delete gameBoard;
    gameBoard= nullptr;
    if(centralWidget()){
        centralWidget()->setParent(0);
    }
    this->setCentralWidget(menu_widget);
    this->resize(300,200);
    this->adjustSize();
    //this->setCentralWidget(central);
}
/**
 * @brief MainWindow::keyPressEvent key press event that allows the stickman to move on the board from a mainwindow
 * @param event is a key event such as the arrow keys
 */
void MainWindow::keyPressEvent(QKeyEvent *event){

    //prevents errors if gameBoard isn't set yet
    if(gameBoard != nullptr){
        switch (event->key()) {
        case Qt::Key_Left:
            gameBoard->keyPressEvent(event);

            break;
        case Qt::Key_Right:
            gameBoard->keyPressEvent(event);

            break;
        case Qt::Key_Up:
            gameBoard->keyPressEvent(event);

            break;
        case Qt::Key_Down:
            gameBoard->keyPressEvent(event);

        break;

        break;
        default:
            QWidget::keyPressEvent(event);
    }
    //QCoreApplication::processEvents();
    repaint();
    return;
    }
}
/**
 * @brief MainWindow::quit_the_game emits a signal that the game should quit
 */
void MainWindow::quit_the_game(){
    emit quit_signal();
}
/**
 * @brief MainWindow::createQuit creates the gameOver menu widget and connects its buttons
 */
void MainWindow::createQuit(){

    game_over->show();
    QWidget::connect(game_over, SIGNAL(quitClicked()), this,SLOT(quit_the_game()) );
    QWidget::connect(game_over, SIGNAL(mainMenuClicked()),this,SLOT(back_to_main_menu_gameOver()));
    QWidget::connect(game_over, SIGNAL(retryClicked()), this, SLOT(createBoard_gameOver()));



}
/**
 * @brief MainWindow::createHS creates the HighScore window menu widget
 */
void MainWindow::createHS(){

    hs->show();
}
