/*
if ((y + 9000 > p.get_y()) && (y - 9000 < p.get_y()) && (x + 9000 > p.get_x()) && (x - 9000 < p.get_x())) {

			// rotation < 180
			if (rotation < 180) {

				if (angle > rotation && angle <= rotation + 130){
					if (distance < 500) {
						if (p.speed > speed && speed < maxSpeed) speed += 0.005;
						else if (p.speed < speed)speed -= 0.005;
					}
					if (altitude <= p.altitude) {
						altitude += 0.1;
						sprite.setScale(0.004*altitude, 0.004*altitude);
					}
					else if (altitude > p.altitude) {
						altitude -= 0.1;
						sprite.setScale(0.004*altitude, altitude*0.004);
					}
					controll(2);
				}
				else if (angle > rotation + 130 && angle <= rotation + 180) {
					behav += 0.001*_time;
					if (behav > 1.0){
						behav = 0;
						std::mt19937_64 re(time(0));
						std::uniform_int_distribution<int> one_to_for{ 1, 4 };
						behav1 = one_to_for(re);
						cout << behav1 << endl;
					}
					switch (behav1) {
					case 1: if (speed < maxSpeed) speed += 0.0005;
						break;
					case 2: controll(1); if (speed < maxSpeed) speed += 0.0005;
						break;
					case 3: controll(2); if(speed < maxSpeed) speed += 0.0005;
						break;
					case 4: if(speed > minSpeed) speed -= 0.0005;
						break;
					}
				}
				else{
					if (altitude <= p.altitude) {
						altitude += 0.1;
						sprite.setScale(0.004*altitude, 0.004*altitude);
					}
					else if (altitude > p.altitude) {
						altitude -= 0.1;
						sprite.setScale(0.004*altitude, altitude*0.004);
					}
					controll(1);
				}
			}
			// rotation > 180
			else {

				if (angle <= rotation && angle >= rotation - 130) {
					if (distance < 500) {
						if (p.speed > speed && speed < maxSpeed) speed += 0.005;
						else if (p.speed < speed)speed -= 0.005;
					}
					if (altitude <= p.altitude) {
						altitude += 0.1;
						sprite.setScale(0.004*altitude, 0.004*altitude);
					}
					else if (altitude > p.altitude) {
						altitude -= 0.1;
						sprite.setScale(0.004*altitude, altitude*0.004);
					}
					controll(1);
				}
				else if (angle < rotation - 130 && angle >= rotation - 180) {
					behav += 0.001*_time;
					if (behav > 1.0) {
						behav = 0;
						std::mt19937_64 re(time(0));
						std::uniform_int_distribution<int> one_to_for{ 1, 4 };
						behav1 = one_to_for(re);
					}
					switch (behav1) {
					case 1: if (speed < maxSpeed) speed += 0.0005;
						break;
					case 2: controll(1); if (speed < maxSpeed) speed += 0.0005;
						break;
					case 3: controll(2); if (speed < maxSpeed) speed += 0.0005;
						break;
					case 4: if (speed > minSpeed) speed -= 0.0005;
						break;
					}
				}
			}

		}
		else
			controll(2);
	}
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include "mission.h"
#include <iostream>
#include <sstream>
#include "level.h"
#include <vector>
#include <list>
#include "TinyXML/tinyxml.h"
#include "Units.h"
#include "pugixml.h"
#include <SFML/Audio.hpp>
#include "Button.h"
#include "Menu.h"


using namespace sf;
using namespace std;
using namespace lv;
class Main {
	sf::Thread* DrawThread1;
	sf::Thread* DrawThread2;
	sf::Thread* DrawThread3;
	sf::Thread* DrawThread4;
	sf::RenderWindow window;
	sf::Event eve;
	sf::Mutex mutex;
	sf::Music music;
	sf::SoundBuffer bs, rs;
	sf::Sound bullet_shot, rocket_shot;
	sf::Clock clock;
	sf::Clock gameTimeClock;
	lv::Level lvl;
	lv::Level parralax1;
	int gameTime = 0;
	float frame = 0;
	bool showMissionText = true; //виведення тексту на екран
	Image heroimage, enemy1image, Bulletimage, Rocketimage, Bombimage, quest_image;
	list<Entity*> bullets;
	list<Entity*>::iterator itbul;
	list<Entity*> entities;
	list<Entity*>::iterator it;
	vector<lv::Object> e = lvl.GetObjects("enemy1");
	lv::Object* player;
	lv::Object milbase = lvl.GetObject("base");

	Player* hero;
	//Military_base* MB;

	Texture quest_texture; //********Місія зображення****
	Sprite quest_sprite;
	Font font, font1; //*******Шрифт*****
	Text text, text1;

public:
	Main() {
		window.create(sf::VideoMode(1366, 768), "//Sapsan//", sf::Style::Close);
		StartMenu startMenu(window);
		startMenu.exec();

		player = new lv::Object(lvl.GetObject("player"));
		cout << "dasdas" << endl;


		bs.loadFromFile("sounds/gun13.wav");
		bullet_shot.setBuffer(bs);
		rs.loadFromFile("sounds/firework.wav");
		rocket_shot.setBuffer(rs);

		parralax1.LoadFromFile("training1.tmx");
		lvl.LoadFromFile("training.tmx");

		heroimage.loadFromFile("images/hero.png");
		enemy1image.loadFromFile("images/enemie1.png");
		Bulletimage.loadFromFile("images/bullet.png");
		Rocketimage.loadFromFile("images/rocket.png");
		Bombimage.loadFromFile("images/bomb.png");

		quest_image.loadFromFile("images/textmission.png");
		quest_texture.loadFromImage(quest_image);
		quest_sprite.setTexture(quest_texture);
		quest_sprite.setTextureRect(IntRect(0, 0, 200, 800));

		font.loadFromFile("images/GN.ttf");
		text.setCharacterSize(20); text.setFont(font1); text.setString(""); text.setColor(Color::Blue); text.setStyle(sf::Text::Bold);
		font1.loadFromFile("images/GN.ttf");
		text1.setCharacterSize(60); text1.setFont(font); text1.setString(""); text1.setColor(Color::Green);	text1.setStyle(sf::Text::Bold);

		for (int i = 0; i < e.size(); i++)
			entities.push_back(new Enemies1(enemy1image, "EasyEnemy", lvl, e[i].rect.left, e[i].rect.top, 26.0, 78.0));
		cout << player->rect.left << " " << player->rect.top << endl;
		hero = new Player(heroimage, "Player1", lvl, player->rect.left, player->rect.top, 90.0, 100.0, 1);
		//Player heroo(heroimage, "Player1", lvl, player.rect.left, player.rect.top, 90.0, 100.0, 1);
		//Military_base mil(enemy1image, "EasyEnemy", lvl, milbase.rect.left, milbase.rect.top, 26.0, 78.0, *hero);

		//*MB = mil;

		PlayMain();
	}

	void PlayMain()
	{

		while (window.isOpen())
		{

			float time = clock.getElapsedTime().asMicroseconds(); //дать прошедшее время в микросекундах
			if (hero->life){ gameTime = gameTimeClock.getElapsedTime().asSeconds(); }
			clock.restart(); //перезагружает время
			time = time / 1000; //скорость игры
			frame += 0.001*time;
			sf::Event eventt;
			parralax1.move(0.0, 0.1);

			//************Цикл натиснення клавіш**************
			while (window.pollEvent(eve))
			{

				if (eve.type == sf::Event::Closed)
					window.close();

				if (eve.type == sf::Event::Resized)
				{
					sf::FloatRect visibleArea(0, 0, eve.size.width, eve.size.height);
					window.setView(sf::View(visibleArea));
				}


				if (eve.type == sf::Event::KeyPressed)
					if (eve.key.code == Keyboard::M)
						music.play();
				if (hero->Shoot_rockets == true && (frame > 3)) {
					hero->Shoot_rockets = false;
					rocket_shot.play();
					bullets.push_back(new Bullet(Rocketimage, "Rocket", lvl, hero->x, hero->y, 6, 15, hero->rect.getPosition().x + hero->speedX, hero->rect.getPosition().y + hero->speedY, 2, 1));
					hero->Rockets_bullets--;
					frame = 0;
				}

				if (hero->Shoot_minigun == true) {
					bullet_shot.play();
					hero->Shoot_minigun = false;
					hero->Minigun_bullets--;
					bullets.push_back(new Bullet(Bulletimage, "Bullet", lvl, hero->x, hero->y, 4, 13, hero->rect.getPosition().x + hero->speedX, hero->rect.getPosition().y + hero->speedY, 2, 1));

				}

				if (hero->Shoot_bomb == true) {
					bullet_shot.play();
					hero->Shoot_bomb = false;
					hero->Bomb_bullets--;
					bullets.push_back(new Bullet(Bombimage, "Bomb", lvl, hero->x, hero->y, 10, 17, hero->rect.getPosition().x + hero->speedX, hero->rect.getPosition().y + hero->speedY, 2, 1, 0, hero->altitude));
				}



				if (eve.type == sf::Event::KeyPressed) //подыя натиснення клавіш
					if (eve.key.code == Keyboard::Tab){
						switch (showMissionText)
						{
						case true:{
							time = 0;
							std::ostringstream playerHealthSTR;
							playerHealthSTR << hero->health;
							std::ostringstream task;
							task << TextMission(getCurrentMission(hero->get_y()));
							text.setString("Health: " + playerHealthSTR.str() + "\n" + task.str());
							text.setPosition(hero->view.getCenter().x - 350, hero->view.getCenter().y - 350);
							quest_sprite.setPosition(hero->view.getCenter().x - 350, hero->view.getCenter().y - 350);
							showMissionText = false; // забирає виведене на екран
							break;
						}
						case false:{
							text.setString("");
							showMissionText = true;
						}
						}
					}
			}

			hero->update1(time, window); // Оживлюємо персонаж
			//MB->update(time);
			//if (MB->isDetectedR == true && hero->altitude < 400)
			//{
			//	bullets.push_back(new Bullet(Rocketimage, "Rocket", lvl, MB->x + MB->w / 2, MB->y + MB->h / 2, 6, 15, hero->x, hero->y, 2));
			//}
			//if (MB->isDetectedB == true && hero->altitude < 300)
			//{
			//	bullets.push_back(new Bullet(Bulletimage, "Bullet", lvl, MB->x + MB->w / 2, MB->y + MB->h / 2, 6, 15, hero->x, hero->y, 2));
			//}

			for (itbul = bullets.begin(); itbul != bullets.end();)
			{
				Entity *b = *itbul;
				b->update(time);
				if (b->life == false) { itbul = bullets.erase(itbul); delete b; }// якщо обэкт мертвий то видаляємо його
				else itbul++;
			}

			//Оживлюємо ворога
			for (it = entities.begin(); it != entities.end();)
			{
				Entity *b = *it;
				b->update(time);
				if (b->life == false) { it = entities.erase(it); delete b; }// якщо обэкт мертвий то видаляємо його
				else it++;
			}

			// Цикл для взаємодії куль з героєм й не підривання на власних
			for (itbul = bullets.begin(); itbul != bullets.end(); itbul++)
			{
				if ((*itbul)->getRect().intersects(hero->getRect()) && (*itbul)->hero_shoot != 1)
				{
					(*itbul)->health = 0;
					(*itbul)->life = false;
					hero->health -= (*itbul)->damage;

				}


			}
			for (itbul = bullets.begin(); itbul != bullets.end(); itbul++)
			{

				//if ((*itbul)->getRect().intersects(MB->getRect()) && (*itbul)->name == "Bomb" && (*itbul)->altitude <= 1 && (*itbul)->hero_shoot == 1)
				//{
				//	MB->health -= (*itbul)->damage;
				//}
			}
			//знищення ворога
			for (it = entities.begin(); it != entities.end(); it++)
			{
				if ((*it)->getRect().intersects(hero->getRect()))// якщо прямокутник спрайта обэкту перетинаэться з гравцем
				{
					if ((*it)->name == "EasyEnemy")
					{
						(*it)->health = 0;
						hero->health -= 50;
					}
				}
				for (itbul = bullets.begin(); itbul != bullets.end(); itbul++)
				{
					if ((*it)->getRect().intersects((*itbul)->getRect()))
					{
						(*it)->health -= (*itbul)->damage;
						(*itbul)->life = false;
					}



				}
			}





			window.setView(hero->view); // Оживлюємо камеру
			window.clear(sf::Color(200, 200, 200));
			window.draw(lvl);
			for (itbul = bullets.begin(); itbul != bullets.end(); itbul++)
				window.draw((*itbul)->sprite);
			for (it = entities.begin(); it != entities.end(); it++)
				window.draw((*it)->sprite);

			//window.draw(MB->sprite);
			window.draw(hero->sprite);
			//window.draw(hero->rect);

			std::ostringstream pSS, GTime, minigun, rockets, altitude;
			pSS << hero->health;
			GTime << gameTime;
			altitude << hero->altitude;	minigun << hero->Minigun_bullets; rockets << hero->Rockets_bullets;
			text.setString("HEALTH:" + pSS.str() + "\nTIME:" + GTime.str() + "\nMinigun: " + minigun.str() + "\nRockets " + rockets.str() + "\nAltitude: " + altitude.str() + " meters");
			text.setPosition(hero->view.getCenter().x - 540, hero->view.getCenter().y - 350);


			//************************Завершення ГРИ*********************
			if (hero->y < 51)
			{
				hero->speed = 0;
				text1.setString("YOU WON!!!");
				text1.setPosition(hero->view.getCenter().x - 150, hero->view.getCenter().y - 100);
				window.draw(text1);
			}

			if (!hero->life)
			{
				hero->speed = 0.0;
				frame += 0.004*time;
				hero->sprite.setTextureRect(IntRect(91 * int(frame), 300, 90, 100));
				text.setString("GAME OVER!!!");
				text.setPosition(hero->view.getCenter().x, hero->view.getCenter().y);
			}
			//************************Завершення ГРИ*********************


			window.draw(text);
			if (!showMissionText){
				text.setPosition(hero->view.getCenter().x - 540, hero->view.getCenter().y - 350);
				quest_sprite.setPosition(hero->view.getCenter().x - 540, hero->view.getCenter().y - 400);
				window.draw(quest_sprite);
				window.draw(text);
			}
			window.draw(parralax1);
			window.display();
		}
	}

	void DrawThread()
	{

	}
};*/