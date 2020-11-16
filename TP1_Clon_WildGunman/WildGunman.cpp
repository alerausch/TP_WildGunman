#include "WildGunman.h"
WildGunman::WildGunman() 
{
	ventanajuego.create(sf::VideoMode(626, 626, 32), "Clon WildGunman", sf::Style::Close);
	ventanajuego.setVerticalSyncEnabled(true);
	texFondo.loadFromFile("archivos/saloon2.jpg");
	sprFondo.setTexture(texFondo);
	texMouse.loadFromFile("archivos/mira_1.png");
	sprMouse.setTexture(texMouse);
	textVidas.loadFromFile("archivos/esfera1.png");
	sprVidas.setTexture(textVidas);
	texMouse.setSmooth(true);
	ventanajuego.setMouseCursorVisible(false);

	//cargo fuente para textos del juego
	fuente.loadFromFile("archivos/ROCK.ttf");
	pausa = "JUEGO PAUSADO";
	findeljuego = "   GAME OVER";
	perdiste = "MUY LENTO AMIGO";
	textoPunt.setCharacterSize(35);
	textoPunt.setStyle(sf::Text::Bold);
	texto.setFont(fuente);
	textoTiempo.setFont(fuente);
	textoPunt.setPosition(528, 574);
	textoPunt.setFont(fuente);
	textoPunt.setFillColor(sf::Color::Green);
	srand(time(NULL));
	//creo los personajes en el array
	for (int i = 0; i < 6; i++) {
		int posicion = rand() % 3;
		arrayPersonajes[i].setearSprite(arrayTexturas[posicion]);
		arrayPersonajes[i].setearPosicion(arrayPosiciones[i][0], arrayPosiciones[i][1]);
		arrayPersonajes[i].setearTipo(true);
	}
	//creo un inocente en la ultima posicion del array de personajes
	/*arrayPersonajes[6].setearSprite(arrayTexturas[3]);
	arrayPersonajes[6].setearPosicion(255,415);
	arrayPersonajes[6].setearTipo(false);*/
	vidasX = 115;
	vidasY = 580;
	enjuego = true;
	sinVidas = false;
	jugadorMuerto = false;
	contadorPersonajes = 0;
	posicionUltima = 10;
	intervalo = sf::seconds(2);
	transcurrido = sf::seconds(0);
	delayDisparo = sf::seconds(0);
	//Se carga la música de fondo
	musica.openFromFile("archivos/musica.ogg");
	musica.setLoop(true);
	musica.play();
	//Se carga el sonido de disparo
	bufferDisparo.loadFromFile("archivos/disparo.ogg");
	disparo.setBuffer(bufferDisparo);
}

void WildGunman::ActualizarElementos(sf::Time t)
{
	if ((jugadorMuerto)) {
		delayDisparo = delayDisparo + t;
		if (delayDisparo >= sf::seconds(1.5)) {
			sprFondo.setColor(colorSprite);
			jugadorMuerto = false;
			if (Jugador1.cantVidas() != 0) {
				enjuego = true;
			}
			delayDisparo = sf::seconds(0);
			//reseteo el array de personajes en pantalla luego de la pausa por jugador muerto
			for (int i = 0; i < 6; i++) {
				arrayPosOcupadas[i] = false;
			}
		}
	}
	if (!enjuego) {
		if (sinVidas) {
			ventanajuego.draw(MostrarMensaje(findeljuego));
			musica.stop();
		}else {
			if (jugadorMuerto) {
				ventanajuego.draw(MostrarMensaje(perdiste));
				musica.stop();
			}else{
				ventanajuego.draw(MostrarMensaje(pausa));
			}
		}
		//ventanajuego.draw(MostrarMensaje(impactado));
		ventanajuego.draw(textoPunt);
		sprVidas.setPosition(vidasX, vidasY);
		for (int i = 1; i <= Jugador1.cantVidas(); i++) {
			ventanajuego.draw(sprVidas);
			sprVidas.setPosition(sprVidas.getPosition().x + 35, vidasY);
		}
	}
	else {
		transcurrido = transcurrido + t;
		if ((contadorPersonajes >= 0) && (contadorPersonajes <3) && (transcurrido >= intervalo)) {
			srand(time(NULL));
			do {
				indice = rand() % 6;
				if (indice == 5) {
					int azar = rand() % 2;
					if (azar == 0) {
						arrayPersonajes[indice].setearSprite(arrayTexturas[3]);
						arrayPersonajes[indice].setearPosicion(arrayPosiciones[5][0], arrayPosiciones[5][1]);
						arrayPersonajes[indice].setearTipo(false);
					}
					else {
						arrayPersonajes[indice].setearSprite(arrayTexturas[rand() % 3]);
						arrayPersonajes[indice].setearPosicion(arrayPosiciones[5][0], arrayPosiciones[5][1]);
						arrayPersonajes[indice].setearTipo(true);
					}
				}
				if ((!arrayPosOcupadas[indice]) && (posicionUltima != indice)) {
					intervalo = sf::seconds(arrayTiempos[rand() % 5]);
					transcurrido = sf::seconds(0);
					arrayPersonajes[indice].setearTiempoVida(rand() % 5 + 1);
					arrayPosOcupadas[indice] = true;
					contadorPersonajes++;
				}
			} while (!arrayPosOcupadas[indice]);
		}
		
		//dibujo los personajes que estan activos
		for (int i = 0; i < 6; i++) {
			if (arrayPosOcupadas[i] && arrayPersonajes[i].actualizar(t)) {
				ventanajuego.draw(arrayPersonajes[i].mostrar());
			}
			else {
				if (arrayPosOcupadas[i]) {
					if (arrayPersonajes[i].verTipo()) {
						ProcesarEvento(true);
						disparo.play();
						colorSprite = sprFondo.getColor();
						sprFondo.setColor(sf::Color::Red);
						jugadorMuerto = true;
						enjuego = false;
					}
					arrayPosOcupadas[i] = false;
					contadorPersonajes--;
				}
			}
		}

		sprVidas.setPosition(vidasX, vidasY);
		for (int i = 1; i <= Jugador1.cantVidas(); i++) {
			ventanajuego.draw(sprVidas);
			sprVidas.setPosition(sprVidas.getPosition().x + 35, vidasY);
		}
		//texto.setPosition(0, 0);
		//ventanajuego.draw(texto);
		ventanajuego.draw(textoTiempo);
		textoPunt.setString(Jugador1.verPuntos());
		ventanajuego.draw(textoPunt);
	}
}

void WildGunman::PausarJuego()
{
	if (enjuego) {
		enjuego = false;
		musica.stop();
	}
	else {
		enjuego = true;
		musica.play();
	}
}

bool WildGunman::CapturarClic(int xCapt, int yCapt, int &posicion)
{	
	bool acierto = false;
	xCapt += 20;
	yCapt += 20;
	int i = 0;
	while ((i!=6) && (!acierto)) {
		if ( (xCapt >= areaPersonajes[i][0]) && (xCapt <= areaPersonajes[i][2]) && 
				(yCapt >= areaPersonajes[i][1]) && (yCapt <= areaPersonajes[i][3]) ) {
			acierto = true;
			posicion = i;
		}
		i++;
	}
	if (acierto) {
		return true;
	}
	else {
		return false;
	}
}

void WildGunman::ProcesarEvento(bool enemDisp)
{
	if (enemDisp) {
		Jugador1.restarVidas();
	}else {
		Jugador1.restarVidas();
		Jugador1.setPuntos();
	}
	if (Jugador1.cantVidas() == 0) {
		sinVidas = true;
		enjuego = false;
	}
}

sf::Text WildGunman::MostrarMensaje(sf::String msj)
{
	texto.setString(msj);
	texto.setPosition(200, 250);
	texto.setFont(fuente);
	return texto;
}

void WildGunman::Jugar()
{
	while (ventanajuego.isOpen())
	{
		sf::Event evento;
		while (ventanajuego.pollEvent(evento))
		{
			switch (evento.type) {
			case sf::Event::Closed:
				ventanajuego.close();
			case sf::Event::MouseMoved:
				sprMouse.setPosition(evento.mouseMove.x, evento.mouseMove.y);
			case sf::Event::MouseButtonPressed:
				if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
					posicionMouse = sf::Mouse::getPosition(ventanajuego);
					posX = std::to_string(posicionMouse.x);
					posY = std::to_string(posicionMouse.y);
					int pos;
					if (enjuego) {
						disparo.play();
					}
					if (CapturarClic(posicionMouse.x, posicionMouse.y, pos)) {
						if (arrayPosOcupadas[pos]) {
							if (arrayPersonajes[pos].verTipo()) {
								Jugador1.setAbatidos();
								Jugador1.setPuntos();
							}
							else {
								ProcesarEvento(false);
							}
							arrayPosOcupadas[pos] = false;
							contadorPersonajes--;
							posicionUltima = pos;
							//seteo intervalo aleatorio de aparición del siguiente personaje
							intervalo = sf::seconds(arrayTiempos[rand() % 5]);
							transcurrido = sf::seconds(0);
						}
					}
					//enemigo
				}
			case sf::Event::KeyPressed:
				if (evento.key.code == sf::Keyboard::Escape)
					PausarJuego();
			}
		}
		//Obtenemos la posición actual del mouse
		//relativo a la ventana
		//posicionMouse = Mouse::getPosition(ventanajuego);
		//posX = std::to_string(posicionMouse.x);
		//posY = std::to_string(posicionMouse.y);
		//cadena = posX + "  "+ posY;
		//texto.setString(cadena);
		
		//limpio ventana
		ventanajuego.clear();
		
		//dibujo fondo
		ventanajuego.draw(sprFondo);
		
		//dibujo personajes - vidas - puntos
		tiempo = reloj.restart();
		ActualizarElementos(tiempo);
		//dibujo reloj de juego
		tiempoJuego = relojJuego.getElapsedTime();
		textoTiempo.setString("Tiempo: " + std::to_string(tiempoJuego.asSeconds()));
		
		//dibujo mouse
		ventanajuego.draw(sprMouse);
		
		//muestro imagen
		ventanajuego.display();
	}
}
