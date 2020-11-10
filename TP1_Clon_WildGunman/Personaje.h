#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
class Personaje {
protected:
	bool visible;
	sf::Time tiempoVida;
	int posX, posY;
	sf::Texture textura;
	sf::Sprite sprite;
public:
	Personaje() {}; //constructor nulo
	Personaje(sf::String text, int x, int y, float durac);
	sf::Sprite mostrar();
	void setearPosicion(int x, int y);
	void setearSprite(sf::String text);
	void setearTiempoVida(float durac);
	void ocultar();
	bool actualizar(sf::Time &tiempo);
};

