#pragma once 
#include "service.h"
#include <vector>
#include "activitate.h"
#include <functional>
#include <random>
#include <algorithm>
#include <chrono>
#include "undo.h"

using namespace std;

void StocareActivitati::adaugare_activitate(string titlu, string descriere, string tip, int durata)
{
	Activitate activitate1{ titlu, descriere, tip, durata };
	validator.validare(activitate1);
	repo.adaugare(activitate1);
	undoActions.push_back(make_unique<UndoAdauga>(repo, activitate1));
}

void StocareActivitati::actualizare_activitate(string titlu, string descriere, string tip, int durata)
{
	Activitate activitate1 = repo.gaseste_activitate(titlu, descriere);
	Activitate activitate2{ titlu, descriere, tip, durata };
	validator.validare(activitate2);
	repo.actualizare(activitate2);
	undoActions.push_back(make_unique<UndoActualizeaza>(repo, activitate1));
}

void StocareActivitati::stergere_activitate(string titlu, string descriere)
{
	Activitate activitate = repo.gaseste_activitate(titlu, descriere);
	repo.stergere(titlu, descriere);
	undoActions.push_back(make_unique<UndoSterge>(repo, activitate));
}

const Activitate& StocareActivitati::cautare_activitate(string titlu, string descriere)
{
	return repo.gaseste_activitate(titlu, descriere);
}

vector<Activitate> StocareActivitati::filtrare(function <bool(const Activitate&)> functie)
{
	vector<Activitate> v{ repo.getAll() };
	vector<Activitate> activitati_filtrate;
	for (auto i : v)
	{
		if (functie(i))
			activitati_filtrate.push_back(i);
	}
	return activitati_filtrate;
}

vector<Activitate> StocareActivitati::filtrare_titlu(string titlu)
{
	return filtrare([titlu](const Activitate& activitate)
		{
			return activitate.getTitlu() == titlu;
		});
}

vector<Activitate> StocareActivitati::filtrare_durata(int durata)
{
	return filtrare([durata](const Activitate& activitate) noexcept
		{
			return activitate.getDurata() == durata;
		});
}

vector<Activitate> StocareActivitati::sortareGenerala(bool(*maiMicF)(const Activitate&, const Activitate&))
{
	vector<Activitate> v{ repo.getAll() };
	for (int i = 0; i < v.size(); i++)
	{
		for (int j = i + 1; j < v.size(); j++)
		{
			if (!maiMicF(v[i], v[j]))
			{
				Activitate aux = v[i];
				v[i] = v[j];
				v[j] = aux;
			}
		}
	}
	return v;
}

vector<Activitate> StocareActivitati::sortare_titlu()
{
	return sortareGenerala(cmpTitlu);
}

vector<Activitate> StocareActivitati::sortare_descriere()
{
	return sortareGenerala(cmpDescriere);
}


vector<Activitate> StocareActivitati::sortare_durata_tip()
{
	return sortareGenerala(cmpTipDurata);
}

size_t StocareActivitati::get_marime_lista() noexcept
{
	size_t numar = 0;
	numar = lista_activitati.getAll_lista().size();
	return numar;
}

void StocareActivitati::adaugare_activitate_in_lista(string titlu, string descriere)
{
	const auto& c = repo.gaseste_activitate(titlu, descriere);
	lista_activitati.adaugare_activitate_in_lista(c);
}

void StocareActivitati::genereaza_lista(int nr)
{
	vector<Activitate> activitati = getAll();
	vector<Activitate> copie(activitati.size());
	int numar_random;
	copy(activitati.begin(), activitati.end(), copie.begin());
	for (int i = 0; i < nr; i++)
	{
		//facem o copie a vectorului de activitati si il amestecam de nr ori
		auto seed = chrono::system_clock::now().time_since_epoch().count();
		shuffle(copie.begin(), copie.end(), default_random_engine(int(seed))); //amesteca vectorul
		// generam o pozitie random cuprinsa intre 0 si lungimea copiei - 1
		mt19937 mt{ std::random_device{}() };
		uniform_int_distribution<> dist(0, int(copie.size() - 1));
		numar_random = dist(mt);
		//adaugam in lista o activitate cu indice random
		adaugare_activitate_in_lista(copie[numar_random].getTitlu(), copie[numar_random].getDescriere());
	}
}

void StocareActivitati::golire_lista() noexcept
{
	lista_activitati.golire_lista();
}

map<string, DTO> StocareActivitati::cerinta_noua()
{
	vector<Activitate> lista = getAll();
	map<string, DTO> dict;
	for (auto c : lista)
	{
		string tip_curent = c.getTip();
		if (dict.find(tip_curent) == dict.end())
		{
			DTO nou{ tip_curent, 1 };
			dict[tip_curent] = nou;
		}
		else
		{
			dict[tip_curent].increment_cnt();
		}
	}
	return dict;
}

void StocareActivitati::export_lista(string nume_fisier)
{
	int validare = 0;
	validare = ValidatorFisier::valideaza(nume_fisier);
	if (validare == 1)
		lista_activitati.export_lista(nume_fisier);
}

bool StocareActivitati::undo()
{
	if (undoActions.empty() == true)
		return 1;
	else
	{
		undoActions.back()->doUndo();
		undoActions.pop_back();
		return 0;
	}
}
