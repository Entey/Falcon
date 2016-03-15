#ifndef ENTITY_H
#define ENTITY_H

#include <SFML/Audio.hpp>
#include "../Level/level.h"
using namespace sf;
using namespace std;
const double PI = 3.141592653589793238463;

class Entity {
public:
	vector<lv::Object> objj;				// Вектор обєктів карти
	float x, y, speed, damage, altitude;	// x,y - координати гравця
	int w, h, health, hero_shoot;			// hero_shoot - для того, щоб гравець не підривався на власних кулях і для
	bool life, isMove,  fire{false};
	String name;
	Texture texture;
	Sprite sprite;

	Entity(Image &image, String NAME, float X, float Y, int W, int H, int heroo = 0, float dam = 0, int altit = 1) 
		: name(NAME), x(X), y(Y), w(W), h(H), hero_shoot(heroo), altitude(altit), damage(dam),
		speed(0), health(100), life(true), isMove(false)
	{
		texture.loadFromImage(image);
		texture.setSmooth(true);
		sprite.setTexture(texture);
	}
	
	virtual void update(const float &time) = 0;
	FloatRect getRect(){
		return FloatRect(x, y, w, h);
	}
	
};

#endif






