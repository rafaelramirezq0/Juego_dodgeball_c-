#pragma once
/*
#ifndef CONTROLADORA 
#define CONTROLADORA
*/
#include "CEntidad.hpp"
#include "CJugador.hpp"
#include "CEnemigo.hpp"

ref class CControladora {
	//atributos
	CImagen^ fondo;
	CImagen^ pausa;
	CEnemigo^ enemigo;
	CJugador^ jugador;
	private: System::Windows::Forms::Timer^ AnimacionPrincipal;
public:
	CControladora(int ancho, int largo) {
		fondo = gcnew CImagen("Imagenes/fondo.png", Rectangle(0, 0, ancho, largo));
		pausa = gcnew CImagen("Imagenes/pause.png", Rectangle(0, 0, ancho, largo));
		enemigo = gcnew CEnemigo(5, 500, 300);
		jugador = gcnew CJugador(200, 300);

	}
	void dibujar_todo(Graphics^ g) {
		enemigo->dibujar(g);
		jugador->dibujar(g);
	}

	void dibujar_pausa(Graphics^ g) {
		pausa->dibujar(g);			// Pause Screen
	}

	void mover_todo() {
		enemigo->mover();
		jugador->mover();
	}
	void animar(Graphics^ g){
		fondo->dibujar(g);
		
		Pelota_Hit(this->jugador->GetPelotas(), this->enemigo);
		Pelota_Hit(this->enemigo->GetPelotas(), this->jugador);
		dibujar_todo(g);
		mover_todo();
		//pausa->dibujar(g);
	}

	void Pelota_Hit(List<CPelota^>^ pelotas, CJugador^ jugador) {
		for each (CPelota ^ pelota in pelotas)
		{
			if (pelota->getSprite()->Colision(jugador->getSprite())) {
				pelotas->Remove(pelota);
				jugador->tomarDanio();
				break;
			}
		}
	}

	void Pelota_Hit(List<CPelota^>^ pelotas, CEnemigo^ enemigo) {
		for each (CPelota ^ pelota in pelotas)
		{
			if (pelota->getSprite()->Colision(enemigo->getSprite())) {
				pelotas->Remove(pelota);
				enemigo->tomarDanio();
				break;
			}
		}
	}


	void JugadorDispara() {
		this->jugador->disparar();
	}
	void EnemigoDispara() {

		int prob = rand() % 25;

		if(prob == 1)
			this->enemigo->disparar();
	}
	void detectarTecla(Direccion dir) {
		this->jugador->SetDireccion(dir);
	}
};

//#endif // !CONTROLADORA 