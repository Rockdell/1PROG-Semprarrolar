#ifndef TRABALHO_H
#define TRABALHO_H

#include "tempo.h"

using namespace std;

//typedef vector<pair<Tempo, Tempo>> vectorTurno;

class Trabalho
{
public:
	Trabalho();
	Trabalho(unsigned int dia, unsigned int linha, unsigned int autocarro, Tempo inicio, Tempo fim);

	void setDiaSemana(unsigned int dia);
	void setLinhaID(unsigned int linhaid);
	void setAutocarroID(unsigned int autocarroid);
	void setInicio(Tempo inicio);
	void setFim(Tempo fim);

	unsigned int getDiaSemana() const;
	unsigned int getLinhaID() const;
	unsigned int getAutocarroID() const;
	Tempo getInicio() const;
	Tempo getFim() const;

	//void showTrabalho();

private:
	unsigned int diaSemana;
	unsigned int idLinha;
	unsigned int idAutocarro;
	Tempo inicioTrabalho;
	Tempo fimTrabalho;

};

#endif