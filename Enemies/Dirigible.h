#ifndef DIRIGABLE_H
#define DIRIGABLE_H

#include "Entity.h"
#include "../Hero/Hero.h"

class Dirigible : public Entity{
public:
	float dir, startX, startY, shootR;
	Player &p;
	Sound *explosion, *engine;
public:
	Dirigible(Image &image, String name, lv::Level &lvl, float X, float Y, float W, float H, Player&ob, const Sound &eng, const Sound &expl);	
	void update(const float &time);
};

#endif