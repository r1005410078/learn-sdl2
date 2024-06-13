#include<stdio.h>
#include<stdbool.h>
#include<SDL2/SDL.h>

bool is_running = true;
SDL_Window* window = NULL;
SDL_Renderer* renderer = NULL;

bool initialize_window(void) {
  if (SDL_Init(SDL_INIT_VIDEO) != 0 ) {
    printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
    return false;
  }

  window = SDL_CreateWindow(
    "Hello, World!", 
    SDL_WINDOWPOS_CENTERED, 
    SDL_WINDOWPOS_CENTERED, 
    640, 480, 
    SDL_WINDOW_SHOWN
  );

  if (window == NULL) {
    printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
    return false;
  }

  renderer = SDL_CreateRenderer(window, -1, 0);

  if (renderer == NULL) {
    printf("Renderer could not be created! SDL_Error: %s\n", SDL_GetError());
    return false;
  }
  
  return true;
}

void process_input(void) {
  SDL_Event event;
  SDL_PollEvent(&event);

  switch (event.type)
  {
    case SDL_QUIT:
      is_running = false;
      break;
    case SDL_KEYDOWN:
      if (event.key.keysym.sym == SDLK_ESCAPE) {
        is_running = false;
      }
      break;
    default:
      break;
  }
}

void update(void) {
  // TODO
}

void render(void) {
  // TODO
  SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
  SDL_RenderClear(renderer);

  SDL_RenderPresent(renderer);
}

void setup(void) {
  // TODO
}

int main(void) {
  is_running = initialize_window();

  setup();

  while (is_running)
  {
    // 处理事件
    process_input();
    // 更新
    update();
    // 渲染
    render();
  }
  
  return 0;
}