#ifndef SPRITECLASS_FUNCTIONS_CPP
#define SPRITECLASS_FUNCTIONS_CPP

#include "SpriteClass.h"

/*
LTexture * spriteSheet;
std::vector <SDL_Rect *> spriteFrames;
bool visible;
*/

LSprite::LSprite() {
	spriteSheet = NULL;
	if (frames.empty() == true) {
		frames.clear();
	}

	SDL_Rect * tempFrame = new SDL_Rect();
	tempFrame->x = 0;
	tempFrame->y = 0;
	tempFrame->w = 1;
	tempFrame->h = 1;
	frames.push_back(tempFrame);

	visible = false;
}

LSprite::LSprite(LTexture * newSpriteSheet) {
	if (newSpriteSheet != NULL) {
		spriteSheet = newSpriteSheet;
	}
	else {
		spriteSheet = NULL;
	}

	if (frames.empty() == true) {
		frames.clear();
	}
	SDL_Rect * tempFrame = new SDL_Rect();
	tempFrame->x = 0;
	tempFrame->y = 0;
	tempFrame->w = 1;
	tempFrame->h = 1;
	frames.push_back(tempFrame);
}
LSprite::LSprite(LTexture * newSpriteSheet, SDL_Rect ** newSpriteFrames) {
	if (newSpriteSheet != NULL) {
		spriteSheet = newSpriteSheet;
	}
	else {
		spriteSheet = NULL;
	}
	int newFrameCount = sizeof(*newSpriteFrames) / sizeof(SDL_Rect);
	if (frames.empty() == true) {
		frames.clear();
	}
	for (int i = 0; i < newFrameCount; i++) {
		frames.push_back(newSpriteFrames[i]);
	}
}

LSprite::LSprite(LTexture * newSpriteSheet, std::vector<SDL_Rect *> newSpriteFrames) {
	if (newSpriteSheet != NULL) {
		spriteSheet = newSpriteSheet;
	}
	else {
		spriteSheet = NULL;
	}
	
	if (frames.empty() == true) {
		frames.clear();
	}

	for (int i = 0; i < newSpriteFrames.size(); i++) {
		frames.push_back(newSpriteFrames[i]);
	}
}

int LSprite::SetFrame(int frameIndex, SDL_Rect * newFrame) {
	if (frameIndex >= frames.size()) {
		fprintf(stderr, "Error | LSprite::SetFrame() >> Attempted to access nonexistant frame.\n");
		return(1);
	}
	if (newFrame == NULL) {
		fprintf(stderr, "Warning | LSprite::SetFrame() >> new frame is empty.\n");
	}

	frames[frameIndex] = newFrame;
	frames.push_back(newFrame);
	
	return(0);
}

int LSprite::SetFrame(int frameIndex, int x, int y, int w, int h) {
	if (frameIndex >= frames.size()) {
		fprintf(stderr, "Error | LSprite::SetFrame() >> Attempted to access nonexistant frame.\n");
		return(1);
	}
	


	return(0);
}

int LSprite::RemoveFrame(int frame) {
	return(0);
}

int LSprite::DrawFrame(int) {
	return(0);
}

#endif