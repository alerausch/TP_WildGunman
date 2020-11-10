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
	//int posicion = rand() % 6;
	
	/*for (int i = 0; i <= 5; i++) {
		int posicion = rand() % 3;
		arrayEnemigos[i].setearSprite(arrayTexturas[posicion]);
		arrayEnemigos[i].setearPosicion(arrayPosiciones[i][0], arrayPosiciones[i][1]);
	}*/

	//enemigo de prueba
	arrayEnemigos[0].setearSprite(arrayTexturas[2]);
	arrayEnemigos[0].setearPosicion(arrayPosiciones[2][0], arrayPosiciones[2][1]);
	arrayEnemigos[0].setearTiempoVida(4);
	///////////////////
	vidasX = 115;
	vidasY = 580;
	inocente1.setearSprite(arrayTexturas[3]);
	inocente1.setearPosicion(255, 415);
	inocente1.setearTiempoVida(3);
	enjuego = true;
	contadorPersonajes = 0;
}

void WildGunman::ActualizarElementos(sf::Time t)
{
	for (int i = 0; i <= 5; i++) {
		arrayPosOcupadas[i] = arrayEnemigos[i].actualizar(t);
	}
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
		tiempo = reloj.getElapsedTime();
		if (inocente1.actualizar(tiempo)) {
			ventanajuego.draw(inocente1.mostrar());
		}
		if (arrayEnemigos[0].actualizar(tiempo)) {
			ventanajuego.draw(arrayEnemigos[0].mostrar());
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

void WildGunman::AdministrarPersonajes(sf::Time t)
{
	
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
	// Reiniciamos el reloj almacenando el tiempo pasado
	//tiempo = reloj.restart();
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
						impactado = std::to_string(pos);
						PausarJuego();
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
		tiempo = reloj.getElapsedTime();
		ActualizarElementos(tiempo);
		
		
		//dibujo mouse
		ventanajuego.draw(sprMouse);
		
		//muestro imagen
		ventanajuego.display();
	}
}
