#pragma once
#include <string>
#include <iostream>

using namespace std;

class Activitate
{
private:
	string titlu;
	string descriere;
	string tip;
	int durata;

public:
	Activitate() = default;
	Activitate(const string titlu, string descriere, string tip, int durata) :titlu{ titlu }, descriere{ descriere }, tip{ tip }, durata{ durata } {}
	Activitate(const Activitate& ot) :titlu{ ot.titlu }, descriere{ ot.descriere }, tip{ ot.tip }, durata{ ot.durata }
	{
		//cout << "\nConstructorul de copiere a fost apelat.\n";
	}

	string getTitlu() const;
	string getDescriere() const;
	string getTip() const;
	int getDurata() const noexcept;

	void setTitlu(string titluNou);
	void setDescriere(string descriereNoua);
	void setTip(string tipNou);
	void setDurata(int durataNoua) noexcept;
};
/*
Compara dupa tip si durata
returneaza true daca a1.durata e mai mic decat c2.durata sau c1.durata = c2.durata si c1.tip < c2.tip
*/
bool cmpTipDurata(const Activitate& a1, const Activitate& a2);

/*
Compara dupa titlu
returneaza true daca a1.titlu e mai mic decat a2.titlu
*/
bool cmpTitlu(const Activitate& a1, const Activitate& a2);

/*
Compara dupa descriere
returneaza true daca a1.descriere e mai mic decat a2.descriere
*/
bool cmpDescriere(const Activitate& a1, const Activitate& a2);