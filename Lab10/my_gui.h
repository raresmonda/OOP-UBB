#pragma once
#include <QtWidgets/QApplication>
#include <QTableWidget>
#include <QTableView>
#include <QHeaderView>
#include <QLabel>
#include <QPushButton>
#include <QHBoxLayout>
#include <QFormLayout>
#include <QLineEdit>
#include <QMessageBox>
#include <QGroupBox>
#include <QListWidget>
#include <QRadioButton>
#include "service.h"
#include <vector>
#include <algorithm>
#include <set>

using namespace std;

class MyGUI : public QWidget
{
private:
	StocareActivitati& srv;

	QLabel* lbl_titlu = new QLabel{ "Titlul activitatii: " };
	QLabel* lbl_descriere = new QLabel{ "Descrierea activitatii: " };
	QLabel* lbl_tip = new QLabel{ "Tipul activitatii: " };
	QLabel* lbl_durata = new QLabel{ "Durata activitatii: " };
	QLabel* lbl_nr = new QLabel{ "Numarul de activitati de adaugat in lista de activitati curente: " };
	QLabel* lbl_nume_fisier = new QLabel{ "Numele fisierului pentru export: " };
	QLabel* op_lista = new QLabel{ "\nOPERATII CU LISTA DE ACTIVITATI\n" };
	QLabel* op_lista_activitati_curente = new QLabel{ "\nOPERATII CU LISTA DE ACTIVITATI CURENTE\n" };
	QLabel* tabel1 = new QLabel{ "LISTA DE ACTIVITATI" };
	QLabel* tabel2 = new QLabel{ "LISTA DE ACTIVITATI CURENTE" };
	QLabel* formular = new QLabel{ "FORMULAR\n" };

	QLineEdit* editare_titlu;
	QLineEdit* editare_descriere;
	QLineEdit* editare_tip;
	QLineEdit* editare_durata;
	QLineEdit* editare_nr;
	QLineEdit* editare_nume_fisier;

	QPushButton* btn_adaugare;
	QPushButton* btn_actualizare;
	QPushButton* btn_stergere;
	QPushButton* btn_cautare;
	QPushButton* btn_filtrare_titlu;
	QPushButton* btn_filtrare_durata;
	QPushButton* btn_undo;
	QPushButton* btn_cnt_tipuri;

	QGroupBox* groupBoxSortare = new QGroupBox(tr("Tip sortare"));
	QRadioButton* radio_sortare_titlu = new QRadioButton(QString::fromStdString("Titlu"));
	QRadioButton* radio_sortare_descriere = new QRadioButton(QString::fromStdString("Descriere"));
	QRadioButton* radio_sortare_tip_durata = new QRadioButton(QString::fromStdString("Tipul activitatii + Durata"));
	QPushButton* btn_sortare;

	// ----------------------- lista activitati curente ----------------------- //
	QPushButton* btn_adaugare_lista_activitati_curente;
	QPushButton* btn_golire_lista_activitati_curente;
	QPushButton* btn_generare_lista_activitati_curente;
	QPushButton* btn_export_lista_activitati_curente;
	QLabel* lblTitluListaActivitatiCurente = new QLabel{ "Titlul activitatii: " };
	QLabel* lblDescriereListaActivitatiCurente = new QLabel{ "Descrierea activitatii: " };
	QLabel* lblNumarListaActivitatiCurente = new QLabel{ "Numarul de activitati de adaugat: " };
	QLabel* lblFisierListaActivitatiCurente = new QLabel{ "Numele fisierului pentru export:" };

	QTableWidget* tabel_activitati;
	QTableWidget* tabel_lista_activitati_curente;
	QListWidget* lista_lista_activitati_curente = new QListWidget;

	QWidget* Report = new QWidget;
	QVBoxLayout* typesLayout = new QVBoxLayout{};
	//QPushButton* reloadTypes = new QPushButton{ "Reincarcare genuri." };

	void initializeGUIComponents();
	void conectare_butoane();
	void preluare_date_din_fisier(vector<Activitate> activitati);
	void incarcare_lista_activitati_curente(vector <Activitate> lista_activitati_curente);

public:
	MyGUI(StocareActivitati& Srv) : srv{ Srv }
	{
		initializeGUIComponents();
		conectare_butoane();
		preluare_date_din_fisier(srv.getAll());
		incarcare_lista_activitati_curente(srv.getAll_lista());
	}
	void gui_adaugare();
	void gui_actualizare();
	void gui_stergere();
	void gui_cautare();
	void gui_filtrare_titlu();
	void gui_filtrare_durata();
	void gui_sortare();
	void gui_undo();
	void gui_cnt_tipuri();
	void gui_adaugare_lista_activitati_curente();
	void gui_generare_lista_activitati_curente();
	void gui_golire_lista_activitati_curente();
	void gui_export_lista_activitati_curente();
	void gui_raport_tipuri();
	void clearLayout(QLayout* layout);
};