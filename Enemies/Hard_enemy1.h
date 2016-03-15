#pragma once

#include "../Hero/Hero.h"
#include "Entity.h"
#include <cmath>
#include <random> 
#include <ctime>

class HardEnemy : public Entity {

	float frame{ 0 }, distance, dis, rotation, behav{ 0.0 };  //  distance - distance to the player, dis - for move forward
	float maxSpeed, minSpeed, maxAltitude{ 500.0 };
	int Minigun_bullets{ 1000 }, behav1{ 1 };
	float FX, FY, dX, dY;
	sf::ConvexShape convex;
	float zip;
	bool is_Detected{ false }, isDetectedR, isDetectedB, turn_animation_right{ false }, turn_animation_left{ false };
	float shootB;
	float speedX{ 0.0 }, speedY{ -1000.0 };
	Player &p;
	float angle{ 0.0 };
	sf::RectangleShape body1, body2;
	float body1SizeW{ 10.0 }, body1SizeH{ 80.0 };
	float body2SizeW{ 65.0 }, body2SizeH{ 25.0 };
	Sound *explosion, *engine;
public:
	HardEnemy(Image &image, String name, lv::Level &lvl, float X, float Y, float W, float H, Player &ob, const Sound &eng, const Sound &expl);
	void controll(int i = 0);
	void Fire(float time);
	void animation(float time);
	void behavior(float _time);
	void update(const float &time);
	void Interaction_MAP();
	sf::RectangleShape get_body1() { return body1; }
	sf::RectangleShape get_body2() { return body2; }
	sf::ConvexShape get_convex() { return convex; }
	float get_speedX() { return speedX; }
	float get_speedY() { return speedY; }

};