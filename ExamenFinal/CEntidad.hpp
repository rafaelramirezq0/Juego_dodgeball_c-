#pragma once

#include "CSprite.hpp"

enum Direccion{Arriba, Abajo, Izquierda, Derecha, Ninguna};

ref class CEntidad {
protected:
	CSprite^ sprite;
	int velocidad;

public:
	CEntidad(int velocidad, int x, int y, int ancho, int alto, short subIMG_x, short subIMG_y, String^ img) {
		sprite = gcnew CSprite(img, Rectangle(x, y, ancho, alto), subIMG_x, subIMG_y);
		this->velocidad = velocidad;
	}

	
	virtual void mover() {}
	virtual void disparar() {}
	virtual void dibujar(Graphics^ g) {
		sprite->dibujar(g);
	}

	CSprite^ getSprite(){
		return this->sprite;
	}
};