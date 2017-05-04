#include <iostream>
#include "condutor.h"
#include "trabalho.h"

using namespace std;

Condutor::Condutor()
{
	this->idCondutor = 0;
	this->nomeCondutor = "";
	this->hturnoCondutor = 0;
	this->hsemanaCondutor = 0;
	this->hdescansoCondutor = 0;
	this->trabalhoCondutor = vector<Trabalho>(0);
}
Condutor::Condutor(unsigned int id, string nome, unsigned int hturno, unsigned int hsemana, unsigned int hdescanso, vector<Trabalho> turnos)
{
	this->idCondutor = id;
	this->nomeCondutor = nome;
	this->hturnoCondutor = hturno;
	this->hsemanaCondutor = hsemana;
	this->hdescansoCondutor = hdescanso;
	this->trabalhoCondutor = turnos;
}

void Condutor::workCondutor()
{
	vector<Trabalho> trab = this->trabalhoCondutor;

	if (trab.size() == 0)
	{
		cout << "Condutor nao tem nenhum trabalho atribuido!" << endl;
	}
	else
	{
		cout << "\nTrabalho atribuido ao condutor " << this->nomeCondutor << " :" << endl << endl;

		for (int i = 0; i < trab.size(); i++)
		{
			Trabalho temp = trab.at(i);
			cout << "De " << temp.getInicio().showTempo() << " a " << temp.getFim().showTempo() << endl;
			cout << "Conduz o autocarro de ordem " << temp.getAutocarroID() << endl;
		}
	}
}

void Condutor::setID(unsigned int id)
{
	this->idCondutor = id;
}
void Condutor::setNome(string nome)
{
	this->nomeCondutor = nome;
}
void Condutor::setTurno(unsigned int hturno)
{
	this->hturnoCondutor = hturno;
}
void Condutor::setSemana(unsigned int hsemana)
{
	this->hsemanaCondutor = hsemana;
}
void Condutor::setDescanso(unsigned int hdescanso)
{
	this->hdescansoCondutor = hdescanso;
}
void Condutor::setTrabalho(vector<Trabalho> turnos)
{
	this->trabalhoCondutor = turnos;
}

unsigned int Condutor::getID() const
{
	return idCondutor;
}
string Condutor::getNome() const
{
	return nomeCondutor;
}
unsigned int Condutor::getTurno() const
{
	return hturnoCondutor;
}
unsigned int Condutor::getSemana() const
{
	return hsemanaCondutor;
}
unsigned int Condutor::getDescanso() const
{
	return hsemanaCondutor;
}
vector<Trabalho> Condutor::getTrabalho() const
{
	return trabalhoCondutor;
}