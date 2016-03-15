#ifndef HERO_H
#define HERO_H

#include "../Enemies/Entity.h"

class Player : public Entity {
public:
	float speedX, speedY;											// to determine the direction of flight
	bool Shoot_minigun, Shoot_rockets, Shoot_bomb, _explosion;		// check shot
	int Minigun_bullets, Rockets_bullets, Bomb_bullets;				// ammunition
	sf::Vector2i pixelPos;											// take mouse
	sf::Vector2f pos;												// take mouse
	sf::RectangleShape rect, body1, body2;							// for correct interaction with bullets
	sf::Texture *Tming;												// minigun texture for bomber
	sf::Sprite SminG1;												
	sf::Sprite SminG2;
	sf::Sprite SminG3;
	sf::View view;
private:
	float fors_timer, frame, distance, dX, dY;						
	float rotation, turret_rotation, shootBulTimer, shootBomTimer, shootRTimer;
	float maxSpeed, minSpeed, maxAltitude, forsage;
	bool stand_graphics, Forsage;
	float zip;														// speed rotation
	float *turret_x0y0, *turret_x1y1, *rxry, *shoot_frame;
	double *alpha;													// angle for turret
	float body1SizeW, body1SizeH;									
	float body2SizeW, body2SizeH;
	sf::Sound engine;
	sf::Sound explosion;
public:
	Player(Image &image, String name, lv::Level &lev, float X, float Y, float W, float H, sf::Sound &expl, sf::Sound &eng, Image &imagee);
	void update1(const float &time, const sf::RenderWindow &window);
	void update(const float &time);
	void Interaction_with_view();
	void Interaction_MAP();
	void shoot_turret_animation(Sprite &sprite, float time);
	void player_animation(char ch, float time);
	void controll(float time);
	float get_x();
	float get_y();
	float get_rotation();
	float get_speed();
	float get_altitude();
};

#endif