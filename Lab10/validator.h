#pragma once 
#include <vector>
#include <string>
#include "activitate.h"

using namespace std;

class ExceptieValidator
{
	vector <string> mesajEroare;

public:
	ExceptieValidator(vector <string> mesajeEroare) :mesajEroare{ mesajeEroare } {};
	string get_mesaje_eroare()
	{
		string mesaje = "";
		for (const string msj : mesajEroare)
			mesaje = mesaje + msj + "\n";
		return mesaje;
	}
};

/*
Clasa pentru validarea activitatilor
O activitate este valida daca:
	are titlu format din mai mult de 3 caractere
	are tipul format din mai mult de 1 caractere
	are descrierea formata din mai mult de 3 caractere
	durata >= 0
*/
class ValidatorActivitate
{
public:
	void validare(const Activitate& activitate)
	{
		vector <string> erori;
		if (activitate.getTitlu().length() < 3)
			erori.push_back("Titlul activitatii trebuie sa aiba cel putin 3 caractere.");
		if (activitate.getTip().length() < 1)
			erori.push_back("Tipul activitatii trebuie sa aiba cel putin 1 caracter.");
		if (activitate.getDescriere().length() < 3)
			erori.push_back("Descrierea activitatii trebuie sa aiba cel putin 3 caractere.");
		if (activitate.getDurata() < 1)
			erori.push_back("Durata activitatii trebuie sa fie mai mare ca si 0.");

		if (erori.size() > 0)
			throw ExceptieValidator(erori);
	}
};

/*
* Clasa pentru validarea numelor de fisiere
  Un nume e valid daca:
	e din mai mult de 3 caractere
	are extensia csv sau html
*/
class ValidatorFisier {
public:
	static int valideaza(string nume_fisier)
	{
		vector <string> erori;
		const int lungime = static_cast<int>(nume_fisier.size());
		int rezultat = 0;
		if (lungime < 4)
			erori.push_back("Numele fisierului trebuie sa aiba cel putin 4 caractere.");
		else
		{
			string extensie = ".csv";
			bool fisier_csv = true;
			size_t index_str;
			if ((index_str = nume_fisier.find(extensie, 0)) != string::npos)
			{
				if (static_cast<int>(index_str) + 1 != lungime - 3) fisier_csv = false;
			}
			else
				fisier_csv = false;

			string extensie2 = ".html";
			bool fisier_html = true;
			size_t index_str2;
			if ((index_str2 = nume_fisier.find(extensie2, 0)) != string::npos)
			{
				if (static_cast<int>(index_str2) + 1 != lungime - 4) fisier_html = false;
			}
			else
				fisier_html = false;

			if (fisier_csv == false && fisier_html == false)
				erori.push_back("Numele fisierului nu are extensia csv sau html.\n");
			else
				rezultat = 1;
		}
		if (erori.size() > 0)
			throw ExceptieValidator(erori);
		return rezultat;
	}
};

