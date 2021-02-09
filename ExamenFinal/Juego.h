#pragma once
#include "CControladora.hpp"
#include <time.h>
#include <stdlib.h>

namespace Dodgeball {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	using namespace System::Media;

	public ref class Juego : public System::Windows::Forms::Form
	{
		Graphics^ g;
		BufferedGraphics^ buffer;
		CControladora^ juegoPrincipal;
		//CImagen^ pausa;
		private: System::Windows::Forms::Timer^ AnimacionPrincipal;
	public:
		Juego(void)
		{	//CONSTRUCTOR
			srand(time(NULL));
			InitializeComponent();
			this->g = CreateGraphics();
			this->buffer = BufferedGraphicsManager::Current->Allocate(this->g, this->ClientRectangle);

			juegoPrincipal = gcnew CControladora(this->ClientRectangle.Width, this->ClientRectangle.Height);
		}

	protected:
		
		~Juego()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::ComponentModel::IContainer^ components;
	protected:

	private:
		


#pragma region Windows Form Designer generated code
		
		void InitializeComponent(void)
		{
			this->components = (gcnew System::ComponentModel::Container());
			this->AnimacionPrincipal = (gcnew System::Windows::Forms::Timer(this->components));
			this->SuspendLayout();
			// 
			// AnimacionPrincipal
			// 
			this->AnimacionPrincipal->Enabled = true;
			this->AnimacionPrincipal->Interval = 50;
			this->AnimacionPrincipal->Tick += gcnew System::EventHandler(this, &Juego::AnimacionPrincipal_Tick);
			// 
			// Juego
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(8, 16);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(1125, 625);
			this->Margin = System::Windows::Forms::Padding(4, 4, 4, 4);
			this->Name = L"Dodgeball";
			this->Text = L"Dodgeball";
			this->Load += gcnew System::EventHandler(this, &Juego::Juego_Load);
			this->KeyDown += gcnew System::Windows::Forms::KeyEventHandler(this, &Juego::ActivarMovimiento);
			this->KeyUp += gcnew System::Windows::Forms::KeyEventHandler(this, &Juego::DesactivarMovimiento);
			this->ResumeLayout(false);

		}
#pragma endregion
	private: System::Void AnimacionPrincipal_Tick(System::Object^ sender, System::EventArgs^ e) {
		juegoPrincipal->animar(this->buffer->Graphics);

		if (this->AnimacionPrincipal->Interval > 100) {
			juegoPrincipal->dibujar_pausa(this->buffer->Graphics);}

		juegoPrincipal->EnemigoDispara();
		this->buffer->Render(); //SE MUESTRA EN PANTALLA
	}
	private: System::Void ActivarMovimiento(System::Object^ sender, System::Windows::Forms::KeyEventArgs^ e) {
		// e->KeyCode
		//EVENTO CUANDO SE PRESIONA UNA TECLA
		if (e->KeyCode == Keys::Up) {
			this->juegoPrincipal->detectarTecla(Direccion::Arriba);

		}
		else if (e->KeyCode == Keys::Down) {
			this->juegoPrincipal->detectarTecla(Direccion::Abajo);

		}
		else if (e->KeyCode == Keys::Left) {
			this->juegoPrincipal->detectarTecla(Direccion::Izquierda);

		}
		else if (e->KeyCode == Keys::Right) {
			this->juegoPrincipal->detectarTecla(Direccion::Derecha);
		}
		else if (e->KeyCode == Keys::Space) {
			this->juegoPrincipal->JugadorDispara();
		}


		//	switch?
		if (e->KeyCode == Keys::P) {
			this->AnimacionPrincipal->Interval = 100000;
		}

		if (e->KeyCode == Keys::O) {
			this->AnimacionPrincipal->Interval = 50;
		}





	}
	private: System::Void DesactivarMovimiento(System::Object^ sender, System::Windows::Forms::KeyEventArgs^ e) {
		this->juegoPrincipal->detectarTecla(Direccion::Ninguna);
	}
	private: System::Void Juego_Load(System::Object^ sender, System::EventArgs^ e) {
	}
};
}
