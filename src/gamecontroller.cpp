#include "gamecontroller.h"
#include <QDebug>
GameController::GameController(GameModel& gm){
    timerId = startTimer(DELAY);
    this->gm = &gm;
    visitor = (new Visitor(this->gm));
    gm.get_player().get_hand()->first_random_card(*visitor);

}

GameController::~GameController(){
    delete visitor;
}

void GameController::timerEvent(QTimerEvent *)
{
    if(!gm->get_enemy().get_alive() && !gm->get_tower().get_alive()){
        gm->change_inGame(false);
    }
    if(!gm->get_inGame()){
        return;
    }

    static int ms_accum = 0;
    static int ms_accum_for_money = 0;
    ms_accum_for_money += DELAY;
    ms_accum += DELAY;

    if(ms_accum >= 500){
        gm->enemy_journey();
    }
    if(ms_accum > 500){
        gm->enemy_attack();
        ms_accum = 0;
    }
    if(ms_accum_for_money % 900 ==0){
        gm->tower_attack();
    }
    if(ms_accum_for_money % 900 == 0 && !gm->get_leons().empty()){
        gm->leon_journey();
        gm->notify();
    }
    if(ms_accum_for_money > 30000){
        gm->get_player().add_money(50);
        ms_accum_for_money = 0;
    }

    gm->notify();

}


void GameController::keyboardHandler(QKeyEvent* e)
{
    qDebug() << "ggg";
    int key = e->key();

    std::vector<int> coord_info;
    int command = 0;
    int count_for_slow;
    switch(key){

    case Qt::Key_Left:
        count_for_slow = gm->get_player().get_count_for_slow();
        coord_info = gm->check_coords_map(-1, 0, count_for_slow, 0);
        gm->get_player().player_journey(coord_info[0], coord_info[1]);
        gm->get_player().change_direction_attack(left);
        break;
    case Qt::Key_Right:
        count_for_slow = gm->get_player().get_count_for_slow();
        coord_info = gm->check_coords_map(1, 0, count_for_slow, 0);
        gm->get_player().player_journey(coord_info[0], coord_info[1]);
        gm->get_player().change_direction_attack(right);
        break;
    case Qt::Key_Up:
        count_for_slow = gm->get_player().get_count_for_slow();
        coord_info = gm->check_coords_map(0, -1, count_for_slow, 0);
        gm->get_player().player_journey(coord_info[0], coord_info[1]);
        gm->get_player().change_direction_attack(up);
        break;
    case Qt::Key_Down:
        count_for_slow = gm->get_player().get_count_for_slow();
        coord_info = gm->check_coords_map(0, 1, count_for_slow, 0);
        gm->get_player().player_journey(coord_info[0], coord_info[1]);
        gm->get_player().change_direction_attack(down);
        break;
    case Qt::Key_Space:
        if(gm->get_player().get_typeBattle() == close_combat){
            command = 1;
        }
        else{
            command = 2;
        }
        break;
    case Qt::Key_Shift:
        gm->get_player().change_typeBattle();
        break;
    }

    if (command == 1){
        gm->player_close_attack();
    }
    else if(command == 2){
        gm->player_ranged_attack();
    }
    gm->notify();

}


void GameController::mouseMoveHandler(QMouseEvent * e)
{
    std::vector<QPushButton*> btns = gm->get_buttons().get_my_buttons();
    for(QPushButton* btn : btns){
        if(btn && btn->geometry().contains(e->pos())){
            QString str = btn->property("spellName").toString();
            if (e->buttons() & Qt::LeftButton){
                QDrag *drag = new QDrag(this);
                QMimeData *mime = new QMimeData;
                mime->setText(str);
                drag->setMimeData(mime);
                QPixmap picture(40, 40);
                picture.fill("red");
                drag->setPixmap(picture);
                drag->setHotSpot(QPoint(0, 0));
                drag->exec(Qt::CopyAction | Qt::MoveAction);

            }
            break;
        }
    }
    gm->notify();
}

void GameController::mouseDragHandler(QDragEnterEvent *e)
{
    e->acceptProposedAction();
}

void GameController::mouseDropHandler(QDropEvent *e)
{
    QString str1 = e->mimeData()->text();
    std::string str = str1.toStdString();
    QPoint pos = e->pos();
    int x = pos.x();
    int y = pos.y();
    // Visitor* visitor = (new Visitor(gm));
    gm->get_player().get_hand()->find_and_use(*visitor, str, x, y);
    e->acceptProposedAction();
    gm->notify();
    // delete visitor;
}

