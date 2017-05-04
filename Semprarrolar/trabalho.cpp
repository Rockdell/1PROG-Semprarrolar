#include "trabalho.h"
#include "tempo.h"

using namespace std;

Trabalho::Trabalho()
{
	this->idAutocarro = 0;
	this->idCondutor = 0;
	this->inicioTrabalho = Tempo();
	this->fimTrabalho = Tempo();
}
Trabalho::Trabalho(unsigned int autocarroid, unsigned int condutorid, Tempo inicio, Tempo fim)
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
void Trabalho::setInicio(Tempo inicio)
{
	this->inicioTrabalho = inicio;
}
void Trabalho::setFim(Tempo fim)
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
Tempo Trabalho::getInicio() const
{
	return inicioTrabalho;
}
Tempo Trabalho::getFim() const
{
	return fimTrabalho;
}