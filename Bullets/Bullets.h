#ifndef BULLETS_H
#define BULLETS_H

#include "../Enemies/Entity.h"

class Bullet : public Entity {
public:

	float frame{ 0.0 }, distance{ 0.0 }, rotation;
	int hero_shoot; // щоб не підриватись на власних кулях
	float FX, FY, dX, dY;
	sf::Sound *sound1, *sound2;
	float scaleX, scaleY;
	Bullet(Image &image, String Name, lv::Level &lvl, float X, float Y, int W, int H, float TempX, float TempY, sf::Sound &soun, sf::Sound &soun_bomb, int heroo = false, float dam = 0, int altit = 1); 
	void update(const float& time);
};

#endif