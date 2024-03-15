#pragma once
#include <QtWidgets/QApplication>
#define _CRTDBG_MAP_ALLOC
#include "ui.h"
#include "activitate.h"
#include <iostream>
#include <stdlib.h>
#include <crtdbg.h>
#include "teste.h"
#include "my_gui.h"

using namespace std;

int main(int argc, char* argv[])
{
	testAll();
	QApplication a(argc, argv);
	string filename = "activitati.txt";
	RepoFile repo{ filename };
	ValidatorActivitate val;
	Lista_activitati_curente lista;
	StocareActivitati service{ repo, lista, val };
	MyGUI gui{ service };
	//gui.show();

	return a.exec();
}
