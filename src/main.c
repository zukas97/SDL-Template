#include <SDL2/SDL_render.h>
#include <SDL2/SDL_timer.h>
#include <SDL2/SDL_video.h>
#include <stdio.h>
#include <SDL2/SDL.h>
#include <stdbool.h>

#define WIN_HEIGHT 720
#define WIN_WIDTH 1280

#define FPS 60
#define FRAME_TIME (1000/FPS)

bool running = false;

bool init(SDL_Window** win, SDL_Renderer** rend) {
	if (SDL_Init(SDL_INIT_EVERYTHING)) {
		perror("SDL");
		return false;
	}
	*win = SDL_CreateWindow(
		"title",
		SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED,
		WIN_WIDTH,
		WIN_HEIGHT,
		0
			);

	if (!*win) {
		perror("window");
		return false;
	}

	*rend = SDL_CreateRenderer(*win, -1, SDL_RENDERER_ACCELERATED || SDL_RENDERER_PRESENTVSYNC);

	if (!*rend) {
		perror("renderer");
		return false;
	}

	printf("init complete\n");
	return true;
}

void input() {
	SDL_Event event;
	if (SDL_PollEvent(&event)) {
		switch (event.type) {
			case SDL_QUIT:
				running = false;
				printf("break\n");
				break;
			case SDL_KEYUP:
				break;
			case SDL_KEYDOWN:
				switch (event.key.keysym.sym) {
					case SDLK_ESCAPE:
						running = false;
						break;
				break;
				}
		}
	}
}

void render(SDL_Renderer* rend) {
	SDL_SetRenderDrawColor(rend, 0,0 ,0, 255);
	SDL_RenderClear(rend);
	SDL_RenderPresent(rend);

}

void update(float delta) {
	int last_frame_time;
	int wait_time = FRAME_TIME - (SDL_GetTicks() - last_frame_time);
	if (wait_time > 0 && wait_time <= FRAME_TIME) {
		SDL_Delay(wait_time);
	}

	delta = (SDL_GetTicks() - last_frame_time) / 1000.0f;

	last_frame_time = SDL_GetTicks();

}

void destroy(SDL_Window** win, SDL_Renderer** rend) {
	SDL_DestroyRenderer(*rend);
	SDL_DestroyWindow(*win);
	SDL_Quit();
}

int main() {
	SDL_Window* win;
	SDL_Renderer* rend;
	float delta;
	running = init(&win, &rend);

	while (running) {
		input();
		render(rend);
		update(delta);
	}
	printf("exiting\n");
	SDL_DestroyRenderer(rend);
	SDL_DestroyWindow(win);
	SDL_Quit();
	//destroy(&win, &rend);
}
