#include "Dirigible.h"

Dirigible::Dirigible(Image &image, String name, lv::Level &lvl, float X, float Y, float W, float H, Player&ob, const Sound &eng, const Sound &expl) : Entity(image, name, X, Y, W, H),
startX(X), startY(Y), p(ob) {
	objj = lvl.GetObjects("enemy1");
	health = 50; dir = 0; speed = 0.03;
	altitude = 100;
	sprite.setTextureRect(IntRect(0, 0, 50, 159));
	sprite.setOrigin(w / 2, h / 2);
	sprite.setRotation(180);
	explosion = new sf::Sound(expl);
	engine = new sf::Sound(eng);
	engine->play();
}

void Dirigible::update(const float &time)
{

	shootR += 0.001*time;
	if (life == true && (y + 700 > p.get_y()) && (y - 700 < p.get_y()) && (x + 700 > p.get_x()) && (x - 700 < p.get_x()) && shootR > 10) {
		fire = true;
		shootR = 0;
	}
	else
		fire = false;

	sprite.setPosition(x + w / 2, y + h / 2);

	if (y < startY + 2000 && x <= startX) {
		sprite.setRotation(180);
		y += speed*time;
	}
	else if (y >= startY + 2000 && x < startX + 2000) {
		sprite.setRotation(-90);
		x += speed*time;
	}
	else if (x >= startX + 2000 && y > startY) {
		sprite.setRotation(180);
		y -= speed*time;
	}
	else if (y <= startY && x > startX) {
		sprite.setRotation(90);
		x -= speed*time;
	}

	dir += 0.01*time; // для часу зміни кадрів
	if (health > 0) {
		if (dir > 8) dir -= 8;  // якщо 5 кадрів починаємо з першого
		sprite.setTextureRect(IntRect(50 * int(dir), 0, 50, 159));
	}
	else {
		if (explosion->getStatus() == sf::Sound::Stopped && dir < 9) { dir = 0; life = false; speed = 0; explosion->play(); }
		sprite.setTextureRect(IntRect(100 * int(dir), 170, 100, 105));
		if (dir >= 9 && explosion->getStatus() == sf::Sound::Stopped) {
			delete explosion;
			delete engine;
			isMove = true;
		}
	}
}