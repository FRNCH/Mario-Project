#pragma once
#ifndef TEXTURECLASS_H
#define TEXTURECLASS_H

//CAUTION: The only reason this doesn't blow up is because of the preprocessor wrappers.
//			DON'T REMOVE THE PREPROCESSOR WRAPPERS.
#include "Includer_CoreFiles.h"

class LTexture {
private:
	
	SDL_Texture * texture;
	int textureID;
	int surfaceWidth;
	int surfaceHeight;

	std::string name;
	std::string filename;
	SDL_Rect * sizeAndPos;
	SDL_Rect * clip;
	bool colorKeyIsActive;
	Uint8 colorKeyR;
	Uint8 colorKeyG;
	Uint8 colorKeyB;
	Uint8 colorKeyA;

	/*
	Instead of including a clip value for drawing the texture, include a 
		DrawRegion(SDL_Rect * sizePos, SDL_Rect * clip) function that draws the specified region at the specified
		location. This gets around the need to create a unique texture for every portion of the sprite sheet.
	*/

public:
	static std::vector<LTexture *> texturePtrArray;
	static SDL_Renderer * renderer;

	LTexture();
	LTexture(std::string, SDL_Renderer *);
	LTexture(std::string, std::string, SDL_Rect *, SDL_Rect *, bool, Uint8, Uint8, Uint8, Uint8);
	~LTexture();

	void SetValues(std::string, std::string, SDL_Rect *, SDL_Rect *, Uint8, Uint8, Uint8, Uint8);
	void SetFilename(std::string);
	void SetName(std::string);
	void SetSizeAndPos(SDL_Rect *);
	void SetClip(SDL_Rect *);
	void SetColorKey(bool, Uint8, Uint8, Uint8, Uint8);

	int LoadTexture(void);
	int DrawTexture(void);
	int DrawRegion(SDL_Rect *, SDL_Rect *);

	int GetID() const;
	std::string GetName() const;
	std::string GetFilename() const;
	SDL_Rect * GetSizePos() const;
	SDL_Rect * GetClip() const;
	int GetSurfaceWidth() const;
	int GetSurfaceHeight() const;


};
#endif