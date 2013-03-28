#ifndef _CAPP_H_
#define _CAPP_H_

#include "CSurface.h"
#include "CEvent.h"

#define SCREEN_WIDTH  640
#define SCREEN_HEIGHT 480

class CApp : public CEvent{
  public:
    CApp();
    int on_execute();

  public:
    bool on_init();
    void on_event(SDL_Event* event);
    void on_exit();
    void on_loop();
    void on_render();
    void on_cleanup();

  private:
    bool         running;
    SDL_Surface* surf_display;
    SDL_Surface* surf_test;
};

#endif
