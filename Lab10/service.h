#pragma once 
#include "repo.h"
#include "validator.h"
#include "dto.h"
#include <functional>
#include <map>
#include "undo.h"

using namespace std;
using std::unique_ptr;

class StocareActivitati
{
private:
	RepoActivitati& repo;
	ValidatorActivitate& validator;
	Lista_activitati_curente& lista_activitati;

	vector <unique_ptr<ActiuneUndo>> undoActions;
	vector <Activitate> filtrare(function<bool(const Activitate&)> functie);

public:
	StocareActivitati(RepoActivitati& repoActivitate, Lista_activitati_curente lista_activitati, ValidatorActivitate& val) noexcept :repo{ repoActivitate }, lista_activitati{ lista_activitati }, validator{ val } {};

	//constructor de copiere
	StocareActivitati(const StocareActivitati& ot) = delete;//: repo{ ot.repo }, lista_activitati{ ot.lista_activitati }, validator{ ot.validator } {}

	/*
	Adauga o activitate cu titlul-titlu, tipul-tip, descrierea-descriere si durata-durata
	*@param titlu: titlul activitatii care se adauga(string)
	*@param descriere:descrierea activitatii care se adauga (string)
	*@param tip: tipul activitatii care se adauga(string)
	*@param durata: durata pentru activitatea care se adauga(int)
	*
	* @throws:
	*ExceptieRepozitoriu daca mai exista o alta activitate cu acelasi titlu si descriere
	*ValidationException daca activitatea introdusa nu este valida
	*/
	void adaugare_activitate(string titlu, string descriere, string tip, int durata);


	/*
	Actualizeaza o activitate cu titlul-titlu, tipul-tip, descrierea-descriere si durata-durata
	*@param titlu: titlul activitatii care se actualizeaza(string)
	*@param descriere: descrierea actuvitatii care se actualizeaza(string)
	*@param tip: tipul nou al activitatii care se actualizeaza(string)
	*@param durata: durata noua a activitatii care se actualizeaza(int)
	*
	* @throws:
	*ExceptieRepozitoriu daca nu exista activitatea
	*ValidationException daca activitatea introdusa nu este valida
	*/
	void actualizare_activitate(string titlu, string descriere, string tip, int durata);


	/*
	Sterge o activitate cu titlul-titlu si descrierea-descriere
	*@param titlu: titlul activitatii care se sterge(string)
	*@param descriere: descrirea activitatii care se sterge(string)
	*
	* @throws:
	*ExceptieRepozitoriu daca nu exista activitatea
	*/
	void stergere_activitate(string titlu, string descriere);



	/*
	Cauta o activitate cu titlul-titlu si descrierea-descriere
	*@param titlu: titlul activitatii care se cauta(string)
	*@param descriere: descrierea activitatii care se cauta(string)
	* return: activitatea cautata (daca ea exista)
	*
	* * @throws:
	*ExceptieRepozitoriu daca nu exista activitatea
	*/
	const Activitate& cautare_activitate(string titlu, string descriere);

	/*
	* return: lista de activitati
	*/
	vector <Activitate> getAll()
	{
		return this->repo.getAll();
	}

	/*
	Filtreaza activitatile dupa titlu dat
	@param titlu: titlul dupa care se filtreaza (string)
	return: lista activitatilor cu titlul dat(Dynamic Vector)
	*/
	vector <Activitate> filtrare_titlu(string titlu);

	/*
	Filtreaza cartile dupa o durata data
	@param durata: durata dupa care se filtreaza (int)
	return: lista activitatilor cu durata data(Dynamic Vector)
	*/
	vector<Activitate> filtrare_durata(int durata);


	vector<Activitate> sortareGenerala(bool(*maiMicF)(const Activitate&, const Activitate&));

	vector<Activitate> sortare_titlu();

	vector<Activitate> sortare_descriere();

	vector<Activitate> sortare_durata_tip();

	/*
	Returneaza activitatile care se afla in lista
	*@param: -
	*@throws:-
	*ExceptieRepozitoriu daca lista e goala
	*/
	vector<Activitate>& getAll_lista() noexcept
	{
		return this->lista_activitati.getAll_lista();
	}

	/*
	* Returneaza numarul de activitati din lista
	*/
	size_t get_marime_lista() noexcept;

	void adaugare_activitate_in_lista(string titlu, string descriere);

	void genereaza_lista(int nr);

	void golire_lista() noexcept;

	map<string, DTO> cerinta_noua();

	void export_lista(string nume_fisier);

	bool undo();
};

