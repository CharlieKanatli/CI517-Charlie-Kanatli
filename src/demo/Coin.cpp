#include "Coin.h"

Coin::Coin() {
	//Setting up the name
	entityName = EntityName::COIN;
	//I know this is not efficent but I would have to add a new subsystem to deal with this
	//Setting the texture
	SDL_Surface* image = IMG_Load("res/images/coin.png");
	texture = gfx->createTextureFromSurface(image);
	rectangle.w = 32;
	rectangle.h = 32;
	isCollider = true;
}

Coin::~Coin() {

}