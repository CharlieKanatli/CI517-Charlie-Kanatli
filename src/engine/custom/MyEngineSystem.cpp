#include "MyEngineSystem.h"

MyEngineSystem::MyEngineSystem(){
	gfx = nullptr;
	eventSystem = nullptr;
	for (int i = 0; i < static_cast<int>(EntityName::NUM_ENTITIES); i++) {
		specificEntities.push_back({});
	}
}
//Deletes entities if the engine system is deleted
MyEngineSystem::~MyEngineSystem(){
	for (int i = 0; i < entities.size(); i++) {
		delete entities[i];
	}
}

//Renders the entities
void MyEngineSystem::render(){
	for (int i = 0; i < entities.size(); i++) {
		entities[i]->render();
	}
}
//Handles the key events of the entities
void MyEngineSystem::handleKeyEvents(){
	for (int i = 0; i < entities.size(); i++) {
		entities[i]->handleKeyEvents();
	}
}

//Updates the entities
void MyEngineSystem::update(){
	for (int i = 0; i < entities.size(); i++) {
		entities[i]->update();
	}
}

//Set the entities graphics engine
void MyEngineSystem::setGfx(GraphicsEngine* gfx){
	this->gfx = gfx;
	for (int i = 0; i < entities.size(); i++) {
		entities[i]->setGfx(gfx);
	}
}

//Switch statement to see what entity needs to be spawned
Entity* MyEngineSystem::entitySpawn(EntityName entityName, Vector2f position){

	switch (entityName) {
		case EntityName::PLAYER:
			entities.push_back(new Player());
			break;
		case EntityName::ENEMY:
			entities.push_back(new Enemy());
			break;
		case EntityName::WALL:
			entities.push_back(new Wall());
			break;
		case EntityName::COIN:
			entities.push_back(new Coin());
			break;
		case EntityName::PORTAL:
			entities.push_back(new Portal());
			break;
		default:
			break;
	}
	//Allows for the entity that just spawned to be returned
	Entity* lastEntity = entities[entities.size() - 1];
	lastEntity->setPosition(position);
	lastEntity->setGfx(gfx);
	lastEntity->setEventSystem(eventSystem);
	lastEntity->setMyEngineSystem(this);
	specificEntities[static_cast<int>(lastEntity->getEntityName())].push_back(lastEntity);
	return lastEntity;
}

//Gets all the entities
std::vector<Entity*> MyEngineSystem::getEntities(std::vector<EntityName> entityNames){
	std::vector<Entity*> output;
	for (int i = 0; i < entityNames.size(); i++) {
		for (int j = 0; j < specificEntities[static_cast<int>(entityNames[i])].size(); j++) {
			output.push_back(specificEntities[static_cast<int>(entityNames[i])][j]);
		}
	}
	return output;
}

//Deletes a specific entity
void MyEngineSystem::deleteEntity(Entity* entity){
	std::vector<Entity*>& specificEntitiesSearch = specificEntities[static_cast<int>(entity->getEntityName())];
	for (int i = 0; i < specificEntitiesSearch.size(); i++) {
		if (specificEntitiesSearch[i] == entity) {
			specificEntitiesSearch.erase(specificEntitiesSearch.begin() + i);
		}
	}
	for (int i = 0; i < entities.size(); i++) {
		if (entities[i] == entity) {
			entities.erase(entities.begin()+i);
			delete entity;
			return;
		}
	}
}

//Moves an entity to the front of the list
void MyEngineSystem::updateFirst(Entity* entity){
	for (int i = 0; i < entities.size(); i++) {
		if (entities[i] == entity) {
			entities.erase(entities.begin() + i);
			entities.insert(entities.begin(),entity);
			return;
		}
	}
}

//Moves an entity to the back of the list
void MyEngineSystem::updateLast(Entity* entity){
	for (int i = 0; i < entities.size(); i++) {
		if (entities[i] == entity) {
			entities.erase(entities.begin() + i);
			entities.push_back(entity);
			return;
		}
	}
}

//Deletes all entities
void MyEngineSystem::deleteEntities(){
	for (int i = 0; i < specificEntities.size(); i++) {
		specificEntities[i].clear();
	}

	for (int i = 0; i < entities.size(); i++) {
		delete entities[i];
	}
	entities.clear();
}

//Sets up the event system for the entities
void MyEngineSystem::setEventSystem(EventEngine* eventSystem){
	this->eventSystem = eventSystem;
	for (int i = 0; i < entities.size(); i++) {
		entities[i]->setEventSystem(eventSystem);
	}
}
