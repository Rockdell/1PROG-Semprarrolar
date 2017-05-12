#ifndef CONDUTOR_H
#define CONDUTOR_H

#include <string>
#include <vector>
#include <tuple>

#include "trabalho.h"

using namespace std;

class Condutor
{
public:
	Condutor();
	Condutor(unsigned int id, string nome, unsigned int hturno, unsigned int hsemana, unsigned int hdescanso, vector<Trabalho> turnos);

	void setID(unsigned int id);
	void setNome(string nome);
	void setTurno(unsigned int hturno);
	void setSemana(unsigned int hsemana);
	void setDescanso(unsigned int hdescanso);
	void setTrabalho(vector<Trabalho> turnos);

	unsigned int getID() const;
	string getNome() const;
	unsigned int getTurno() const;
	unsigned int getSemana() const;
	unsigned int getDescanso() const;
	vector<Trabalho> getTrabalho() const;

	void showCondutor();
	void showTrabalho();

private:
	unsigned int idCondutor;
	string nomeCondutor;
	unsigned int hturnoCondutor;
	unsigned int hsemanaCondutor;
	unsigned int hdescansoCondutor;
	vector<Trabalho> trabalhoCondutor;
	//unsigned int sumTempo;
	//Tempo proximoTempo;

};

#endif