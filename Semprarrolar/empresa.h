#ifndef EMPRESA_H
#define EMPRESA_H

#include <map>
#include <vector>

#include "linha.h"
#include "condutor.h"

using namespace std;

typedef map <unsigned int, Condutor> mapCondutor;
typedef map <unsigned int, Linha> mapLinha;

class Empresa
{
public:
	Empresa();

	void setCondutores(mapCondutor lcondutores);
	void setLinhas(mapLinha llinhas);

	mapCondutor getCondutores() const;
	mapLinha getLinhas() const;

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
	//void infoAutocarro();

private:
	mapCondutor listaCondutores;
	mapLinha listaLinhas;

};

#endif
