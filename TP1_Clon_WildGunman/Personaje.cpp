#include "Personaje.h"

Personaje::Personaje(sf::String text, int x, int y, float durac)
{
	textura.loadFromFile(text);
	sprite.setTexture(textura);
	posX = x;
	posY = y;
	tiempoVida = sf::seconds(durac);
	visible = false;
}

sf::Sprite Personaje::mostrar()
{
	sprite.setPosition(posX, posY);
	visible = true;
	return sprite;
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
}

void Personaje::ocultar()
{
	if (visible) {
		visible = false;
	}
}

bool Personaje::actualizar(sf::Time &tiempo)
{
	if (tiempo > tiempoVida) {
		visible = false;
		return false;
	}
	else {
		return true;
	}
}
