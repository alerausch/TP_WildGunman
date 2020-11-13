#include "Personaje.h"

Personaje::Personaje()
{
	tiempoAcum = sf::seconds(0);
}

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

void Personaje::setearVisible()
{
	visible = true;
}

bool Personaje::actualizar()
{
	tiempoAcum = tiempoAcum + timer.restart();
	if (tiempoAcum > tiempoVida) {
		visible = false;
		//tiempoAcum = sf::seconds(0);
		return false;
	}
	else {
		return true;
	}
}
