#ifndef TEXTURECLASS_FUNCTIONS_CPP
#define TEXTURECLASS_FUNCTIONS_CPP
#include "TextureClass.h"

std::vector<LTexture *> LTexture::texturePtrArray;
SDL_Renderer * LTexture::renderer;

LTexture::LTexture() {
	texture = NULL;
	name = "";
	filename = "";
	sizeAndPos->x = 0;
	sizeAndPos->y = 0;
	sizeAndPos->w = 1;
	sizeAndPos->h = 1;

	colorKeyIsActive = false;
	colorKeyR = 0x00;
	colorKeyG = 0x00;
	colorKeyB = 0x00;
	colorKeyA = 0x00;

	if (texturePtrArray.empty() == true) {
		textureID = 0;
	}
	else {
		textureID = texturePtrArray.back()->GetID() + 1;
	}
	texturePtrArray.push_back(this);

}

LTexture::LTexture(std::string fn, SDL_Renderer * r) {
	if (fn.empty() == false) {
		filename = fn;
	}
	else {
		filename = "";
	}

	if(r != NULL) {
		if (typeid(r) != typeid(renderer)) {
			fprintf(stderr, "Warning | LTexture() >> Invalid renderer argument. Defaulting to NULL.\n");
			renderer = NULL;
		}
		else {
			renderer = r;
		}
		
	}
	

	texture = NULL;
	name = "";

	sizeAndPos = new SDL_Rect();
	sizeAndPos->x = 0;
	sizeAndPos->y = 0;
	sizeAndPos->w = 1;
	sizeAndPos->h = 1;

	colorKeyIsActive = false;
	colorKeyR = 0x00;
	colorKeyG = 0x00;
	colorKeyB = 0x00;
	colorKeyA = 0x00;

	clip = new SDL_Rect();
	clip->x = 0;
	clip->y = 0;
	clip->w = 1;
	clip->h = 1;

	if (texturePtrArray.empty() == true) {
		textureID = 0;
	}
	else {
		textureID = texturePtrArray.back()->GetID() + 1;
	}

	texturePtrArray.push_back(this);
}

LTexture::LTexture(std::string fn, std::string n, SDL_Rect * tempClip, SDL_Rect * tempSizePos, bool useColorKey, Uint8 r, Uint8 g, Uint8 b, Uint8 a) {
	if (fn.empty() == false) {
		filename = fn;
	}
	else {
		filename = "";
	}

	colorKeyR = r;
	colorKeyG = g;
	colorKeyB = b;
	colorKeyA = a;

	LoadTexture();

	name = n;

	if (tempSizePos != NULL) {
		sizeAndPos = new SDL_Rect(*tempSizePos);
	}
	else {
		sizeAndPos = new SDL_Rect();
		sizeAndPos->x = 0;
		sizeAndPos->y = 0;
		sizeAndPos->w = surfaceWidth;
		sizeAndPos->h = surfaceHeight;
	}
	if (tempClip != NULL) {
		clip = new SDL_Rect(*tempClip);
	}
	else {
		clip = new SDL_Rect();
		clip->x = 0;
		clip->y = 0;
		clip->w = surfaceWidth;
		clip->h = surfaceHeight;
	}
	
	if (texturePtrArray.empty() == true) {
		textureID = 0;
	}
	else {
		textureID = texturePtrArray.back()->GetID() + 1;
	}


	texturePtrArray.push_back(this);
}

LTexture::~LTexture() {
	for (unsigned int i = 0; i < texturePtrArray.size(); i++) {
		if (textureID == texturePtrArray[i]->GetID()) {
			texturePtrArray.erase(texturePtrArray.begin() + i);
			break;
		}
	}
	SDL_DestroyTexture(texture);
	renderer = NULL;

	textureID = 0;
	name = "";
	filename = "";
	
	sizeAndPos->x = 0;
	sizeAndPos->y = 0;
	sizeAndPos->w = 0;
	sizeAndPos->h = 0;

	colorKeyIsActive = false;
	colorKeyR = 0x00;
	colorKeyG = 0x00;
	colorKeyB = 0x00;
	colorKeyA = 0x00;

	clip->x = 0;
	clip->y = 0;
	clip->w = 0;
	clip->h = 0;

	delete sizeAndPos;
	delete clip;
}

void LTexture::SetValues(std::string fn, std::string n, SDL_Rect * tempSizePos, SDL_Rect * tempClip, Uint8 r, Uint8 g, Uint8 b, Uint8 a) {
	filename = fn;
	name = n;
	sizeAndPos = tempSizePos;
	clip = tempClip;
	colorKeyR = r;
	colorKeyG = g;
	colorKeyB = b;
	colorKeyA = a;
	return;
}

void LTexture::SetFilename(std::string fn) {
	filename = fn;
	return;
}

void LTexture::SetName(std::string n) {
	name = n;
	return;
}

void LTexture::SetSizeAndPos(SDL_Rect * tempSizePos) {
	sizeAndPos = tempSizePos;
	return;
}

void LTexture::SetClip(SDL_Rect * tempClip) {
	clip = tempClip;
	return;
}

void LTexture::SetColorKey(bool useColorKey, Uint8 r, Uint8 g, Uint8 b, Uint8 a) {
	colorKeyIsActive = useColorKey;
	colorKeyR = r;
	colorKeyG = g;
	colorKeyB = b;
	colorKeyA = a;
	return;
}

int LTexture::LoadTexture(void) {
	SDL_Surface * initialSurface;
	SDL_Texture * generatedTexture;
	
	if (texture != NULL) {
		SDL_DestroyTexture(texture);
		texture = NULL;
	}

	if (filename.empty() == true) {
		fprintf(stderr, "LTexture::LoadTexture() >> No filename provided.\n");
		return(1);
	}

	initialSurface = IMG_Load(filename.c_str());
	if (initialSurface == NULL) {
		fprintf(stderr, "LTexture::LoadTexture() >> SDL Error: %s.\n", IMG_GetError());
		fprintf(stderr, "LTexture::LoadTexture() >> Failed to load [%s]. Is the file path correct?", filename.c_str());
		return(2);
	}
	surfaceWidth = initialSurface->w;
	surfaceHeight = initialSurface->h;

	if (renderer == NULL) {
		fprintf(stderr, "LTexture::LoadTexture() >> Renderer is null.\n");
		return(3);
	}

	if (colorKeyIsActive) {
		SDL_SetColorKey(initialSurface, SDL_TRUE, SDL_MapRGB(initialSurface->format, colorKeyR, colorKeyG, colorKeyB));
	}
	generatedTexture = SDL_CreateTextureFromSurface(renderer, initialSurface);
	if (generatedTexture == NULL) {
		fprintf(stderr, "LTexture::LoadTexture() >> SDL Error: %s.\n", SDL_GetError());
		fprintf(stderr, "LTexture::LoadTexture() >> Failed to convert surface to texture (%s). Returning NULL.\n", filename.c_str());
		return(4);
	}
	SDL_FreeSurface(initialSurface);

	texture = generatedTexture;

	return(0);
}

int LTexture::DrawTexture(void) {
	SDL_RenderCopy(renderer, texture, clip, sizeAndPos);
	return(0);
}

//Note: Another version of this function that takes an SDL_Renderer * as an argument can be used
//			if/when drawing the texture to more than one renderer becomes an issue.
int LTexture::DrawRegion(SDL_Rect * tempClip, SDL_Rect * tempSizePos) {
	SDL_Rect sp;
	SDL_Rect c;
	
	if (tempSizePos == NULL) {
		sp.x = sizeAndPos->x;
		sp.y = sizeAndPos->y;
		sp.w = sizeAndPos->w;
		sp.h = sizeAndPos->h;
	}
	else {
		sp.x = tempSizePos->x;
		sp.y = tempSizePos->y;
		sp.w = tempSizePos->w;
		sp.h = tempSizePos->h;
	}

	if (tempClip == NULL) {
		c.x = clip->x;
		c.y = clip->y;
		c.w = clip->w;
		c.h = clip->h;
	}
	else {
		c.x = tempClip->x;
		c.y = tempClip->y;
		c.w = tempClip->w;
		c.h = tempClip->h;
	}

	SDL_RenderCopy(renderer, texture, &c, &sp);
	return(0);
}


int LTexture::GetID() const { return(textureID); }
std::string LTexture::GetName() const { return(name); }
std::string LTexture::GetFilename() const { return(filename); }

SDL_Rect * LTexture::GetSizePos() const {
	SDL_Rect * tempRect = new SDL_Rect(*sizeAndPos);
	return(tempRect);
}

SDL_Rect * LTexture::GetClip() const {
	SDL_Rect * tempRect = new SDL_Rect(*clip);
	return(tempRect);
}

int LTexture::GetSurfaceWidth() const { return(surfaceWidth); }
int LTexture::GetSurfaceHeight() const { return(surfaceHeight); }

#endif