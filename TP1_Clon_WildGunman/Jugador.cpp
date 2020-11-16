#include "Jugador.h"
Jugador::Jugador() {
	vidas = 3;
	puntos = 0;
	abatidos = 0;
}

int Jugador::cantVidas()
{
	return vidas;
}

void Jugador::restarVidas()
{
	if (vidas > 0) {
		vidas--;
	}
}

void Jugador::setPuntos()
{
	puntos =  (abatidos - (3-vidas)) * 10;
}

void Jugador::setAbatidos()
{
	abatidos++;
}

sf::String Jugador::verPuntos()
{
	return std::to_string(puntos);
}
