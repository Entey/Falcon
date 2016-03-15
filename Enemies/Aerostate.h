#pragma once


#include "Entity.h"

class Aerostat : public Entity{
	bool dir{ true };
public:
	Aerostat(Image &image, String name, lv::Level &lvl, float X, float Y, float W, float H) : Entity(image, name, X, Y, W, H) {
		objj = lvl.GetObjects("Aerostat");
		if (name == "Aerostat"){
			health = 10;  speed = 0.03;
			altitude = 100;
			sprite.setTextureRect(IntRect(0, 0, 27, 78));
			sprite.setOrigin(w / 2, h / 2);
		}
	}
	void update(const float &time)
	{
		Interaction_MAP();
		switch (dir){
		case true:
			x += 0.01*time;
			y += 0.01*time;
			break;
		case false:
			x -= 0.01*time;
			y -= 0.01*time;
			break;
		}
		sprite.setPosition(x, y);
		sprite.rotate(0.01*time);
		sprite.setTextureRect(IntRect(0, 0, 100, 100));

		if (health <= 0) { life = false; speed = 0; }
	}

	void Interaction_MAP() {
		for (int i = 0; i<objj.size(); i++)
			if (getRect().intersects(objj[i].rect)) {
				if (objj[i].name == "solid") {
					dir == true ? (dir = false) : (dir = true);
				}
			}
	}
};