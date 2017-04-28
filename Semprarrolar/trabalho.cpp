#include "trabalho.h"

using namespace std;

Trabalho::Trabalho()
{
	this->idAutocarro = 0;
	this->idCondutor = 0;
	this->inicioTrabalho = 0;
	this->fimTrabalho = 0;
}
Trabalho::Trabalho(unsigned int autocarroid, unsigned int condutorid, unsigned int inicio, unsigned int fim)
{
	this->idAutocarro = autocarroid;
	this->idCondutor = condutorid;
	this->inicioTrabalho = inicio;
	this->fimTrabalho = fim;
}

void Trabalho::setAutocarroID(unsigned int autocarroid)
{
	this->idAutocarro = autocarroid;
}
void Trabalho::setCondutorID(unsigned int condutorid)
{
	this->idCondutor = condutorid;
}
void Trabalho::setInicio(unsigned int inicio)
{
	this->inicioTrabalho = inicio;
}
void Trabalho::setFim(unsigned int fim)
{
	this->fimTrabalho = fim;
}

unsigned int Trabalho::getAutocarroID() const
{
	return idAutocarro;
}
unsigned int Trabalho::getCondutorID() const
{
	return idCondutor;
}
unsigned int Trabalho::getInicio() const
{
	return inicioTrabalho;
}
unsigned int Trabalho::getFim() const
{
	return fimTrabalho;
}