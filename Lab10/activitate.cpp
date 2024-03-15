#pragma once
#include "activitate.h"

string Activitate::getTitlu() const {
	return this->titlu;
}

string Activitate::getDescriere() const {
	return this->descriere;
}

string Activitate::getTip() const {
	return this->tip;
}

int Activitate::getDurata() const noexcept {
	return this->durata;
}


void Activitate::setTitlu(string titluNou)
{
	this->titlu = titluNou;
}

void Activitate::setTip(string tipNou)
{
	this->tip = tipNou;
}

void Activitate::setDescriere(string descriereNoua)
{
	this->descriere = descriereNoua;
}

void Activitate::setDurata(int durataNoua) noexcept
{
	this->durata = durataNoua;
}

bool cmpTipDurata(const Activitate& a1, const Activitate& a2)
{
	if (a1.getDurata() < a2.getDurata())
		return true;
	if (a1.getDurata() == a2.getDurata() && a1.getTip() <= a2.getTip())
		return true;
	return false;
}

bool cmpTitlu(const Activitate& a1, const Activitate& a2)
{
	return a1.getTitlu() < a2.getTitlu();
}

bool cmpDescriere(const Activitate& a1, const Activitate& a2)
{
	return a1.getDescriere() < a2.getDescriere();
}