#ifndef AUTOCARRO_H
#define AUTOCARRO_H

#include <vector>

#include "trabalho.h"

using namespace std;

class Autocarro
{
public:
	Autocarro();
	Autocarro(unsigned int linhaid, unsigned int condutorid, unsigned int ordem, vector<Trabalho> turnos);

	void setOrdem(unsigned int ordem);
	void setLinhaID(unsigned int linhaid);
	void setCondutorID(unsigned int condutorid);
	void setTrabalho(vector<Trabalho> turnos);
	
	unsigned int getOrdem() const;
	unsigned int getLinhaID() const;
	unsigned int getCondutorID() const;
	vector<Trabalho> getTrabalho() const;

	//void showAutocarros();
	//void showTrabalho();

private:
	unsigned int idLinha;
	unsigned int idCondutor;
	unsigned int ordemAutocarro;
	vector<Trabalho> trabalhoAutocarro;

};

#endif
