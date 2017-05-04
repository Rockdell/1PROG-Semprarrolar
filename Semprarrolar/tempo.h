#ifndef TEMPO_H
#define TEMPO_H

#include <string>

using namespace std;

class Tempo
{
public:
	Tempo();
	Tempo(unsigned int h, unsigned int m);

	void setHora(unsigned int h);
	void setMinuto(unsigned int m);

	unsigned int getHora() const;
	unsigned int getMinuto() const;

	string showTempo() const;
	void sumTempo(unsigned int m);
	unsigned int subtractTempo(Tempo t);

private:
	int hora;
	int minuto;
};

#endif