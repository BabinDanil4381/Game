#include "gameview.h"
#include <QDebug>
GameView::GameView(GameModel* gm) {
    this->gm = gm;
    this->gm->add_observer(this);
    resize(DOT_WIDTH * (FIELD_WIDTH), DOT_HEIGHT * (FIELD_HEIGHT + 3));
    this->setWindowTitle("Game");
    setAcceptDrops(true);
    setFocusPolicy(Qt::StrongFocus);
    setFocus();
    input = nullptr;
    load_sourse();
    show_buttons(*gm);
}

void GameView::load_sourse()
{
    QPixmap image_map("C:/Users/tomil/Downloads/map.jpg");
    mapPixmap = image_map.copy();

    QPixmap image_boloto("C:/Users/tomil/Downloads/boloto1.jpg");
    bolotoPixmap = image_boloto.copy();
    bolotoPixmap.setMask(image_boloto.createMaskFromColor(Qt::white));

    QPixmap image_user("C:/Users/tomil/Downloads/user1.jpg");
    userPixmap = image_user.copy();
    userPixmap.setMask(image_user.createMaskFromColor(Qt::white));

    QPixmap image_enemy("C:/Users/tomil/Downloads/enemy.jpg");
    enemyPixmap = image_enemy.copy();
    enemyPixmap.setMask(image_enemy.createMaskFromColor(Qt::white));


    QPixmap image_plant("C:/Users/tomil/Downloads/plant.jpg");
    plantPixmap = image_plant.copy();
    plantPixmap.setMask(image_plant.createMaskFromColor(Qt::white));

    QPixmap tower("C:/Users/tomil/Downloads/tower1.jpg");
    towerPixmap = tower.copy();
    towerPixmap.setMask(tower.createMaskFromColor(Qt::white));

    QPixmap trap("C:/Users/tomil/Downloads/trap.jpg");
    trapPixmap = trap.copy();
    trapPixmap.setMask(trap.createMaskFromColor(Qt::white));

    QPixmap build("C:/Users/tomil/Downloads/build.png");
    buildPixmap = build.copy();
    buildPixmap.setMask(build.createMaskFromColor(Qt::white));

    QPixmap ln("C:/Users/tomil/Downloads/leon.jpg");
    leonPixmap = ln.copy();
    leonPixmap.setMask(ln.createMaskFromColor(Qt::white));
}

void GameView::show_buttons(GameModel &gm)
{
    auto& buttons_ref = gm.get_buttons().get_my_buttons();
    // int x = 10;
    // int y = 500;

    for (auto it = buttons_ref.begin(); it != buttons_ref.end(); ++it) {
        auto* btn = *it;
        if (btn) {
            // Если кнопка уже создана, меняем ей родителя
            btn->setParent(this);
            // btn->setGeometry(x, y, 80, 30);
            btn->show();
            // x += 90;
        }
    }

}

void GameView::set_handler(HandlerEvent *input)
{
    this->input = input;
}

void GameView::updating()
{
    update();
}

void GameView::keyPressEvent(QKeyEvent *e)
{
    input->keyboardHandler(e);
}

void GameView::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    drawing_game(painter, *gm);
}

void GameView::mouseMoveEvent(QMouseEvent *e)
{
    input->mouseMoveHandler(e);
}

void GameView::dragEnterEvent(QDragEnterEvent *e)
{
    input->mouseDragHandler(e);
}

void GameView::dropEvent(QDropEvent *e)
{
    input->mouseDropHandler(e);
}


void GameView::drawing_game(QPainter& painter, GameModel& gm)

{
    if (gm.get_player().get_health() != 0 && gm.get_inGame() /*&& myGame.get_player().get_score() < 300*/){

        drawing_map(painter, gm);
        if(!gm.get_leons().empty()) drawing_leon(painter, gm);
        drawing_user(painter, gm);
        if(gm.get_player().get_zoneX() != 100){
            drawing_zone(painter, gm);
        }
        gm.get_player().set_zoneX(100);

        if(gm.get_enemy().get_alive()){
            drawing_enemy(painter, gm);
        }
        if(gm.get_tower().get_alive() == true){
            drawing_tower(painter, gm);
        }
        drawing_info(painter, gm);
    }
    else{
        drawing_gameOver(painter);
        gm.change_inGame(false);
    }
}

void GameView::drawing_enemy(QPainter& painter, GameModel& gm)
{
    int e_x = gm.get_enemy().get_coord_x();
    int e_y = gm.get_enemy().get_coord_y();

    painter.drawPixmap(QRect(e_x * DOT_HEIGHT, e_y * DOT_WIDTH, FIELD_HEIGHT, FIELD_WIDTH), enemyPixmap);
    qDebug() << gm.get_flagAtack();
    if(gm.get_flagAtack() == 1){
        painter.setBrush(QColor(255, 0, 0, 50));
        painter.drawEllipse((e_x-1) * DOT_HEIGHT, (e_y-1) * DOT_WIDTH, FIELD_HEIGHT * 3, FIELD_WIDTH * 3);
    }
}

void GameView::drawing_zone(QPainter& painter, GameModel& gm)
{
    painter.setBrush(QColor(0, 255, 0, 50));
    painter.drawRect(gm.get_player().get_zoneX() * DOT_HEIGHT, gm.get_player().get_zoneY() * DOT_WIDTH, FIELD_HEIGHT * 3, FIELD_WIDTH * 3);
}

void GameView::drawing_tower(QPainter& painter, GameModel& gm)
{
    int left_x = gm.get_tower().get_left_x();
    int down_y = gm.get_tower().get_down_y();

    painter.drawPixmap(QRect(left_x * DOT_HEIGHT, down_y * DOT_WIDTH, FIELD_HEIGHT * 3, FIELD_WIDTH * 3), towerPixmap);
}

void GameView::drawing_info(QPainter& painter,  GameModel& gm)
{
    painter.setFont(QFont("Arial", 15));
    painter.setPen(Qt::green);
    painter.drawText(10, 20, QString("Score %1").arg(gm.get_player().get_score()));
    painter.drawText(10, 40, QString("Health %1").arg(gm.get_player().get_health()));
    painter.drawText(10, 60, QString("Enemy %1").arg(gm.get_enemy().get_health()));
    painter.drawText(10, 80, QString("Money %1").arg(gm.get_player().get_money()));
    painter.drawText(10, 100, QString("Tower %1").arg(gm.get_tower().get_health()));
}

void GameView::drawing_gameOver(QPainter& painter)
{
    painter.drawText(painter.window(), Qt::AlignCenter, "Game Over");
}

void GameView::drawing_leon(QPainter &painter, GameModel& gm)
{
    for(Leon* l : gm.get_leons()){
        if(l != nullptr){
            int x = l->get_leon_x();
            int y = l->get_leon_y();
            qDebug() << x << y;
            painter.drawPixmap(QRect(x * DOT_HEIGHT, y * DOT_WIDTH, FIELD_HEIGHT, FIELD_WIDTH), leonPixmap);
        }

    }
}

void GameView::drawing_user(QPainter& painter, GameModel& gm)
{
    int x = gm.get_player().get_x();
    int y = gm.get_player().get_y();

    painter.setBrush(QColor(0, 0, 255, 50));
    painter.drawEllipse((x-1) * DOT_HEIGHT , (y-1) * DOT_WIDTH , FIELD_HEIGHT * 3, FIELD_WIDTH * 3);
    painter.drawPixmap(QRect(x * DOT_HEIGHT, y * DOT_WIDTH, FIELD_HEIGHT, FIELD_WIDTH), userPixmap);
}

void GameView::drawing_map(QPainter& painter, GameModel& gm)
{
    painter.drawPixmap(QRect(0 , 0, DOT_HEIGHT * FIELD_HEIGHT, DOT_WIDTH * FIELD_WIDTH), mapPixmap);
    for(int i = 0; i < FIELD_HEIGHT; i++){
        for(int j = 0; j < FIELD_WIDTH; j++){
            if(gm.get_map().get_point(i, j).get_point_opt() == lock){
                painter.drawPixmap(QRect(i * DOT_HEIGHT, j * DOT_WIDTH, FIELD_HEIGHT, FIELD_WIDTH), plantPixmap);
            }
            if(gm.get_map().get_point(i, j).get_point_opt() == slow){
                painter.drawPixmap(QRect(i * DOT_HEIGHT, j* DOT_WIDTH, FIELD_HEIGHT, FIELD_WIDTH), bolotoPixmap);
            }
            if(gm.get_map().get_point(i, j).get_point_opt() == trap){
                painter.drawPixmap(QRect(i * DOT_HEIGHT, j* DOT_WIDTH, FIELD_HEIGHT, FIELD_WIDTH), trapPixmap);
            }
            if(gm.get_map().get_point(i, j).get_point_opt() == build){
                painter.drawPixmap(QRect(i * DOT_HEIGHT, j* DOT_WIDTH, FIELD_HEIGHT, FIELD_WIDTH), buildPixmap);
            }

        }
    }
}




