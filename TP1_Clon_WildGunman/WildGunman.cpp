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
	pausa = "   JUEGO PAUSADO";
	textoPunt.setCharacterSize(35);
	textoPunt.setStyle(sf::Text::Bold);
	texto.setFont(fuente);
	textoTiempo.setFont(fuente);
	textoPunt.setPosition(528, 574);
	textoPunt.setFont(fuente);
	textoPunt.setFillColor(sf::Color::Green);
	srand(time(NULL));
	//creo los personajes bandidos en el array
	for (int i = 0; i < 6; i++) {
		int posicion = rand() % 2;
		arrayPersonajes[i].setearSprite(arrayTexturas[posicion]);
		arrayPersonajes[i].setearPosicion(arrayPosiciones[i][0], arrayPosiciones[i][1]);
		arrayPersonajes[i].setearTiempoVida(rand() % 5 + 2);
	}
	//creo un inocente en la ultima posicion del array de personajes
	arrayPersonajes[6].setearSprite(arrayTexturas[3]);
	arrayPersonajes[6].setearPosicion(255,415);
	arrayPersonajes[6].setearTiempoVida(3);

	vidasX = 115;
	vidasY = 580;
	enjuego = true;
	contadorPersonajes = 0;
	transcurrido = sf::seconds(0);
}

void WildGunman::ActualizarElementos(sf::Time t)
{
	if (!enjuego) {
		ventanajuego.draw(MostrarMensaje(pausa));
		ventanajuego.draw(MostrarMensaje(impactado));
		ventanajuego.draw(textoPunt);
		sprVidas.setPosition(vidasX, vidasY);
		for (int i = 1; i <= Jugador1.cantVidas(); i++) {
			ventanajuego.draw(sprVidas);
			sprVidas.setPosition(sprVidas.getPosition().x + 35, vidasY);
		}
	}
	else {
		if ((contadorPersonajes >= 0) && (contadorPersonajes <3)) {
			indice = rand() % 6;
			/*float comparador = 0;
			delta = reloj.getElapsedTime();
			transcurrido = delta - transcurrido;
			comparador = transcurrido.asSeconds();
			arrayTimers[indice] = arrayTimers[indice] + transcurrido;*/
			if (!arrayPosOcupadas[indice]) {
				//transcurrido = sf::seconds(0);
				arrayPosOcupadas[indice] = true;
				//arrayTimers[indice] = arrayTimers[indice] + t;
				contadorPersonajes++;
			}

		}
		//ventanajuego.draw(arrayPersonajes[6].mostrar());
		//dibujo los personajes que estan activos
		for (int i = 0; i < 7; i++) {
			if (arrayPosOcupadas[i] && arrayPersonajes[i].actualizar()) {
				ventanajuego.draw(arrayPersonajes[i].mostrar());
			}
		}

		sprVidas.setPosition(vidasX, vidasY);
		for (int i = 1; i <= Jugador1.cantVidas(); i++) {
			ventanajuego.draw(sprVidas);
			sprVidas.setPosition(sprVidas.getPosition().x + 35, vidasY);
		}
		texto.setPosition(0, 0);
		ventanajuego.draw(texto);
		ventanajuego.draw(textoTiempo);
		textoPunt.setString(Jugador1.verPuntos());
		ventanajuego.draw(textoPunt);
	}
}

void WildGunman::PausarJuego()
{
	if (enjuego) {
		enjuego = false;
	}
	else {
		enjuego = true;
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

sf::Text WildGunman::MostrarMensaje(sf::String msj)
{
	texto.setString(msj);
	texto.setPosition(250, 250);
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
					//int posicion = rand() % 6;
					//arrayEnemigos[0].setearPosicion(arrayPosiciones[posicion][0], arrayPosiciones[posicion][1]);
					tiempo = reloj.getElapsedTime();
					textoTiempo.setString(std::to_string(tiempo.asSeconds()));
					textoTiempo.setPosition(0, 40);
					int pos;
					if (CapturarClic(posicionMouse.x, posicionMouse.y, pos)) {
						if (arrayPosOcupadas[pos]) {
							arrayPosOcupadas[pos] = false;
							contadorPersonajes--;
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
		cadena = posX + "  "+ posY;
		texto.setString(cadena);
		
		//limpio ventana
		ventanajuego.clear();
		
		//dibujo fondo
		ventanajuego.draw(sprFondo);
		
		//dibujo personajes - vidas - puntos
		tiempo = reloj.restart();
		ActualizarElementos(tiempo);
		
		
		//dibujo mouse
		ventanajuego.draw(sprMouse);
		
		//muestro imagen
		ventanajuego.display();
	}
}
