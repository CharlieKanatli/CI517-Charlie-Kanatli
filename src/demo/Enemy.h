#ifndef __ENEMY_H__
#define __ENEMY_H__

#include "../engine/custom/Entity.h"
#include "../engine/AbstractGame.h"
#include <vector>

class Enemy :public Entity {
public:
	Enemy();
	~Enemy();
	virtual void update()override;
protected:

};
#endif

