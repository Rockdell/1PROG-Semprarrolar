#ifndef LINHA_H
#define LINHA_H

#include <string>
#include <vector>

using namespace std;

class Linha
{
public:
	Linha();
	Linha(unsigned int id, unsigned int freq, vector<string> paragem, vector<unsigned int> tempo, unsigned int autocarros);

	void setID(unsigned int id);
	void setFreq(unsigned int freq);
	void setParagens(vector<string> paragens);
	void setTempos(vector<unsigned int> tempos);
	void setAutocarros(unsigned int autocarros);

	unsigned int getID() const;
	unsigned int getFreq() const;
	vector<string> getParagens() const;
	vector<unsigned int> getTempos() const;
	unsigned int getAutocarros() const;

	void showLinha();

private:
	unsigned int idLinha;
	unsigned int frequenciaLinha;
	vector<string> paragensLinha;
	vector<unsigned int> temposLinha;
	unsigned int autocarrosLinha;

};

#endif