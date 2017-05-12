#include "trabalho.h"
#include "tempo.h"

using namespace std;

Trabalho::Trabalho()
{
	this->diaSemana = 8;
	this->idLinha = 0;
	this->idAutocarro = 0;
	this->inicioTrabalho = Tempo();
	this->fimTrabalho = Tempo();
}
Trabalho::Trabalho(unsigned int dia, unsigned int linha, unsigned int autocarro, Tempo inicio, Tempo fim)
{
	this-> diaSemana = dia;
	this->idLinha = linha;
	this->idAutocarro = autocarro;
	this->inicioTrabalho = inicio;
	this->fimTrabalho = fim;
}

void Trabalho::setDiaSemana(unsigned int dia)
{
	this->diaSemana = dia;
}
void Trabalho::setLinhaID(unsigned int linhaid)
{
	this->idLinha = linhaid;
}
void Trabalho::setAutocarroID(unsigned int autocarroid)
{
	this->idAutocarro = autocarroid;
}
void Trabalho::setInicio(Tempo inicio)
{
	this->inicioTrabalho = inicio;
}
void Trabalho::setFim(Tempo fim)
{
	this->fimTrabalho = fim;
}

unsigned int Trabalho::getDiaSemana() const
{
	return diaSemana;
}
unsigned int Trabalho::getLinhaID() const
{
	return idLinha;
}
unsigned int Trabalho::getAutocarroID() const
{
	return idAutocarro;
}
Tempo Trabalho::getInicio() const
{
	return inicioTrabalho;
}
Tempo Trabalho::getFim() const
{
	return fimTrabalho;
}