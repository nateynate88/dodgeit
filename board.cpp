#include "board.h"
//random generator
unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
std::default_random_engine generator (seed);

/**
 * @brief Board::Board creates a Board widget that contains the game to play
 * @param parent is the parent widget
 */
Board::Board(QWidget *parent) :
    QWidget(parent), board_size(8), score(0), level(1)
{
    QVBoxLayout *overall_layout = new QVBoxLayout;
    //top menu
    QHBoxLayout *top_layout = new QHBoxLayout;
    QString score_string = QString::number(score);
    QString level_string = QString::number(level);

    score_label = new QLabel("Score: " + score_string);
    level_label = new QLabel("Level: " + level_string);
    menu = new QPushButton("Main Menu");
    QWidget::connect(menu,SIGNAL(clicked()),this, SLOT(emit_signal()));
    top_layout->addWidget(score_label);
    top_layout->addWidget(level_label);
    top_layout->addWidget(menu);
    labels = new QLabel*[board_size*board_size];
    Board_grid = new QWidget;


//board part
    QString up_arrow_filename("/Users/Nathan/Desktop/School_Stuff/Fall_2014/PIC_10C/DodgeitPics/Black_Up_Arrow.png");
    up_arrow_image= new QPixmap(up_arrow_filename);
    QString left_arrow_filename("/Users/Nathan/Desktop/School_Stuff/Fall_2014/PIC_10C/DodgeitPics/Black_Left_Arrow.png");
    left_arrow_image= new QPixmap(left_arrow_filename);
    QString right_arrow_filename("/Users/Nathan/Desktop/School_Stuff/Fall_2014/PIC_10C/DodgeitPics/Black_Right_Arrow.png");
    right_arrow_image= new QPixmap(right_arrow_filename);
    QString down_arrow_filename("/Users/Nathan/Desktop/School_Stuff/Fall_2014/PIC_10C/DodgeitPics/Black_Down_Arrow.png");
    down_arrow_image= new QPixmap(down_arrow_filename);
    QString stickman_filename("/Users/Nathan/Desktop/School_Stuff/Fall_2014/PIC_10C/DodgeitPics/stickman.png");
    stickman= new QPixmap(stickman_filename);
    QString bomb_filename("/Users/Nathan/Desktop/School_Stuff/Fall_2014/PIC_10C/DodgeitPics/bomb.png");
    bomb_image = new QPixmap(bomb_filename);
    QString anvil_filename("/Users/Nathan/Desktop/School_Stuff/Fall_2014/PIC_10C/DodgeitPics/anvil.png");
    anvil_image= new QPixmap(anvil_filename);


    QGridLayout *gridLayout = new QGridLayout;//(Board_grid);
    gridLayout->setGeometry(QRect());
    gridLayout->setSpacing(3);

    for(size_t i= 0; i<board_size; i++){
        for(size_t j=0; j<board_size; j++){
            labels[i*board_size+j]= new QLabel;
            labels[i*board_size+j]->setMaximumSize(40,40);
            labels[i*board_size+j]->setMinimumSize(40,40);
           if (i==0 || j ==0 || i==board_size -1 || j==board_size -1){
               labels[i*board_size+j]->setStyleSheet(("QLabel { background-color : red; color : white; }"));
            }
            else{
                labels[i*board_size+j]->setStyleSheet(("QLabel { background-color : yellow; color : white; }"));
            }

            //labels[i*board_size+j]->setStyleSheet(("QLabel { background-color : yellow; color : white; }"));
            gridLayout->addWidget(labels[i*board_size+j],i,j);
            /*QLabel *square = new QLabel;
            square->setMaximumSize(40,40);
            square->setMinimumSize(40,40);
            if (i==0 || j ==0 || i== board_size -1 || j == board_size-1){
               square->setStyleSheet(("QLabel { background-color : red; color : white; }"));
            }
           else {
               square->setStyleSheet(("QLabel { background-color : yellow; color : white; }"));
            }
            gridLayout->addWidget(square,i,j);
            */

        }
    }

    //sample lazer beam shot
    /*labels[4]->setPixmap(*down_arrow_image);
    labels[4]->setScaledContents(true);
    for(size_t i= 1; i<board_size; i++){
        labels[4+i*board_size]->setStyleSheet(("QLabel { background-color : turquoise; color : white; }"));

    }

    labels[15]->setPixmap(*left_arrow_image);
    labels[15]->setScaledContents(true);
    for(int i =15; i>=8;i--)
        labels[i]->setStyleSheet(("QLabel { background-color : turquoise; color : white; }"));*/


    stickman_position = new QPoint(3,3);
    laser_position_up = new QPoint(-1,7);
    laser_position_down= new QPoint(-1,0);
    laser_position_left= new QPoint(7,-1);
    laser_position_right= new QPoint (0,-1);

    warning_signal_right = new QPoint(0,1);
    warning_signal_left= new QPoint(7,0);
    warning_signal_up = new QPoint(0,7);
    warning_signal_down = new QPoint(-1,0);

    //sample bomb

    //labels[47]->setPixmap(*bomb_image);
    //labels[47]->setScaledContents(true);

    //sample anvil
    //labels[3]->setPixmap(*anvil_image);
    //labels[3]->setScaledContents(true);

    //check for death? and pop up window

    //attempt at random shit
    //unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    //std::default_random_engine generator (seed);
    std::uniform_int_distribution<int> distribution(1,6);
    timer = new QTimer(this);
    checking_timer =new QTimer(this);
    warning_timer = new QTimer(this);

    //warning_signal_right->setX(0);
    //warning_signal_right->setY(1);

    //connect(timer,SIGNAL(timeout()), this, SLOT(updateLasers()));
    connect(checking_timer, SIGNAL(timeout()),this, SLOT (checkIfDead()));
    connect(warning_timer, SIGNAL(timeout()), this, SLOT(laser_warning_update()));
    //timer->start(1500);
    checking_timer->start(100);
    int warning_timer_time = 2000;

    warning_timer->start(warning_timer_time);







    overall_layout->addLayout(top_layout);
    overall_layout->addLayout(gridLayout);
    setFixedSize(450,450);
    this->setLayout(overall_layout);



}
/**
 * @brief Board::keyPressEvent moves around the stickman
 * @param event is a keyboard event like pressing the arrow keys
 */
void Board::keyPressEvent(QKeyEvent *event){

    int x = stickman_position->rx();
    int y = stickman_position->ry();

    switch (event->key()) {
    case Qt::Key_Left:
        if(stickman_position->rx() != 1)
            updateStickman(x,y,x-1,y);

        break;
    case Qt::Key_Right:
        if(stickman_position->rx() != board_size-2)
            updateStickman(x,y,x+1,y);

        break;
    case Qt::Key_Up:
        if(stickman_position->ry() != 1)
            updateStickman(x,y,x,y-1);

        break;
    case Qt::Key_Down:
        if(stickman_position->ry() != board_size-2)
            updateStickman(x,y,x,y+1);

        break;

        break;
    default:
        QWidget::keyPressEvent(event);
    }
    //QCoreApplication::processEvents();
    repaint();
    return;
}
/**
 * @brief Board::updateStickman updates the stickman position
 * @param px is the previous x position
 * @param py is the previous y position
 * @param nx is the new x position
 * @param ny is the new y position
 */
void Board::updateStickman(int px, int py, int nx, int ny) {
    labels[py*board_size+px]->clear();

    stickman_position->setX(nx);
    stickman_position->setY(ny);
}

/**
 * @brief Board::paintEvent paint event that draws the board and puts all the graphics on it
 * @param e is a paint event that is called through repaint()
 */
void Board::paintEvent(QPaintEvent *e) {

    int x = stickman_position->rx();
    int y = stickman_position->ry();

    labels[y*board_size+x]->setPixmap(*stickman);
    labels[y*board_size+x]->setScaledContents(true);

    //up laser shot
    if(laser_position_up->rx() >0 && laser_position_right->rx() <board_size){
    int lux= laser_position_up->rx();
    int luy= laser_position_up->ry();
    //labels[luy*board_size+lux]->setPixmap(*up_arrow_image);
    //labels[luy*board_size+lux]->setScaledContents(true);
    for(size_t i= 0; i<board_size; i++)
        labels[luy*board_size+lux-board_size*i]->setStyleSheet(("QLabel { background-color : turquoise; color : white; }"));
    }
    /*
    //down laser shot
    int ldx= laser_position_down->rx();
    int ldy= laser_position_down->ry();
    labels[ldy*board_size+ldx]->setPixmap(*down_arrow_image);
    labels[ldy*board_size+ldx]->setScaledContents(true);
    for(size_t i= 0; i<board_size; i++)
        labels[board_size*i+ldx]->setStyleSheet(("QLabel { background-color : turquoise; color : white; }"));
        */


    //left laser shot

    int llx= laser_position_left->rx();
    int lly= laser_position_left->ry();
    if(lly>0 && llx <board_size){
        labels[lly*board_size+llx]->setPixmap(*left_arrow_image);
        labels[lly*board_size+llx]->setScaledContents(true);

        for(size_t i= 1; i<board_size; i++){
            labels[lly*board_size + i]->setStyleSheet(("QLabel { background-color : turquoise; color : white; }"));
        }
    }

    //right laser shot
    if(laser_position_right->ry() >0 && laser_position_right->ry() <board_size){
        int lrx= laser_position_right->rx();
        int lry= laser_position_right->ry();
    //labels[lry*board_size+lrx]->setPixmap(*right_arrow_image);
    //labels[lry*board_size+lrx]->setScaledContents(true);
        for(size_t i= 0; i<board_size; i++){
            if(i !=7)
            labels[lry*board_size + i]->setStyleSheet(("QLabel { background-color : turquoise; color : white; }"));

        }
    }

    //down laser shot
    if(laser_position_down->rx()>0 && laser_position_down->rx() < board_size){
        int ldx= laser_position_down->rx();
        int ldy= laser_position_down->ry();
        for(size_t i = 0; i<board_size-1; i++)
        {
            labels[ldx + board_size*i]->setStyleSheet("QLabel { background-color: turquoise; color: white;}");
        }
    }




}
/**
 * @brief Board::updateLasers updates the positions of the lasers to the position of the warnings that come before
 */
void Board::updateLasers() {

    //updates laser position so it shoots in the warning spot
    laser_position_right->setY(warning_signal_right->ry());


    laser_position_up->setX(warning_signal_up->rx());

    laser_position_left->setY(warning_signal_left->ry());

    laser_position_down->setX(warning_signal_down->rx());
    score++;
    QString score_string= QString::number(score);

    score_label->setText("Score: " +score_string);
    repaint();



}
/**
 * @brief Board::checkIfDead checks to see whether you are dead and hit by obstacles, and displays game over message
 * @return true if dead
*/
bool Board::checkIfDead (){
    bool right_kill =  stickman_position->ry() == laser_position_right->ry();
    bool up_kill= stickman_position->rx() == laser_position_up->rx();
    bool left_kill= stickman_position->ry() == laser_position_left->ry();
    bool down_kill = stickman_position->rx() == laser_position_down->rx();
    //check if killed by laser
    if(right_kill || up_kill || left_kill || down_kill){

        this->gameOver();
        checking_timer->stop();
        warning_timer->stop();

        return true;

    }
    else
        return false;


}
/**
 * @brief Board::gameOver slot that emits the score and a signal that the player lost
 */
void Board::gameOver(){
    qDebug() << "The Score from the gameOver() function is: " << score;
    emit score_signal(score);
    emit you_lost();



}

/**
 * @brief Board::laser_warning_update changes the position of the warning lasers and also actually fires the lasers
 */
void Board::laser_warning_update (){
    //right laser
    //clear out the old warning
    if(warning_signal_right->ry() != laser_position_right->ry()){
        int x= warning_signal_right->rx();
        int y= warning_signal_right->ry();
        labels[y*board_size]->clear();
    }




    warning_signal_right->setX(0);
    std::uniform_int_distribution<int> position(1,6);
    warning_signal_right->setY(position(generator));
    int updated_x = warning_signal_right->rx();
    int updated_y = warning_signal_right->ry();

    labels[updated_y*board_size+updated_x]->setPixmap(*right_arrow_image);
    labels[updated_y*board_size+updated_x]->setScaledContents(true);

    //left laser
    if(warning_signal_left->rx() != laser_position_left->ry()){
        int x = warning_signal_left->rx();
        int y= warning_signal_left->ry();
        labels[y*board_size+x]->clear();
    }

   warning_signal_left->setX(7);
   std::uniform_int_distribution<int> left_pos(1,6);
   warning_signal_left->setY(position(generator));
   int updated_lx =warning_signal_left->rx();
   int updated_ly = warning_signal_left->ry();
   labels[updated_ly*board_size + updated_lx]->setPixmap(*left_arrow_image);
   labels[updated_ly*board_size + updated_lx]->setScaledContents(true);
    //do the same for the up warning
    if(warning_signal_up->rx() != laser_position_up->rx()){
        int ux= warning_signal_up->rx();
        int uy= warning_signal_up->ry();
        labels[uy*board_size+ux]->clear();
    }
    warning_signal_up->setY(7);
    std::uniform_int_distribution<int> up_pos(1,6);
    warning_signal_up->setX(up_pos(generator));
    int up_updated_x = warning_signal_up->rx();
    int up_updated_y= warning_signal_up->ry();
    labels[up_updated_y*board_size+up_updated_x]->setPixmap(*up_arrow_image);
    labels[up_updated_y*board_size+up_updated_x]->setScaledContents(true);

    //down warning
    if(warning_signal_down->rx() != laser_position_down->rx()){
        int dx = warning_signal_down->rx();
        int dy = warning_signal_down->ry();
        labels[dx]->clear();
    }
    warning_signal_down->setY(0);
    std::uniform_int_distribution<int> down_pos(1,6);
    warning_signal_down->setX(down_pos(generator));
    int new_down_x= warning_signal_down->rx();
    int new_down_y= warning_signal_down->ry();
    labels[new_down_x]->setPixmap(*down_arrow_image);
    labels[new_down_x]->setScaledContents(true);

    //fire ze lazers
    QTimer* fire_lasers = new QTimer;
    int warning_timer_time=4000;
    //update level every 10 scores and make timer go faster
    if(score!= 0 && score%10==0)
    {
        warning_timer_time -= 200;
        level++;
        qDebug() << "Level:" << QString::number(level);
    }
    QTimer::singleShot(warning_timer_time,this,SLOT(updateLasers()));


    //get rid of them quickly

    QTimer::singleShot(200,this,SLOT(endLaser()));




    QString level_string = QString::number(level);
    level_label->setText("Level: " + level_string);

    repaint();

}
/**
 * @brief Board::endLaser clears out the laser so the next laser can be fired
 */
void Board::endLaser(){
    //clear up laser
    if(laser_position_up->rx() != -1){
        if(warning_signal_up->rx() != laser_position_up->rx())
            labels[laser_position_up->ry()*board_size+laser_position_up->rx()]->clear();
        labels[laser_position_up->ry()*board_size+laser_position_up->rx()]->setStyleSheet(("QLabel { background-color : red; color : white; }"));
        for(size_t i =1; i<board_size; i++)
            labels[laser_position_up->ry()*board_size+laser_position_up->rx()-board_size*i]->setStyleSheet(("QLabel { background-color : yellow; color : white; }"));
        labels[laser_position_up->rx()]->setStyleSheet(("QLabel { background-color : red; color : white; }"));
    }
    //clear down laser
    if(laser_position_down->rx() != -1){
        if(warning_signal_down->rx() != laser_position_down->rx()){
            labels[laser_position_down->rx()]->clear();
            labels[laser_position_down->rx()]->setStyleSheet("QLabel { background-color : red; color : white; }");
        }
        for(size_t i= 1; i<board_size-1; i++){
            labels[laser_position_down->rx() +board_size*i]->setStyleSheet("QLabel {background-color: yellow; color: white}");
        }
    }

    //clear right laser
    if(laser_position_right->ry() != -1)
    {
        for(size_t i=0; i<board_size-1; i++){

            if(i==0)
                labels[laser_position_right->ry()*board_size + i]->setStyleSheet(("QLabel { background-color : red; color : white; }"));
            //prevents erasing if in the same spot
            if(warning_signal_right->ry() != laser_position_right->ry())
                labels[laser_position_right->ry()*board_size + i]->clear();

            if ( i !=0)
                labels[laser_position_right->ry()*board_size + i]->setStyleSheet(("QLabel { background-color : yellow; color : white; }"));




        }
    }

    //clear leftlaser
    if (laser_position_left->ry() != -1){
        for(size_t i = board_size-1; i>0; i--){
           if(i == 7){
                labels[laser_position_left->ry()*board_size + i]->setStyleSheet(("QLabel { background-color : red; color : white; }"));
                if(warning_signal_left->ry() != laser_position_left->ry()){
                    labels[laser_position_left->ry()*board_size + i]->clear();
                }
           }
            else{
                labels[laser_position_left->ry()*board_size + i]->setStyleSheet(("QLabel { background-color : yellow; color : white; }"));
           }
        }
}
    laser_position_up->setX(-1);
    laser_position_right->setY(-1);
    laser_position_left->setY(-1);
    laser_position_down->setX(-1);
    repaint();
    return;
}
/**
 * @brief Board::back_to_menu emits a signal that main menu was clicked and should return there
 */
void Board::back_to_menu(){
    emit main_menu_clicked();
    //this->close();

}
/**
 * @brief Board::emit_signal emits signal that main menu was clicked and should return
 */
void Board::emit_signal(){

    emit main_menu_clicked();

}
/**
 * @brief Board::score_slot emits score signal and passes along the score
 * @param n is the value to be passed, should be the score
 */
void Board::score_slot(int n ){
    emit score_signal(n);

}



