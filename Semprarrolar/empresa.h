#ifndef EMPRESA_H
#define EMPRESA_H

#include <map>
#include <vector>
#include <string>

#include "linha.h"
#include "condutor.h"
#include "autocarro.h"

using namespace std;

typedef map <unsigned int, Condutor> mapCondutor;
typedef map <unsigned int, Linha> mapLinha;
typedef map<unsigned int, Autocarro> mapAutocarro;

typedef map<unsigned int, mapAutocarro> linhasDia;

class Empresa
{
public:
	Empresa();

	void setCondutores(mapCondutor lcondutores);
	void setLinhas(mapLinha llinhas);
	void setTrabalho(vector<linhasDia> vtrabalho);

	mapCondutor getCondutores() const;
	mapLinha getLinhas() const;
	vector<linhasDia> getTrabalho() const;

	void fillCondutores(string filename);
	void fillLinhas(string filename);

	void saveCondutores(string filename);
	void saveLinhas(string filename);

	//Linha
	void createLinha();
	void modifyLinha();
	void removeLinha();

	//Condutor
	void createCondutor();
	void modifyCondutor();
	void removeCondutor();

	//Horários
	void horarioLinha();
	void horarioParagem();
	void percursoParagem();

	void inquirirParagem();

	void infoLinha();
	void infoTrabalho();
	void infoService();
	//void infoAutocarro();

private:
	mapCondutor listaCondutores;
	mapLinha listaLinhas;
	vector<linhasDia> vectorTrabalho;
	
	/*
	0 - segunda
	1 - terça
	2 - quarta
	3 - quinta
	4 - sexta
	5 - sabado
	6 - domingo
	*/

};

#endif
