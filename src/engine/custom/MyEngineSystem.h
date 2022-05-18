#ifndef __MY_ENGINE_H__
#define __MY_ENGINE_H__

#include <vector>
#include "Entity.h"
#include "../../demo/Wall.h"
#include "../../demo/Player.h"
#include "../../demo/Enemy.h"
#include "../../demo/Coin.h"
#include "../../demo/Portal.h"

class MyEngineSystem {
	public:
		MyEngineSystem();
		~MyEngineSystem();
		void render();
		void handleKeyEvents();
		void update();

		void setGfx(GraphicsEngine* gfx);

		Entity* entitySpawn(EntityName entityName, Vector2f position);
		Entity* entitySpawn(EntityName entityName, float x, float y) { return entitySpawn(entityName, Vector2f(x, y)); };

		std::vector<Entity*>* getEntities() { return &entities; };
		std::vector<Entity*>* getEntities(EntityName entityName) { return &specificEntities[static_cast<int>(entityName)]; };
		std::vector<Entity*> getEntities(std::vector<EntityName>entityNames);

		void deleteEntity(Entity* entity);

		void updateFirst(Entity* entity);

		void updateLast(Entity* entity);

		void deleteEntities();

		void setEventSystem(EventEngine* eventSystem);

	protected:
		std::vector<Entity*> entities;
		std::vector<std::vector<Entity*>> specificEntities;
		GraphicsEngine* gfx;
		EventEngine* eventSystem;
};
		
#endif