#pragma once 
#include "service.h"
#include "teste.h"

class consola
{
private:
	StocareActivitati& service;

public:
	consola(StocareActivitati& service) noexcept :service{ service } {};
	consola(const consola& ot) = delete;

	void Meniu();
	void run();
	void afisare_activitati();

	void adaugare_ui();

	void modificare_ui();

	void stergere_ui();

	void cautare_ui();

	void filtrare_ui();

	void sortare_ui();

	void afisare_lista();

	void adaugare_in_lista_ui();

	void generare_lista_ui();

	void golire_lista_ui();

	void cerinta_noua();

	void export_lista_ui();

	void undo_ui();
};