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

	void setLinhaID(unsigned int linhaid);
	void setCondutorID(unsigned int condutorid);
	void setOrdem(unsigned int ordem);
	void setTrabalho(vector<Trabalho> turnos);
	
	unsigned int getLinhaID() const;
	unsigned int getCondutorID() const;
	unsigned int getOrdem() const;
	vector<Trabalho> getTrabalho() const;

	void showTrabalho();

private:
	unsigned int idLinha;
	unsigned int idCondutor;
	unsigned int ordemAutocarro;
	vector<Trabalho> trabalhoAutocarro;

};

#endif
