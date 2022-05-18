#include "MyGame.h"

MyGame::MyGame() : AbstractGame(), score(0), gameWin(false), portalFail(false), easterEgg(false), 
deathSound(Mix_LoadWAV("res/sounds/deathSound.wav")), deathSoundCheck(false){
	//Setting up font
	TTF_Font * font = ResourceManager::loadFont("res/fonts/arial.ttf", 32);
	gfx->useFont(font);
	gfx->setVerticalSync(true);

	//Setting up graphics and event engines
	myEngineSystem.setGfx(gfx.get());
	myEngineSystem.setEventSystem(eventSystem.get());

	//Spawning Player
	player = static_cast<Player*>(myEngineSystem.entitySpawn(EntityName::PLAYER, 150, 150));

	//Spawning Walls im sorry
	std::vector<Vector2f> wallCoords = { 
		{256, 64}, {288, 64}, {320, 64}, {352, 64}, {384, 64}, {416, 64}, {448, 64}, {480, 64}, {512, 64}, {544, 64}, {576, 64}, {608, 64}, {640, 64}, {672, 64},
		{256, 96}, {352, 96}, {448, 96}, {672, 96},
		{256, 128}, {352, 128}, {448, 128}, {672, 128},
		{256, 160}, {352, 160}, {448, 160}, {672, 160},
		{256, 192}, {352, 192}, {448, 192}, {672, 192},
		{128, 224}, {160, 224}, {192, 224}, {224, 224}, {256, 224}, {672, 224},
		{672, 256},
		{672, 288},
		{128, 320}, {160, 320}, {192, 320}, {224, 320}, {256, 320}, {672, 320},
		{256, 352}, {672, 352},
		{256, 384}, {352, 384}, {448, 384}, {672, 384},
		{256, 416}, {352, 416}, {448, 416}, {576, 416}, {640, 416}, {672, 416}, {704, 416}, {736, 416}, {768, 416},
		{256, 448}, {352, 448}, {448, 448}, {576, 448},
		{640, 448}, {672, 448}, {256, 480}, {352, 480}, {448, 480}, {576, 480}, {640, 480}, {672, 480}, 
		{256, 512}, {288, 512}, {320, 512}, {352, 512}, {384, 512}, {416, 512}, {448, 512}, {480, 512}, {512, 512}, {544, 512}, {576, 512}, {608, 512}, {640, 512}, {672, 512}};
	
	for (int i = 0; i < wallCoords.size(); i++) {
		myEngineSystem.entitySpawn(EntityName::WALL, wallCoords[i]);
	}

	//Spawning Enemys
	Enemy* enemy = static_cast<Enemy*>(myEngineSystem.entitySpawn(EntityName::ENEMY, 352, 224));
	enemy->setVelocity(0, 3);

	enemy = static_cast<Enemy*>(myEngineSystem.entitySpawn(EntityName::ENEMY, 576, 224));
	enemy->setVelocity(3, 0);

	enemy = static_cast<Enemy*>(myEngineSystem.entitySpawn(EntityName::ENEMY, 416, 352));
	enemy->setVelocity(-3, 0);

	enemy = static_cast<Enemy*>(myEngineSystem.entitySpawn(EntityName::ENEMY, 448, 352));
	enemy->setVelocity(0, 3);

	enemy = static_cast<Enemy*>(myEngineSystem.entitySpawn(EntityName::ENEMY, 576, 224));
	enemy->setVelocity(0, 3);

	//Spawning Coins
	myEngineSystem.entitySpawn(EntityName::COIN, 320,96);
	myEngineSystem.entitySpawn(EntityName::COIN, 416, 96);
	myEngineSystem.entitySpawn(EntityName::COIN, 416, 480);
	myEngineSystem.entitySpawn(EntityName::COIN, 608, 480);
	myEngineSystem.entitySpawn(EntityName::COIN, 640, 96);

	//Spawning Portal
	myEngineSystem.entitySpawn(EntityName::PORTAL, 736, 352);

	//Background Music
	Mix_Chunk* music = Mix_LoadWAV("res/sounds/background.mp3");
	Mix_PlayChannel(1, music, -1);
	Mix_Volume(1, 1);

	//Setting up death sound volume
	Mix_Volume(2, 2);

	//Setting up coin sound volume
	Mix_Volume(3, 2);
}

MyGame::~MyGame() {

}

//Handle all object key events
void MyGame::handleKeyEvents() {
	myEngineSystem.handleKeyEvents();
}

//Updating all the objects and game
void MyGame::update() {
	myEngineSystem.update();

	//Getting the score from player
	score = player->getScore();

	//Getting if portal fails from player
	portalFail = player->getFailPortal();

	//Getting if game win from player
	gameWin = player->getGameWin();

	//Getting if easter egg from player
	easterEgg = player->getEasterEgg();

}

//Rendering all the objects
void MyGame::render() {
	myEngineSystem.render();
}

void MyGame::renderUI() {
	//Score Text
	gfx->setDrawColor(SDL_COLOR_AQUA);
	std::string scoreStr = std::to_string(score);
	gfx->drawText(scoreStr, 700, 15);

	//Portal Fail Text
	if (portalFail) {
		gfx->drawText("You Need More Coins", 0, 560);
	}

	//Game Win Text
	if (gameWin) {
		gfx->drawText("YOU WIN", 325, 290);
	}

	//Easter Egg Text
	if (easterEgg) {
		gfx->drawText("CHARLES_KANATLI-CI517-2021", 0, 15);
	}

	//Game Over Text
	if (!player->getVisible() && !gameWin) {
		if (!deathSoundCheck) {
			//Playing Death Sound
			Mix_PlayChannel(2, deathSound, 0);
			deathSoundCheck = true;
		}
		gfx->drawText("GAME OVER", 325, 290);
	}
}