#pragma once
#include "activitate.h"
#include <vector>

using namespace std;

//Clasa de exceptii specifice Repo-ului
class ExceptieRepo
{
private:
	string mesajEroare;
public:
	ExceptieRepo(string mesajEroare) : mesajEroare{ mesajEroare } {};
	string getMesajeEroare()
	{
		return this->mesajEroare;
	}
};

class RepoActivitati
{
private:
	vector <Activitate> activitati;
public:

	RepoActivitati() = default;
	//constructorul de copiere
	RepoActivitati(const RepoActivitati& ot) = delete;

	/*
	Adauga o activitate in lista
	@param activitate: activitatea care se adauga(Activitate)
	@return -
	post: activitatea va fi adaugata in lista
	@throws: ExceptieRepo daca o activitate cu acelasi titlu si aceeasi descriere exista deja
	*/
	virtual void adaugare(const Activitate& activitate);



	/*
	Actualizeaza o activitate din lista
	@param activitate: activitatea care se actualizeaza(Activitate)
	@return -
	post: activitatea din lista va fi actualizata
	@throws: ExceptieRepo daca nu exista o activitate cu acelasi titlu si aceeasi descriere
	*/
	virtual void actualizare(const Activitate& activitate);



	/*
	Sterge o activitate din lista
	@param activitate: activitatea care se sterge(Activitate)
	@return -
	post: activitatea din lista va fi stearsa
	@throws: ExceptieRepo daca nu exista o activitate cu acelasi titlu si aceeasi descriere
	*/
	virtual void stergere(string titlu, string descriere);


	/*
	Returneaza o lista cu toate activitatile
	@return: lista cu activitatile (vector de obiecte Activitate)
	*/
	vector <Activitate> getAll();


	/*
	Cauta o activitate cu titlul si descrierea data

	@param titlu: titlul dupa care se cauta
	@param descriere: descrierea dupa care se cauta
	@return: entitatea Activitate cu titlul si descrierea (daca aceasta exista)
	@throws: ExceptieRepo daca nu exista activitatea cu titlul si descrierea data
	*/
	const Activitate& gaseste_activitate(string titlu, string descriere);


	/*
	Verifica daca o activitate data exista in lista

	@param activitate: activitatea care se cauta in lista
	@return: true daca activitatea exista, false altfel
	*/
	bool exista(const Activitate& activitate);

	virtual void sterge_undo(string titlu, string descriere)
	{
		auto iterator = remove_if(activitati.begin(), activitati.end(), [titlu, descriere](Activitate activitate)
			{
				if (activitate.getTitlu() == titlu && activitate.getDescriere() == descriere)
					return true;
				return false;
			});
		activitati.erase(iterator, activitati.end());
	}

	virtual void actualizeaza_undo(const Activitate& activitate)
	{
		if (exista(activitate))
			for (auto& a : activitati)
				if (a.getTitlu() == activitate.getTitlu() && a.getDescriere() == activitate.getDescriere())
				{
					a = activitate;
					break;
				}
	}


	virtual void adauga_undo(const Activitate& activitate) {
		if (!exista(activitate))
			this->activitati.push_back(activitate);
	}

};

class RepoFile : public RepoActivitati {
private:
	string filename;
	/*
	Incarca datele din fisier
	*/
	void loadFromFile();
	/*
	* Salveaza datele din fisier
	* Format: titlu,descriere,tip,durata\n
	*/
	void saveToFile();
public:
	RepoFile(string fname) :RepoActivitati(), filename{ fname } {
		loadFromFile();
	};
	void adaugare(const Activitate& activitate) override;
	void stergere(string titlu, string descriere)override;
	void actualizare(const Activitate& activitate)override;
	void sterge_undo(string titlu, string descriere) override;
	void actualizeaza_undo(const Activitate& activitate)override;
	void adauga_undo(const Activitate& activitate) override;
};

class Lista_activitati_curente
{
private:
	vector <Activitate> lista_activitati;
public:
	Lista_activitati_curente() = default;

	friend class RepoActivitati;

	vector<Activitate>& getAll_lista() noexcept;

	void adaugare_activitate_in_lista(const Activitate& activitate);

	void golire_lista() noexcept;

	void export_lista(string nume_fisier);
};
