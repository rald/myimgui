#include "imgui.h"



// Rendering function
void render() {   
  static int bgcolor = 0x77;
  static char sometext[80] = "Some text";

  // clear screen
  drawrect(0,0,640,480,bgcolor);

  imgui_prepare();

  button(GEN_ID,50,50);
  
  button(GEN_ID,150,50);
  
  if (button(GEN_ID,50,150))
    bgcolor = (SDL_GetTicks() * 0xc0cac01a) | 0x77;
  
  if (button(GEN_ID,150,150))
    exit(0);

  textfield(GEN_ID,50,250,sometext);

  int slidervalue = bgcolor & 0xff;
  if (slider(GEN_ID, 500, 40, 255, &slidervalue)) {
    bgcolor = (bgcolor & 0xffff00) | slidervalue;
  }

  slidervalue = ((bgcolor >> 8) & 0xff);
  if (slider(GEN_ID, 550, 40, 255, &slidervalue)) {
    bgcolor = (bgcolor & 0xff00ff) | (slidervalue << 8);
  }

  slidervalue = ((bgcolor >> 16) & 0xff);
  if (slider(GEN_ID, 600, 40, 255, &slidervalue)) {
    bgcolor = (bgcolor & 0x00ffff) | (slidervalue << 16);
  }


  imgui_finish();
  

  // update the screen
    SDL_UpdateRect(gScreen, 0, 0, 640, 480);    

  // don't take all the cpu time
  SDL_Delay(10); 
}



// Entry point
int main(int argc, char *argv[]) {
  // Initialize SDL's subsystems - in this case, only video.
  if (SDL_Init(SDL_INIT_VIDEO) < 0) {
    fprintf(stderr, "Unable to init SDL: %s\n", SDL_GetError());
    exit(1);
  }

  // Register SDL_Quit to be called at exit; makes sure things are
  // cleaned up when we quit.
  atexit(SDL_Quit);
    
  // Attempt to create a 640x480 window with 32bit pixels.
  gScreen = SDL_SetVideoMode(640, 480, 32, SDL_SWSURFACE);

  // Enable keyboard repeat to make sliders more tolerable
  SDL_EnableKeyRepeat(SDL_DEFAULT_REPEAT_DELAY, SDL_DEFAULT_REPEAT_INTERVAL);
  // Enable keyboard UNICODE processing for the text field.
  SDL_EnableUNICODE(1);

  // If we fail, return error.
  if (gScreen == NULL) {
    fprintf(stderr, "Unable to set up video: %s\n", SDL_GetError());
    exit(1);
  }

  SDL_Surface *temp = SDL_LoadBMP("images/font14x24.bmp");
  gFont = SDL_ConvertSurface(temp, gScreen->format, SDL_SWSURFACE);
  SDL_FreeSurface(temp);
  
  // Seeing through the black areas in the font may be a good idea..
  SDL_SetColorKey(gFont, SDL_SRCCOLORKEY, 0);  

  // Main loop: loop forever.
  while (1) {
    // Render stuff
		render();

    // Poll for events, and handle the ones we care about.
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
    	switch (event.type) {
    		case SDL_MOUSEMOTION:
	        // update mouse position
	        uistate.mousex = event.motion.x;
	        uistate.mousey = event.motion.y;
	        break;
	      case SDL_MOUSEBUTTONDOWN:
	        // update button down state if left-clicking
	        if (event.button.button == 1)
	          uistate.mousedown = 1;
	        break;
	      case SDL_MOUSEBUTTONUP:
	        // update button down state if left-clicking
	        if (event.button.button == 1)
	          uistate.mousedown = 0;
	        break;
	      case SDL_KEYDOWN:
	        // If a key is pressed, report it to the widgets
	        uistate.keyentered = event.key.keysym.sym;
	        uistate.keymod = event.key.keysym.mod;
	        // if key is ASCII, accept it as character input
	        if ((event.key.keysym.unicode & 0xFF80) == 0)
	          uistate.keychar = event.key.keysym.unicode & 0x7f;        
	        break;
	      case SDL_KEYUP:                  
	        switch (event.key.keysym.sym) {
	        	case SDLK_ESCAPE:
	          // If escape is pressed, return (and thus, quit)
	          return 0;
	        }
	        break;
	      case SDL_QUIT:
	        return(0);
	    }
		}
  }
  return 0;
}

