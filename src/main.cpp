#include <QApplication>
#include <QMainWindow>
#include "gamemodel.h"
#include "gameview.h"
#include "gamecontroller.h"

int main(int argc, char* argv[])
{
    QApplication app(argc, argv);
    app.setWindowIcon(QIcon(":/images/images/user1.jpg"));

    GameModel* model = new GameModel();
    GameView* view = new GameView(model);
    GameController* controller = new GameController(*model);
    view->set_handler(controller);

    QMainWindow window;
    window.setCentralWidget(view);
    window.setWindowTitle("Game");
    window.resize(650, 800);
    window.show();

    return app.exec();
}
