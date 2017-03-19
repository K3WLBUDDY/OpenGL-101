#ifndef DENGINE_H
#define DENGINE_H

#include <QMainWindow>
#include <SDL2/SDL.h>

namespace Ui {
class DEngine;
}

class DEngine : public QMainWindow
{
    Q_OBJECT

public:
    explicit DEngine(QWidget *parent = 0);
     int image_w, image_h;
     SDL_Window* _sdlWindow;

    ~DEngine();

private:
    Ui::DEngine *ui;





};

#endif // DENGINE_H