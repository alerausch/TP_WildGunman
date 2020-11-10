#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
class Jugador{
private:
	int vidas, puntos;
public:
	Jugador();
	int cantVidas();
	int restarVidas();
	sf::String verPuntos();
};

