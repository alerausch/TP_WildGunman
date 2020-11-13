#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
class Personaje {
protected:
	bool visible;
	sf::Clock timer;
	sf::Time tiempoVida, tiempoAcum;
	int posX, posY;
	sf::Texture textura;
	sf::Sprite sprite;
public:
	Personaje(); 
	Personaje(sf::String text, int x, int y, float durac);
	sf::Sprite mostrar();
	void setearPosicion(int x, int y);
	void setearSprite(sf::String text);
	void setearTiempoVida(float durac);
	void setearVisible();
	bool actualizar();
};

