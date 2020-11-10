#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "Enemigo.h"
#include "Inocente.h"
#include "Jugador.h"
class WildGunman {
private:
	sf::RenderWindow ventanajuego;
	sf::Vector2i posicionMouse;
	sf::Clock reloj;
	sf::Time tiempo;
	sf::Texture texFondo, texMouse, textVidas;
	sf::Sprite sprFondo, sprMouse, sprVidas;
	sf::Font fuente;
	sf::Text texto, textoTiempo, textoPunt;
	sf::String pausa, posX, posY, cadena, impactado;
	bool enjuego;
	int vidasX, vidasY, contadorPersonajes;
	int arrayPosiciones[6][2] = { {107,223}, {254,223}, {401,223}, {107,412}, {401,412}, {252,415} };
	bool arrayPosOcupadas[6] = { false, false, false, false, false,false };
	//array que contiene al area que ocupan los personajes {{xInic, yInic, xFin, yFin} 
	int areaPersonajes[6][4] = { {127,243,202,353}, {264,243,349,353}, {421,243,496,353},
									{127,432,202,540}, {421,432,496,540}, {272,435,347,545} };
	sf::String arrayTexturas[4] = { "archivos/enemigo1.png", "archivos/enemigo2.png", 
									"archivos/enemigo3.png", "archivos/inocente1.png"};
	float arrayTiempos[3] = { 2, 3, 4 };
	Jugador Jugador1;
	Enemigo arrayEnemigos[6];
	Inocente inocente1;
public:
	WildGunman();
	void ActualizarElementos(sf::Time t);
	void AdministrarPersonajes(sf::Time t);
	void PausarJuego();
	bool CapturarClic(int xCapt, int yCapt, int &posicion);
	sf::Text MostrarMensaje(sf::String msj);
	void Jugar();
};

