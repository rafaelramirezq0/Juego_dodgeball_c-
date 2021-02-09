#pragma once

using namespace System;
using namespace System::Drawing;

ref class CImagen
{
protected:
	Bitmap^ imagen;//Una imagen agrega un mapa de bits
	Rectangle area_dibujo;//Una imagen agrega un área donde será dibujada
public:
	CImagen(String^ ruta, Rectangle area_dibujo) {
		this->imagen = gcnew Bitmap(ruta);
		this->area_dibujo = area_dibujo;
	}
	~CImagen() {
		delete this->imagen;
	}
	virtual void dibujar(Graphics^ graficador) {//Dependencia, la imagen depende del graficador para ser dibujada
		graficador->DrawImage(this->imagen, this->area_dibujo);
	}

	void moverx(int dx)
	{
		this->area_dibujo.X += dx;
	}

	void movery(int dy)
	{
		this->area_dibujo.Y += dy;
	}

	bool detectar_colision(Rectangle other)
	{
		if (this->area_dibujo.IntersectsWith(other) )
		{
			return true;
		}
		else
		{
			return false;
		}
	}

	int getY(){
		return area_dibujo.Y;
	}

	int getX() {
		return area_dibujo.X;
	}

	void setY(int y){
		this->area_dibujo.Y = y;
	}

	void setX(int x){
		this->area_dibujo.X = x;
	}

};