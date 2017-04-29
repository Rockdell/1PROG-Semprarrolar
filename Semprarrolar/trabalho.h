#ifndef TRABALHO_H
#define TRABALHO_H

#include "tempo.h"

using namespace std;

class Trabalho
{
public:
	Trabalho();
	Trabalho(unsigned int autocarroid, unsigned int condutorid, unsigned int inicio, unsigned int fim);

	void setAutocarroID(unsigned int autocarroid);
	void setCondutorID(unsigned int condutorid);
	void setInicio(unsigned int inicio);
	void setFim(unsigned int fim);

	unsigned int getAutocarroID() const;
	unsigned int getCondutorID() const;
	unsigned int getInicio() const;
	unsigned int getFim() const;

	void showTrabalho();

private:
	unsigned int idAutocarro;
	unsigned int idCondutor;
	unsigned int inicioTrabalho;
	unsigned int fimTrabalho;

};

#endif