#include "teste.h"

void testAll()
{
	test_activitate();
	test_adaugare_repo();
	test_actualizare_repo();
	test_stergere_repo();
	test_cmp();
	test_actualizare_service();
	test_stergere_service();
	test_adaugare_service();
	test_cautare_service();
	test_gaseste_repo();
	test_filtrare();
	test_sortare();
	test_adaugare_lista_repo();
	test_golire_lista_repo();
	test_generare_lista_repo();
	test_adaugare_lista_service();
	test_golire_lista_service();
	test_generare_lista_service();
	test_get_marime_lista();
	test_dto();
	test_cerinta_noua();
	test_undo();
	test_validare_fisier();
	test_export_cos_csv();
	test_export_cos_html();
}

void test_activitate()
{
	Activitate Activitate{ "Fotbal","Meci de fotbal", "sport", 90 };
	assert(Activitate.getTitlu() == "Fotbal");
	assert(Activitate.getTip() == "sport");
	assert(Activitate.getDescriere() == "Meci de fotbal");
	assert(Activitate.getDurata() == 90);

	Activitate.setTitlu("Stand-up");
	Activitate.setTip("comedie");
	Activitate.setDescriere("Show de comedie");
	Activitate.setDurata(60);

	assert(Activitate.getTitlu() == "Stand-up");
	assert(Activitate.getTip() == "comedie");
	assert(Activitate.getDescriere() == "Show de comedie");
	assert(Activitate.getDurata() == 60);
}


void test_cmp()
{
	Activitate activitate1{ "Fotbal","Meci de fotbal", "sport", 90 };
	Activitate activitate2{ "Stand-up","Show de comedie","comedie", 60 };
	Activitate activitate3{ "Fotbal","Meci de fotbal din nou", "sport din nou", 90 };
	assert(cmpDescriere(activitate1, activitate2) == true);
	assert(cmpTitlu(activitate1, activitate2) == true);
	assert(cmpTipDurata(activitate1, activitate2) == false);
	assert(cmpTipDurata(activitate1, activitate3) == true);
}

void test_adaugare_repo()
{
	RepoActivitati test;
	Activitate activitate1{ "Fotbal","Meci de fotbal", "sport", 90 };
	Activitate activitate2{ "Stand-up","Show de comedie","comedie", 60 };
	test.adaugare(activitate1);
	test.adaugare(activitate2);
	assert(test.getAll().size() == 2);

	Activitate activitate3{ "AA","nimic","nothing", 10 };
	try
	{
		test.adaugare(activitate2);
	}
	catch (ExceptieRepo) {
		assert(true);
	}
}

void test_adaugare_service()
{
	RepoActivitati testR;
	ValidatorActivitate testV;
	Lista_activitati_curente testL;
	StocareActivitati testService{ testR,testL,testV };

	testService.adaugare_activitate("Fotbal", "Meci de fotbal", "sport", 90);
	testService.adaugare_activitate("Stand-up", "Show de comedie", "comedie", 60);

	assert(testService.getAll().size() == 2);
	try
	{
		testService.adaugare_activitate("Fotbal", "Meci de fotbal", "sport", 90);
	}
	catch (ExceptieRepo&)
	{
		assert(true);
	}
	try
	{
		testService.adaugare_activitate("aa", "aa", "", -1);
	}
	catch (ExceptieValidator& ev)
	{
		assert(ev.get_mesaje_eroare() == "Titlul activitatii trebuie sa aiba cel putin 3 caractere.\nTipul activitatii trebuie sa aiba cel putin 1 caracter.\nDescrierea activitatii trebuie sa aiba cel putin 3 caractere.\nDurata activitatii trebuie sa fie mai mare ca si 0.\n");
	}
}


void test_actualizare_repo()
{
	RepoActivitati test;
	Activitate activitate1{ "Fotbal","Meci de fotbal", "sport", 90 };
	Activitate activitate2{ "Stand-up","Show de comedie","comedie", 60 };
	Activitate activitate3{ "Fotbal","Meci de fotbal","sport", 120 };
	Activitate activitate4{ "Baschet","Meci de baschet","sport", 40 };
	test.adaugare(activitate1);
	test.adaugare(activitate2);
	test.actualizare(activitate3);
	try
	{
		test.actualizare(activitate4);
	}
	catch (ExceptieRepo) {
		assert(true);
	}
}

void test_actualizare_service()
{
	RepoActivitati testR;
	ValidatorActivitate testV;
	Lista_activitati_curente testL;
	StocareActivitati testService{ testR,testL,testV };
	testService.adaugare_activitate("Fotbal", "Meci de fotbal", "sport", 90);
	testService.actualizare_activitate("Fotbal", "Meci de fotbal", "sport", 120);
	auto activitate_gasita = testService.cautare_activitate("Fotbal", "Meci de fotbal");
	assert(activitate_gasita.getDurata() == 120);
}

void test_stergere_repo()
{
	RepoActivitati test;
	try
	{
		test.stergere("Fotbal", "Meci de fotbal");
	}
	catch (ExceptieRepo)
	{
		assert(true);
	}
	Activitate activitate1{ "Fotbal","Meci de fotbal", "sport", 90 };
	Activitate activitate2{ "Stand-up","Show de comedie","comedie", 60 };
	Activitate activitate3{ "Baschet", "Meci de baschet", "sport", 40 };
	test.adaugare(activitate1);
	test.adaugare(activitate2);
	test.adaugare(activitate3);
	assert(test.getAll().size() == 3);
	test.stergere("Baschet", "Meci de baschet");
	assert(test.getAll().size() == 2);
	try
	{
		test.stergere("Volei", "Mecide de volei");
	}
	catch (const ExceptieRepo&)
	{
		assert(true);
	}
}

void test_stergere_service()
{
	RepoActivitati testR;
	ValidatorActivitate testV;
	Lista_activitati_curente testL;
	StocareActivitati testService{ testR,testL,testV };
	testService.adaugare_activitate("Fotbal", "Meci de fotbal", "sport", 90);
	testService.adaugare_activitate("Stand-up", "Show de comedie", "comedie", 609);
	testService.stergere_activitate("Fotbal", "Meci de fotbal");
	assert(testService.getAll().size() == 1);
}

void test_gaseste_repo()
{
	RepoActivitati test;
	Activitate activitate1{ "Fotbal","Meci de fotbal", "sport", 90 };
	Activitate activitate2{ "Stand-up","Show de comedie","comedie", 60 };
	Activitate actvitate3{ "Baschet", "Meci de baschet", "sport", 40 };
	test.adaugare(activitate1);
	test.adaugare(activitate2);

	assert(test.exista(activitate1));
	assert(!test.exista(actvitate3));

	auto activitate_gasita = test.gaseste_activitate("Fotbal", "Meci de fotbal");
	assert(activitate_gasita.getDurata() == 90);
	assert(activitate_gasita.getTip() == "sport");
	try
	{
		test.gaseste_activitate("Volei", "Meci de volei");
	}
	catch (ExceptieRepo& ev)
	{
		assert(ev.getMesajeEroare() == "Activitatea cu titlul si descrierea introdusa nu exista in lista!\n");
	}
}


void test_cautare_service()
{
	RepoActivitati testR;
	ValidatorActivitate testV;
	Lista_activitati_curente testL;
	StocareActivitati testService{ testR,testL,testV };
	testService.adaugare_activitate("Fotbal", "Meci de fotbal", "sport", 90);
	auto activitate_gasita = testService.cautare_activitate("Fotbal", "Meci de fotbal");
	assert(activitate_gasita.getDurata() == 90);
	assert(activitate_gasita.getTip() == "sport");
}

void test_filtrare()
{
	RepoActivitati testR;
	ValidatorActivitate testV;
	Lista_activitati_curente testL;
	StocareActivitati testService{ testR,testL,testV };

	testService.adaugare_activitate("Fotbal", "Meci de fotbal", "sport", 90);
	testService.adaugare_activitate("Stand-up", "Show de comedie", "comedie", 60);
	testService.adaugare_activitate("Fotbal", "Meci de fotbal din nou", "sport", 120);
	testService.adaugare_activitate("Stand-up", "Show de comedie din nou", "comedie", 60);

	auto lista_filtrata_titlu = testService.filtrare_titlu("Fotbal");
	assert(lista_filtrata_titlu.size() == 2);
	lista_filtrata_titlu = testService.filtrare_titlu("Fobal");
	assert(lista_filtrata_titlu.size() == 0);

	auto lista_filtrata_durata = testService.filtrare_durata(60);
	assert(lista_filtrata_durata.size() == 2);
	lista_filtrata_durata = testService.filtrare_durata(100);
	assert(lista_filtrata_durata.size() == 0);
}

void test_sortare()
{
	RepoActivitati testR;
	ValidatorActivitate testV;
	Lista_activitati_curente testL;
	StocareActivitati testService{ testR,testL,testV };

	testService.adaugare_activitate("Fotbal", "Meci de fotbal", "sport", 90);
	testService.adaugare_activitate("Stand-up", "Show de comedie", "comedie", 60);
	testService.adaugare_activitate("Fotbal", "Meci de fotbal din nou", "sport", 120);
	testService.adaugare_activitate("Stand-up", "Show de comedie din nou", "comedie", 70);

	auto lista_sortata = testService.sortare_titlu();
	assert(lista_sortata[1].getTitlu() == "Fotbal");
	assert(lista_sortata[3].getTitlu() == "Stand-up");

	lista_sortata = testService.sortare_descriere();
	assert(lista_sortata[0].getDescriere() == "Meci de fotbal");
	assert(lista_sortata[3].getDescriere() == "Show de comedie din nou");

	lista_sortata = testService.sortare_durata_tip();
	assert(lista_sortata[0].getTitlu() == "Stand-up");
	assert(lista_sortata[3].getTitlu() == "Fotbal");
}

void test_adaugare_lista_repo()
{
	RepoActivitati testR;
	ValidatorActivitate testV;
	Lista_activitati_curente testL;
	StocareActivitati testService{ testR,testL,testV };
	Activitate activitate1{ "Fotbal","Meci de fotbal", "sport", 90 };
	Activitate activitate2{ "Stand-up","Show de comedie","comedie", 60 };
	Activitate activitate3{ "Fotbal","Meci de fotbal din nou", "sport din nou", 90 };
	testR.adaugare(activitate1);
	testR.adaugare(activitate2);
	testService.adaugare_activitate_in_lista("Fotbal", "Meci de fotbal");
	testService.adaugare_activitate_in_lista("Stand-up", "Show de comedie");
	try
	{
		testService.adaugare_activitate_in_lista("Fotbal", "Meci de fotbal din nou");
	}
	catch (ExceptieRepo)
	{
		assert(true);
	}
}

void test_golire_lista_repo()
{
	RepoActivitati testR;
	ValidatorActivitate testV;
	Lista_activitati_curente testL;
	StocareActivitati testService{ testR,testL,testV };
	try
	{
		testR.stergere("Fotbal", "Meci de fotbal din nou");
	}
	catch (ExceptieRepo)
	{
		assert(true);
	}
	Activitate activitate1{ "Fotbal","Meci de fotbal", "sport", 90 };
	Activitate activitate2{ "Stand-up","Show de comedie","comedie", 60 };
	testR.adaugare(activitate1);
	testR.adaugare(activitate2);
	testService.adaugare_activitate_in_lista("Fotbal", "Meci de fotbal");
	testService.adaugare_activitate_in_lista("Stand-up", "Show de comedie");
	assert(testService.getAll_lista().size() == 2);
	testService.golire_lista();
	assert(testService.getAll_lista().size() == 0);
}

void test_generare_lista_repo()
{
	RepoActivitati testR;
	ValidatorActivitate testV;
	Lista_activitati_curente testL;
	StocareActivitati testService{ testR,testL,testV };
	Activitate activitate1{ "Fotbal","Meci de fotbal", "sport", 90 };
	Activitate activitate2{ "Stand-up","Show de comedie","comedie", 60 };
	Activitate activitate3{ "Fotbal","Meci de fotbal din nou", "sport din nou", 90 };
	testR.adaugare(activitate1);
	testR.adaugare(activitate2);
	testR.adaugare(activitate3);
	assert(testService.getAll_lista().size() == 0);
	testService.genereaza_lista(2);
	assert(testService.getAll_lista().size() == 2);
}

void test_adaugare_lista_service()
{
	vector<Activitate>carti;
	RepoActivitati testR;
	ValidatorActivitate testV;
	Lista_activitati_curente testL;
	StocareActivitati testService{ testR,testL,testV };
	testService.adaugare_activitate("Fotbal", "Meci de fotbal", "sport", 90);
	testService.adaugare_activitate("Stand-up", "Show de comedie", "comedie", 60);
	testService.adaugare_activitate_in_lista("Fotbal", "Meci de fotbal");
	testService.adaugare_activitate_in_lista("Stand-up", "Show de comedie");
	assert(testService.getAll_lista().size() == 2);
}

void test_golire_lista_service()
{
	vector<Activitate>lista_activitati;
	RepoActivitati testR;
	ValidatorActivitate testV;
	Lista_activitati_curente testL;
	StocareActivitati testService{ testR,testL,testV };
	testService.adaugare_activitate("Fotbal", "Meci de fotbal", "sport", 90);
	testService.adaugare_activitate("Stand-up", "Show de comedie", "comedie", 60);
	testService.adaugare_activitate_in_lista("Fotbal", "Meci de fotbal");
	testService.adaugare_activitate_in_lista("Stand-up", "Show de comedie");
	assert(testService.getAll_lista().size() == 2);
	testService.golire_lista();
	assert(testService.getAll_lista().size() == 0);
}

void test_generare_lista_service()
{
	vector<Activitate>lista_activitati;
	RepoActivitati testR;
	ValidatorActivitate testV;
	Lista_activitati_curente testL;
	StocareActivitati testService{ testR,testL,testV };
	testService.adaugare_activitate("Fotbal", "Meci de fotbal", "sport", 90);
	testService.adaugare_activitate("Stand-up", "Show de comedie", "comedie", 60);
	testService.adaugare_activitate("Fotbal", "Meci de fotbal din nou", "sport", 120);
	testService.genereaza_lista(3);
	assert(testService.get_marime_lista() == 3);
}

void test_get_marime_lista()
{
	vector<Activitate>lista_activitati;
	RepoActivitati testR;
	ValidatorActivitate testV;
	Lista_activitati_curente testL;
	StocareActivitati testService{ testR,testL,testV };
	testService.adaugare_activitate("Fotbal", "Meci de fotbal", "sport", 90);
	testService.adaugare_activitate("Stand-up", "Show de comedie", "comedie", 60);
	testService.adaugare_activitate("Fotbal", "Meci de fotbal din nou", "sport", 120);
	testService.adaugare_activitate_in_lista("Fotbal", "Meci de fotbal");
	testService.adaugare_activitate_in_lista("Stand-up", "Show de comedie");
	testService.adaugare_activitate_in_lista("Fotbal", "Meci de fotbal din nou");
	assert(testService.get_marime_lista() == 3);
}
void test_cerinta_noua()
{
	vector<Activitate>lista_activitati;
	RepoActivitati testR;
	ValidatorActivitate testV;
	Lista_activitati_curente testL;
	StocareActivitati testService{ testR,testL,testV };
	auto dict1 = testService.cerinta_noua();
	assert(dict1.empty());
	testService.adaugare_activitate("Fotbal", "Meci de fotbal", "sport", 90);
	testService.adaugare_activitate("Baschet", "Meci de baschet", "sport", 40);
	auto dict2 = testService.cerinta_noua();
	assert(dict2.size() == 1);
	assert(dict2["tip"].get_cnt() == 0);
}

void test_dto()
{
	DTO dto1;
	assert(dto1.get_tip() == "");

	DTO dto2("nimic", 5);
	assert(dto2.get_tip() == "nimic");
	assert(dto2.get_cnt() == 5);

	DTO dto3("nimic", 5);
	assert(dto3.get_tip() == "nimic");
	assert(dto3.get_cnt() == 5);

	DTO dto4("nimic", 5);
	dto4.increment_cnt();
	assert(dto4.get_cnt() == 6);

	DTO dto5("nimic", 5);
	dto5.increment_cnt();
	dto5.increment_cnt();
	assert(dto5.get_cnt() == 7);

	DTO dto6;
	dto6.increment_cnt();

	DTO dto7;
	dto7.increment_cnt();
	dto7 = DTO("nimic", 5);
	assert(dto7.get_tip() == "nimic");
	assert(dto7.get_cnt() == 5);

}

void test_undo()
{
	RepoActivitati testR;
	ValidatorActivitate testV;
	Lista_activitati_curente testL;
	StocareActivitati testService{ testR,testL,testV };
	testService.adaugare_activitate("Fotbal", "Meci de fotbal", "sport", 90);
	testService.adaugare_activitate("Stand-up", "Show de comedie", "comedie", 60);
	testService.adaugare_activitate("Fotbal", "Meci de fotbal din nou", "sport", 120);
	assert(testService.getAll().size() == 3);

	testService.stergere_activitate("Fotbal", "Meci de fotbal");
	assert(testService.getAll().size() == 2);
	testService.undo();
	assert(testService.getAll().size() == 3);

	testService.undo();
	assert(testService.getAll().size() == 2);

	Activitate activitate1 = testService.cautare_activitate("Stand-up", "Show de comedie");
	assert(activitate1.getTip() == "comedie");
	testService.actualizare_activitate("Stand-up", "Show de comedie", "umor", 70);
	Activitate activitate2 = testService.cautare_activitate("Stand-up", "Show de comedie");
	assert(activitate2.getTip() == "umor");
	testService.undo();
	Activitate activitate3 = testService.cautare_activitate("Stand-up", "Show de comedie");
	assert(activitate3.getTip() == "comedie");
	testService.undo();
	testService.undo();

	assert(testService.undo() == 1);
}

void test_validare_fisier()
{
	RepoActivitati testR;
	ValidatorActivitate testV;
	Lista_activitati_curente testL;
	StocareActivitati testService{ testR,testL,testV };
	try
	{
		testService.export_lista("csv");
	}
	catch (ExceptieValidator& ev)
	{
		assert(ev.get_mesaje_eroare() == "Numele fisierului trebuie sa aiba cel putin 4 caractere.\n");
	}
	try
	{
		testService.export_lista("cos.txt");
	}
	catch (ExceptieValidator& ev)
	{
		assert(ev.get_mesaje_eroare() == "Numele fisierului nu are extensia csv sau html.\n\n");
	}
}

void test_export_cos_csv()
{
	RepoActivitati testR;
	ValidatorActivitate testV;
	Lista_activitati_curente testL;
	StocareActivitati testService{ testR,testL,testV };
	testService.adaugare_activitate("Fotbal", "Meci de fotbal", "sport", 90);
	testService.adaugare_activitate("Stand-up", "Show de comedie", "comedie", 60);
	testService.adaugare_activitate("Fotbal", "Meci de fotbal din nou", "sport", 120);

	vector <Activitate> activitati;
	Activitate activitate1{ "Fotbal","Meci de fotbal", "sport", 90 };
	Activitate activitate2{ "Stand-up","Show de comedie","comedie", 60 };
	Activitate activitate3{ "Baschet", "Meci de baschet", "sport", 40 };
	activitati.push_back(activitate1);
	activitati.push_back(activitate2);
	activitati.push_back(activitate3);

	testL.adaugare_activitate_in_lista(activitate1);
	testL.adaugare_activitate_in_lista(activitate2);
	testL.adaugare_activitate_in_lista(activitate3);

	string nume_fisier = "test.csv";
	testService.export_lista(nume_fisier);
	/*std::ifstream in(nume_fisier);
	string linie, delimitator = "|";
	size_t pozitie, numar_linie = 0;
	vector <string> cuvinte;
	getline(in, linie);
	while (getline(in, linie))
	{
		cuvinte.erase(cuvinte.begin(), cuvinte.end());
		while ((pozitie = linie.find(delimitator)) != linie.npos)
		{
			string cuvant = linie.substr(0, pozitie);
			cuvinte.push_back(cuvant);
			linie.erase(linie.begin(), linie.begin() + pozitie + delimitator.length());
		}
		cuvinte.push_back(linie);
		assert(cuvinte[0] == activitati[numar_linie].getTitlu());
		assert(cuvinte[1] == activitati[numar_linie].getDescriere());
		assert(cuvinte[2] == activitati[numar_linie].getTip());
		numar_linie++;
	}
	in.close();*/
	remove("test.csv");
}

void test_export_cos_html()
{
	RepoActivitati testR;
	ValidatorActivitate testV;
	Lista_activitati_curente testL;
	StocareActivitati testService{ testR,testL,testV };
	testService.adaugare_activitate("Fotbal", "Meci de fotbal", "sport", 90);
	testService.adaugare_activitate("Stand-up", "Show de comedie", "comedie", 60);
	testService.adaugare_activitate("Fotbal", "Meci de fotbal din nou", "sport", 120);

	vector <Activitate> activitati;
	Activitate activitate1{ "Fotbal","Meci de fotbal", "sport", 90 };
	Activitate activitate2{ "Stand-up","Show de comedie","comedie", 60 };
	Activitate activitate3{ "Baschet", "Meci de baschet", "sport", 40 };
	activitati.push_back(activitate1);
	activitati.push_back(activitate2);
	activitati.push_back(activitate3);

	testL.adaugare_activitate_in_lista(activitate1);
	testL.adaugare_activitate_in_lista(activitate2);
	testL.adaugare_activitate_in_lista(activitate3);

	string nume_fisier = "test.html";
	testService.export_lista(nume_fisier);
	/*std::ifstream in(nume_fisier);
	string linie, delimitator = "|";
	size_t pozitie, numar_linie = 0;
	vector <string> cuvinte;
	getline(in, linie);
	while (getline(in, linie))
	{
		cuvinte.erase(cuvinte.begin(), cuvinte.end());
		while ((pozitie = linie.find(delimitator)) != linie.npos)
		{
			string cuvant = linie.substr(0, pozitie);
			cuvinte.push_back(cuvant);
			linie.erase(linie.begin(), linie.begin() + pozitie + delimitator.length());
		}
		cuvinte.push_back(linie);
		assert(cuvinte[0] == activitati[numar_linie].getTitlu());
		assert(cuvinte[1] == activitati[numar_linie].getDescriere());
		assert(cuvinte[2] == activitati[numar_linie].getTip());
		numar_linie++;
	}
	in.close();*/
	remove("test.html");
}