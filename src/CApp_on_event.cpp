#include "CApp.h"

void
CApp::on_event(SDL_Event* event) {
  CEvent::on_event(event);
}

void
CApp::on_lbutton_down(int m_x, int m_y) {
  if (finish)
    return;
  int id = m_x / (SCREEN_WIDTH / MATRIX_SIZE);
  id += MATRIX_SIZE * (m_y / (SCREEN_HEIGHT / MATRIX_SIZE));

  if (grid[id] != GRID_TYPE_NONE)
    return;

  if (current_player == 0) {
    set_cell(id, GRID_TYPE_X);
    current_player = 1;
  }
  else {
    set_cell(id, GRID_TYPE_O);
    current_player = 0;
  }

  ++grid_used;
  verify_winner(id);
}

void
CApp::on_key_down(SDLKey sym, SDLMod mod, Uint16 unicode) {
  if (!finish)
    return;
  if (sym == SDLK_RETURN) {
    reset();
  }
}

void
CApp::on_exit() {
  running = false;
}

