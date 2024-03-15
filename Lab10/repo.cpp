#pragma once
#include "repo.h"
#include <vector>
#include <assert.h>
#include <fstream>
#include <sstream>
#include <iostream>

vector <Activitate> RepoActivitati::getAll()
{
	return this->activitati;
}


bool RepoActivitati::exista(const Activitate& activitate)
{
	try
	{
		gaseste_activitate(activitate.getTitlu(), activitate.getDescriere());
		return true;
	}
	catch (ExceptieRepo)
	{
		return false;
	}
}

const Activitate& RepoActivitati::gaseste_activitate(string titlu, string descriere)
{
	auto iterator = std::find_if(this->activitati.begin(), this->activitati.end(), [titlu, descriere](Activitate activitate)
		{
			if (activitate.getTitlu() == titlu && activitate.getDescriere() == descriere)
				return true;
			return false;
		});
	if (iterator == this->activitati.end())
		throw ExceptieRepo("Activitatea cu titlul si descrierea introdusa nu exista in lista!\n");
	return *iterator;
}

void RepoActivitati::adaugare(const Activitate& activitate)
{
	if (exista(activitate))
	{
		throw ExceptieRepo("Activitatea cu titlul si descrierea introdusa exista deja in lista!\n");
	}
	this->activitati.push_back(activitate);
}


void RepoActivitati::actualizare(const Activitate& activitate)
{
	if (exista(activitate))
	{
		int i = 0;
		for (i = 0; i < this->activitati.size(); i++)
			if (activitati[i].getTitlu() == activitate.getTitlu() && activitati[i].getDescriere() == activitate.getDescriere())
			{
				activitati[i] = activitate;
				break;
			}
	}
	else
		throw ExceptieRepo("Activitatea cu titlul si descrierea introdusa nu exista in lista!\n");
}


void RepoActivitati::stergere(string titlu, string descriere)
{
	auto iterator = std::remove_if(this->activitati.begin(), this->activitati.end(), [titlu, descriere](Activitate activitate) {
		if (activitate.getTitlu() == titlu && activitate.getDescriere() == descriere)
			return true;
		return false;
		});
	if (iterator == this->activitati.end())
		throw ExceptieRepo("Activitatea cu titlul si descrierea introdusa nu exista in lista!\n");
	this->activitati.erase(iterator, this->activitati.end());
}



void RepoFile::loadFromFile() {
	ifstream fisier_activitati(this->filename);
	if (!fisier_activitati.is_open()) {
		throw ExceptieRepo("Nu se poate citi din fisierul " + filename);
	}
	string line;
	while (getline(fisier_activitati, line))
	{
		string titlu, descriere, tip;
		int durata = 0;

		stringstream linestream(line);
		string current_item;
		int item_no = 0;

		while (getline(linestream, current_item, ','))
		{
			if (item_no == 0) titlu = current_item;
			if (item_no == 1) descriere = current_item;
			if (item_no == 2) tip = current_item;
			if (item_no == 3) durata = stoi(current_item);
			item_no++;
		}
		Activitate c{ titlu, descriere, tip, durata };

		RepoActivitati::adaugare(c);
	}
	fisier_activitati.close();
}

void RepoFile::saveToFile() {
	ofstream fisier(this->filename);
	if (!fisier.is_open())
		throw ExceptieRepo("Nu se poate scrie in fisierul " + filename);
	for (auto& c : getAll()) {
		fisier << c.getTitlu() << "," << c.getDescriere() << "," << c.getTip() << "," << c.getDurata() << endl;
	}
	fisier.close();
}

void RepoFile::adaugare(const Activitate& activitate) {

	RepoActivitati::adaugare(activitate);
	saveToFile();
}

void RepoFile::stergere(string titlu, string descriere) {

	RepoActivitati::stergere(titlu, descriere);
	saveToFile();
}

void RepoFile::actualizare(const Activitate& activitate)
{
	RepoActivitati::actualizare(activitate);
	saveToFile();
}

void RepoFile::sterge_undo(string titlu, string descriere)
{
	RepoActivitati::sterge_undo(titlu, descriere);
	saveToFile();
}
void RepoFile::actualizeaza_undo(const Activitate& activitate)
{
	RepoActivitati::actualizeaza_undo(activitate);
	saveToFile();
}
void RepoFile::adauga_undo(const Activitate& activitate)
{
	RepoActivitati::adauga_undo(activitate);
	saveToFile();
}



vector <Activitate>& Lista_activitati_curente::getAll_lista() noexcept
{
	return this->lista_activitati;
}
void Lista_activitati_curente::adaugare_activitate_in_lista(const Activitate& activitate)
{
	this->lista_activitati.push_back(activitate);
}

void Lista_activitati_curente::golire_lista() noexcept
{
	this->lista_activitati.clear();
}

void Lista_activitati_curente::export_lista(string nume_fisier)
{
	std::ofstream fout(nume_fisier);
	fout << "Titlu | Descriere | Tip | Durata \n";
	for (auto activitate : this->lista_activitati) fout << activitate.getTitlu() << "|" << activitate.getDescriere() << "|" << activitate.getTip() << "| " << activitate.getDurata() << "\n";//" <br>";
	fout.close();
}