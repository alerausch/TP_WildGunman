#pragma once
#include "Personaje.h"
class Enemigo : public Personaje{
private:
	int velocDisparo;
public:
	Enemigo() {};
	Enemigo(sf::String text, int x, int y, float durac) :Personaje(text, x, y, durac) {};
};

