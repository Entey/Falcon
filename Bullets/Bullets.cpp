#include "Bullets.h"

Bullet::Bullet(Image &image, String Name, lv::Level &lvl, float X, float Y, int W, int H, float TempX, float TempY, sf::Sound &soun, sf::Sound &soun_bomb, int heroo, float dam, int altit):
Entity(image, Name, X, Y, W, H, heroo, dam, altit), hero_shoot(heroo), frame(0)
{
	objj = lvl.GetObjects("solid");	
	sound1 = new sf::Sound(soun);

	if (name == "Bomb") {
		
		damage = 100;
		speed = 0.05;
		sound2 = new sf::Sound(soun_bomb);
	}
	if (name == "Rocket") {
		damage = 50;
		speed = 1.0;
		sound2 = new sf::Sound(soun_bomb);
	}
	if (name == "Bullet"){
		damage = 5;
		speed = 1.3;
	}

	if (altitude < 100)
		sprite.setScale(0.6, 0.6);
	else if (altitude >= 100 && altitude < 150)
		sprite.setScale(0.7, 0.7);
	else if (altitude >= 150 && altitude < 200)
		sprite.setScale(0.8, 0.8);
	else if (altitude >= 200 && altitude < 250)
		sprite.setScale(0.9, 0.9);
	else if (altitude >= 250 && altitude < 300)
		sprite.setScale(1.0, 1.0);
	else if (altitude >= 300 && altitude < 350)
		sprite.setScale(1.2, 1.2);
	else if (altitude >= 350 && altitude < 400)
		sprite.setScale(1.4, 1.4);
	else if (altitude >= 400 && altitude < 450)
		sprite.setScale(1.6, 1.6);
	else if (altitude >= 450 && altitude <= 500)
		sprite.setScale(1.8, 1.8);

	scaleX = sprite.getScale().x;
	scaleY = sprite.getScale().y;

	for (int i = 0; i < objj.size(); i++)
		if (getRect().intersects(objj[i].rect))
			life = false;

	sound1->setVolume(50);
	sound1->play();

	if (hero_shoot == 2) {
		FX = TempX - ((x - TempX) * 2); // множимо вектор для того, щою кулі не зникали при промаху для бомбардувальника
		FY = TempY - ((y - TempY) * 2);
	}
	else {
		FX = TempX - ((x - TempX) * 15);
		FY = TempY - ((y - TempY) * 15);
	}

	dX = FX - x;
	dY = FY - y;
	rotation = (atan2(dY, dX)) * 180 / PI; // для того, щоб куля поверталась в сторону цілі
	sprite.rotate(rotation + 90);
	sprite.setOrigin(w / 2, h / 2);
	sprite.setTextureRect(IntRect(0, 0, w, h));
}

void Bullet::update(const float& time)
{

	distance = (sqrt(((FX - x)*(FX - x)) + ((FY - y)*(FY - y))));

	if (distance > 7) {
		x += speed*time*(FX - x) / distance;
		y += speed*time*(FY - y) / distance;
	}
	else
		life = false;


	sprite.setPosition(x, y);

	if (x <= 0) x = 1;
	if (y <= 0) y = 1;

	if (name == "Bomb") {
		if (altitude >= 10) {
			altitude -= 0.5;
			if (scaleX > 0.0){ scaleX -= time*0.0002; scaleY -= time*0.0002; } // falling animation
			sprite.setScale(scaleX, scaleY);
		}
		else if (life && altitude < 10){
			life = false;
			speed = 0;
			sprite.setScale(1.0, 1.0);
		}

		if (!life  && frame < 12) {
			frame += 0.03*time;
			sound1->stop();
			if (sound2->getStatus() == sf::Sound::Stopped) sound2->play();
			sprite.setTextureRect(IntRect(50 * int(frame), 50, 50, 50));
		}
		else if (frame >= 12 && isMove == false) {
			sprite.setTextureRect(IntRect(0, 0, 0, 0));
			if (sound2->getStatus() == sf::Sound::Stopped) { // чтобы звук взрыва был проигран до конца
				delete sound1;
				delete sound2;
				isMove = true;
				return;
			}
		}
	}

	if (name == "Rocket") {
		if (life) {
			frame += 0.01*time;
			if (frame > 8) frame -= 8;
			sprite.setTextureRect(IntRect(8 * int(frame), 0, 8, 60));
		}
		else {
			if (frame && speed) { speed = 0; frame = 0; }
			sound1->stop();
			if (sound2->getStatus() == sf::Sound::Stopped) sound2->play();
			frame += 0.015*time;
			sprite.setOrigin(50, 50);
			sprite.setTextureRect(IntRect(100 * int(frame), 100, 100, 100));
			if (frame > 9) {
				sound2->stop();
				delete sound1; delete sound2;
				isMove = true;
			}
		}
	}

	if (name == "Bullet"){
		if (life == false) {
			sound1->stop(); delete sound1; isMove = true;
		}
	}

	for (int i = 0; i < objj.size(); i++)
		if (getRect().intersects(objj[i].rect))
			life = false;
}