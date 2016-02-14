#include "Includer_CoreFiles.h"
#include "Includer_ProgramFiles.h"

int main(int argc, char * argv[]) {

	//Initialization steps need to be ran before the creation of LTexture objects, otherwise LTexture will be
	//	unable to have the renderer set to the game window's renderer.
	if (Init() != 0) {
		fprintf(stderr, "Error | main(...) >> Failed to initialize properly. Terminating.\n");
		return(1);
	}
	
	
	SDL_Rect standingFrame;
	standingFrame.x = 16*16+2;
	standingFrame.y = 0;
	standingFrame.w = 16;
	standingFrame.h = 32;
	SDL_Rect runningFrames[3];
	runningFrames[0].x = 295;
	runningFrames[0].y = 0;
	runningFrames[0].w = 17;
	runningFrames[0].h = 32;
	runningFrames[1].x = 314;
	runningFrames[1].y = 0;
	runningFrames[1].w = 15;
	runningFrames[1].h = 32;
	runningFrames[2].x = 331;
	runningFrames[2].y = 0;
	runningFrames[2].w = 16;
	runningFrames[2].h = 32;

	int animation = 0;
	int animationFrame = 0;
	SDL_Rect * anim = &standingFrame;

	SDL_Rect * sizePos = new SDL_Rect();
	sizePos->x = 0;
	sizePos->y = 0;
	sizePos->w = 32;
	sizePos->h = 32;
	
	LTexture::renderer = windowRenderer;
	LTexture testTexture("resources/characters.gif", "test_texture", NULL, sizePos, false, 0xFF, 0xFF, 0xFF, 0xFF);
	//testTexture.LoadTexture();

	
	

	while (userQuit == false) {
		while (SDL_PollEvent(&mainEvent) != 0) {
			switch (mainEvent.type) {
			case SDL_KEYDOWN:
				if (mainEvent.key.keysym.sym == SDLK_d) {
					sizePos->x += 5;
					animation = 1;
				}
				if (mainEvent.key.keysym.sym == SDLK_a) {
					sizePos->x -= 5;
					animation = 1;
				}
				if (mainEvent.key.keysym.sym == SDLK_w) {
					sizePos->y -= 5;
					animation = 1;
				}
				if (mainEvent.key.keysym.sym == SDLK_s) {
					sizePos->y += 5;
					animation = 1;
				}
				break;

			case SDL_KEYUP:
				if (mainEvent.key.keysym.sym == SDLK_d ||
					mainEvent.key.keysym.sym == SDLK_a ||
					mainEvent.key.keysym.sym == SDLK_w ||
					mainEvent.key.keysym.sym == SDLK_s) {
					animation = 0;
				}
				break;

			case SDL_QUIT:
				userQuit = true;
				break;

			default:
				break;
			}
		}

		SDL_RenderClear(windowRenderer);

		//testTexture.DrawRegion(clip, sizePos);
		if (animation == 1) {
			testTexture.DrawRegion(&runningFrames[animationFrame/8], sizePos);
			animationFrame++;
			if (animationFrame / 8 > 2) { animationFrame = 0; }
		}
		else {
			testTexture.DrawRegion(&standingFrame, sizePos);
		}
		
		
		SDL_RenderPresent(windowRenderer);
	}

	delete sizePos;
	Cleanup();
	SDL_Quit();

	return(0);
}