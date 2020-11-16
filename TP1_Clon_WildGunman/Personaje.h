#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
class Personaje {
protected:
	bool visible, tipo; //tipo -> TRUE: enemigo, FALSE: inocente
	sf::Time tiempoVida, tiempoAcum;
	int posX, posY;
	sf::Texture textura;
	sf::Sprite sprite; 
	sf::Sound disparo;
	sf::SoundBuffer buffer;
public:
	Personaje(); 
	Personaje(sf::String text, int x, int y);
	sf::Sprite mostrar();
	bool verTipo();
	void setearTipo(bool t);
	void setearVisible(bool v);
	void setearPosicion(int x, int y);
	void setearSprite(sf::String text);
	void setearTiempoVida(float durac);
	bool actualizar(sf::Time t);
};

