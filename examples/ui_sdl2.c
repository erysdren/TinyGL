
/* headers */
#include <stdio.h>
#include <stdlib.h>

#include "SDL.h"

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
	/* variables */
	int w, h;

	/* suppress warnings */
	(void)argc;
	(void)argv;

	/* get width, height from commandline */
	if (argc >= 3)
	{
		if (!(w = atoi(argv[1]))) w = WIDTH;
		if (!(h = atoi(argv[2]))) h = HEIGHT;
	}
	else
	{
		w = WIDTH;
		h = HEIGHT;
	}

	/* init sdl */
	SDL_Init(SDL_INIT_VIDEO);

	/* alloc */
	ctx = ostgl_create_context(w, h, BPP);
	ostgl_make_current(ctx);

	/* call user functions */
	init();
	reshape(ctx->width, ctx->height);

	/* create sdl context */
	window = SDL_CreateWindow(name, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, ctx->width, ctx->height, SDL_WINDOW_RESIZABLE | SDL_WINDOW_HIDDEN);

	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_PRESENTVSYNC);

	texture = SDL_CreateTexture(renderer, SDL_GetWindowPixelFormat(window), SDL_TEXTUREACCESS_STREAMING, ctx->width, ctx->height);

	SDL_ShowWindow(window);

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
							texture = SDL_CreateTexture(renderer, SDL_GetWindowPixelFormat(window),
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
						case SDL_SCANCODE_UP: key(KEY_UP); break;
						case SDL_SCANCODE_DOWN: key(KEY_DOWN); break;
						case SDL_SCANCODE_LEFT: key(KEY_LEFT); break;
						case SDL_SCANCODE_RIGHT: key(KEY_RIGHT); break;
						case SDL_SCANCODE_ESCAPE: key(KEY_ESCAPE); break;
						default: key(event.key.keysym.sym); break;
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
void swap_buffers(void)
{
	SDL_Surface *src = SDL_CreateRGBSurfaceWithFormatFrom(ctx->pixels, ctx->width, ctx->height, ctx->depth, ctx->width * (ctx->depth / 8), SDL_PIXELFORMAT_RGB565);
	SDL_Surface *dst = SDL_CreateRGBSurfaceWithFormatFrom(NULL, ctx->width, ctx->height, 0, 0, SDL_GetWindowPixelFormat(window));

	if (SDL_LockTexture(texture, NULL, &dst->pixels, &dst->pitch) == 0)
	{
		if (SDL_BlitSurface(src, NULL, dst, NULL) != 0)
		{
			SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "surface blit failed: %s", SDL_GetError());
		}

		SDL_UnlockTexture(texture);
	}
	else
	{
		SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "texture lock failed: %s", SDL_GetError());
	}

	SDL_FreeSurface(dst);
	SDL_FreeSurface(src);

	SDL_RenderClear(renderer);
	SDL_RenderCopy(renderer, texture, NULL, NULL);
	SDL_RenderPresent(renderer);
}
