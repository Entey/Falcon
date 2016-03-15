#ifndef MILITARY_BASE_H
#define MILITARY_BASE_H


#include "Entity.h"
#include "../Hero/Hero.h"

class Military_base : public Entity{

public:
	float dir;
	bool isDetectedR, isDetectedB;
	Player &p;
	float shootR, shootB;

public:
	Military_base(Image &image, String name, lv::Level &lvl, float X, float Y, float W, float H, Player &ob) : Entity(image, name, X, Y, W, H), p(ob), shootR(0.0), shootB(0.0){
		objj = lvl.GetObjects("base");
		if (name == "MilitaryBase"){
			health = 100; dir = 0; speed = 0;
			sprite.setTextureRect(IntRect(0, 0, 27, 78));
			isDetectedR = isDetectedB = false;
		}
	}
	void update(const float &time)
	{
		shootR += 0.001*time;
		if ((y + 700 > p.get_y()) && (y - 700 < p.get_y()) && (x + 700 > p.get_x()) && (x - 700 < p.get_x()) && shootR > 3) {
			isDetectedR = true;
			shootR = 0;
		}
		else
			isDetectedR = false;
		shootB += 0.01*time;
		if ((y + 500 > p.get_y()) && (y - 500 < p.get_y()) && (x + 500 > p.get_x()) && (x - 500 < p.get_x()) && shootB > 1) {
			isDetectedB = true;
			shootB = 0;
		}
		else
			isDetectedB = false;


		sprite.setPosition(x, y);
		{
			dir += 0.0008*time; // для часу зміни кадрів
			if (dir > 3) dir -= 3; // якщо 5 кадрів починаємо з першого
			sprite.setTextureRect(IntRect(27 * int(dir), 0, 27, 78));
		}
		if (health <= 0) {
			isDetectedR = false;
			isDetectedB = false;
			life = false; sprite.setTextureRect(IntRect(27 * int(dir), 0, 50, 50));
		}
	}
};

#endif