#pragma once

#ifndef JUGADOR 
#define JUGADOR

#include "CEntidad.hpp"
#include "CPelota.hpp"

using namespace System;
using namespace System::Collections;
using namespace System::Collections::Generic;

ref class CJugador : public CEntidad {
	Direccion dir = Direccion::Ninguna;
	CSprite^ barraVida;
	List<CPelota^>^ pelotas;
	int vidas = 5;
public:
	CJugador(int x, int y) : CEntidad(5, x, y, 50, 50, 1, 1, "Imagenes/jugador.png") {
		pelotas = gcnew List<CPelota^>();
		barraVida = gcnew CSprite ("Imagenes/barravida.png",Rectangle(this->sprite->getX()-30, this->sprite->getY() - 35, 60, 20),1,5);
	}

	void mover() override {
			if (dir == Direccion::Izquierda  && this->sprite->getX() - velocidad >= 50)
				this->sprite->moverx(-this->velocidad);
	
			else if (dir == Direccion::Derecha  && this->sprite->getX() + velocidad <= 400)
				this->sprite->moverx(this->velocidad);
			else if (dir == Direccion::Arriba	&& this->sprite->getY() - velocidad >= 200)
				this->sprite->movery(-this->velocidad);
			else if (dir == Direccion::Abajo && this->sprite->getY() + velocidad <= 400)
				this->sprite->movery(this->velocidad);  
		

		for each (CPelota ^ pelota in pelotas)
		{
			pelota->mover();
		}
	
		this->barraVida->setX(this->sprite->getX());
		this->barraVida->setY(this->sprite->getY()-30);
	
	
	}
	void disparar() override {
		if (pelotas->Count < 3) {
			this->pelotas->Add(gcnew CPelota(10, this->sprite->getX() + 5, this->sprite->getY() + 5));
		}
	}

	void SetDireccion(Direccion dir) {
		this->dir = dir;
	}

	void dibujar(Graphics^ g) override {
		if (this->vidas > 0) {
			this->sprite->dibujar(g);
			this->barraVida->setIndexY(this->vidas-1);
			this->barraVida->dibujar(g);

			for each (CPelota ^ pelota in pelotas)
			{
				pelota->dibujar(g);
				if (pelota->getX() > 850) {
					pelotas->Remove(pelota);
					break;
				}
			}
		}

	}
	void tomarDanio() {
		this->vidas--;
	}
	List<CPelota^>^ GetPelotas() {
		return this->pelotas;
	}
};

#endif // !JUGADOR 