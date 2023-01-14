#pragma once 
#include <ctime> 
#include <string> 
#include <SFML/Graphics.hpp> 

const float WINDOW_X = 800.f;
const float WINDOW_Y = 600.f;
const std::string WINDOW_NAME = "Ping-pong";
const std::string Play = "Play";
const std::string Exit = "Exit";
const std::string BestScoreString = "Best Score: ";
const float TextSize = 128;
const float TextSize2 = 64;
const float TextSize3 = 32;

const float BAT_HEIGHT = 20.f; 
const float BAT_WIDHT = 120.f;
const float BAT_OFFSET = 50.f;
float radius = 15.f;

const float FPS = 100;
float d1 = 3.f;
float d2 = 3.f;

bool pointInRect(sf::RectangleShape bat, sf::Vector2f point) {
	float batX = bat.getPosition().x;
	float batY = bat.getPosition().y;
	return (point.x >= batX && point.x <= batX + BAT_WIDHT)
		&& (point.y >= batY && point.y <= batY + BAT_HEIGHT);
}