#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "Personaje.h"
class Inocente : public Personaje {
private:
	int tiempoVisible;
public:
	Inocente() {};
	Inocente(sf::String text, int x, int y, float durac) :Personaje(text, x, y, durac) {};
};

