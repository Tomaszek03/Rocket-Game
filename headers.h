#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

using namespace sf;

//Zmienne
int W = 1280;
int H = 720;
int X = 640;
int Y = 360;
int b = 3000;
int a = 0;
int c = 0;
bool wait = false;


//SFML
Texture t1, t2, t3, t4, t5, t6, t7, t8;
Music level, level2, main_menu;
SoundBuffer coin_get_buffer;
SoundBuffer engine_buffer;


//Funkcje
bool check_pos(Sprite obj, int s);
void save(int score, int coins, int next_coin);
void get_progress();
int speed_up(int s);
void rocket_sound(bool s);