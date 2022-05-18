#include "Player.h"

Player::Player() : coinSound(Mix_LoadWAV("res/sounds/coinSound.wav")) {
	//Setting up the name
	entityName = EntityName::PLAYER;
	//I know this is not efficent but I would have to add a new subsystem to deal with this
	//Setting the texture
	SDL_Surface* image = IMG_Load("res/images/player.png");
	texture = gfx->createTextureFromSurface(image);
	rectangle.w = 32;
	rectangle.h = 32;
	isCollider = true;
	score = 0;
	failPortal = false;
	gameWin = false;
	easterEgg = false;
}

Player::~Player() {

}

void Player::handleKeyEvents(){
	//Checking for inputs
	int speed = 3;

	if (eventSystem->isPressed(Key::W)) {
		velocity.y = -speed;
	}

	if (eventSystem->isPressed(Key::S)) {
		velocity.y = speed;
	}

	if (eventSystem->isPressed(Key::A)) {
		velocity.x = -speed;
	}

	if (eventSystem->isPressed(Key::D)) {
		velocity.x = speed;
	}
}

void Player::update(){
	//Movement
	rectangle.x += velocity.x;
	rectangle.y += velocity.y;
	velocity.x = 0;
	velocity.y = 0;

	//Keeping Player in screen
	Dimension2i window = gfx->getCurrentWindowSize();
	if (rectangle.x < 0) {
		rectangle.x = 0;
	}
	else if (rectangle.x + rectangle.w > window.w) {
		rectangle.x = window.w - rectangle.w;
	}
	if (rectangle.y < 0) {
		rectangle.y = 0;
	}
	else if (rectangle.y + rectangle.h > window.h) {
		rectangle.y = window.h - rectangle.h;
	}

	if (isCollider) {
		//Collision with walls
		std::vector<Entity*>* walls = myEngineSystem->getEntities(EntityName::WALL);
		for (int i = 0; i < walls->size(); i++) {
			if ((*walls)[i]->getIsCollider() && (*walls)[i]->getCollisionBox().intersects(rectangle)) {

				//Getting middle of wall & player
				Vector2f wallPosition = (*walls)[i]->getPosition();
				wallPosition.x += (*walls)[i]->getCollisionBox().w / 2;
				wallPosition.y += (*walls)[i]->getCollisionBox().h / 2;

				Vector2f playerPosition = { rectangle.x, rectangle.y };
				playerPosition.x += rectangle.w / 2;
				playerPosition.y += rectangle.h / 2;

				Vector2f playerToWall = { wallPosition.x - playerPosition.x, wallPosition.y - playerPosition.y };

				if (abs(playerToWall.x) > abs(playerToWall.y)) {
					//Player is on left or right of wall
					if (playerToWall.x > 0) {
						//Player is on the left of wall
						rectangle.x = (*walls)[i]->getPosition().x - rectangle.w;
					}
					else {
						//Player is on the right of wall
						rectangle.x = (*walls)[i]->getPosition().x + (*walls)[i]->getCollisionBox().w;
					}
				}
				else {
					//Player is on top or bottom of wall
					if (playerToWall.y > 0) {
						//Player is on top of wall
						rectangle.y = (*walls)[i]->getPosition().y - rectangle.h;
					}
					else {
						//Player is on bottom of wall
						rectangle.y = (*walls)[i]->getPosition().y + (*walls)[i]->getCollisionBox().h;
					}
				}
			}
		}

		//Colliding with enemies
		std::vector<Entity*>* enemies = myEngineSystem->getEntities(EntityName::ENEMY);
		for (int i = 0; i < enemies->size(); i++) {
			if ((*enemies)[i]->getIsCollider() && (*enemies)[i]->getCollisionBox().intersects(rectangle)) {
				setVisible(false);
				setIsCollider(false);
			}
		}

		//Colliding with coins
		std::vector<Entity*>* coins = myEngineSystem->getEntities(EntityName::COIN);
		for (int i = 0; i < coins->size(); i++) {
			if ((*coins)[i]->getIsCollider() && (*coins)[i]->getCollisionBox().intersects(rectangle)) {
				score += 200;
				myEngineSystem->deleteEntity((*coins)[i]);
				Mix_PlayChannel(3, coinSound, 0);
			}
		}

		//Colliding with portal
		std::vector<Entity*>* portal = myEngineSystem->getEntities(EntityName::PORTAL);
		for (int i = 0; i < portal->size(); i++) {
			if ((*portal)[i]->getIsCollider() && (*portal)[i]->getCollisionBox().intersects(rectangle)) {
				if (score >= 1000) {
					gameWin = true;
					failPortal = false;
					setVisible(false);
					setIsCollider(false);
				}
				else {
					failPortal = true;
				}
			}
		}

		//Checking for Easter Egg
		if (rectangle.x > 704 && rectangle.x < 768) {
			if (rectangle.y > 416 && rectangle.y < 480) {
				setEasterEgg(true);
			}
		}

	}
}
