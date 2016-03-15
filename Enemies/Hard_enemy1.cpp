#include "Hard_enemy1.h"

HardEnemy::HardEnemy(Image &image, String name, lv::Level &lvl, float X, float Y, float W, float H, Player &ob, const Sound &eng, const Sound &expl) : Entity(image, name, X, Y, W, H), p(ob) {
	objj = lvl.GetAllObjects();
	convex.setPointCount(3);
	convex.setPoint(0, sf::Vector2f(0, 0));
	convex.setPoint(1, sf::Vector2f(600, 160));
	convex.setPoint(2, sf::Vector2f(602, 160));
	convex.setPosition(x, y);
	body1.setSize(sf::Vector2f(body1SizeW, body1SizeH));
	body1.setOrigin(body1SizeW / 3.0, body1SizeH / 2.2);
	body1.setPosition(x, y);
	body2.setSize(sf::Vector2f(body2SizeW, body2SizeH));
	body2.setOrigin(body2SizeW / 2.0, body2SizeH / -20.0);
	body2.setPosition(x, y);
	sprite.setOrigin(w / 2, h / 2);
	sprite.setRotation(0);
	sprite.setScale(0.4, 0.4);
	altitude = 100;
	if (name == "Hard1"){
		health = 500; speed = 0.1; zip = 8.0; maxSpeed = 0.5; minSpeed = 0.3;
	}
	if (name == "Hard2"){
		health = 200; speed = 0.1; zip = 5.0; maxSpeed = 0.4; minSpeed = 0.3;
	}
	explosion = new sf::Sound(expl);
	engine = new sf::Sound(eng);
	engine->play();
}

void HardEnemy::controll(int i) {
	switch (i) {
	case 1: {
		turn_animation_left = false; turn_animation_right = true;
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
		turn_animation_right = false; turn_animation_left = true;
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
	default: turn_animation_right = false; turn_animation_left = false; break;
	}
	return;
}

void HardEnemy::Fire(float time){
	shootB += 0.01*time;
	if (shootB >= 1.0) {
		shootB = 0.0;
		fire = true;
		Minigun_bullets--;
	}
	else
		fire = false;
}

void HardEnemy::animation(float time) {

	if (life == true && frame > 7) frame -= 7;
	if (life == true) {
		frame += 0.02*time;
		if (turn_animation_right == true && turn_animation_left == false){
			sprite.setTextureRect(IntRect(105 * int(frame), 180, 105, 180));
		}
		else if (turn_animation_right == false && turn_animation_left == true)
			sprite.setTextureRect(IntRect(105 * int(frame), 360, 105, 180));
		else{
			sprite.setTextureRect(IntRect(105 * int(frame), 0, 105, 180));
		}
	}
	else {
		if (explosion->getStatus() == sf::Sound::Stopped && frame < 9) { frame = 0;  explosion->play(); }
		frame += 0.007*time;
		sprite.setTextureRect(IntRect(105 * int(frame), 540, 105, 180));
		if (frame >= 9 && explosion->getStatus() == sf::Sound::Stopped) {
			delete explosion;
			delete engine;
			isMove = true;
		}
	}
}

void HardEnemy::behavior(float _time)
{
	FX = p.get_x() - x;
	FY = p.get_y() - y;
	angle = (atan2(FY, FX)) * 180 / PI; // ��� �������� ������� ������

	std::mt19937_64 re(time(0));							// ��������� ���������� �����
	std::uniform_int_distribution<int> one_to_for{ 1, 4 };  // ��� ���������� �������� ������

	if (angle < 0) angle = 180 + (180 - fabs(angle));				// ����������� ����� �������
	if (rotation < 0) rotation = 180 + (180 - fabs(rotation));		// ����������� ����� �������

	if ((y + 900 > p.get_y()) && (y - 900 < p.get_y()) && (x + 900 > p.get_x()) && (x - 900 < p.get_x())) {  // ���� ������� ������ � ���� ������� ������ 900�900
		//��������� ��� �� �� �������, �� ������� �� ��������

		if (rotation < 180) {										// ��� �� ���� �� 180 �������

			if (angle > rotation && angle <= rotation + 130) {     // ���� �� ��������� �������� ������
				if (p.get_speed() > speed && speed < maxSpeed && distance > 400) speed += 0.005;		// ���� �������� ����� - �������
				else if (p.get_speed() <= speed && distance < 400)speed -= 0.005;

				if (angle <= rotation + 7 && angle >= rotation - 7) controll(0); // ��� ��������� ������ �������, ��� ������ ������ �� �������� ���� ����
				else controll(2);	// ������� ����
			}
			else if (angle > rotation + 130 && angle <= rotation + 230) { // ���� �� ��������� ������ ������
				behav += 0.001*_time;
				if (behav > 1.0){
					behav = 0;
					behav1 = one_to_for(re);
				}
				switch (behav1) { // brain enemy
				case 1: controll(0); if (speed < maxSpeed) speed += 0.0005;
					break;
				case 2: controll(1); if (speed < maxSpeed) speed += 0.0005;
					break;
				case 3: controll(2); if (speed < maxSpeed) speed += 0.0005;
					break;
				case 4: if (speed > minSpeed) speed -= 0.0005; controll(0);
					break;
				}
			}
			else  controll(1);		// ������� �������
		}
		else {																// ��� �� 180 �� 360 ������� �������, ��� ���������
			if (angle <= rotation && angle >= rotation - 130){
				if (p.get_speed() > speed && speed < maxSpeed && distance > 400) speed += 0.005;		// ���� �������� ����� - �������
				else if (p.get_speed() <= speed && distance < 400)speed -= 0.005;

				if (angle <= rotation + 7 && angle >= rotation - 7) controll(0);
				else controll(1);
			}
			else if (angle < rotation - 130 && angle >= rotation - 230) {
				behav += 0.001*_time;
				if (behav > 1.0){
					behav = 0;
					behav1 = one_to_for(re);
				}
				switch (behav1) {
				case 1: if (speed < maxSpeed) speed += 0.0005; controll(0);
					break;
				case 2: controll(1); if (speed < maxSpeed) speed += 0.0005;
					break;
				case 3: controll(2); if (speed < maxSpeed) speed += 0.0005;
					break;
				case 4: if (speed > minSpeed) speed -= 0.0005; controll(0);
					break;
				}
			}
			else  controll(2);
		}

		if (altitude <= p.get_altitude()) {		// �������� ������
			body2SizeW += 0.1; body2SizeH += 0.1;
			body2.setSize(sf::Vector2f(body2SizeW, body2SizeH));
			body2.setOrigin(body2SizeW / 2.1, body2SizeH / -15);
			body2.setPosition(x, y);

			body1SizeH += 0.2;
			body1.setSize(sf::Vector2f(body1SizeW, body1SizeH));
			body1.setOrigin(body1SizeW / 3, body1SizeH / 2.2);
			body1.setPosition(x, y);
			altitude += 0.2;
			sprite.setScale(0.004*altitude, 0.004*altitude);
		}
		else if (altitude > p.get_altitude()) {
			body2SizeW -= 0.1; body2SizeH += -.1;
			body2.setSize(sf::Vector2f(body2SizeW, body2SizeH));
			body2.setOrigin(body2SizeW / 2.1, body2SizeH / -15);
			body2.setPosition(x, y);

			body1SizeH -= 0.2;
			body1.setSize(sf::Vector2f(body1SizeW, body1SizeH));
			body1.setOrigin(body1SizeW / 3, body1SizeH / 2.2);
			body1.setPosition(x, y);
			altitude -= 0.2;
			sprite.setScale(0.004*altitude, altitude*0.004);
		}
	}
	else
		controll(2); // default behavior
}


void HardEnemy::update(const float &time) {
	if (p.life && health > 0){
		if (Minigun_bullets && convex.getGlobalBounds().intersects(p.body2.getGlobalBounds())) Fire(time);
		behavior(time);
	}
	else controll(2);

	animation(time);
	Interaction_MAP();
	convex.setPosition(x, y);
	sprite.setPosition(x, y);
	body1.setPosition(x, y);
	body2.setPosition(x, y);
	dX = (convex.getPosition().x + speedX) - x;
	dY = (convex.getPosition().y + speedY) - y;
	dis = (sqrt((((convex.getPosition().x - speedX) - x)*((convex.getPosition().x - speedX) - x)) + ((convex.getPosition().y - speedY) - y)*((convex.getPosition().y - speedY) - y)));
	rotation = (atan2(dY, dX)) * 180 / PI;
	convex.setRotation(rotation - 15);
	sprite.setRotation(rotation + 90);
	body1.setRotation(rotation + 90);
	body2.setRotation(rotation + 90);

	x += speed*time*(convex.getPosition().x + speedX - x) / dis;
	y += speed*time*(convex.getPosition().y + speedY - y) / dis;
	distance = (sqrt(((p.get_x() - x)*(p.get_x() - x)) + ((p.get_y() - y)*(p.get_y() - y))));

	if (health <= 0) { life = false; speed = 0; }
}

void HardEnemy::Interaction_MAP() {
	for (int i = 0; i<objj.size(); i++)
		if (getRect().intersects(objj[i].rect)) {
			if (objj[i].name == "solid") {
				speedY *= -1;
				speedX *= -1;
			}
		}
}