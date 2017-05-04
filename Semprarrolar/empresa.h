#ifndef EMPRESA_H
#define EMPRESA_H

#include <map>
#include <vector>
#include <locale>
#include <clocale>

#include "condutor.h"
#include "linha.h"
#include "tempo.h"

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
	void workCondutor();

	//Horários
	void horarioLinha();
	void horarioParagem();
	void percursoParagem();

	//Display do horário da linha (a ser usado pelo horarioLinha e pelo ponto 7 do trabalho)
	void showHorario(Linha l, unsigned int direcao);

	void inquirirParagem();

private:
	mapCondutor listaCondutores;
	mapLinha listaLinhas;

};

#endif
