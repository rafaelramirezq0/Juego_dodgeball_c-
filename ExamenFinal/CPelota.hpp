#pragma once
#include "CEntidad.hpp"

ref class CPelota : public CEntidad {
public:
	CPelota(int v,int x, int y) : CEntidad(v, x, y, 20, 20, 1, 1, "Imagenes/pelota2.png") {
	}
	void mover() override {
		this->sprite->moverx(this->velocidad);
	}
	int getX() {
		return sprite->getX();
	}
};