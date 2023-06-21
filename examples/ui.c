
/* headers */
#include <stdio.h>
#include <stdlib.h>

#include <SDL2/SDL.h>

#include <GL/gl.h>
#include <GL/ostinygl.h>

#include "ui.h"

/* constants */
#define WIDTH 800
#define HEIGHT 600
#define BPP 16

/* globals */
ostgl_context_t *ctx;
int running;
SDL_Window *window;
SDL_Renderer *renderer;
SDL_Texture *texture;

/* open window, handle inputs */
int ui_loop(int argc, char **argv, const char *name)
{
	/* suppress warnings */
	(void)argc;
	(void)argv;

	/* init sdl */
	SDL_Init(SDL_INIT_VIDEO);

	/* alloc */
	ctx = ostgl_create_context(WIDTH, HEIGHT, BPP);
	ostgl_make_current(ctx);

	/* call user functions */
	init();
	reshape(ctx->width, ctx->height);

	/* create sdl context */
	window = SDL_CreateWindow(name, SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED, ctx->width, ctx->height, SDL_WINDOW_RESIZABLE);

	renderer = SDL_CreateRenderer(window, -1,
		SDL_RENDERER_PRESENTVSYNC | SDL_RENDERER_SOFTWARE);

	texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGB565,
		SDL_TEXTUREACCESS_STREAMING, ctx->width, ctx->height);

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
							/* resize gl */
							ostgl_resize(ctx, event.window.data1, event.window.data2);
							reshape(event.window.data1, event.window.data2);

							/* destroy texture and make new one */
							SDL_DestroyTexture(texture);
							texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGB565,
								SDL_TEXTUREACCESS_STREAMING, ctx->width, ctx->height);
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
	SDL_Quit();

	/* return success */
	return 0;
}

/* swap buffers */
void swap_buffers()
{
	SDL_UpdateTexture(texture, NULL, ctx->pixels, ctx->width * (ctx->depth / 8));
	SDL_RenderClear(renderer);
	SDL_RenderCopy(renderer, texture, NULL, NULL);
	SDL_RenderPresent(renderer);
}
