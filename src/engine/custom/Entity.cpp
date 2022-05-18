#include "Entity.h"
#include "MyEngineSystem.h"

Entity::Entity() :rectangle(0, 0, 0, 0) {
	velocity = { 0,0 };
	isCollider = false;
	visible = true;
	active = true;
	texture = nullptr;
	gfx = nullptr;
	myEngineSystem = nullptr;
	isFlipped = SDL_FLIP_NONE;
	entityName = EntityName::NOTHING;
	eventSystem = nullptr;
}

Entity::~Entity() {

}

void Entity::render() {
	//Renders the objects if they are visible
	if (visible == true) {
		gfx->drawTexture(texture, &rectangle.getSDLRect(), isFlipped);
	}
}

void Entity::handleKeyEvents() {

}

void Entity::update() {

}
