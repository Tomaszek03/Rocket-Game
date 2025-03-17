#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <string>
#include <sstream>
#include <fstream>
#include <iostream>
#include <windows.h>
#include <time.h>
#include "headers.h"

using namespace std;
using namespace sf;

//To show X and Y positions in map, uncomment parts in line 77, 144 and 257

int main()
{
	RenderWindow window{ VideoMode(W,H), "Rocket Game" };
	window.setFramerateLimit(60);

	if (!level.openFromFile("music/level.wav")) return -1;
	if (!level2.openFromFile("music/level2.wav")) return -1;
	if (!main_menu.openFromFile("music/menu.wav")) return -1;
	if (!coin_get_buffer.loadFromFile("music/coin.wav")) return -1;
	if (!engine_buffer.loadFromFile("music/silnik.wav")) return -1;
	
	t1.loadFromFile("images/background.png");
	t2.loadFromFile("images/rocket.png");
	t6.loadFromFile("images/menu.png");
	t7.loadFromFile("images/coin.png");
	t8.loadFromFile("images/background2.png");

	Sound coin_get;
	coin_get.setBuffer(coin_get_buffer);
	Sound engine;
	engine.setBuffer(engine_buffer);
	engine.setLoop(true);
	bool sound = false;

	Font font, coords;
	Text text, text2, text3, text4;
	font.loadFromFile("fonts/joystix monospace.otf");
	coords.loadFromFile("fonts/Arial.TTF");
	text.setFont(font);
	text.setString("DYSTANS:");
	text.setCharacterSize(50);
	text.setFillColor(Color::White);
	text.setStyle(Text::Bold);

	text2.setFont(font);
	text2.setCharacterSize(50);
	text2.setFillColor(Color::White);
	text2.setStyle(Text::Bold);
	text2.setPosition(335, 0);

	text3.setFont(font);
	text3.setCharacterSize(50);
	text3.setFillColor(Color::White);
	text3.setStyle(Text::Bold);
	text3.setPosition(1180, 0);
	text3.setString("0");

	text4.setFont(font);
	text4.setCharacterSize(60);
	text4.setFillColor(Color::White);
	text4.setStyle(Text::Bold);
	text4.setPosition(500,300);

	Sprite background(t6), item(t2), coin(t7);
	item.setTexture(t2);
	item.setOrigin(306.f, 306.f);
	item.setPosition(Vector2f(X, Y));
	coin.setTexture(t7);
	coin.setPosition(675, -265);

	//Show X and Y positions
	/*Text XX, YY;
	XX.setFont(coords);
	XX.setString(to_string(X));
	XX.setCharacterSize(30);
	XX.setFillColor(Color::White);
	XX.setStyle(Text::Bold);
	XX.setPosition(0, 70);
	YY.setFont(coords);
	YY.setString(to_string(Y));
	YY.setCharacterSize(30);
	YY.setFillColor(Color::White);
	YY.setStyle(Text::Bold);
	YY.setPosition(85, 70);*/
	
	main_menu.play();
	main_menu.setLoop(true);

	while (window.isOpen())
	{
		window.clear(Color::Black);
		Event event;
		while (window.pollEvent(event))
		{
			if ((event.type == Event::Closed) || (event.key.code == Keyboard::Escape))
			{
				window.close();
				break;
			}
			
			window.draw(background);
			window.display();
			if ((event.key.code == Keyboard::Num1) || (event.key.code == Keyboard::Num2))
			{
				if (Keyboard::isKeyPressed(Keyboard::Num2)) get_progress();

				main_menu.stop();
				if (a < 30000)
				{
					level.play();
					level.setLoop(true);
				}
				

				while (true)
				{
					
					if (a < 30000) background.setTexture(t1);
					if (a >= 30000)
					{
						background.setTexture(t8);
						level.stop();
						if (level2.getStatus() != level2.Playing)
						{
							level2.play();
							level2.setLoop(true);
						}
					}

					window.draw(background);
					window.draw(item);
					window.draw(coin);
					window.draw(text);
					window.draw(text2);
					window.draw(text3);
					window.draw(text4);

					//Show X and Y positions
					/*window.draw(XX);
					window.draw(YY);*/

					window.display();
					text2.setString(to_string(a));
					text3.setString(to_string(c));


					check_pos(item, a);

					int speed = 2;
					
					if(wait == false)
					{
						
						if (Keyboard::isKeyPressed(Keyboard::Space))
						{
							speed *= 3;
						}

						if ((Keyboard::isKeyPressed(Keyboard::Left)) || (Keyboard::isKeyPressed(Keyboard::A)))
						{
							item.setRotation(270.f);
							item.setPosition(X - speed, Y);
							X = X - speed;
						}
						if ((Keyboard::isKeyPressed(Keyboard::Right)) || (Keyboard::isKeyPressed(Keyboard::D)))
						{
							item.setRotation(90.f);
							item.setPosition(X + speed, Y);
							X = X + speed;
						}
						if ((Keyboard::isKeyPressed(Keyboard::Down)) || (Keyboard::isKeyPressed(Keyboard::S)))
						{
							item.setRotation(180.f);
							item.setPosition(X, Y + speed);
							Y = Y + speed;
						}
						if ((Keyboard::isKeyPressed(Keyboard::Up)) || (Keyboard::isKeyPressed(Keyboard::W)))
						{
							item.setRotation(0.f);
							item.setPosition(X, Y - speed);
							Y = Y - speed;
						}

						if (((Keyboard::isKeyPressed(Keyboard::Left)) && (Keyboard::isKeyPressed(Keyboard::Up))) || ((Keyboard::isKeyPressed(Keyboard::A)) && (Keyboard::isKeyPressed(Keyboard::W))))
						{
							item.setRotation(315.f);
						}
						if (((Keyboard::isKeyPressed(Keyboard::Left)) && (Keyboard::isKeyPressed(Keyboard::Down))) || ((Keyboard::isKeyPressed(Keyboard::A)) && (Keyboard::isKeyPressed(Keyboard::S))))
						{
							item.setRotation(225.f);
						}
						if (((Keyboard::isKeyPressed(Keyboard::Right)) && (Keyboard::isKeyPressed(Keyboard::Up))) || ((Keyboard::isKeyPressed(Keyboard::D)) && (Keyboard::isKeyPressed(Keyboard::W))))
						{
							item.setRotation(45.f);
						}
						if (((Keyboard::isKeyPressed(Keyboard::Right)) && (Keyboard::isKeyPressed(Keyboard::Down))) || ((Keyboard::isKeyPressed(Keyboard::D)) && (Keyboard::isKeyPressed(Keyboard::S))))
						{
							item.setRotation(135.f);
						}

						if ((Keyboard::isKeyPressed(Keyboard::Up)) || (Keyboard::isKeyPressed(Keyboard::W)) || (Keyboard::isKeyPressed(Keyboard::Down)) || (Keyboard::isKeyPressed(Keyboard::S)) || (Keyboard::isKeyPressed(Keyboard::Right)) || (Keyboard::isKeyPressed(Keyboard::D)) || (Keyboard::isKeyPressed(Keyboard::Left)) || (Keyboard::isKeyPressed(Keyboard::A)))
						{
							if (check_pos(item, a))
							{
								text2.setString(to_string(a + speed));
								a = a + speed;
							};
							if (sound == false)
							{
								engine.play();
								sound = true;
							}
						}
						else
						{
							sound = false;
							engine.pause();
						}
					}
					if (a >= b)
					{
						b = b + 3000;
						c++;
						coin_get.play();
						text3.setString(to_string(c));
					}

					save(a, c, b);
					Event ev;
					while (window.pollEvent(ev))
					{
						if ((ev.type == Event::Closed) || (ev.key.code == Keyboard::Escape))
						{
							window.close();
							exit(0);
						}
						if ((ev.key.code == Keyboard::P)&&(wait==false))
						{
							wait = true;
							text4.setString("PAUZA");
							level.pause();
						}
						if ((ev.key.code == Keyboard::Space)&&(wait==true))
						{
							wait = false;
							text4.setString("");
							level.play();
						}
					}
					
					//Show X and Y positions
					//XX.setString(to_string(X));
					//YY.setString(to_string(Y));

				}
			}
			else if (event.key.code == Keyboard::Num3)
			{
				window.close();
			}
		}
	}
	return 0;
}


bool check_pos(Sprite obj, int s)
{
	if (X < 76)
	{
		X = 76;
		return false;
	}
	if (X > 1205)
	{
		X = 1205;
		return false;
	}
	if (Y < 76)
	{
		Y = 76;
		return false;
	}
	if (Y > 645)
	{
		Y = 645;
		return false;
	}
	obj.setPosition(X, Y);
	return true;
}

void save(int score, int coins, int next_coin)
{
	fstream data;
	data.open("progress.txt", ios::out);
	data << score << endl;
	data << coins << endl;
	data << next_coin << endl;
	data.close();
}

void get_progress()
{
	fstream data;
	data.open("progress.txt", ios::in);

	if (data.good() == false)
	{
		cout << "Cannot found progress file!";
	}
	string line;
	int nr = 1;
	while (getline(data, line))
	{
		switch (nr)
		{
		case 1:
			a = atoi(line.c_str());
			break;
		case 2:
			c = atoi(line.c_str());
			break;
		case 3:
			b = atoi(line.c_str());
			break;
	}
		nr++;
	}
	data.close();

}