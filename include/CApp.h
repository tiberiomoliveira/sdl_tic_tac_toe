#ifndef _CAPP_H_
#define _CAPP_H_

#include "CSurface.h"
#include "CEvent.h"

#define SCREEN_WIDTH  600
#define SCREEN_HEIGHT 600
#define MATRIX_SIZE   3

class CApp : public CEvent{
  public:
    CApp();
    int on_execute();
    void reset();
    void set_cell(int id, int type);
    void verify_winner(int id);

    bool on_init();
    void on_event(SDL_Event* event);
    void on_lbutton_down(int m_x, int m_y);
    void on_key_down(SDLKey sym, SDLMod mod, Uint16 unicode);
    void on_exit();
    void on_loop();
    void on_render();
    void on_cleanup();

  private:
    int  next_pos(int id, int x_dir, int y_dir);
    bool check_anti_diag(int id);
    bool check_diag(int id);
    bool check_pos(int id, int pos, int x_dir, int y_dir);

    enum {
      GRID_TYPE_NONE = 0,
      GRID_TYPE_X,
      GRID_TYPE_O
    };
    enum {
      FINAL_UNKNOW,
      FINAL_X_WON,
      FINAL_O_WON,
      FINAL_DRAW
    };

    bool         running;
    bool         finish;
    SDL_Surface* surf_display;
    SDL_Surface* surf_grid;
    SDL_Surface* surf_x;
    SDL_Surface* surf_x_won;
    SDL_Surface* surf_o;
    SDL_Surface* surf_o_won;
    SDL_Surface* surf_draw;
    int          grid[9];
    int          current_player;
    int          x_points;
    int          o_points;
    int          grid_used;
    int          result;
};

#endif
