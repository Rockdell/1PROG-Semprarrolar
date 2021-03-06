#include "autocarro.h"

using namespace std;

Autocarro::Autocarro()
{
	this->idLinha = 0;
	this->idCondutor = 0;
	this->ordemAutocarro = 0;
	this->trabalhoAutocarro = vector<Trabalho>(0);
}
Autocarro::Autocarro(unsigned int linhaid, unsigned int condutorid, unsigned int ordem, vector<Trabalho> turnos)
{
	this->idLinha = linhaid;
	this->idCondutor = condutorid;
	this->ordemAutocarro = ordem;
	this->trabalhoAutocarro = turnos;
}

void Autocarro::setLinhaID(unsigned int linhaid)
{
	this->idLinha = linhaid;
}
void Autocarro::setCondutorID(unsigned int condutorid)
{
	this->idCondutor = condutorid;
}
void Autocarro::setOrdem(unsigned int ordem)
{
	this->ordemAutocarro = ordem;
}
void Autocarro::setTrabalho(vector<Trabalho> turnos)
{
	this->trabalhoAutocarro = turnos;
}

unsigned int Autocarro::getLinhaID() const
{
	return idLinha;
}
unsigned int Autocarro::getCondutorID() const
{
	return idCondutor;
}
unsigned int Autocarro::getOrdem() const
{
	return ordemAutocarro;
}
vector<Trabalho> Autocarro::getTrabalho() const
{
	return trabalhoAutocarro;
}