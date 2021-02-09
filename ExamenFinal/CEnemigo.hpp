#pragma once

#ifndef ENEMIGO 
#define ENEMIGO


#include "CEntidad.hpp"
#include "CPelota.hpp"
#include <stdlib.h>

using namespace System;
using namespace System::Collections;
using namespace System::Collections::Generic;

ref class CEnemigo : public CEntidad {
	int x_objetivo;
	int y_objetivo;
	int vida = 5;
	CSprite^ barraVida2;
	List<CPelota^>^ pelotas;
public:
	CEnemigo(int velocidad, int x, int y) : CEntidad(velocidad, x, y, 50, 50, 1, 1, "Imagenes/enemigo.png") {
		this->x_objetivo = rand() % 353 + 435;
		this->y_objetivo = rand() % 179 + 256;
		barraVida2 = gcnew CSprite("Imagenes/barravida.png", Rectangle(this->sprite->getX() - 30, this->sprite->getY() - 35, 60, 20), 1, 5);
		pelotas = gcnew List<CPelota^>();
	}
	void mover() override {
		bool validacion_x = this->sprite->getX() >= x_objetivo - 5 && this->sprite->getX() <= x_objetivo + 5;
		bool validacion_y = this->sprite->getY() >= y_objetivo - 5 && this->sprite->getY() <= y_objetivo + 5;
		
		if (validacion_x && validacion_y) {
			this->x_objetivo = rand() % 353 + 435;
			this->y_objetivo = rand() % 179 + 256;
		}
		else {
			//4 CASOS
			//IZQ
			if (this->sprite->getX() > x_objetivo) {
				this->sprite->moverx(-this->velocidad);
			}
			//DER
			if (this->sprite->getX() < x_objetivo) {
				this->sprite->moverx(this->velocidad);
			}
			//ARRIBA
			if (this->sprite->getY() > y_objetivo) {
				this->sprite->movery(-this->velocidad);
			}
			//ABAJO
			if (this->sprite->getY() < y_objetivo) {
				this->sprite->movery(this->velocidad);
			}
		}

		for each (CPelota ^ pelota in pelotas)
		{
			pelota->mover();
		}

		this->barraVida2->setX(this->sprite->getX());
		this->barraVida2->setY(this->sprite->getY() - 30);


	}
	void disparar() override {
		if (pelotas->Count < 3) {
			this->pelotas->Add(gcnew CPelota(-10, this->sprite->getX() - 5, this->sprite->getY() + 5));
		}
	}
	void dibujar(Graphics^ g) override {
		if (vida > 0) {
			this->sprite->dibujar(g);
			this->barraVida2->setIndexY(this->vida - 1);
			this->barraVida2->dibujar(g);

			for each (CPelota ^ pelota in pelotas)
			{
				pelota->dibujar(g);
				if (pelota->getX() < 0) {
					pelotas->Remove(pelota);
					break;
				}
			}
		}
	}

	void tomarDanio() {
		this->vida--;
	}
	List<CPelota^>^ GetPelotas() {
		return this->pelotas;
	}
};

#endif // !ENEMIGO 