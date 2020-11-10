#include "Jugador.h"
Jugador::Jugador() {
	vidas = 3;
	puntos = 0;
}

int Jugador::cantVidas()
{
	return vidas;
}

int Jugador::restarVidas()
{
	if (vidas > 0) {
		vidas--;
	};
	return vidas;
}

sf::String Jugador::verPuntos()
{
	return std::to_string(puntos);
}
