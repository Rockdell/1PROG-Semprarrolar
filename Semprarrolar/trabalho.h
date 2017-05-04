#ifndef TRABALHO_H
#define TRABALHO_H

#include "tempo.h"

using namespace std;

class Trabalho
{
public:
	Trabalho();
	Trabalho(unsigned int autocarroid, unsigned int condutorid, Tempo inicio, Tempo fim);

	void setAutocarroID(unsigned int autocarroid);
	void setCondutorID(unsigned int condutorid);
	void setInicio(Tempo inicio);
	void setFim(Tempo fim);

	unsigned int getAutocarroID() const;
	unsigned int getCondutorID() const;
	Tempo getInicio() const;
	Tempo getFim() const;

	void showTrabalho();

private:
	unsigned int idAutocarro;
	unsigned int idCondutor;
	Tempo inicioTrabalho;
	Tempo fimTrabalho;

};

#endif