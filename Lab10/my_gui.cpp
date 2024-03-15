#include "my_gui.h"

void MyGUI::initializeGUIComponents() {
	// main layout

	QWidget* fereastra_lista = new QWidget;

	QHBoxLayout* lyMain = new QHBoxLayout;
	fereastra_lista->setLayout(lyMain);

	// layout parte dreapta
	QWidget* right = new QWidget;
	QVBoxLayout* lyRight = new QVBoxLayout;
	right->setLayout(lyRight);

	// formular pt adaugare
	QWidget* form = new QWidget;
	QFormLayout* ly_form = new QFormLayout;
	form->setLayout(ly_form);

	btn_adaugare = new QPushButton("Adaugare activitate");
	btn_actualizare = new QPushButton("Actualizare activitate");
	btn_stergere = new QPushButton("Stergere activitate");
	btn_cautare = new QPushButton("Cautare activitate");
	btn_filtrare_titlu = new QPushButton("Filtrare activitati dupa titlu");
	btn_filtrare_durata = new QPushButton("Filtrare activitati dupa durata");
	btn_undo = new QPushButton("Undo");

	QVBoxLayout* lyRadioBoxSortare = new QVBoxLayout;
	this->groupBoxSortare->setLayout(lyRadioBoxSortare);
	lyRadioBoxSortare->addWidget(radio_sortare_titlu);
	lyRadioBoxSortare->addWidget(radio_sortare_descriere);
	lyRadioBoxSortare->addWidget(radio_sortare_tip_durata);
	btn_sortare = new QPushButton("Sortare");
	lyRadioBoxSortare->addWidget(btn_sortare);

	Report->setLayout(typesLayout);

	ly_form->addRow(op_lista);
	ly_form->addRow(btn_adaugare);
	ly_form->addRow(btn_actualizare);
	ly_form->addRow(btn_stergere);
	ly_form->addRow(btn_cautare);
	ly_form->addRow(btn_filtrare_titlu);
	ly_form->addRow(btn_filtrare_durata);
	ly_form->addRow(groupBoxSortare);
	ly_form->addRow(btn_undo);

	lyRight->addWidget(form);
	lyRight->addWidget(Report);

	// layout parte stanga
	QWidget* left = new QWidget;
	QVBoxLayout* lyLeft = new QVBoxLayout;
	left->setLayout(lyLeft);

	// tabel cu activitati
	int nr_linii = 10;
	int nr_coloane = 4;
	tabel_activitati = new QTableWidget{ nr_linii, nr_coloane };

	QStringList HeaderTabel;
	HeaderTabel << "Titlu" << "Descriere" << "Tip" << "Durata";
	tabel_activitati->setHorizontalHeaderLabels(HeaderTabel);
	tabel_activitati->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
	lyLeft->addWidget(tabel1);
	lyLeft->addWidget(tabel_activitati);

	// tabel cu cos de carti
	//tabel_cos = new QTableWidget{ nr_linii, nr_coloane };
	//tabel_cos->setHorizontalHeaderLabels(HeaderTabel);
	//tabel_cos->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
	//lyLeft->addWidget(tabel2);
	//lyLeft->addWidget(tabel_cos);

	/// adaugare left si right pe lyMain
	lyMain->addWidget(left);
	lyMain->addWidget(right);

	fereastra_lista->show();

	///////////////////////////////////////////////////////////////

	QWidget* fereastra_lista_activitati_curente = new QWidget;

	QHBoxLayout* lyMain2 = new QHBoxLayout;
	fereastra_lista_activitati_curente->setLayout(lyMain2);

	// layout parte dreapta
	QWidget* right2 = new QWidget;
	QVBoxLayout* lyRight2 = new QVBoxLayout;
	right2->setLayout(lyRight2);

	// formular pt adaugare
	QWidget* form2 = new QWidget;
	QFormLayout* ly_form2 = new QFormLayout;
	form2->setLayout(ly_form2);
	editare_titlu = new QLineEdit;
	editare_descriere = new QLineEdit;
	editare_tip = new QLineEdit;
	editare_durata = new QLineEdit;
	editare_nr = new QLineEdit;
	editare_nume_fisier = new QLineEdit;

	ly_form2->addRow(formular);
	ly_form2->addRow(lbl_titlu, editare_titlu);
	ly_form2->addRow(lbl_descriere, editare_descriere);
	ly_form2->addRow(lbl_tip, editare_tip);
	ly_form2->addRow(lbl_durata, editare_durata);
	ly_form2->addRow(lbl_nr, editare_nr);
	ly_form2->addRow(lbl_nume_fisier, editare_nume_fisier);

	btn_adaugare_lista_activitati_curente = new QPushButton("Adaugare activitate in lista de activitati curente");
	btn_golire_lista_activitati_curente = new QPushButton("Golire lista de activitati curente");
	btn_generare_lista_activitati_curente = new QPushButton("Generare lista de activitati curente");
	btn_export_lista_activitati_curente = new QPushButton("Export lista de activitati curente");
	btn_cnt_tipuri = new QPushButton("Inventar tipuri");

	ly_form2->addRow(op_lista_activitati_curente);
	ly_form2->addRow(btn_adaugare_lista_activitati_curente);
	ly_form2->addRow(btn_generare_lista_activitati_curente);
	ly_form2->addRow(btn_golire_lista_activitati_curente);
	ly_form2->addRow(btn_export_lista_activitati_curente);

	lyRight2->addWidget(form2);

	// layout parte stanga
	QWidget* left2 = new QWidget;
	QVBoxLayout* lyLeft2 = new QVBoxLayout;
	left2->setLayout(lyLeft2);

	// tabel cu cos de carti
	QStringList HeaderTabel2;
	HeaderTabel2 << "Titlu" << "Descriere" << "Tip" << "Durata";
	tabel_lista_activitati_curente = new QTableWidget{ nr_linii, nr_coloane };
	tabel_lista_activitati_curente->setHorizontalHeaderLabels(HeaderTabel);
	tabel_lista_activitati_curente->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
	lyLeft2->addWidget(tabel2);
	lyLeft2->addWidget(lista_lista_activitati_curente);

	/// adaugare left si right pe lyMain
	lyMain2->addWidget(left2);
	lyMain2->addWidget(right2);

	fereastra_lista_activitati_curente->show();
}


void MyGUI::preluare_date_din_fisier(vector <Activitate> activitati)
{
	tabel_activitati->clearContents();
	tabel_activitati->setRowCount(activitati.size());

	int linie = 0;
	for (auto& a : activitati)
	{
		tabel_activitati->setItem(linie, 0, new QTableWidgetItem(QString::fromStdString(a.getTitlu())));
		tabel_activitati->setItem(linie, 1, new QTableWidgetItem(QString::fromStdString(a.getDescriere())));
		tabel_activitati->setItem(linie, 2, new QTableWidgetItem(QString::fromStdString(a.getTip())));
		tabel_activitati->setItem(linie, 3, new QTableWidgetItem(QString::number(a.getDurata())));
		linie++;
	}
	gui_raport_tipuri();
}

void MyGUI::incarcare_lista_activitati_curente(vector<Activitate> lista_activitati_curente) {
	tabel_lista_activitati_curente->clearContents();
	tabel_lista_activitati_curente->setRowCount(lista_activitati_curente.size());
	int linie = 0;
	for (auto& a : lista_activitati_curente)
	{
		tabel_lista_activitati_curente->setItem(linie, 0, new QTableWidgetItem(QString::fromStdString(a.getTitlu())));
		tabel_lista_activitati_curente->setItem(linie, 1, new QTableWidgetItem(QString::fromStdString(a.getDescriere())));
		tabel_lista_activitati_curente->setItem(linie, 2, new QTableWidgetItem(QString::fromStdString(a.getTip())));
		tabel_lista_activitati_curente->setItem(linie, 3, new QTableWidgetItem(QString::number(a.getDurata())));
		linie++;
	}

	lista_lista_activitati_curente->clear();
	for (auto& a : lista_activitati_curente)
	{
		string activitate = a.getTitlu() + " | " + a.getDescriere() + " | " + a.getTip() + " | " + to_string(a.getDurata());
		QListWidgetItem* it = new QListWidgetItem{ QString::fromStdString(activitate) };
		lista_lista_activitati_curente->addItem(it);
	}
}


void MyGUI::conectare_butoane()
{
	QObject::connect(btn_adaugare, &QPushButton::clicked, this, &MyGUI::gui_adaugare);
	QObject::connect(btn_actualizare, &QPushButton::clicked, this, &MyGUI::gui_actualizare);
	QObject::connect(btn_stergere, &QPushButton::clicked, this, &MyGUI::gui_stergere);
	QObject::connect(btn_undo, &QPushButton::clicked, this, &MyGUI::gui_undo);
	QObject::connect(btn_cautare, &QPushButton::clicked, this, &MyGUI::gui_cautare);
	QObject::connect(btn_filtrare_titlu, &QPushButton::clicked, this, &MyGUI::gui_filtrare_titlu);
	QObject::connect(btn_filtrare_durata, &QPushButton::clicked, this, &MyGUI::gui_filtrare_durata);
	QObject::connect(btn_sortare, &QPushButton::clicked, [&]()
		{
			if (radio_sortare_titlu->isChecked())
				preluare_date_din_fisier(srv.sortare_titlu());
			if (radio_sortare_descriere->isChecked())
				preluare_date_din_fisier(srv.sortare_descriere());
			if (radio_sortare_tip_durata->isChecked())
				preluare_date_din_fisier(srv.sortare_durata_tip());
		});
	QObject::connect(btn_cnt_tipuri, &QPushButton::clicked, this, &MyGUI::gui_cnt_tipuri);
	QObject::connect(btn_adaugare_lista_activitati_curente, &QPushButton::clicked, this, &MyGUI::gui_adaugare_lista_activitati_curente);
	QObject::connect(btn_golire_lista_activitati_curente, &QPushButton::clicked, this, &MyGUI::gui_golire_lista_activitati_curente);
	QObject::connect(btn_generare_lista_activitati_curente, &QPushButton::clicked, this, &MyGUI::gui_generare_lista_activitati_curente);
	QObject::connect(btn_export_lista_activitati_curente, &QPushButton::clicked, this, &MyGUI::gui_export_lista_activitati_curente);

}

void MyGUI::gui_adaugare()
{
	try
	{
		string titlu = editare_titlu->text().toStdString();
		string descriere = editare_descriere->text().toStdString();
		string tip = editare_tip->text().toStdString();
		int durata = editare_durata->text().toInt();

		editare_durata->clear();
		editare_descriere->clear();
		editare_tip->clear();
		editare_titlu->clear();

		srv.adaugare_activitate(titlu, descriere, tip, durata);
		preluare_date_din_fisier(srv.getAll());

		QMessageBox::information(this, "info", QString::fromStdString("Activitate adaugata cu succes!"));

	}
	catch (ExceptieRepo& e)
	{
		QMessageBox::warning(this, "warning", QString::fromStdString(e.getMesajeEroare()));
	}
	catch (ExceptieValidator& e)
	{
		QMessageBox::warning(this, "warning", QString::fromStdString(e.get_mesaje_eroare()));
	}
	gui_raport_tipuri();
}

void MyGUI::gui_actualizare()
{
	try
	{
		string titlu = editare_titlu->text().toStdString();
		string descriere = editare_descriere->text().toStdString();
		string tip = editare_tip->text().toStdString();
		int durata = editare_durata->text().toInt();

		editare_durata->clear();
		editare_descriere->clear();
		editare_tip->clear();
		editare_titlu->clear();

		srv.actualizare_activitate(titlu, descriere, tip, durata);
		preluare_date_din_fisier(srv.getAll());

		QMessageBox::information(this, "info", QString::fromStdString("activitate actualizata cu succes!"));

	}
	catch (ExceptieRepo& e)
	{
		QMessageBox::warning(this, "warning", QString::fromStdString(e.getMesajeEroare()));
	}
	catch (ExceptieValidator& e)
	{
		QMessageBox::warning(this, "warning", QString::fromStdString(e.get_mesaje_eroare()));
	}
	gui_raport_tipuri();
}

void MyGUI::gui_stergere()
{
	try
	{
		string titlu = editare_titlu->text().toStdString();
		string descriere = editare_descriere->text().toStdString();

		editare_descriere->clear();
		editare_titlu->clear();

		srv.stergere_activitate(titlu, descriere);
		preluare_date_din_fisier(srv.getAll());

		QMessageBox::information(this, "info", QString::fromStdString("Activitate stearsa cu succes!"));

	}
	catch (ExceptieRepo& e)
	{
		QMessageBox::warning(this, "warning", QString::fromStdString(e.getMesajeEroare()));
	}
	catch (ExceptieValidator& e)
	{
		QMessageBox::warning(this, "warning", QString::fromStdString(e.get_mesaje_eroare()));
	}
	gui_raport_tipuri();
}

void MyGUI::gui_cautare()
{
	try
	{
		string titlu = editare_titlu->text().toStdString();
		string descriere = editare_descriere->text().toStdString();

		editare_descriere->clear();
		editare_titlu->clear();

		Activitate a = srv.cautare_activitate(titlu, descriere);
		string activitate;
		activitate = "Titlu:";
		activitate.append(a.getTitlu());
		activitate.append("; ");
		activitate.append("Descrire:");
		activitate.append(a.getDescriere());
		activitate.append("; ");
		activitate.append("Tip:");
		activitate.append(a.getTip());
		activitate.append("; ");
		activitate.append("Durata:");
		activitate.append(std::to_string(a.getDurata()));
		QMessageBox::information(this, "info", QString::fromStdString(activitate));
	}
	catch (ExceptieRepo& e)
	{
		QMessageBox::warning(this, "warning", QString::fromStdString(e.getMesajeEroare()));
	}
	catch (ExceptieValidator& e)
	{
		QMessageBox::warning(this, "warning", QString::fromStdString(e.get_mesaje_eroare()));
	}
	gui_raport_tipuri();
}

void MyGUI::gui_filtrare_titlu()
{
	string activitate;
	string titlu = editare_titlu->text().toStdString();
	editare_titlu->clear();
	QListWidget* lista_activitati = new QListWidget;
	vector <Activitate> filtrare_titlu = srv.filtrare_titlu(titlu);
	if (filtrare_titlu.empty())
		QListWidgetItem* item = new QListWidgetItem(QString::fromStdString("Nu exista activitate cu titlul dat"), lista_activitati);
	for (auto a : filtrare_titlu)
	{
		activitate = "Titlu:";
		activitate.append(a.getTitlu());
		activitate.append("; ");
		activitate.append("Descriere:");
		activitate.append(a.getDescriere());
		activitate.append("; ");
		activitate.append("Tip:");
		activitate.append(a.getTip());
		activitate.append("; ");
		activitate.append("Durata:");
		activitate.append(std::to_string(a.getDurata()));
		QListWidgetItem* item = new QListWidgetItem(QString::fromStdString(activitate), lista_activitati);
	}
	lista_activitati->show();
}

void MyGUI::gui_filtrare_durata()
{
	string activitate;
	int durata = editare_durata->text().toInt();
	editare_durata->clear();
	QListWidget* lista_activitati = new QListWidget;
	vector <Activitate> filtrare_durata = srv.filtrare_durata(durata);
	if (filtrare_durata.empty())
		QListWidgetItem* item = new QListWidgetItem(QString::fromStdString("Nu exista nicio activitate cu durata data"), lista_activitati);
	for (auto a : filtrare_durata)
	{
		activitate = "Titlu:";
		activitate.append(a.getTitlu());
		activitate.append("; ");
		activitate.append("Descriere:");
		activitate.append(a.getDescriere());
		activitate.append("; ");
		activitate.append("Tip:");
		activitate.append(a.getTip());
		activitate.append("; ");
		activitate.append("Durata:");
		activitate.append(std::to_string(a.getDurata()));
		QListWidgetItem* item = new QListWidgetItem(QString::fromStdString(activitate), lista_activitati);
	}
	lista_activitati->show();
}

void MyGUI::gui_undo()
{
	if (srv.undo() == 0)
	{
		preluare_date_din_fisier(srv.getAll());
		QMessageBox::information(this, "info", QString::fromStdString("Undo efectuat cu succes!"));

	}
	else
		QMessageBox::information(this, "info", QString::fromStdString("Nu se mai poate face undo!"));
	gui_raport_tipuri();
}

void MyGUI::gui_cnt_tipuri()
{
	QListWidget* lista_tipuri = new QListWidget;
	map<string, DTO> dict = srv.cerinta_noua();
	for (map<string, DTO>::iterator it = dict.begin(); it != dict.end(); ++it)
	{
		string tip;
		tip.append(it->second.get_tip());
		tip.append(": ");
		tip.append(std::to_string(it->second.get_cnt()));
		QListWidgetItem* item = new QListWidgetItem(QString::fromStdString(tip), lista_tipuri);
	}
	lista_tipuri->show();
}

void MyGUI::gui_adaugare_lista_activitati_curente()
{
	try
	{
		string titlu = editare_titlu->text().toStdString();
		string descriere = editare_descriere->text().toStdString();

		editare_descriere->clear();
		editare_titlu->clear();

		srv.adaugare_activitate_in_lista(titlu, descriere);
		incarcare_lista_activitati_curente(srv.getAll_lista());

		QMessageBox::information(this, "info", QString::fromStdString("Activitatea a fost adaugata in lista de activitati curente cu succes!"));

	}
	catch (ExceptieRepo& e)
	{
		QMessageBox::warning(this, "warning", QString::fromStdString(e.getMesajeEroare()));
	}
	catch (ExceptieValidator& e)
	{
		QMessageBox::warning(this, "warning", QString::fromStdString(e.get_mesaje_eroare()));
	}
}

void MyGUI::gui_golire_lista_activitati_curente()
{
	try
	{
		srv.golire_lista();
		incarcare_lista_activitati_curente(srv.getAll_lista());

		QMessageBox::information(this, "info", QString::fromStdString("Lista de activitati curente a fost golita cu succes!"));

	}
	catch (ExceptieRepo& e)
	{
		QMessageBox::warning(this, "warning", QString::fromStdString(e.getMesajeEroare()));
	}
}

void MyGUI::gui_generare_lista_activitati_curente()
{
	try
	{
		int nr = editare_nr->text().toInt();
		editare_nr->clear();
		if (nr > srv.getAll().size())
			QMessageBox::warning(this, "warning", QString::fromStdString("Numarul depaseste lungimea listei!"));
		else
		{
			srv.genereaza_lista(nr);
			incarcare_lista_activitati_curente(srv.getAll_lista());
			QMessageBox::information(this, "info", QString::fromStdString("Lista de activitati curente a fost generata cu succes!"));
		}
	}
	catch (ExceptieRepo& e)
	{
		QMessageBox::warning(this, "warning", QString::fromStdString(e.getMesajeEroare()));
	}
}

void MyGUI::gui_export_lista_activitati_curente()
{
	try
	{
		string nume_fisier = editare_nume_fisier->text().toStdString();
		editare_nume_fisier->clear();

		srv.export_lista(nume_fisier);
		QMessageBox::information(this, "info", QString::fromStdString("Lista de activitati curente a fost exportata cu succes!"));
	}
	catch (ExceptieValidator& ve)
	{
		QMessageBox::warning(this, "warning", QString::fromStdString(ve.get_mesaje_eroare()));
	}
}

void MyGUI::gui_raport_tipuri()
{
	clearLayout(typesLayout);
	map<string, DTO> dict = srv.cerinta_noua();
	for (map<string, DTO>::iterator it = dict.begin(); it != dict.end(); ++it)
	{
		auto tip = it->second.get_tip();
		auto nr = it->second.get_cnt();

		QPushButton* typeButton = new QPushButton(QString::fromStdString(tip));
		typesLayout->addWidget(typeButton);
		QObject::connect(typeButton, &QPushButton::clicked, this, [=]() {
			QMessageBox::information(this, "info", QString::fromStdString("Tipul: " + tip + " - numarul activitatilor: " + std::to_string(nr)));
			});
	}
}

void MyGUI::clearLayout(QLayout* layout) {
	if (layout == NULL)
		return;
	QLayoutItem* item;
	while ((item = layout->takeAt(0))) {
		if (item->layout()) {
			clearLayout(item->layout());
			delete item->layout();
		}
		if (item->widget()) {
			delete item->widget();
		}
		delete item;
	}
}