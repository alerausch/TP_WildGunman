#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "Personaje.h"
#include "Jugador.h"
class WildGunman {
private:
	sf::RenderWindow ventanajuego;
	sf::Vector2i posicionMouse;
	sf::Clock reloj, relojJuego;
	sf::Time tiempo, tiempoJuego, intervalo, transcurrido, delayDisparo;
	sf::Texture texFondo, texMouse, textVidas;
	sf::Sprite sprFondo, sprMouse, sprVidas;
	sf::Font fuente;
	sf::Text texto, textoTiempo, textoPunt;
	sf::String pausa, posX, posY, cadena, impactado, findeljuego, perdiste;
	sf::Music musica;
	sf::Sound disparo, baleado;
	sf::SoundBuffer bufferDisparo, bufferBaleado;
	sf::Color colorSprite;
	bool enjuego, sinVidas, jugadorMuerto;
	int vidasX, vidasY, contadorPersonajes, indice, posicionUltima;
	//array con las coordenadas de las posiciones donde aparecen los personajes
	int arrayPosiciones[6][2] = { {107,223}, {254,223}, {401,223}, {107,412}, {401,412}, {252,415} };

	//array que lleva el control de los personajes que estan activos, la ultima posición es el inocente de la puerta
	bool arrayPosOcupadas[6] = { false, false, false, false, false, false};

	//array que contiene al area que ocupan los personajes {{xInic, yInic, xFin, yFin} 
	int areaPersonajes[6][4] = { {127,243,202,353}, {264,243,349,353}, {421,243,496,353},
									{127,432,202,540}, {421,432,496,540}, {272,435,347,545} };
	sf::String arrayTexturas[4] = { "archivos/enemigo1.png", "archivos/enemigo2.png", 
									"archivos/enemigo3.png", "archivos/inocente1.png"};
	float arrayTiempos[5] = { 0.3, 0.6, 0.9, 1.2, 1.5 };
	Jugador Jugador1;
	Personaje arrayPersonajes[6];
public:
	WildGunman();
	void ActualizarElementos(sf::Time t);
	void PausarJuego();
	bool CapturarClic(int xCapt, int yCapt, int &posicion);
	void ProcesarEvento(bool enemDisp);
	sf::Text MostrarMensaje(sf::String msj);
	void Jugar();
};

