#include "Hero.h"

Player::Player(Image &image, String name, lv::Level &lev, float X, float Y, float W, float H, sf::Sound &expl, sf::Sound &eng, Image &imagee) : Entity(image, name, X, Y, W, H) {
	
	speedX = 0.0; speedY = -100.0;
	_explosion = false;
	fors_timer = 0.0; 
	rotation = 0.0;
	shootBulTimer = 0.0; shootBomTimer = 0.0; shootRTimer = 0.0;
	stand_graphics = 0; Forsage = 0;
	Shoot_minigun = Shoot_rockets = Shoot_bomb = 0;
	altitude = 100.0;
	frame = 0;
	objj = lev.GetObjects("solid");
	engine = eng; explosion = expl;
	view.reset(sf::FloatRect(0, 0, 1366, 768));
	rect.setSize(sf::Vector2f(100, 100));
	rect.setPosition(x, y);
	rect.setRotation(135);

	sprite.setScale(0.4, 0.4);
	sprite.setTextureRect(IntRect(0, 0, w, h));
	sprite.setOrigin(w / 2, h / 2);

	if (name == "destroyer"){
		health = 500;
		maxSpeed = 0.6; minSpeed = 0.2; maxAltitude = 350.0;
		Minigun_bullets = 500; Rockets_bullets = 6; Bomb_bullets = 5;
		speed = 0.2;
		body1SizeW = 10; body1SizeH = 80;
		body2SizeW = 65; body2SizeH = 25;
		forsage = 0.2;
		body1.setSize(sf::Vector2f(body1SizeW, body1SizeH));
		body1.setOrigin(body1SizeW / 3, body1SizeH / 2.2);
		body1.setPosition(x, y);
		body2.setSize(sf::Vector2f(body2SizeW, body2SizeH));
		body2.setOrigin(body2SizeW / 2, body2SizeH / -20);
		body2.setPosition(x, y);
		zip = 1;
	}
	if (name == "assault_plane"){
		health = 700;
		maxSpeed = 0.45; minSpeed = 0.2; maxAltitude = 400.0;
		Minigun_bullets = 300; Rockets_bullets = 10; Bomb_bullets = 8;
		speed = 0.2;
		body1SizeW = 10; body1SizeH = 60;
		body2SizeW = 70; body2SizeH = 15;
		forsage = 0.2;
		body1.setSize(sf::Vector2f(body1SizeW, body1SizeH));
		body1.setOrigin(body1SizeW / 3, body1SizeH / 1.5);
		body1.setPosition(x, y);
		body2.setSize(sf::Vector2f(body2SizeW, body2SizeH));
		body2.setOrigin(body2SizeW / 2, body2SizeH);
		body2.setPosition(x, y);
		zip = 0.6;
	}
	if (name == "bomber"){
		health = 1500;
		maxSpeed = 0.3; minSpeed = 0.1; maxAltitude = 400.0;
		Minigun_bullets = 1000; Rockets_bullets = 0; Bomb_bullets = 30;
		speed = 0.2;
		body1SizeW = 10; body1SizeH = 90;
		body2SizeW = 90; body2SizeH = 25;

		body1.setSize(sf::Vector2f(body1SizeW, body1SizeH));
		body1.setOrigin(body1SizeW / 3, body1SizeH / 2);
		body1.setPosition(x, y);
		body2.setSize(sf::Vector2f(body2SizeW, body2SizeH));
		body2.setOrigin(body2SizeW / 2, body2SizeH / -20);
		body2.setPosition(x, y);
		forsage = 0.1;
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
		SminG3.setTexture(*Tming);
		SminG3.setTextureRect(IntRect(45, 0, 45, 15));
		SminG3.setOrigin(37, 15 / 2);
		SminG3.setPosition(x, y - 50);
		SminG3.setScale(0.4, 0.4);
		zip = 1.4;
		turret_x0y0 = new float[6];
		turret_x0y0[0] = x; turret_x0y0[1] = y;						// initial point for the left turret
		turret_x0y0[2] = x - 45; turret_x0y0[3] = y + 5;			// initial point for the right turret
		turret_x0y0[4] = x + 45; turret_x0y0[5] = y + 5;			// initial point for the back turret
		rxry = new float[6];
		rxry[0] = turret_x0y0[0] - x; rxry[1] = turret_x0y0[1] - y; // radius for on X and on Y
		rxry[2] = turret_x0y0[2] - x; rxry[3] = turret_x0y0[3] - y; // radius for on X and on Y
		rxry[4] = turret_x0y0[4] - x; rxry[5] = turret_x0y0[5] - y; // radius for on X and on Y
		turret_x1y1 = new float[6];
		alpha = new double;											// to determine the rotation angle of the turret
		shoot_frame = new float;
		*shoot_frame = { 0.0 };
	}
	engine.setVolume(50);
	engine.play();

	explosion.setVolume(100);
}

void Player::update1(const float &time, const sf::RenderWindow &window) {
	engine.setLoop(true);

	rect.setPosition(x, y);
	body1.setPosition(x, y);
	body2.setPosition(x, y);

	dX = (rect.getPosition().x + speedX) - x;
	dY = (rect.getPosition().y + speedY) - y;
	distance = (sqrt((((rect.getPosition().x - speedX) - x)*((rect.getPosition().x - speedX) - x)) + ((rect.getPosition().y - speedY) - y)*((rect.getPosition().y - speedY) - y)));
	rotation = (atan2(dY, dX)) * 180 / 3.14159265;
	x += speed*time*(rect.getPosition().x + speedX - x) / distance;
	y += speed*time*(rect.getPosition().y + speedY - y) / distance;
	body1.setRotation(rotation + 90);
	body2.setRotation(rotation + 90);
	sprite.setRotation(rotation + 90);
	
	if (name == "bomber") {
		pixelPos = Mouse::getPosition(window);
		pos = window.mapPixelToCoords(pixelPos);
		distance = (sqrt(((pos.x - SminG1.getPosition().x)*(pos.x - SminG1.getPosition().x)) + ((pos.y - SminG1.getPosition().y)*(pos.y - SminG1.getPosition().y))));
		dX = pos.x - SminG1.getPosition().x;
		dY = pos.y - SminG1.getPosition().y;
		turret_rotation = (atan2(dY, dX)) * 180 / 3.14159265;

		SminG1.setRotation(turret_rotation - 180);
		SminG2.setRotation(turret_rotation - 180);
		SminG3.setRotation(turret_rotation - 180);

		*alpha = rotation * PI / 180;

		turret_x1y1[0] = x + rxry[0] * (sin(*alpha)) - rxry[1] * (cos(*alpha));
		turret_x1y1[1] = y + rxry[0] * (cos(*alpha)) - rxry[1] * (sin(*alpha));
		SminG1.setPosition(turret_x1y1[0], turret_x1y1[1]);

		turret_x1y1[2] = x + rxry[2] * (sin(-*alpha)) - rxry[3] * (cos(*alpha));
		turret_x1y1[3] = y + rxry[2] * (cos(-*alpha)) - rxry[3] * (sin(*alpha));
		SminG2.setPosition(turret_x1y1[2], turret_x1y1[3]);

		turret_x1y1[4] = x + rxry[4] * (sin(-*alpha)) - rxry[5] * (cos(*alpha));
		turret_x1y1[5] = y + rxry[4] * (cos(-*alpha)) - rxry[5] * (sin(*alpha));
		SminG3.setPosition(turret_x1y1[4], turret_x1y1[5]);
		shoot_turret_animation(SminG1, time);
		shoot_turret_animation(SminG2, time);
		shoot_turret_animation(SminG3, time);
	}

	if (health <= 0 || altitude <= 0) {
		life = false;
		if (stand_graphics == true && frame > 0) { frame = 0; stand_graphics = false; }				// for correct display explosion
		if (life == false && explosion.getStatus() == sf::Sound::Stopped && _explosion == false) {  // we explosion and free the memory
			engine.stop();
			explosion.play();
			_explosion = true;
			if (name == "bomber"){
				delete alpha;
				delete[] turret_x1y1;
				delete[] turret_x0y0;
				delete[] rxry;
				delete shoot_frame;
				delete Tming;
				SminG1.setTextureRect(IntRect(0, 0, 0, 0));
			}
		}
		stand_graphics == false;
		player_animation('D', time);
		speed = 0.0;
	}

	sprite.setPosition(x, y);
	Interaction_MAP();
	Interaction_with_view();
	if (life == true) controll(time);
}

void Player::update(const float &time) {}

void Player::Interaction_with_view() {
	view.setCenter(x, y);
}

void Player::Interaction_MAP() {
	for (int i = 0; i<objj.size(); i++)
		if (getRect().intersects(objj[i].rect)) {
			if (objj[i].name == "solid") {
				speedY *= -1;
				speedX *= -1;
			}
		}
}

void Player::shoot_turret_animation(Sprite &sprite, float time) {
	if (Shoot_minigun){
		*shoot_frame += time*0.1;
		if (*shoot_frame >= 3) *shoot_frame = 0;
		sprite.setTextureRect(IntRect(45 * int(*shoot_frame), 0, 45, 15));
	}
	else
		sprite.setTextureRect(IntRect(45, 0, 45, 15));
}

void Player::player_animation(char ch, float time) {
	if (life == true) frame += 0.02*time;
	else frame += 0.007*time;

	if (name == "destroyer"){
		if (life == true && frame > 8) frame -= 8;
		else if (life == false && frame > 9) return;

		switch (ch){
		case 'R': sprite.setTextureRect(IntRect(120 * int(frame), 180, 120, 180));
			break;
		case 'L': sprite.setTextureRect(IntRect(120 * int(frame), 360, 120, 180));
			break;
		case 'D': sprite.setTextureRect(IntRect(120 * int(frame), 540, 120, 180));
			break;
		default: sprite.setTextureRect(IntRect(120 * int(frame), 0, 120, 180));
		}
	}
	if (name == "assault_plane"){
		if (life == true && frame > 5) frame -= 5;
		else if (life == false && frame > 11) return;
		switch (ch){
		case 'R': sprite.setTextureRect(IntRect(200 * int(frame), 200, 200, 200));
			break;
		case 'L': sprite.setTextureRect(IntRect(200 * int(frame), 400, 200, 200));
			break;
		case 'D': (frame < 5) ? sprite.setTextureRect(IntRect(200 * int(frame), 600, 200, 200)) :
			sprite.setTextureRect(IntRect(200 * (int(frame) - 5), 800, 200, 200));
			break;
		default: sprite.setTextureRect(IntRect(200 * int(frame), 0, 200, 200));
		}
	}
	if (name == "bomber"){
		if (life == true && frame > 8) frame -= 8;
		else if (life == false && frame > 9) return;
		switch (ch){
		case 'D': sprite.setTextureRect(IntRect(300 * int(frame), 258, 300, 258));
			break;
		default: sprite.setTextureRect(IntRect(300 * int(frame), 0, 300, 258));
		}
	}

}

void Player::controll(float time){
	if (life == true && stand_graphics == false) player_animation('q', time);

	if (Keyboard::isKeyPressed && life == true)
	{
		// Controll
		if (Keyboard::isKeyPressed(Keyboard::Left))
		{
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
			}
			stand_graphics = true;
			player_animation('L', time);
		}
		else if (Keyboard::isKeyPressed(Keyboard::Right))
		{
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
			}
			stand_graphics = true;
			player_animation('R', time);
		}
		else stand_graphics = false;

		// Speed
		if (Keyboard::isKeyPressed(Keyboard::Up) && speed <= maxSpeed) {
			speed += 0.001;
		}
		if (Keyboard::isKeyPressed(Keyboard::Down) && speed >= minSpeed) {
			speed -= 0.001;
		}
		// Altitude
		if (Keyboard::isKeyPressed(Keyboard::PageUp)){
			if (altitude < maxAltitude) {
				if (name == "destroyer") {
					altitude++;
					body2SizeW += 0.1; body2SizeH += 0.1;
					body1SizeH += 0.2;
					body2.setOrigin(body2SizeW / 2.1, body2SizeH / -15);
					body1.setOrigin(body1SizeW / 3, body1SizeH / 2.2);
				}
				if (name == "bomber") {
					altitude += 0.5;
					body2SizeW += 0.5; body2SizeH += 0.1; body1SizeH += 0.5;
					body2.setOrigin(body2SizeW / 2.1, body2SizeH / -15);
					body1.setOrigin(body1SizeW / 3, body1SizeH / 2);
					SminG1.setScale(0.004*altitude, 0.004*altitude);
					SminG2.setScale(0.004*altitude, 0.004*altitude);
					SminG3.setScale(0.004*altitude, 0.004*altitude);
					rxry[2] -= 0.23; rxry[3] += 0.05;
					rxry[4] += 0.23; rxry[5] += 0.05;
				}
				if (name == "assault_plane") {
					altitude++;
					body2SizeW += 0.7; body2SizeH += 0.1;
					body1SizeH += 0.5;
					body2.setOrigin(body2SizeW / 2.1, body2SizeH);
					body1.setOrigin(body1SizeW / 3, body1SizeH / 1.5);
				}
				body2.setSize(sf::Vector2f(body2SizeW, body2SizeH));
				body1.setSize(sf::Vector2f(body1SizeW, body1SizeH));
				body2.setPosition(x, y);
				body1.setPosition(x, y);
				view.zoom(1.001f);
				sprite.setScale(0.004*altitude, 0.004*altitude);
			}
		}
		if (Keyboard::isKeyPressed(Keyboard::PageDown)){
			if (altitude >= 0) {
				if (name == "destroyer") {
					altitude--;
					body2SizeW -= 0.1; body2SizeH -= 0.1;
					body1SizeH -= 0.2;
					body2.setOrigin(body2SizeW / 2.1, body2SizeH / -15);
					body1.setOrigin(body1SizeW / 3, body1SizeH / 2.2);
				}
				if (name == "bomber") {
					altitude -= 0.5;
					body2SizeW -= 0.5; body2SizeH -= 0.1;
					body1SizeH -= 0.5;
					body2.setOrigin(body2SizeW / 2.1, body2SizeH / -15);
					body1.setOrigin(body1SizeW / 3, body1SizeH / 2);
					SminG1.setScale(0.004*altitude, 0.004*altitude);
					SminG2.setScale(0.004*altitude, 0.004*altitude);
					SminG3.setScale(0.004*altitude, 0.004*altitude);
					rxry[2] += 0.23; rxry[3] -= 0.05;
					rxry[4] -= 0.23; rxry[5] -= 0.05;
				}
				if (name == "assault_plane") {
					altitude--;
					body2SizeW -= 0.7; body2SizeH -= 0.1;
					body1SizeH -= 0.5;
					body2.setOrigin(body2SizeW / 2.1, body2SizeH);
					body1.setOrigin(body1SizeW / 3, body1SizeH / 1.5);
				}

				body2.setSize(sf::Vector2f(body2SizeW, body2SizeH));
				body1.setSize(sf::Vector2f(body1SizeW, body1SizeH));
				body2.setPosition(x, y);
				body1.setPosition(x, y);
				if (altitude >= 50) {
					view.zoom(0.999f);
					sprite.setScale(0.004*altitude, altitude*0.004);
				}
			}
		}

		// Weapons
		shootBulTimer += 0.01*time;
		shootBomTimer += 0.01*time;
		shootRTimer += 0.01*time;

		if (Mouse::isButtonPressed(Mouse::Left) && name == "bomber"){
			if ((Minigun_bullets > 0) && (shootBulTimer >= 0.5)) {
				Shoot_minigun = true;	shootBulTimer = 0.0;
			}
		}


		if (Keyboard::isKeyPressed(Keyboard::Space) && Minigun_bullets > 0 && shootBulTimer >= 0.5 && (name == "destroyer" || name == "assault_plane")) {
			Shoot_minigun = true;
			shootBulTimer = 0.0;
		}

		if (Keyboard::isKeyPressed(Keyboard::R) && Rockets_bullets > 0 && shootRTimer >= 2.0) {
			shootRTimer = 0;
			Shoot_rockets = true;
		}

		if (Keyboard::isKeyPressed(Keyboard::LControl) && Bomb_bullets > 0 && shootBomTimer >= 3.0) {
			shootBomTimer = 0;
			Shoot_bomb = true;
		}


		if (Keyboard::isKeyPressed(Keyboard::F)) {
			if (Forsage == false && fors_timer < 5)	{
				speed += forsage;
				Forsage = true;
				engine.setPitch(1.1);
			}
		}
		else if (Forsage == true && fors_timer > 5){
			Forsage = false;
			speed -= forsage;
			engine.setPitch(1.0);
		}

		if (Forsage == true && fors_timer < 5) {
			fors_timer += 0.001 * time;
		}
		else if (fors_timer >= 5) fors_timer += 0.001 * time;
		if (fors_timer > 15) fors_timer = 0;
	}
}


float Player::get_x() { return x; }
float Player::get_y() { return y; }
float Player::get_altitude() { return altitude; }
float Player::get_rotation() { return rotation; }
float Player::get_speed() { return speed; }