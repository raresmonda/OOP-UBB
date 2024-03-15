#include "ui.h"
#include <iostream>

using namespace std;

void consola::Meniu()
{
	cout << "1.Afisare activitati." << "\n";
	cout << "2.Adaugare activitate." << "\n";
	cout << "3.Modificare activitate." << "\n";
	cout << "4.Stergere activitate." << "\n";
	cout << "5.Cautare activitate." << "\n";
	cout << "6.Filtrare activitati." << "\n";
	cout << "7.Sortare activitati." << "\n";
	cout << "8.Afisare activitati din lista de activitati curente." << "\n";
	cout << "9.Adaugare activitate in lista de activitati curente." << "\n";
	cout << "10.Generare lista de activitati curente." << "\n";
	cout << "11.Golire lista de activitati curente." << "\n";
	cout << "12.Afisare cate activitati din fiecare tip exista." << "\n";
	cout << "13.Undo" << "\n";
	cout << "14.Export cos in fisier CSV sau HTML." << "\n";
	cout << "15.Iesire." << "\n";
}

void consola::afisare_activitati()
{
		auto activitati = service.getAll();
		if (activitati.size() == 0)
			cout << "\nNu exista activitati.\n";
		else
			cout << "\nActivitatile existente sunt: \n";
		for (const auto& Activitate : activitati)
			cout << "Titlu: " << Activitate.getTitlu() << " | Descriere: " << Activitate.getDescriere() << " | Tip: " << Activitate.getTip() << " | Durata: " << Activitate.getDurata() << "\n";
		cout << "\n";
}

void consola::adaugare_ui()
{

	string titlu, tip, descriere;
	int durata;
	cout << "Titlu: ";
	getline(cin >> ws, titlu);
	cout << "Descriere: ";
	getline(cin >> ws, descriere);
	cout << "Tip: ";
	getline(cin >> ws, tip);
	cout << "Durata: ";
	cin >> durata;

	try
	{
		service.adaugare_activitate(titlu, descriere, tip, durata);
		cout << "\nActivitate adaugata cu succes!\n";
	}
	catch (ExceptieValidator& ev)
	{
		cout << ev.get_mesaje_eroare() << "\n";
	}
	catch (ExceptieRepo& ev)
	{
		cout << ev.getMesajeEroare() << "\n";
	}

}

void consola::modificare_ui()
{
	string titlu, tip, descriere;
	int durata;
	cout << "Titlul activitatii: ";
	getline(cin >> ws, titlu);
	cout << "Descrierea activitatii: ";
	getline(cin >> ws, descriere);
	cout << "Modificare tip: ";
	getline(cin >> ws, tip);
	cout << "Modificare durata: ";
	cin >> durata;
	try
	{
		service.actualizare_activitate(titlu, descriere, tip, durata);
		cout << "\nActivitate modificata cu succes!\n";
	}
	catch (ExceptieValidator& ev)
	{
		cout << ev.get_mesaje_eroare() << "\n";
	}
	catch (ExceptieRepo& ev)
	{
		cout << ev.getMesajeEroare() << "\n";

	}

}

void consola::stergere_ui()
{
	string titlu, descriere;
	cout << "Titlul activitatii: ";
	getline(cin >> ws, titlu);
	cout << "Descrierea activitatii: ";
	getline(cin >> ws, descriere);
	try
	{
		service.stergere_activitate(titlu, descriere);
		cout << "\nActivitate eliminata cu succes!\n";
	}
	catch (ExceptieValidator& ev)
	{
		cout << ev.get_mesaje_eroare() << "\n";
	}
	catch (ExceptieRepo& ev)
	{
		cout << ev.getMesajeEroare() << "\n";
	}
}

void consola::cautare_ui()
{
	string titlu, descriere;
	cout << "Titlul activitatii: ";
	getline(cin >> ws, titlu);
	cout << "Descrierea activitatii: ";
	getline(cin >> ws, descriere);

	try
	{
		Activitate c = service.cautare_activitate(titlu, descriere);
		cout << "\nActivitatea cautata este: \n";
		cout << "Titlu: " << c.getTitlu() << " | Descriere: " << c.getDescriere() << " | Tip: " << c.getTip() << " | Durata: " << c.getDurata() << "\n\n";
	}
	catch (ExceptieRepo& ev)
	{
		cout << ev.getMesajeEroare() << "\n";
	}
	catch (ExceptieValidator& ev)
	{
		cout << ev.get_mesaje_eroare() << "\n";
	}
}


void consola::filtrare_ui()
{
	string titlu;
	int durata;
	cout << "Dupa ce doriti sa filtrati?\n 1. Titlu\n 2.Durata ";
	int comanda;
	cin >> comanda;
	if (comanda == 1)
	{
		cout << "Titlul: ";
		getline(cin >> ws, titlu);
		auto lista_activitati = service.filtrare_titlu(titlu);
		if (lista_activitati.size() == 0)
			cout << "Nu exista activitati." << endl;
		else
			for (auto activitate : lista_activitati)
			{
				cout << "Titlu: " << activitate.getTitlu() << " | Descriere: " << activitate.getDescriere() << " | Tip: " << activitate.getTip() << " | Durata: " << activitate.getDurata() << "\n";
			}
	}
	else if (comanda == 2)
	{
		cout << "Durata: ";
		cin >> durata;
		auto lista_activitati = service.filtrare_durata(durata);
		if (lista_activitati.size() == 0)
			cout << "Nu exista activitati." << "\n";
		else
			for (auto activitate : lista_activitati)
			{
				cout << "Titlu: " << activitate.getTitlu() << " | Descriere: " << activitate.getDescriere() << " | Tip: " << activitate.getTip() << " | Durata: " << activitate.getDurata() << "\n";
			}
	}
	else
	{
		cout << "Optiune invalida.\n";
	}
}

void consola::sortare_ui()
{
	cout << "Dupa ce doriti sa sortati?\n 1. Titlu\n 2. Descriere\n 3.Tip + durata ";
	int comanda;
	cin >> comanda;
	if (comanda == 1)
	{
		auto lista_activitati = service.sortare_titlu();
		if (lista_activitati.size() == 0)
			cout << "Nu exista activitati." << endl;
		else
			for (auto activitate : lista_activitati)
			{
				cout << "Titlu: " << activitate.getTitlu() << " | Descriere: " << activitate.getDescriere() << " | Tip: " << activitate.getTip() << " | Durata: " << activitate.getDurata() << "\n";
			}
	}
	else if (comanda == 2)
	{
		auto lista_activitati = service.sortare_descriere();
		if (lista_activitati.size() == 0)
			cout << "Nu exista activitati." << endl;
		else
			for (auto activitate : lista_activitati)
			{
				cout << "Titlu: " << activitate.getTitlu() << " | Descriere: " << activitate.getDescriere() << " | Tip: " << activitate.getTip() << " | Durata: " << activitate.getDurata() << "\n";
			}
	}
	else if (comanda == 3)
	{
		auto lista_activitati = service.sortare_durata_tip();
		if (lista_activitati.size() == 0)
			cout << "Nu exista activitati." << endl;
		else
			for (auto activitate : lista_activitati)
			{
				cout << "Titlu: " << activitate.getTitlu() << " | Descriere: " << activitate.getDescriere() << " | Tip: " << activitate.getTip() << " | Durata: " << activitate.getDurata() << "\n";
			}
	}
	else
		cout << "Optiune invalida\n";
}

void consola::afisare_lista() {
	auto lista_activitati = service.getAll_lista();
	if (lista_activitati.size() == 0)
		cout << "\nLista de activitati curente este goala.\n";
	else
		for (auto activitate : lista_activitati)
		{
			cout << "Titlu: " << activitate.getTitlu() << " | Descriere: " << activitate.getDescriere() << " | Tip: " << activitate.getTip() << " | Durata: " << activitate.getDurata() << "\n";
		}
	cout << "\n";
}

void consola::adaugare_in_lista_ui()
{
	size_t cnt_activitati;
	auto activitati = service.getAll();
	if (activitati.size() == 0)
	{
		cout << "\nLista de activitati este goala momentan!\n\n";
		cnt_activitati = service.get_marime_lista();
		cout << "\nIn lista de activitati curente se afla " << cnt_activitati << " activitati.\n\n";
	}
	else
	{
		string titlu, descriere;
		cout << "Titlu: ";
		getline(cin >> ws, titlu);
		cout << "Descriere: ";
		getline(cin >> ws, descriere);

		try
		{
			service.adaugare_activitate_in_lista(titlu, descriere);
			cnt_activitati = service.get_marime_lista();
			cout << "\nIn lista de activitati curente se afla " << cnt_activitati << " activitati.\n\n";
		}
		catch (ExceptieRepo& er)
		{
			cout << er.getMesajeEroare();
		}
	}
}

void consola::generare_lista_ui()
{
	size_t cnt_activitati;
	auto activitati = service.getAll();
	if (activitati.size() == 0)
	{
		cout << "\nLista de activitati este goala momentan!\n\n";
		cnt_activitati = service.get_marime_lista();
		cout << "\nIn lista de activitati curente se afla " << cnt_activitati << " activitati.\n\n";
	}
	else
	{
		int ok = 1;
		string nr;
		cout << "Introduceti numarul dorit: ";
		getline(cin >> ws, nr);
		for (char const& c : nr)
		{
			if (std::isdigit(c) == 0)
			{
				ok = 0;
				break;
			}
		}
		if (ok == 0)
			cout << "Trebuie sa introduceti un numar pozitiv!" << endl;
		else
		{
			try
			{
				const int numar = stoi(nr);
				if (numar > activitati.size())
				{
					cout << "Numarul dorit depaseste lungimea listei!" << endl;
					return;
				}
				service.genereaza_lista(numar);
				cnt_activitati = service.get_marime_lista();
				cout << "\nIn lista de activitati curente se afla " << cnt_activitati << " activitati.\n\n";
			}
			catch (ExceptieValidator& ev)
			{
				cout << ev.get_mesaje_eroare();
			}
		}
	}
}

void consola::golire_lista_ui()
{
	size_t cnt_activitati;
	auto lista = service.getAll_lista();
	if (lista.size() == 0)
	{
		cout << "Lisat de activitati curente este deja goala!\n";
		return;
	}
	service.golire_lista();
	cnt_activitati = service.get_marime_lista();
	cout << "\nIn lista de activitati curente se afla " << cnt_activitati << " activitati.\n\n";
}

void consola::cerinta_noua()
{
	map<string, DTO> dict = service.cerinta_noua();
	for (map<string, DTO>::iterator it = dict.begin(); it != dict.end(); ++it)
	{
		cout << it->second.get_tip() << " " << it->second.get_cnt() << "\n";
	}
}

void consola::export_lista_ui()
{
	string fisier;
	cout << "\nDati numele fisierului: ";
	getline(cin >> ws, fisier);
	try
	{
		service.export_lista(fisier);
		cout << "Export efectuat cu succes!\n\n";
	}
	catch (ExceptieValidator& ve)
	{
		cout << ve.get_mesaje_eroare();
	}
}

void consola::undo_ui()
{
	if (service.undo() == 1)
		cout << "\nNu se mai poate face undo!\n\n";
	else
		cout << "\nUndo realizat cu succes!\n\n";
}

void consola::run()
{
	int comanda, ok = 1;
	while (ok)
	{
		Meniu();
		cout << "Introduceti comanda: ";
		cin >> comanda;
		switch (comanda)
		{
		case 1:
			afisare_activitati();
			break;
		case 2:
			adaugare_ui();
			break;
		case 3:
			modificare_ui();
			break;
		case 4:
			stergere_ui();
			break;
		case 5:
			cautare_ui();
			break;
		case 6:
			filtrare_ui();
			break;
		case 7:
			sortare_ui();
			break;
		case 8:
			afisare_lista();
			break;
		case 9:
			adaugare_in_lista_ui();
			break;
		case 10:
			generare_lista_ui();
			break;
		case 11:
			golire_lista_ui();
			break;
		case 12:
			cerinta_noua();
			break;
		case 13:
			undo_ui();
			break;
		case 14:
			export_lista_ui();
			break;
		case 15:
			ok = 0;
			break;
		default:
			break;
		}
	}
}