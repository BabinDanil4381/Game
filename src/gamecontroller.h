#ifndef GAMECONTROLLER_H
#define GAMECONTROLLER_H
#include <QWidget>
#include <QTimer>
#include <QFont>
#include <QDebug>
#include <QKeyEvent>
#include <QMouseEvent>
#include <QLabel>
#include <vector>
#include<QDrag>
#include<QMimeData>
#include <QPixmap>
#include <QPoint>
#include "handlerevent.h"
#include "gamemodel.h"
#include "visitor.h"

class GameController : public QObject, public HandlerEvent
{
private:
    int timerId;
    GameModel* gm;
    Visitor* visitor;

protected:
    void timerEvent(QTimerEvent*) override;
    void keyboardHandler(QKeyEvent* e) override;
    void mouseMoveHandler(QMouseEvent* e) override;
    void mouseDragHandler(QDragEnterEvent* e) override;
    void mouseDropHandler(QDropEvent* e) override;



public:
    GameController(GameModel& gm);
    ~GameController();
};


#endif // GAMECONTROLLER_H
