#ifndef __ENTITY_H__
#define __ENTITY_H__

#include "../EngineCommon.h"
#include "../GameMath.h"
#include <SDL.h>
#include "../GraphicsEngine.h"
#include "../EventEngine.h"

//This holds all of the entity types
enum class EntityName {
	NOTHING, PLAYER, ENEMY, WALL, COIN, PORTAL, NUM_ENTITIES
};

class MyEngineSystem;

class Entity {
	public:
		Entity();
		~Entity();
		virtual void render();
		virtual void handleKeyEvents();
		virtual void update();

		//Get and Set of variables
		void setIsCollider(bool isCollider) { this->isCollider = isCollider; };
		bool getIsCollider() { return isCollider; };

		void setVisible(bool visible) { this->visible = visible; };
		bool getVisible() { return visible; };

		void setActive(bool active) { this->active = active; };
		bool getActive() { return active; };

		void setVelocity(Vector2f velocity) { this->velocity = velocity; };
		void setVelocity(float x, float y) { this->velocity = { x,y }; };
		Vector2f getVelocity() { return velocity; };

		void setTexture(SDL_Texture* texture) { this->texture = texture; };

		void setGfx(GraphicsEngine* gfx) { this->gfx = gfx; };

		void setIsFlipped(SDL_RendererFlip isFlipped) { this->isFlipped = isFlipped; };

		void setPosition(Vector2f position) { rectangle.x = position.x; rectangle.y = position.y; };
		void setPosition(float x, float y) { rectangle.x = x; rectangle.y = y; };
		Vector2f getPosition() { return {rectangle.x, rectangle.y}; };

		void setCollisionBox(Vector2f collisionBox) { rectangle.w = collisionBox.x; rectangle.h = collisionBox.y; };
		void setCollisionBox(float w, float h) { rectangle.w = w; rectangle.h = h; };
		Rectf getCollisionBox() { return  rectangle; };

		void setMyEngineSystem(MyEngineSystem* myEngineSystem) { this->myEngineSystem = myEngineSystem; };

		EntityName getEntityName() { return entityName; };

		void setEventSystem(EventEngine* eventSystem) { this->eventSystem = eventSystem; };

	protected:
		Rectf rectangle;
		bool isCollider;
		Vector2f velocity;
		bool visible;
		bool active;
		SDL_Texture* texture;
		GraphicsEngine* gfx;
		SDL_RendererFlip isFlipped;
		MyEngineSystem* myEngineSystem;
		EntityName entityName;
		EventEngine* eventSystem;
};
#endif