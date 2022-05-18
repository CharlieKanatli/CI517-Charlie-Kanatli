#include "Enemy.h"

Enemy::Enemy() {
	//Setting up the name
	entityName = EntityName::ENEMY;
	//I know this is not efficent but I would have to add a new subsystem to deal with this
	//Setting the texture
	SDL_Surface* image = IMG_Load("res/images/enemy.png");
	texture = gfx->createTextureFromSurface(image);
	rectangle.w = 32;
	rectangle.h = 32;
	isCollider = true;
}

Enemy::~Enemy() {

}

void Enemy::update(){
	rectangle.x += velocity.x;
	rectangle.y += velocity.y;

	if (isCollider) {
		//Collision with walls
		std::vector<Entity*>* walls = myEngineSystem->getEntities(EntityName::WALL);
		for (int i = 0; i < walls->size(); i++) {
			if ((*walls)[i]->getIsCollider() && (*walls)[i]->getCollisionBox().intersects(rectangle)) {
				velocity = { -velocity.x, -velocity.y };
			}
		}
	}

}
