#pragma once
#ifndef SPRITECLASS_H
#define SPRITECLASS_H

//CAUTION: The only reason this doesn't blow up is because of the preprocessor wrappers.
//			DON'T REMOVE THE PREPROCESSOR WRAPPERS.
#include "Includer_CoreFiles.h"
#include "TextureClass.h"

class LSprite {
private:
	LTexture * spriteSheet;
	bool visible;

public:
	//Usually this would probably be private and functions would be made to access it as needed,
	//	however all the functions are already provided by the std::vector class template.
	std::vector<SDL_Rect *> frames;

	LSprite();
	LSprite(LTexture *);
	LSprite(LTexture *, SDL_Rect **);
	LSprite(LTexture *, std::vector<SDL_Rect *>);

	int SetFrame(int, SDL_Rect *);
	int SetFrame(int, int, int, int, int);
	int RemoveFrame(int);
		
	int DrawFrame(int);
};

#endif