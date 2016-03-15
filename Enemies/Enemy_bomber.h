#ifndef ENEMY_BOMBER
#define ENEMY_BOMBER

#include "Entity.h"
#include "../Hero/Hero.h"


class Enemy_bomber : public Entity{
public:
	float distance, rotation, mission_course, maxSpeed, minSpeed, maxAltitude{ 500.0 };
	float zip, mission_timer{ 0.0 }, frame;
	float mission_x, mission_y;
	int Minigun_bullets{1000};
	float speedX{ 0.0 }, speedY{ -1000.0 };
	Player &p;
	bool damage{ false }, Shoot_minigun{false};
	sf::RectangleShape rect;
	sf::RectangleShape body1, body2;
	sf::Sound * engine, *explosion;
	sf::Vector2f coord_mission;
	sf::Texture *Tming;												// minigun texture for bomber
	sf::Sprite SminG1;
	sf::Sprite SminG2;
	float body1SizeW{ 10.0 }, body1SizeH{ 80.0 };
	float body2SizeW{ 65.0 }, body2SizeH{ 25.0 };
	float *turret_x0y0, *turret_x1y1, *rxry, *shoot_frame;
	double *alpha;
	float MisX, MisY, dX, dY;
	float turret_rotation, shootBulTimer;
	sf::ConvexShape convex;

public:
	Enemy_bomber(Image &image, String NAME, lv::Level &lvl, float X, float Y, int W, int H, float TX, float TY, Player &ob, const Sound &eng, const Sound &expl, Image &imagee) : Entity(image, name, X, Y, W, H), mission_x(TX), mission_y(TY), p(ob)
	{
		convex.setPointCount(3);
		convex.setPoint(0, sf::Vector2f(0, 0));
		convex.setPoint(1, sf::Vector2f(600, 160));
		convex.setPoint(2, sf::Vector2f(602, 160));
		convex.setPosition(x, y);
		convex.setFillColor(sf::Color::Cyan);


		health = 1500;
		maxSpeed = 0.3; minSpeed = 0.1; maxAltitude = 400.0;
		Minigun_bullets = 1000;
		speed = 0.2;
		body1SizeW = 10; body1SizeH = 90;
		body2SizeW = 90; body2SizeH = 25;

		body1.setSize(sf::Vector2f(body1SizeW, body1SizeH));
		body1.setOrigin(body1SizeW / 3, body1SizeH / 2);
		body1.setPosition(x, y);
		body2.setSize(sf::Vector2f(body2SizeW, body2SizeH));
		body2.setOrigin(body2SizeW / 2, body2SizeH);
		body2.setPosition(x, y);
		Tming = new Texture;

		Tming->loadFromImage(imagee);
		SminG1.setTexture(*Tming);
		SminG1.setTextureRect(IntRect(45, 0, 45, 15));
		SminG1.setOrigin(37, 15 / 2);
		SminG1.setPosition(x, y - 50);
		SminG1.setScale(0.4, 0.4);
		SminG2.setTexture(*Tming);
		SminG2.setTextureRect(IntRect(45, 0, 45, 15));
		SminG2.setOrigin(37, 15 / 2);
		SminG2.setPosition(x, y - 50);
		SminG2.setScale(0.4, 0.4);
		
		zip = 1.4;
		turret_x0y0 = new float[4];
		turret_x0y0[0] = x + 45; turret_x0y0[1] = y - 10;						// initial point for the left turret
		turret_x0y0[2] = x - 45; turret_x0y0[3] = y - 10;			// initial point for the right turret
		
		rxry = new float[6];
		rxry[0] = turret_x0y0[0] - x; rxry[1] = turret_x0y0[1] - y; // radius for on X and on Y
		rxry[2] = turret_x0y0[2] - x; rxry[3] = turret_x0y0[3] - y; // radius for on X and on Y
		
		turret_x1y1 = new float[4];
		alpha = new double;											// to determine the rotation angle of the turret
		shoot_frame = new float;
		*shoot_frame = { 0.0 };
	
		explosion = new sf::Sound(expl);
		engine = new sf::Sound(eng);
		engine->play();

		sprite.setOrigin(w / 2, h / 2);
		sprite.setRotation(0);
		sprite.setTextureRect(IntRect(0, 0, w, h));
		sprite.setScale(0.4, 0.4);
	}

	void update(const float &time) {
		engine->setLoop(true);
		check_fire(p);
		turret_rot(p);
		
		convex.setPosition(x, y);
		convex.setRotation(mission_course);
		check_mission(time);

		if (int(rotation) != int(mission_course)) controll(2);

		cout << "rotation" << rotation << endl;
		cout << "mission_course" << mission_course << endl;
		rect.setPosition(x, y);
		body1.setPosition(x, y);
		body2.setPosition(x, y);
		sprite.setPosition(x, y);

		MisX = (mission_x + speedX) - x;
		MisY = (mission_y + speedY) - y;
		mission_course = (atan2(MisX, MisY) * 180 / PI) -180;

		dX = (rect.getPosition().x + speedX) - x;
		dY = (rect.getPosition().y + speedY) - y;
		distance = (sqrt((((rect.getPosition().x - speedX) - x)*((rect.getPosition().x - speedX) - x)) + ((rect.getPosition().y - speedY) - y)*((rect.getPosition().y - speedY) - y)));
		rotation = (atan2(dY, dX)) * 180 / PI;
		x += speed*time*(rect.getPosition().x + speedX - x) / distance;
		y += speed*time*(rect.getPosition().y + speedY - y) / distance;
		body1.setRotation(rotation + 90);
		body2.setRotation(rotation + 90);
		sprite.setRotation(rotation + 90);
		




		*alpha = rotation * PI / 180;
		turret_x1y1[0] = x + rxry[0] * (sin(-*alpha)) - rxry[1] * (cos(*alpha));
		turret_x1y1[1] = y + rxry[0] * (cos(-*alpha)) - rxry[1] * (sin(*alpha));
		SminG1.setPosition(turret_x1y1[0], turret_x1y1[1]);
		turret_x1y1[2] = x + rxry[2] * (sin(-*alpha)) - rxry[3] * (cos(*alpha));
		turret_x1y1[3] = y + rxry[2] * (cos(-*alpha)) - rxry[3] * (sin(*alpha));
		SminG2.setPosition(turret_x1y1[2], turret_x1y1[3]);

		shoot_turret_animation(SminG1, time);
		shoot_turret_animation(SminG2, time);


		frame += 0.01*time;
		if (health > 0) {
			if (frame > 8) frame -= 8;  // якщо 5 кадрів починаємо з першого
			sprite.setTextureRect(IntRect(300 * int(frame), 0, 300, 210));
		}
		else {
			if (explosion->getStatus() == sf::Sound::Stopped && frame < 9) { frame = 0; life = false; speed = 0; explosion->play(); }
			sprite.setTextureRect(IntRect(300 * int(frame), 210, 300, 210));
			if (frame >= 9 && explosion->getStatus() == sf::Sound::Stopped) {
				delete explosion;
				delete engine;
				delete alpha;
				delete[] turret_x1y1;
				delete[] turret_x0y0;
				delete[] rxry;
				delete shoot_frame;
				delete Tming;
				SminG1.setTextureRect(IntRect(0, 0, 0, 0));
				SminG2.setTextureRect(IntRect(0, 0, 0, 0));
				isMove = true;
			}
		}


					
	}

	void turret_rot(Player &p){ 
		if (check_fire(p)){
			distance = (sqrt(((p.get_x() - SminG1.getPosition().x)*(p.get_x() - SminG1.getPosition().x)) + ((p.get_y() - SminG1.getPosition().y)*(p.get_y() - SminG1.getPosition().y))));
			dX = p.get_x() - SminG1.getPosition().x;
			dY = p.get_y() - SminG1.getPosition().y;
			turret_rotation = (atan2(dY, dX)) * 180 / 3.14159265;

			SminG1.setRotation(turret_rotation - 180);
			SminG2.setRotation(turret_rotation - 180);		
		}
		else{
			SminG1.setRotation(rotation);
			SminG2.setRotation(rotation);
		}
	}
	void controll(int i) {
		switch (i) {
		case 1: {
			if (speedY < 0 && speedX <= 0) {
				speedY += zip;
				speedX -= zip;
			}
			if (speedY >= 0 && speedX < 0) {
				speedY += zip;
				speedX += zip;
			}
			if (speedY > 0 && speedX >= 0) {
				speedY -= zip;
				speedX += zip;
			}
			if (speedY <= 0 && speedX > 0) {
				speedY -= zip;
				speedX -= zip;
			} }  break;
		case 2: {
			if (speedY <= 0 && speedX < 0) {
				speedY -= zip;
				speedX += zip;
			}
			if (speedY > 0 && speedX <= 0) {
				speedY -= zip;
				speedX -= zip;
			}
			if (speedY >= 0 && speedX > 0) {
				speedY += zip;
				speedX -= zip;
			}
			if (speedY < 0 && speedX >= 0) {
				speedY += zip;
				speedX += zip;
			} }  break;
		}
		return;
	}
	void shoot_turret_animation(Sprite &sprite, float time) {
		if (Shoot_minigun){
			*shoot_frame += time*0.1;
			if (*shoot_frame >= 3) *shoot_frame = 0;
			sprite.setTextureRect(IntRect(45 * int(*shoot_frame), 0, 45, 15));
		}
		else
			sprite.setTextureRect(IntRect(45, 0, 45, 15));
	}
	bool check_fire(Player &p){
		if ((y + 700 > p.get_y()) && (y - 700 < p.get_y()) && (x + 700 > p.get_x()) && (x - 700 < p.get_x())) return true;
		else return false;
	}
	void check_mission(const float &time) {
		if (damage) mission_timer += 0.01 * time;
			
		if (mission_timer > 5){
			damage = false;
			mission_timer = 0.0;
			}
	}
	
	void set_damage(bool x) { damage = x; }
	bool get_damage() { return damage; }
};



#endif ENEMY_BOMBER