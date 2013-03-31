#include "CApp.h"

void CApp::on_render() {
  CSurface::on_draw(surf_grid, surf_display, 0, 0);

  for (int i = 0; i < 9; ++i) {
    int x = (i % MATRIX_SIZE) * (SCREEN_WIDTH / MATRIX_SIZE);
    int y = (i / MATRIX_SIZE) * (SCREEN_HEIGHT / MATRIX_SIZE);

    if (grid[i] == GRID_TYPE_X)
      CSurface::on_draw(surf_x, surf_display, x, y);
    else
      if (grid[i] == GRID_TYPE_O)
        CSurface::on_draw(surf_o, surf_display, x, y);
  }
  switch (result) {
    case FINAL_UNKNOW:
      break;
    case FINAL_X_WON:
      CSurface::on_draw(surf_x_won, surf_display,
                        SCREEN_WIDTH / 2 - surf_x_won->w / 2,
                        SCREEN_HEIGHT / 2 - surf_x_won->h / 2);
      break;
    case FINAL_O_WON:
      CSurface::on_draw(surf_o_won, surf_display,
                        SCREEN_WIDTH / 2 - surf_o_won->w / 2,
                        SCREEN_HEIGHT / 2 - surf_o_won->h / 2);
      break;
    case FINAL_DRAW:
      CSurface::on_draw(surf_draw, surf_display,
                        SCREEN_WIDTH / 2 - surf_draw->w / 2,
                        SCREEN_HEIGHT / 2 - surf_draw->h / 2);
      break;
  }

  SDL_Flip(surf_display);
}
