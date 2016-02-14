#pragma once
#ifndef FUNCS_H
#define FUNCS_H

int Init() {
	if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
		fprintf(stderr, "Error | Init() >> Failed to initialize SDL components.\n");
		return(1);
	}

	gameWindow = SDL_CreateWindow("Mario Clone", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WINDOW_WIDTH, WINDOW_HEIGHT, 0);
	
	if (gameWindow == NULL) {
		fprintf(stderr, "Error | Init() >> Failed to create SDL window.\n");
		return(2);
	}

	//TODO: Add a VSync variable to allow the initialization to be customized (VSync on/off)
	windowRenderer = SDL_CreateRenderer(gameWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (windowRenderer == NULL) {
		fprintf(stderr, "Error | Init() >> Failed to create game window renderer.\n");
		return(3);
	}

	return(0);
}

int Cleanup() {
	SDL_DestroyWindow(gameWindow);
	gameWindow = NULL;
	LTexture::renderer = NULL;
	windowRenderer = NULL;
	IMG_Quit();
	SDL_Quit();
	return(0);
}

#endif