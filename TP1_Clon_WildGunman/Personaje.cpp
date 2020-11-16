#include "Personaje.h"

Personaje::Personaje()
{
	tiempoAcum = sf::seconds(0);
	visible = false;
}

Personaje::Personaje(sf::String text, int x, int y)
{
	textura.loadFromFile(text);
	sprite.setTexture(textura);
	posX = x;
	posY = y;
	visible = false;
}

sf::Sprite Personaje::mostrar()
{
	sprite.setPosition(posX, posY);
	return sprite;
}

bool Personaje::verTipo()
{
	if (tipo) {
		return true;
	}
	else {
		return false;
	}
}

void Personaje::setearTipo(bool t)
{
	tipo = t;
}

void Personaje::setearVisible(bool v)
{
	visible = v;
}

void Personaje::setearPosicion(int x, int y)
{
	posX = x;
	posY = y;
}

void Personaje::setearSprite(sf::String text)
{
	textura.loadFromFile(text);
	sprite.setTexture(textura);
}

void Personaje::setearTiempoVida(float durac)
{
	tiempoVida = sf::seconds(durac);
	tiempoAcum = sf::seconds(0);
}

bool Personaje::actualizar(sf::Time t)
{
	tiempoAcum = tiempoAcum + t;

	if (tiempoAcum > tiempoVida) {
		visible = false;
		return false;
	}
	else {
		visible = true;
		return true;
	}
}
