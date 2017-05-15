#include "tempo.h"

Tempo::Tempo()
{
	this->hora = 0;
	this->minuto = 0;
}
Tempo::Tempo(unsigned int h, unsigned int m)
{
	this->hora = h;
	this->minuto = m;
}

void Tempo::setHora(unsigned int h)
{
	this->hora = h;
}
void Tempo::setMinuto(unsigned int m)
{
	this->minuto = m;
}

unsigned int Tempo::getHora() const
{
	return hora;
}
unsigned int Tempo::getMinuto() const
{
	return minuto;
}

string Tempo::showTempo() const
{
	string result = "";

	int h = this->hora;
	int m = this->minuto;

	if (h < 10)
		result += "0" + to_string(h) + ":";
	else
		result += to_string(h) + ":";

	if (m < 10)
		result += "0" + to_string(m);
	else
		result += to_string(m);

	return result;
}
void Tempo::sumTempo(unsigned int m)
{
	this->setMinuto(this->getMinuto() + m);

	while (this->getMinuto() >= 60)
	{
		this->setHora(this->getHora() + 1);
		this->setMinuto(this->getMinuto() - 60);
	}

	return;
}
void Tempo::subtractTempo(unsigned int m)
{
	int hora_temp = this->getHora();
	int minuto_temp = this->getMinuto() - m;

	while (minuto_temp < 0)
	{
		hora_temp--;
		minuto_temp += 60;
	}

	this->setHora(hora_temp);
	this->setMinuto(minuto_temp);

	return;
}
unsigned int Tempo::subtractTempo(Tempo t)
{
	unsigned int horas = this->getHora() - t.getHora();
	unsigned int minutos = this->getMinuto() - t.getMinuto();

	return (horas * 60) + minutos;
}