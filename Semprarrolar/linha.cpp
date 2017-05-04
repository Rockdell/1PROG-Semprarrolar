#include <iostream>
#include <iomanip>
#include <conio.h>

#include "linha.h"
#include "library.h"
#include "global.h"

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

void Linha::showLinha()
{
	cout << endl << " Linha:\n" << " ID: " << this->idLinha <<
		"\n Frequência: " << this->frequenciaLinha <<
		"\n Paragens: ";

	for (size_t i = 0; i < this->paragensLinha.size(); i++)
	{
		if (i == this->paragensLinha.size() - 1)
			cout << this->paragensLinha.at(i) << "\n Tempos: ";
		else
			cout << this->paragensLinha.at(i) << ", ";
	}

	for (size_t i = 0; i < this->temposLinha.size(); i++)
	{
		if (i == this->temposLinha.size() - 1)
			cout << this->temposLinha.at(i) << endl << endl;
		else
			cout << this->temposLinha.at(i) << ", ";
	}

	return;
}
void Linha::showHorario(unsigned int sentido)
{
	//Tempo que demora a fazer um viagem (quer no sentido normal, quer no sentido inverso)
	unsigned int sum = 0;
	for (size_t i = 0; i < this->temposLinha.size(); i++)
	{
		sum += this->temposLinha.at(i);
	}

	Tempo actualNormal = T_INICIO;
	Tempo actualInverso = T_INICIO; actualInverso.sumTempo(sum);

	bool acabarPreencher = false;

	//Vetores com os tempos iniciais dos dois sentidos
	vector <Tempo> temposNormais; temposNormais.push_back(actualNormal);
	vector <Tempo> temposInversos; temposInversos.push_back(actualInverso);

	//Preencher vetores
	while (!acabarPreencher)
	{
		actualNormal.sumTempo(this->frequenciaLinha);
		actualInverso.sumTempo(this->frequenciaLinha);

		if (actualNormal.getHora() > T_FIM.getHora() || (actualNormal.getHora() == T_FIM.getHora() && actualNormal.getMinuto() > T_FIM.getMinuto()))
			acabarPreencher = true;
		else
			temposNormais.push_back(actualNormal);

		if (actualInverso.getHora() > T_FIM.getHora() || (actualInverso.getHora() == T_FIM.getHora() && actualInverso.getMinuto() > T_FIM.getMinuto()))
			acabarPreencher = true;
		else
			temposInversos.push_back(actualInverso);
	}

	//Vector com os tempos entre paragens (bi-direcional)
	vector<unsigned int> temp_normal = this->temposLinha, temp_reverso = this->temposLinha;
	reverse(temp_reverso.begin(), temp_reverso.end());

	//Vetor com elementos vetores (cada um com um conjunto de tempos ordenados a que se vai fazer output)
	vector < vector <Tempo> > vectorOutput;

	//Contadores
	unsigned int p_index = 0;
	unsigned int t_index = 0;

	//Vetor com as valores para usar no setw (de modo a formatar o output conforme o número de carácteres das paragens)
	vector<unsigned int> width;
	unsigned int t_width = 0;

	//Preencher vectorOutput com os tempos entre cada paragem, para todos as horas de saída da paragem inicial (numa direção)
	switch (sentido)
	{
	case 1:
	{
		for (size_t i = 0; i < temposNormais.size(); i++)
		{
			//Horas a que sai o autocarro da paragem inicial
			Tempo time = temposNormais.at(i);

			//Vetor temporario para guardar 1 linha que se vai fazer cout
			vector <Tempo> normal;

		next_n:
			if (p_index == this->paragensLinha.size() - 1)
			{
				normal.push_back(time);
				vectorOutput.push_back(normal);

				t_index = 0;
				p_index = 0;

				continue;
			}
			else
			{
				normal.push_back(time);

				time.sumTempo(temp_normal.at(t_index));

				t_index++;
				p_index++;

				goto next_n;
			}
		}

		break;
	}
	case 2:
	{
		for (size_t i = 0; i < temposInversos.size(); i++)
		{
			//Horas a que sai o autocarro da paragem inicial
			Tempo time = temposInversos.at(i);

			//Vetor temporario para guardar 1 linha que se vai fazer cout
			vector <Tempo> inverso;

		next_i:
			if (p_index == this->paragensLinha.size() - 1)
			{
				inverso.push_back(time);

				vectorOutput.push_back(inverso);

				t_index = 0;
				p_index = 0;

				continue;
			}
			else
			{
				inverso.push_back(time);

				time.sumTempo(temp_reverso.at(t_index));

				t_index++;
				p_index++;

				goto next_i;
			}
		}

		break;
	}
	}

	//Output do header do horário
	switch (sentido)
	{
	case 1:
	{
		cout << " ";

		for (size_t i = 0; i < this->paragensLinha.size(); i++)
		{
			if (i == this->paragensLinha.size() - 1)
			{
				cout << this->paragensLinha.at(i) << endl;
				width.push_back(this->paragensLinha.at(i).length() + 5);
			}
			else
			{
				cout << this->paragensLinha.at(i) << "     ";
				width.push_back(this->paragensLinha.at(i).length() + 5);
			}
		}

		cout << endl;

		break;
	}
	case 2:
	{
		vector<string> inv = this->paragensLinha;
		reverse(inv.begin(), inv.end());

		cout << " ";

		for (size_t i = 0; i < inv.size(); i++)
		{
			if (i == inv.size() - 1)
			{
				cout << inv.at(i) << endl;
				width.push_back(inv.at(i).length() + 5);
			}
			else
			{
				cout << inv.at(i) << "     ";
				width.push_back(inv.at(i).length() + 5);
			}
		}

		cout << endl;

		break;
	}
	}

	//Output dos tempos do vetor preenchido na função anterior
	for (size_t x = 0; x < vectorOutput.size(); x++)
	{
		cout << " ";

		for (size_t y = 0; y < vectorOutput.at(x).size(); y++)
		{
			if (y == vectorOutput.at(x).size() - 1)
				cout << vectorOutput.at(x).at(y).showTempo() << endl;
			else
				cout << vectorOutput.at(x).at(y).showTempo() << setw(width.at(t_width));
			t_width++;
		}

		//Renicializar o índice para ser usado na próxima hora de partida
		t_width = 0;
	}
	
	cout << endl;

	_getch();

	return;
}