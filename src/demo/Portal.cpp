#include "Portal.h"

Portal::Portal() {
	//Setting up the name
	entityName = EntityName::PORTAL;
	//I know this is not efficent but I would have to add a new subsystem to deal with this
	//Setting the texture
	SDL_Surface* image = IMG_Load("res/images/portal.png");
	texture = gfx->createTextureFromSurface(image);
	rectangle.w = 32;
	rectangle.h = 32;
	isCollider = true;
}

Portal::~Portal() {

}