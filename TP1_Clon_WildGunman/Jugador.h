#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
class Jugador{
private:
	int vidas, puntos, abatidos;
public:
	Jugador();
	int cantVidas();
	void restarVidas();
	void setPuntos();
	void setAbatidos();
	sf::String verPuntos();
};

