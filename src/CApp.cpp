#include "CApp.h"

CApp::CApp ()
: running(true),
  finish(false),
  current_player(0),
  grid_used(0),
  result(FINAL_UNKNOW) {
  surf_display = NULL;
  surf_grid    = NULL;
  surf_x       = NULL;
  surf_x_won   = NULL;
  surf_o       = NULL;
  surf_o_won   = NULL;
  surf_draw    = NULL;
}

int
CApp::on_execute() {
  if (!on_init())
    return -1;

  SDL_Event event;

  while (running) {
    while (SDL_PollEvent(&event))
      on_event(&event);

    on_loop();
    on_render();
  }

  on_cleanup();

  return 0;
}

void
CApp::reset() {
  finish         = false;
  current_player = 0;
  grid_used      = 0;
  result         = FINAL_UNKNOW;

  for (int i = 0; i < 9; ++i)
    grid[i] = GRID_TYPE_NONE;
}

void
CApp::set_cell(int id, int type) {
  if (id < 0 || id >= 9) return;
  if (type < 0 || type > GRID_TYPE_O) return;

  grid[id] = type;
}

void
CApp::verify_winner(int id) {
  if (check_pos(id, next_pos(id, 0, 1), 0, 1) ||
      check_pos(id, next_pos(id, 1, 0), 1, 0) ||
      (check_anti_diag(id) &&
       check_pos(id, next_pos(id, 1, -1), 1, -1)) ||
      (check_diag(id) &&
       check_pos(id, next_pos(id, 1, 1), 1, 1))) {
    if (grid[id] == GRID_TYPE_X)
      result = FINAL_X_WON;
    else
      result = FINAL_O_WON;
    finish = true;
  }
  if (grid_used == MATRIX_SIZE * MATRIX_SIZE) {
    result = FINAL_DRAW;
    finish = true;
  }
}

bool
CApp::check_anti_diag(int id) {
  int x = id % MATRIX_SIZE;
  int y = id / MATRIX_SIZE;
  return ((x + y == MATRIX_SIZE - 1) ? true : false);
}

bool
CApp::check_diag(int id) {
  int x = id % MATRIX_SIZE;
  int y = id / MATRIX_SIZE;
  return x == y ? true : false;
}

bool
CApp::check_pos(int id, int pos, int x_dir, int y_dir) {
  if (id == pos)
    return true;

  if (grid[id] != grid[pos])
    return false;

  return check_pos(id, next_pos(pos, x_dir, y_dir), x_dir, y_dir);
}

int
CApp::next_pos(int id, int x_dir, int y_dir) {
  int x = id % MATRIX_SIZE + x_dir;
  x = x < 0 ? MATRIX_SIZE - 1 : x >= MATRIX_SIZE ? 0 : x;

  int y = id / MATRIX_SIZE + y_dir;
  y = (y < 0 ? MATRIX_SIZE - 1 : y >= MATRIX_SIZE ? 0 : y) * MATRIX_SIZE;

  return x + y;
}

int
main(int argc, char* argv[]) {
  CApp the_app;

  return the_app.on_execute();
}
