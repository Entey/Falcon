#include <sstream>
#include <list>
//#include "mission.h"
#include "../code/Menu/Button.h"
#include "../code/Menu/Menu.h"
#include "../code/Hero/Hero.h"
#include "../code/Enemies/Military_base.h"
#include "../code/Enemies/Hard_enemy1.h"
#include "../code/Enemies/Aerostate.h"
#include "../code/Bullets/Bullets.h"
#include "../code/Enemies/Dirigible.h"
#include "../code/Enemies/Enemy_bomber.h"





int main()
{

	RenderWindow window(sf::VideoMode(1366, 768), "//Sapsan//", sf::Style::Close); //Розмір вікна
	StartMenu startMenu(window);
	startMenu.exec();

//****************music******************************************
	Music music;
	music.openFromFile("sounds/level2.ogg");

	sf::SoundBuffer bs;
	bs.loadFromFile("sounds/gun_9.wav");
	sf::Sound bullet_shot;
	bullet_shot.setBuffer(bs);

	sf::SoundBuffer rs;
	rs.loadFromFile("sounds/firework.wav");
	sf::Sound rocket_shot;
	rocket_shot.setBuffer(rs);

	sf::SoundBuffer boms;
	boms.loadFromFile("sounds/bomb_1.wav");
	sf::Sound bomb_shot;
	bomb_shot.setBuffer(boms);

	sf::SoundBuffer explosion_p;
	explosion_p.loadFromFile("sounds/explosion.wav");
	sf::Sound explosion_plane;
	explosion_plane.setBuffer(explosion_p);

	sf::SoundBuffer engine_p1;
	engine_p1.loadFromFile("sounds/engine_1.wav");
	sf::Sound engine_destroer;
	engine_destroer.setBuffer(engine_p1);

	sf::SoundBuffer engine_p2;
	engine_p2.loadFromFile("sounds/engine_2.wav");
	sf::Sound engine_bomber;
	engine_bomber.setBuffer(engine_p2);

	sf::SoundBuffer engine_p3;
	engine_p3.loadFromFile("sounds/engine_3.wav");
	sf::Sound engine_assault;
	engine_assault.setBuffer(engine_p3);

//****************music******************************************

	Clock clock; 
	Clock gameTimeClock; // час проведеий в грі

	lv::Level lvl;
	lv::Level parralax1;
	parralax1.LoadFromFile("training11.tmx");
	lvl.LoadFromFile("training.tmx");



	int gameTime = { 0 };
	float frame = { 0.0 }, parralaxMove { 0.0 };
	float explosion_timer = {0.0};

	bool showMissionText = true; //виведення тексту на екран
	Image heroimage1; heroimage1.loadFromFile("images/Destroerr.png");
	Image heroimage2; heroimage2.loadFromFile("images/Bomber.png"); 
	Image heroimage3; heroimage3.loadFromFile("images/Assault_plane.png");
	Image Bulletimage; Bulletimage.loadFromFile("images/bullet.png");
	Image Rocketimage; Rocketimage.loadFromFile("images/rocket1.png");
 	Image Bombimage; Bombimage.loadFromFile("images/bomb.png");
	Image minG; minG.loadFromFile("images/minG.png");
	Image enemy1image; enemy1image.loadFromFile("images/enemy1.png");
	Image hurd_enemy1image; hurd_enemy1image.loadFromFile("images/hard_enemy1.png");
	Image hurd_enemy2image; hurd_enemy2image.loadFromFile("images/hard_enemy.png");
	Image enemy3image; enemy3image.loadFromFile("images/enemy3.png");
	Image enemy_bomber; enemy_bomber.loadFromFile("images/Enemy_bomber.png");


	lv::Object player = lvl.GetObject("player");
	
	/*Об'єкт гравця*/	Player hero(heroimage1, "destroyer", lvl, player.rect.left, player.rect.top, 120.0, 180.0, explosion_plane, engine_destroer, minG);
						//Player hero(heroimage2, "bomber", lvl, player.rect.left, player.rect.top, 300.0, 258.0, explosion_plane, engine_bomber, minG);
						//Player hero(heroimage3, "assault_plane", lvl, player.rect.left, player.rect.top, 200.0, 200.0, explosion_plane, engine_assault, minG);
	list<Entity*> bullets;
	list<Entity*>::iterator itbul;
//*************Список обєктів ворогів****************************
	list<Entity*> easy_enemys;
	list<Entity*>::iterator ee_it;
	vector<lv::Object> e = lvl.GetObjects("Dirigable");
	for (int i = 0; i < e.size(); i++)
		easy_enemys.push_back(new Dirigible(enemy1image, "EasyEnemy", lvl, e[i].rect.left, e[i].rect.top, 50.0, 159.0, hero, engine_bomber, explosion_plane));
	vector<lv::Object> e1 = lvl.GetObjects("Aerostat");
	for (int i = 0; i < e1.size(); i++)
		easy_enemys.push_back(new Aerostat(enemy3image, "Aerostat", lvl, e1[i].rect.left, e1[i].rect.top, 100.0, 100.0));

	list<HardEnemy*> Hard_enemy;
	list<HardEnemy*>::iterator ithard, ithard1;
	vector<lv::Object> hard_e1 = lvl.GetObjects("HardEnemy");
	vector<lv::Object> hard_e2 = lvl.GetObjects("HardEnemy1");
	vector<lv::Object> hard_e3 = lvl.GetObjects("Bomber");
	vector<lv::Object> target_e3 = lvl.GetObjects("Bomber_target");
	for (int i = 0; i < hard_e1.size(); i++)
		Hard_enemy.push_back(new HardEnemy(hurd_enemy1image, "Hard1", lvl, hard_e1[i].rect.left, hard_e1[i].rect.top, 118.0, 185.0, hero, engine_bomber, explosion_plane));
	for (int i = 0; i < hard_e2.size(); i++)
		Hard_enemy.push_back(new HardEnemy(hurd_enemy2image, "Hard2", lvl, hard_e2[i].rect.left, hard_e2[i].rect.top, 118.0, 185.0, hero, engine_bomber, explosion_plane));
	
	//for (int i = 0; i < hard_e3.size(); i++)
		//Enemy_bomber EB(enemy_bomber, "enemy_bomber", lvl, hard_e3[i].rect.left, hard_e3[i].rect.top, 300.0, 210.0, target_e3[i].rect.left, target_e3[i].rect.top, hero, engine_bomber, explosion_plane, minG);
	
	lv::Object zz = lvl.GetObject("Bomber");
	lv::Object zzz = lvl.GetObject("Bomber_target");

	Enemy_bomber EB(enemy_bomber, "enemy_bomber", lvl, zz.rect.left, zz.rect.top, 300.0, 210.0, zzz.rect.left, zzz.rect.top, hero, engine_bomber, explosion_plane, minG);

//********Місія зображення****
	Image quest_image;
	quest_image.loadFromFile("images/textmission.png");
	Texture quest_texture;
	quest_texture.loadFromImage(quest_image);
	Sprite quest_sprite;
	quest_sprite.setTexture(quest_texture);
	quest_sprite.setTextureRect(IntRect(0,0,200,800));
//*******Кінець місія*****

//*******Шрифт початок*****
	Font font;
	font.loadFromFile("images/GN.ttf");
	Text text("", font, 20);
	text.setColor(Color::Blue);
	text.setStyle(sf::Text::Bold );

	Font font1;
	font1.loadFromFile("images/GN.ttf");
	Text text1("", font, 60);
	text1.setColor(Color::Green);
	text1.setStyle(sf::Text::Bold );
//*******Шрифт кінець*****

	
	lv::Object milbase = lvl.GetObject("base");
						Military_base MB(enemy1image, "EasyEnemy", lvl, milbase.rect.left, milbase.rect.top, 50.0, 159.0,hero);
						
						//music.play();

						sf::Event eventt;
// Нескінченний цикл поки вікно відчинене
	while(window.isOpen())
	{
		
		float time = clock.getElapsedTime().asMicroseconds(); //дать прошедшее время в микросекундах
		if (hero.life){ gameTime = gameTimeClock.getElapsedTime().asSeconds(); }
		clock.restart(); //перезагружает время	
		time = time/1000; //скорость игры
		frame += 0.001*time;
		
		// перевірка на рух хмар
		parralaxMove += 0.0001*time;
			
			if (parralaxMove <= 10) {
				parralax1.move(0.1, 0.0);
			}
			else if (parralaxMove > 10 && parralaxMove < 20){
				parralax1.move(0.0, 0.1);
			}
			else
				parralaxMove = 0;

	//************Цикл натиснення клавіш**************
		while(window.pollEvent(eventt))
		{
			
			if(eventt.type == sf::Event::Closed)
				window.close();

			if (eventt.type == sf::Event::Resized) {
				sf::FloatRect visibleArea(0, 0, eventt.size.width, eventt.size.height);
				window.setView(sf::View(visibleArea));
			}

			if (eventt.type == sf::Event::KeyPressed)
				if (eventt.key.code == Keyboard::M)
					music.play();

			if (hero.Shoot_rockets == true && (hero.name == "destroyer" || hero.name == "assault_plane")) {
				hero.Shoot_rockets = false;
				bullets.push_back(new Bullet(Rocketimage, "Rocket", lvl, (hero.x), (hero.y), 10, 80, hero.rect.getPosition().x + hero.speedX, hero.rect.getPosition().y + hero.speedY, rocket_shot, bomb_shot, 1, 0, hero.altitude));
				hero.Rockets_bullets--;
			}
			
			if (hero.Shoot_minigun == true) {
				hero.Minigun_bullets--;
				if (hero.name == "destroyer" || hero.name == "assault_plane")
					bullets.push_back(new Bullet(Bulletimage, "Bullet", lvl, hero.x, hero.y, 4, 13, hero.rect.getPosition().x + hero.speedX, hero.rect.getPosition().y + hero.speedY, bullet_shot, bomb_shot, 1, 0, hero.altitude));
				if (hero.name == "bomber"){
					bullets.push_back(new Bullet(Bulletimage, "Bullet", lvl, hero.SminG1.getPosition().x, hero.SminG1.getPosition().y, 5, 17, hero.pos.x, hero.pos.y, bullet_shot, bomb_shot, 2, 0, hero.altitude));
					bullets.push_back(new Bullet(Bulletimage, "Bullet", lvl, hero.SminG2.getPosition().x, hero.SminG2.getPosition().y, 5, 17, hero.pos.x, hero.pos.y, bullet_shot, bomb_shot, 2, 0, hero.altitude));
					bullets.push_back(new Bullet(Bulletimage, "Bullet", lvl, hero.SminG3.getPosition().x, hero.SminG3.getPosition().y, 5, 17, hero.pos.x, hero.pos.y, bullet_shot, bomb_shot, 2, 0, hero.altitude));
				}
				hero.Shoot_minigun = false;
			}

			if (hero.Shoot_bomb == true) {
				hero.Shoot_bomb = false;
				hero.Bomb_bullets--;
				bullets.push_back(new Bullet(Bombimage, "Bomb", lvl, hero.x, hero.y, 15, 30, hero.rect.getPosition().x + hero.speedX, hero.rect.getPosition().y + hero.speedY, bomb_shot, bomb_shot, 1, 0, hero.altitude));
			}

			if(eventt.type == sf::Event::KeyPressed)
				if(eventt.key.code == Keyboard::Tab){
					switch(showMissionText)
					{
					case true:{
						time = 0;
						std::ostringstream playerHealthSTR;
						playerHealthSTR << hero.health;
						std::ostringstream task;
						
						text.setString("Health: "+playerHealthSTR.str()+"\n"+task.str());
						text.setPosition(hero.view.getCenter().x-350,hero.view.getCenter().y-350);
						quest_sprite.setPosition(hero.view.getCenter().x-350,hero.view.getCenter().y-350);
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

		hero.update1(time,window); // Оживлюємо персонаж
		

		MB.update(time);
		EB.update(time);
		if (MB.isDetectedR == true && hero.altitude < 400)
			bullets.push_back(new Bullet(Rocketimage, "Rocket", lvl, MB.x + MB.w / 2, MB.y + MB.h / 2, 10, 80, hero.x, hero.y, rocket_shot, bomb_shot, 0, 0, MB.altitude));
		if (MB.isDetectedB == true && hero.altitude < 300)
			bullets.push_back(new Bullet(Bulletimage, "Bullet", lvl, MB.x + MB.w / 2, MB.y + MB.h / 2, 6, 15, hero.x, hero.y, bullet_shot, bomb_shot, 0, 0, MB.altitude));


		for (itbul = bullets.begin(); itbul != bullets.end();) {
			Entity *b = *itbul;
			b->update(time);
			if (b->life == false && b->isMove == true) {
				itbul = bullets.erase(itbul);
				delete b;
			}
			else itbul++;
		}
		
//update тяжких ворогів 
		for (ithard = Hard_enemy.begin(); ithard != Hard_enemy.end();)
		{
			HardEnemy *b = *ithard;
			b->update(time);
			if (b->life == false && b->isMove == true) { ithard = Hard_enemy.erase(ithard); delete b; }// якщо об'єкт мертвий то видаляємо його
			else ithard++;
		}

		for (ithard = Hard_enemy.begin(); ithard != Hard_enemy.end(); ithard++) {
			if ((*ithard)->fire == true)
			{
				bullets.push_back(new Bullet(Bulletimage, "Bullet", lvl, (*ithard)->x, (*ithard)->y, 6, 15, (*ithard)->get_convex().getPosition().x + (*ithard)->get_speedX(), (*ithard)->get_convex().getPosition().y + (*ithard)->get_speedY(), bullet_shot, bomb_shot, 0, 0, (*ithard)->altitude));
				(*ithard)->fire = false;
			}
		}

		
//update легкого ворога 
		for (ee_it = easy_enemys.begin(); ee_it != easy_enemys.end();){
			Entity *b = *ee_it;
			b->update(time);
			if (b->life == false && b->isMove == true) {  ee_it = easy_enemys.erase(ee_it); delete b; } // якщо об'єкт мертвий то видаляємо його
			else ee_it++;
		}
		for (ee_it = easy_enemys.begin(); ee_it != easy_enemys.end(); ++ee_it){
			if ((*ee_it)->fire == true)
				bullets.push_back(new Bullet(Rocketimage, "Rocket", lvl, (*ee_it)->x, (*ee_it)->y, 10, 80, hero.get_x(), hero.get_y(), rocket_shot, bomb_shot, 0, 0, (*ee_it)->altitude));
		}

	// Цикл для взаємодії куль з героєм й не підривання на власних
		for (itbul = bullets.begin(); itbul != bullets.end(); itbul++)
		{
			if (((*itbul)->getRect().intersects(hero.body1.getGlobalBounds()) || (*itbul)->getRect().intersects(hero.body2.getGlobalBounds())) && (*itbul)->hero_shoot != 1 && (*itbul)->hero_shoot != 2)
			{
				(*itbul)->health = 0;
				(*itbul)->life = false;
				hero.health -= (*itbul)->damage;
			}			
		}

	// Цикл взаэмодії бомб з наземними цілями
		for (itbul = bullets.begin(); itbul != bullets.end(); itbul++) {
			if ((*itbul)->getRect().intersects(MB.getRect()) && (*itbul)->name == "Bomb" && (*itbul)->altitude <= 10 && (*itbul)->hero_shoot == 1 && (*itbul)->hero_shoot == 2)
				MB.health -= (*itbul)->damage;
		}

	// Цикл знищення легких ворогів
		for (ee_it = easy_enemys.begin(); ee_it != easy_enemys.end(); ee_it++)
		{
			if (((*ee_it)->getRect().intersects(hero.body1.getGlobalBounds()) && (*ee_it)->altitude == hero.altitude) ||
				((*ee_it)->getRect().intersects(hero.body2.getGlobalBounds()) && (*ee_it)->altitude == hero.altitude))// якщо прямокутник спрайта обєкту перетинаэться з гравцем
			{
				if ((*ee_it)->name == "EasyEnemy")
				{
					(*ee_it)->health = 0;
					hero.health -= 50;
				}
			}
			for (itbul = bullets.begin(); itbul != bullets.end(); itbul++)
			{
				if ((*ee_it)->getRect().intersects((*itbul)->getRect()) && (((*itbul)->hero_shoot == 1) || ((*itbul)->hero_shoot == 2)))
				{
					(*ee_it)->health -= (*itbul)->damage;
					(*itbul)->life = false;
				}
			}
		}
	// Цикл знищення тяжкого ворога
		for (ithard = Hard_enemy.begin(); ithard != Hard_enemy.end(); ithard++) {
			if ((((*ithard)->get_body1().getGlobalBounds().intersects(hero.body1.getGlobalBounds()) || ((*ithard)->get_body1().getGlobalBounds().intersects(hero.body1.getGlobalBounds()))) && (*ithard)->altitude == hero.altitude) ||
				(((*ithard)->get_body2().getGlobalBounds().intersects(hero.body2.getGlobalBounds()) || (*ithard)->get_body2().getGlobalBounds().intersects(hero.body2.getGlobalBounds())) && (*ithard)->altitude == hero.altitude))
				{
					//(*ithard)->health -= 70;
					//hero.health -= 70;
					//(*ithard)->sprite.setTextureRect(IntRect(0, 0, 100, 100));
				}
			
				//(*ithard)->sprite.setTextureRect(IntRect(0, 0, 118.0, 185.0));

			for (itbul = bullets.begin(); itbul != bullets.end(); itbul++)
			{
				if (((*ithard)->get_body1().getGlobalBounds().intersects((*itbul)->getRect()) ||
					(*ithard)->get_body2().getGlobalBounds().intersects((*itbul)->getRect())) && (((*itbul)->hero_shoot == 1) || ((*itbul)->hero_shoot == 2)))
				{
					(*ithard)->health -= (*itbul)->damage;
					(*itbul)->life = false;
				}
			}
			for (ithard1 = Hard_enemy.begin(); ithard1 != Hard_enemy.end(); ithard1++){
				if ((*ithard)->getRect() != (*ithard1)->getRect())
				if ((*ithard)->getRect().intersects((*ithard1)->getRect()))
					(*ithard1)->controll(1);
			}
		}
		

			
		window.setView(hero.view); // Оживлюємо камеру
		window.clear(sf::Color(200,200,200));
		window.draw(lvl);
		
		for (itbul = bullets.begin(); itbul != bullets.end(); itbul++)
			window.draw((*itbul)->sprite);
		for (ee_it = easy_enemys.begin(); ee_it != easy_enemys.end(); ee_it++)
			window.draw((*ee_it)->sprite);
		
		window.draw(MB.sprite);
		window.draw(EB.sprite);
		window.draw(EB.SminG1);
		window.draw(EB.SminG2);
		window.draw(EB.convex);
		for (ithard = Hard_enemy.begin(); ithard != Hard_enemy.end(); ithard++)
			window.draw((*ithard)->sprite);

		
		window.draw(hero.SminG1);
		window.draw(hero.SminG2);
		window.draw(hero.SminG3);
		window.draw(hero.sprite);

		

		//window.draw(hero.body1);
		//window.draw(hero.body2);
		std::ostringstream pSS, GTime, minigun, rockets, altitude;
		pSS << hero.health;
		GTime << gameTime;
		altitude << hero.altitude;	minigun << hero.Minigun_bullets; rockets << hero.Rockets_bullets;
		text.setString("HEALTH:"+pSS.str() +"\nTIME:"+ GTime.str() + "\nMinigun: " + minigun.str() + "\nRockets " + rockets.str() + "\nAltitude: " + altitude.str() + " meters");
		text.setPosition(hero.view.getCenter().x-540,hero.view.getCenter().y-350);

		
//************************Завершення ГРИ*********************	
		if(hero.y < 0)
			{ 
				hero.speed = 0;
				text1.setString("YOU WON!!!");
				text1.setPosition(hero.view.getCenter().x-150,hero.view.getCenter().y-100);
				window.draw(text1);
			}

		if(!hero.life)
		{
			frame += 0.004*time;
			text.setString("GAME OVER!!!");
			text.setPosition(hero.view.getCenter().x, hero.view.getCenter().y);
		}
//************************Завершення ГРИ*********************


		window.draw(text);
		if(!showMissionText){
			text.setPosition(hero.view.getCenter().x-540,hero.view.getCenter().y-350);
			quest_sprite.setPosition(hero.view.getCenter().x-540,hero.view.getCenter().y-400);
			window.draw(quest_sprite);
			window.draw(text);
		}		
		window.draw(parralax1);
		
		window.display();
	}
	
	return 0;
}



