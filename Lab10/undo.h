#pragma once
#include "activitate.h"
#include "repo.h"

class ActiuneUndo {
public:
	virtual void doUndo() = 0;
	virtual ~ActiuneUndo() = default;
};

class UndoAdauga :public ActiuneUndo {
	Activitate activitateAdaugata;
	RepoActivitati& repo;
public:
	UndoAdauga(RepoActivitati& rep, Activitate activitate) : repo{ rep }, activitateAdaugata{ activitate } {};
	void doUndo() override {
		repo.sterge_undo(activitateAdaugata.getTitlu(), activitateAdaugata.getDescriere());
	}
};



class UndoActualizeaza :public ActiuneUndo {
	Activitate activitateActualizata;
	RepoActivitati& repo;
public:
	UndoActualizeaza(RepoActivitati& rep, Activitate activitate) : repo{ rep }, activitateActualizata{ activitate } {};
	void doUndo() override {
		repo.actualizeaza_undo(activitateActualizata);
	}
};



class UndoSterge :public ActiuneUndo {
	Activitate activitateStearsa;
	RepoActivitati& repo;
public:
	UndoSterge(RepoActivitati& rep, Activitate activitate) : repo{ rep }, activitateStearsa{ activitate } {};
	void doUndo() override {
		repo.adauga_undo(activitateStearsa);
	}

};