#pragma once

#include "CImagen.hpp"
using namespace System;
using namespace System::Drawing;

ref class CSprite : public CImagen
{
	short n_subimagenes_x;
	short n_subimagenes_y;
	short indice_x;
	short indice_y;
public:
	CSprite(String^ ruta, Rectangle area_dibujo, short n_subimagenes_x, short n_subimagenes_y)
		: CImagen(ruta, area_dibujo), n_subimagenes_x(n_subimagenes_x), n_subimagenes_y(n_subimagenes_y), indice_x(0), indice_y(0) {}
	void dibujar(Graphics^ graficador) override {
		Rectangle area_recorte = this->calcular_area_recorte();
		graficador->DrawImage(this->imagen, this->area_dibujo, area_recorte, GraphicsUnit::Pixel);
	}
	bool Colision(CSprite^ hitbox) {
		return this->area_dibujo.IntersectsWith(hitbox->area_dibujo);
	}
	void setIndexY(short y_index) {
		this->indice_y = y_index;
	}

private:
	Rectangle calcular_area_recorte() {
		short ancho = this->imagen->Width / this->n_subimagenes_x;
		short alto = this->imagen->Height / this->n_subimagenes_y;
		short x = this->indice_x * ancho;
		short y = this->indice_y * alto;
		return Rectangle(x, y, ancho, alto);
	}
};
