#include "linha.h"

using namespace std;

Linha::Linha()
{	
	this->idLinha = 0;
	this->frequenciaLinha = 0;
	this->paragensLinha = vector<string>(0);
	this->temposLinha = vector<unsigned int>(0);
	this->autocarrosLinha = 0;
}
Linha::Linha(unsigned int id, unsigned int freq, vector<string> paragens, vector<unsigned int> tempos, unsigned int autocarros)
{
	this->idLinha = id;
	this->frequenciaLinha = freq;
	this->paragensLinha = paragens;
	this->temposLinha = tempos;
	this->autocarrosLinha = autocarros;
}

void Linha::setID(unsigned int id)
{
	this->idLinha = id;
}
void Linha::setFreq(unsigned int freq)
{
	this->frequenciaLinha = freq;
}
void Linha::setParagens(vector<string> paragens)
{
	this->paragensLinha = paragens;
}
void Linha::setTempos(vector<unsigned int> tempos)
{
	this->temposLinha = tempos;
}
void Linha::setAutocarros(unsigned int autocarros)
{
	this->autocarrosLinha = autocarros;
}

unsigned int Linha::getID() const
{
	return idLinha;
}
unsigned int Linha::getFreq() const
{
	return frequenciaLinha;
}
vector<string> Linha::getParagens() const
{
	return paragensLinha;
}
vector<unsigned int> Linha::getTempos() const
{
	return temposLinha;
}
unsigned int Linha::getAutocarros() const
{
	return autocarrosLinha;
}