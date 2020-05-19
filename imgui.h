#ifndef IMGUI_H
#define IMGUI_H

#include <stdlib.h>
#include <string.h>
#include <SDL/SDL.h>



// If you're going to render widgets to the same
// UI from different source files, you can avoid
// ID collisions by defining IMGUI_SRC_ID before
// this define block:
#ifdef IMGUI_SRC_ID
#define GEN_ID ((IMGUI_SRC_ID) + (__LINE__))
#else
#define GEN_ID (__LINE__)
#endif

struct UIState {
  int mousex;
  int mousey;
  int mousedown;

  int hotitem;
  int activeitem;

  int kbditem;
  int keyentered;
  int keymod;
  int keychar;
  
  int lastwidget;
}; 

extern SDL_Surface *gScreen;
extern SDL_Surface *gFont;
extern struct UIState uistate; 

void drawchar(char ch, int x, int y);
void drawstring(char * string, int x, int y);
void drawrect(int x, int y, int w, int h, int color);
int regionhit(int x, int y, int w, int h);
int button(int id, int x, int y);
int slider(int id, int x, int y, int max, int *value);
int textfield(int id, int x, int y, char *buffer);
void imgui_prepare();
void imgui_finish();

#endif

