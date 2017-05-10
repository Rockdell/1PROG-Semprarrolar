#ifndef TRABALHO_H
#define TRABALHO_H

#include "tempo.h"

using namespace std;

//typedef vector<pair<Tempo, Tempo>> vectorTurno;

class Trabalho
{
public:
	Trabalho();
	Trabalho(Tempo inicio, Tempo fim);

	//void setAutocarroID(unsigned int autocarroid);
	//void setCondutorID(unsigned int condutorid);
	void setInicio(Tempo inicio);
	void setFim(Tempo fim);

	//unsigned int getAutocarroID() const;
	//unsigned int getCondutorID() const;
	Tempo getInicio() const;
	Tempo getFim() const;

	//void showTrabalho();

private:
	//unsigned int idAutocarro;
	//unsigned int idCondutor;
	Tempo inicioTrabalho;
	Tempo fimTrabalho;

};

#endif