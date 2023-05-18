
/* headers */
#include <stdio.h>
#include <stdlib.h>

#include <SDL2/SDL.h>

#include <GL/gl.h>
#include <GL/oscontext.h>

#include "ui.h"

/* constants */
#define WIDTH 800
#define HEIGHT 600
#define BPP 16

/* globals */
ostgl_context *ctx;
void *pixels;
int running;
SDL_Window *window;
SDL_Renderer *renderer;
SDL_Texture *texture;
int width;
int height;

/* open window, handle inputs */
int ui_loop(int argc, char **argv, const char *name)
{
	/* init sdl */
	SDL_Init(SDL_INIT_VIDEO);

	/* yeah */
	width = WIDTH;
	height = HEIGHT;

	/* alloc */
	pixels = malloc(WIDTH * HEIGHT * (BPP / 8));
	ctx = ostgl_create_context(WIDTH, HEIGHT, BPP, &pixels, 1);
	ostgl_make_current(ctx, 0);

	/* call user functions */
	init();
	reshape(WIDTH, HEIGHT);

	/* create sdl context */
	window = SDL_CreateWindow(name, SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED, WIDTH, HEIGHT, SDL_WINDOW_RESIZABLE);

	renderer = SDL_CreateRenderer(window, -1,
		SDL_RENDERER_PRESENTVSYNC | SDL_RENDERER_SOFTWARE);

	texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGB565,
		SDL_TEXTUREACCESS_STREAMING, WIDTH, HEIGHT);

	/* main loop */
	running = SDL_TRUE;
	while (running == SDL_TRUE)
	{
		/* variables */
		SDL_Event event;

		/* event poll loop */
		while (SDL_PollEvent(&event))
		{
			switch (event.type)
			{
				/* quit */
				case SDL_QUIT:
					running = SDL_FALSE;
					break;

				/* window resize event */
				case SDL_WINDOWEVENT:
				{
					switch (event.window.event)
					{
						case SDL_WINDOWEVENT_SIZE_CHANGED:
						{
							width = event.window.data1;
							height = event.window.data2;
							pixels = realloc(pixels, width * height * (BPP / 8));
							ostgl_resize(ctx, width, height, &pixels);
							reshape(width, height);
							break;
						}
					}
					break;
				}
				
				/* key event */
				case SDL_KEYDOWN:
				{
					switch (event.key.keysym.scancode)
					{
						case SDL_SCANCODE_UP: key(KEY_UP, 0); break;
						case SDL_SCANCODE_DOWN: key(KEY_DOWN, 0); break;
						case SDL_SCANCODE_LEFT: key(KEY_LEFT, 0); break;
						case SDL_SCANCODE_RIGHT: key(KEY_RIGHT, 0); break;
						case SDL_SCANCODE_ESCAPE: key(KEY_ESCAPE, 0); break;
						default: key(event.key.keysym.sym, 0); break;
					}
					break;
				}
			}
		}

		idle();
	}

	/* shutdown */
	ostgl_delete_context(ctx);
	free(pixels);
	SDL_Quit();

	/* return success */
	return 0;
}

/* swap buffers */
void swap_buffers()
{
	SDL_UpdateTexture(texture, NULL, pixels, width * (BPP / 8));
	SDL_RenderClear(renderer);
	SDL_RenderCopy(renderer, texture, NULL, NULL);
	SDL_RenderPresent(renderer);
}
