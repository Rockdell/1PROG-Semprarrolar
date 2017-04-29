#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <conio.h>
#include <queue>
#include <tuple>

#include "library.h"
#include "global.h"
#include "linha.h"

using namespace std;

Empresa::Empresa()
{
	mapCondutor newCondutor;
	mapLinha newLinha;

	this->listaCondutores = newCondutor;
	this->listaLinhas = newLinha;
}

void Empresa::setCondutores(mapCondutor lcondutores)
{
	this->listaCondutores = lcondutores;
}
void Empresa::setLinhas(mapLinha llinhas)
{
	this->listaLinhas = llinhas;
}

mapCondutor Empresa::getCondutores() const
{
	return listaCondutores;
}
mapLinha Empresa::getLinhas() const
{
	return listaLinhas;
}

void Empresa::fillCondutores(string filename)
{
	mapCondutor newCondutores;

	ifstream file(filename);

	string temp;
	unsigned int contador = 0;

	while (getline(file, temp))
		contador++;
	file.close();

	file.open(filename);

	if (file.is_open())
	{

		for (size_t i = 1; i <= contador; i++)
		{
			string line;
			getline(file, line);

			//Novo condutor
			Condutor c;

			unsigned int c_id, c_hturno, c_hsemana, c_hdescanso;
			string c_nome1, c_nome2, c_nome;
			char ignore;

			istringstream input(line);
			input >> c_id >> ignore >> c_nome1 >> c_nome2 >> ignore >> c_hturno >> ignore >> c_hsemana >> ignore >> c_hdescanso;
			c_nome = c_nome1 + " " + c_nome2;

			c.setID(c_id);
			c.setNome(c_nome);
			c.setTurno(c_hturno);
			c.setSemana(c_hsemana);
			c.setDescanso(c_hdescanso);

			newCondutores[c_id] = c;
		}

		file.close();
	}

	empresa.setCondutores(newCondutores);
}
void Empresa::fillLinhas(string filename)
{
	mapLinha newLinhas;

	ifstream file(filename);

	string temp;
	unsigned int contador = 0;

	while (getline(file, temp))
		contador++;
	file.close();

	file.open(filename);

	if (file.is_open())
	{
		for (size_t i = 1; i <= contador; i++)

		{
			string line;
			getline(file, line);

			//Nova linha
			Linha l;

			unsigned int l_id, l_freq;
			vector<string> l_paragens;
			vector<unsigned int> l_tempo;
			char ignore;

			istringstream input(line);

			input >> l_id >> ignore >> l_freq;

			string input_paragens = line;
			string input_tempos = line;

			//Retirar a parte incial
			unsigned int uno = input_paragens.find(';');
			input_paragens.erase(0, uno + 2);
			input_tempos.erase(0, uno + 2);

			//Retirar a segunda parte
			unsigned int duo = input_paragens.find(';');
			input_paragens.erase(0, duo + 2);
			input_tempos.erase(0, duo + 2);

			//Retirar a parte final
			unsigned int tre_p = input_paragens.find(';');
			unsigned int tre_t = input_tempos.find(';');
			input_paragens.erase(tre_p, input_paragens.length() - tre_p);
			input_tempos.erase(0, tre_t + 2);

			//Variaveis temporárias para retirar as paragens e os tempos
			string paragem_1a1;
			string tempo_1a1;

			//Retirar paragens
			for (size_t i = 0; i < input_paragens.length(); i++)
			{
				//Última paragem
				if (i == input_paragens.length() - 1)
				{
					if (input_paragens.at(i) != ' ')
						paragem_1a1 += input_paragens.at(i);

					l_paragens.push_back(paragem_1a1);

				}
				else if (input_paragens.at(i) == ';')
					break;
				else if (input_paragens.at(i) == ' ')
				{
					if (input_paragens.at(i - 1) == ',')
						continue;
					else
						paragem_1a1 += " ";
				}
				else if (input_paragens.at(i) == ',')
				{
					l_paragens.push_back(paragem_1a1);
					paragem_1a1 = "";
				}
				else
					paragem_1a1 += input_paragens.at(i);
			}

			//Retirar tempos
			for (size_t i = 0; i < input_tempos.length(); i++)
			{
				//Último tempo
				if (i == input_tempos.length() - 1)
				{
					tempo_1a1 += input_tempos.at(i);
					int tempo_temp;
					istringstream temp(tempo_1a1);
					temp >> tempo_temp;
					l_tempo.push_back(tempo_temp);
				}
				else if (input_paragens.at(i) == ';')
					break;
				else if (input_tempos.at(i) == ' ')
					continue;
				else if (input_tempos.at(i) == ',')
				{
					int tempo_temp;
					istringstream temp(tempo_1a1);
					temp >> tempo_temp;
					l_tempo.push_back(tempo_temp);
					tempo_1a1 = "";
				}
				else
					tempo_1a1 += input_tempos.at(i);
			}

			l.setID(l_id);
			l.setFreq(l_freq);
			l.setParagens(l_paragens);
			l.setTempos(l_tempo);

			newLinhas[l_id] = l;

		}

		file.close();
	}

	empresa.setLinhas(newLinhas);
}

void Empresa::saveCondutores(string filename)
{
	ofstream file(filename);

	mapCondutor oldCondutores = empresa.getCondutores();

	for (mapCondutor::iterator i = oldCondutores.begin(); i != oldCondutores.end(); i++)
	{
		Condutor c = i->second;

		file << c.getID() << " ; " << c.getNome() << " ; " << c.getTurno() << " ; " << c.getSemana() << " ; " << c.getDescanso() << endl;

	}

	file.close();
}
void Empresa::saveLinhas(string filename)
{
	ofstream file(filename);

	mapLinha oldLinhas = empresa.getLinhas();

	for (mapLinha::iterator i = oldLinhas.begin(); i != oldLinhas.end(); i++)
	{
		Linha l = i->second;

		file << l.getID() << setw(3) << " ; " << l.getFreq() << " ; ";

		for (size_t y = 0; y < l.getParagens().size(); y++)
		{
			if (y == l.getParagens().size() - 1)
				file << l.getParagens().at(y) << " ; ";
			else
				file << l.getParagens().at(y) << ", ";
		}
		for (size_t y = 0; y < l.getTempos().size(); y++)
		{
			if (y == l.getTempos().size() - 1)
				file << l.getTempos().at(y) << endl;
			else
				file << l.getTempos().at(y) << ", ";
		}
	}

	file.close();
}

void Empresa::createLinha()
{
	//Nova linha
	Linha l;

	unsigned int l_id, l_freq;
	vector<string> l_paragens;
	vector<unsigned int> l_tempo;

	string input_id;
	string input_freq;
	string input_paragem;
	string input_tempo;

	cout << endl << " ID? ";

id:
	getline(cin, input_id);

	switch (inputErrorHandling(input_id, 'i'))
	{
	case 0:
		cerr << "Input inválido. Introduza novamente:";
		goto id;
	case 1:
		break;
	case 2:
		cerr << "Operação cancelada.\n";
		_getch();
		return;
	}

	istringstream stream_id(input_id);
	stream_id >> l_id;

	if (inputExist(l_id, 'l'))
	{
		cerr << " Essa linha já existe. Escolha outra: ";
		goto id;
	}

	cout << endl << " Frequência de circulação de autocarros? ";

frequencia:
	getline(cin, input_freq);

	switch (inputErrorHandling(input_freq, 'n'))
	{
	case 0:
		cerr << "Input inválido. Introduza novamente:";
		goto frequencia;
	case 1:
		break;
	case 2:
		cerr << "Operação cancelada.\n";
		_getch();
		return;
	}

	istringstream stream_freq(input_freq);
	stream_freq >> l_freq;

	cout << endl << " Lista de paragens (CTRL-Z para terminar): " << endl;
	unsigned int cont_p = 0;

paragens:
	cout << " Paragem número " << cont_p + 1 << ": ";

	getline(cin, input_paragem);

	if (cin.eof())
	{
		cin.clear();
		goto endparagens;
	}

	switch (inputErrorHandling(input_paragem, 'p'))
	{
	case 0:
		cerr << "Input inválido. Introduza novamente:";
		goto paragens;
	case 1:
		break;
	case 2:
		cerr << "Operação cancelada.\n";
		_getch();
		return;
	}

	if (inputExist(input_paragem, l_paragens))
	{
		cerr << " Já existe esta paragem nesta linha.\n";
		goto paragens;
	}

	cont_p++;
	l_paragens.push_back(input_paragem);
	goto paragens;

endparagens:
	cout << " Lista dos tempos entre paragens: " << endl;
	int cont_t = 0;

tempo:
	if (cont_t == cont_p - 1)
		goto endtempos;
	else
	{
		cout << " Tempo número " << cont_t + 1 << ": ";

		getline(cin, input_tempo);

		switch (inputErrorHandling(input_tempo, 'n'))
		{
		case 0:
			cerr << "Input inválido. Introduza novamente:";
			goto tempo;
		case 1:
			break;
		case 2:
			cerr << "Operação cancelada.\n";
			_getch();
			return;
		}

		cont_t++;
		int temp;
		istringstream t(input_tempo); t >> temp;
		l_tempo.push_back(temp);
		goto tempo;
	}

endtempos:
	l.setID(l_id);
	l.setFreq(l_freq);
	l.setParagens(l_paragens);
	l.setTempos(l_tempo);

	mapLinha newLinhas = empresa.getLinhas();
	newLinhas[l_id] = l;

	empresa.setLinhas(newLinhas);

	alterado_linha = true;

	return;

}
void Empresa::modifyLinha()
{
	string input_id;
	unsigned int l_id;

	mapLinha lLinhas = empresa.getLinhas();

	cout << "Linhas existentes:" << endl;

	for (mapLinha::iterator i = lLinhas.begin(); i != lLinhas.end(); i++)
	{
		cout << i->second.getID() << endl;
	}

	cout << " \nQue linha pretende alterar? ";

id:
	getline(cin, input_id);

	switch (inputErrorHandling(input_id, 'i'))
	{
	case 0:
		cerr << "Input inválido. Introduza novamente:";
		goto id;
	case 1:
		break;
	case 2:
		cerr << "Operação cancelada.\n";
		_getch();
		return;
	}

	istringstream stream_id(input_id);
	stream_id >> l_id;

	if (!inputExist(l_id, 'l'))
	{
		cerr << " Essa linha não existe. Escolha outro: ";
		goto id;
	}

	mapLinha newLinhas = empresa.getLinhas();

	mapLinha::iterator it = newLinhas.find(l_id);

	cout << endl << " Linha:\n" << " ID: " << it->second.getID() <<
		"\n Frequência: " << it->second.getFreq() <<
		"\n Paragens: ";

	for (size_t i = 0; i < it->second.getParagens().size(); i++)
	{
		if (i == it->second.getParagens().size() - 1)
			cout << it->second.getParagens().at(i) << "\n Tempos: ";
		else
			cout << it->second.getParagens().at(i) << ", ";
	}
	for (size_t i = 0; i < it->second.getTempos().size(); i++)
	{
		if (i == it->second.getTempos().size() - 1)
			cout << it->second.getTempos().at(i) << endl << endl;
		else
			cout << it->second.getTempos().at(i) << ", ";
	}

	cout << " Que propriedade pretende alterar?\n\n" <<
		" [#1] ID\n" <<
		" [#2] Frequência\n" <<
		" [#3] Paragens\n" <<
		" [#4] Tempos\n\n";
	cout << " Escolha uma opção!\n\n";

erro:
	char input = _getch();

	switch (input)
	{
	case '0':
	{
		cout << " Operação cancelada.\n";
		_getch();
		return;
	}
	case '1':
	{
		//Novo ID
		unsigned int new_id;
		string alt_id;

		cout << " ID? ";

	a_id:
		getline(cin, alt_id);

		switch (inputErrorHandling(alt_id, 'i'))
		{
		case 0:
			cerr << "Input inválido. Introduza novamente:";
			goto a_id;
		case 1:
			break;
		case 2:
			cerr << "Operação cancelada.\n";
			_getch();
			return;
		}

		istringstream stream_alt_id(alt_id);
		stream_alt_id >> new_id;

		if (inputExist(new_id, 'l'))
		{
			cerr << " Essa linha já existe. Escolha outra: ";
			goto a_id;
		}

		it->second.setID(new_id);

		alterado_linha = true;

		break;
	}
	case '2':
	{
		//Nova frequência
		unsigned int new_freq;
		string alt_freq;

		cout << " Frequência de circulação de autocarros? ";

	a_frequencia:
		getline(cin, alt_freq);

		switch (inputErrorHandling(alt_freq, 'n'))
		{
		case 0:
			cerr << "Input inválido. Introduza novamente:";
			goto a_frequencia;
		case 1:
			break;
		case 2:
			cerr << "Operação cancelada.\n";
			_getch();
			return;
		}

		istringstream stream_alt_freq(alt_freq);
		stream_alt_freq >> new_freq;

		it->second.setFreq(new_freq);

		alterado_linha = true;

		break;
	}
	case '3':
	{
		//Nova paragem
		vector<string> new_paragens;
		string alt_paragens;
		unsigned int cont_p = 1;

		cout << " Lista de paragens (CTLR-Z para terminar): " << endl;

	a_paragem:
		cout << " Paragem número " << cont_p << ": ";

		getline(cin, alt_paragens);

		if (cin.eof())
		{
			cin.clear();
			goto endparagens;
		}

		switch (inputErrorHandling(alt_paragens, 'p'))
		{
		case 0:
			cerr << "Input inválido. Introduza novamente:";
			goto a_paragem;
		case 1:
			break;
		case 2:
			cerr << "Operação cancelada.\n";
			_getch();
			return;
		}

		switch (inputExist(alt_paragens, new_paragens))
		{
		case false:
			cont_p++;
			new_paragens.push_back(alt_paragens);
			goto a_paragem;
		case true:
			cerr << " Já existe esta paragem nesta linha.";
			goto a_paragem;
		}

	endparagens:
		if (new_paragens.size() != it->second.getTempos().size() + 1)
		{
			vector<unsigned int> temp(new_paragens.size() - 1, 0);
			it->second.setTempos(temp);

			cout << " Reset dos tempos desta linha! Não se esqueça de preenchê-los.\n";
		}

		it->second.setParagens(new_paragens);

		alterado_linha = true;

		break;
	}
	case '4':
	{
		//Novo tempo
		vector<unsigned int> new_tempo;
		string alt_tempos;
		unsigned int cont_t = 1;

		cout << " Lista dos tempos entre paragens (CTLR-Z para terminar): " << endl;

	a_tempos:
		cout << " Tempo número " << cont_t << ": ";

		getline(cin, alt_tempos);

		if (cin.eof())
		{
			cin.clear();
			goto endtempos;
		}

		switch (inputErrorHandling(alt_tempos, 'n'))
		{
		case 0:
			cerr << "Input inválido. Introduza novamente:";
			goto a_tempos;
		case 1:
		{
			cont_t++;
			int temp;
			istringstream t(alt_tempos); t >> temp;
			new_tempo.push_back(temp);
			goto a_tempos;
		}
		case 2:
			cerr << "Operação cancelada.\n";
			_getch();
			return;
		}

	endtempos:
		if (new_tempo.size() != it->second.getParagens().size() - 1)
		{
			vector<string> temp(new_tempo.size() + 1, "null");
			it->second.setParagens(temp);

			cout << " Reset das paragens desta linha! Não se esqueça de preenchê-las.\n";
		}

		it->second.setTempos(new_tempo);

		alterado_linha = true;

		break;
	}
	default:
		goto erro;
	}

	empresa.setLinhas(newLinhas);

	cout << " A linha foi alterada com sucesso.\n.";
	_getch();

	return;
}
void Empresa::removeLinha()
{
	string input_id;
	unsigned int l_id, contador = 0;

	mapLinha lLinhas = empresa.getLinhas();

	cout << "Linhas existentes:" << endl;

	for (mapLinha::iterator i = lLinhas.begin(); i != lLinhas.end(); i++)
	{
		cout << i->second.getID() << endl;
	}

	cout << " \nQue linha pretende remover? ";

id:
	getline(cin, input_id);

	switch (inputErrorHandling(input_id, 'i'))
	{
	case 0:
		cerr << "Input inválido. Introduza novamente:";
		goto id;
	case 1:
		break;
	case 2:
		cerr << "Operação cancelada.\n";
		_getch();
		return;
	}

	istringstream stream_id(input_id);
	stream_id >> l_id;

	if (!inputExist(l_id, 'l'))
	{
		cerr << " Essa linha não existe. Escolha outra: ";
		goto id;
	}

	mapLinha newLinhas = empresa.getLinhas();
	newLinhas.erase(l_id);

	empresa.setLinhas(newLinhas);

	alterado_linha = true;

	return;

}

void Empresa::createCondutor()
{
	//Novo condutor
	Condutor c;

	unsigned int c_id, c_hturno, c_hsemana, c_hdescanso;
	string c_nome;

	string input_id;
	string input_nome1;
	string input_nome2;
	string input_hturno;
	string input_hsemana;
	string input_hdescanso;

	cout << " ID? ";

id:
	getline(cin, input_id);

	switch (inputErrorHandling(input_id, 'i'))
	{
	case 0:
		cerr << "Input inválido. Introduza novamente:";
		goto id;
	case 1:
		break;
	case 2:
		cerr << "Operação cancelada.\n";
		_getch();
		return;
	}

	istringstream stream_id(input_id);
	stream_id >> c_id;

	if (inputExist(c_id, 'c'))
	{
		cerr << " Esse condutor já existe. Escolha outro: ";
		goto id;
	}

	cout << endl << " Primeiro nome? ";

nome1:
	getline(cin, input_nome1);

	switch (inputErrorHandling(input_nome1, 's'))
	{
	case 0:
		cerr << "Input inválido. Introduza novamente:";
		goto nome1;
	case 1:
		break;
	case 2:
		cerr << "Operação cancelada.\n";
		_getch();
		return;
	}

	istringstream stream_nome1(input_nome1);
	string c_nome1;
	stream_nome1 >> c_nome1;
	c_nome = c_nome1 + " ";

	cout << endl << " Segundo nome? ";

nome2:
	getline(cin, input_nome2);

	switch (inputErrorHandling(input_nome2, 's'))
	{
	case 0:
		cerr << "Input inválido. Introduza novamente:";
		goto nome2;
	case 1:
		break;
	case 2:
		cerr << "Operação cancelada.\n";
		_getch();
		return;
	}

	istringstream stream_nome2(input_nome2);
	string c_nome2;
	stream_nome2 >> c_nome2;

	c_nome += c_nome2;

	cout << endl << " Número de horas de trabalho por turno? ";

turno:
	getline(cin, input_hturno);

	switch (inputErrorHandling(input_hturno, 'n'))
	{
	case 0:
		cerr << "Input inválido. Introduza novamente:";
		goto turno;
	case 1:
		break;
	case 2:
		cerr << "Operação cancelada.\n";
		_getch();
		return;
	}

	istringstream stream_hturno(input_hturno);
	stream_hturno >> c_hturno;

	cout << endl << " Número de horas de trabalho por semana? ";

semana:
	getline(cin, input_hsemana);

	switch (inputErrorHandling(input_hsemana, 'n'))
	{
	case 0:
		cerr << "Input inválido. Introduza novamente:";
		goto semana;
	case 1:
		break;
	case 2:
		cerr << "Operação cancelada.\n";
		_getch();
		return;
	}

	istringstream stream_hsemana(input_hsemana);
	stream_hsemana >> c_hsemana;

	cout << endl << " Número de horas de descanso entre turnos? ";

descanso:
	getline(cin, input_hdescanso);

	switch (inputErrorHandling(input_hdescanso, 'n'))
	{
	case 0:
		cerr << "Input inválido. Introduza novamente:";
		goto descanso;
	case 1:
		break;
	case 2:
		cerr << "Operação cancelada.\n";
		_getch();
		return;
	}

	istringstream stream_hdescanso(input_hdescanso);
	stream_hdescanso >> c_hdescanso;

	c.setID(c_id);
	c.setNome(c_nome);
	c.setTurno(c_hturno);
	c.setSemana(c_hsemana);
	c.setDescanso(c_hdescanso);

	mapCondutor newCondutores = empresa.getCondutores();
	newCondutores[c_id] = c;

	empresa.setCondutores(newCondutores);

	alterado_condutor = true;

	return;
}
void Empresa::modifyCondutor()
{
	string input_id;
	unsigned int c_id;

	mapCondutor cCondutores = empresa.getCondutores();

	cout << "Condutores existentes:" << endl;

	for (mapCondutor::iterator i = cCondutores.begin(); i != cCondutores.end(); i++)
	{
		cout << i->second.getID() << endl;
	}

	cout << " \nQue condutor pretende alterar? ";

id:
	getline(cin, input_id);

	switch (inputErrorHandling(input_id, 'i'))
	{
	case 0:
		cerr << "Input inválido. Introduza novamente:";
		goto id;
	case 1:
		break;
	case 2:
		cerr << "Operação cancelada.\n";
		_getch();
		return;
	}

	istringstream stream_id(input_id);
	stream_id >> c_id;

	if (!inputExist(c_id, 'c'))
	{
		cerr << " Esse condutor não existe. Escolha outro: ";
		goto id;
	}

	mapCondutor newCondutores = empresa.getCondutores();

	mapCondutor::iterator it = newCondutores.find(c_id);

	cout << endl << " Condutor:\n" << " ID: " << it->second.getID() <<
		"\n Nome: " << it->second.getNome() <<
		"\n Horas turno: " << it->second.getTurno() <<
		"\n Horas semanais: " << it->second.getSemana() <<
		"\n Horas de descanso: " << it->second.getDescanso() << endl << endl;

	cout << " Que propriedade pretende alterar?\n" << endl <<
		" (1) ID\n" <<
		" (2) Nome\n" <<
		" (3) Horas turno\n" <<
		" (4) Horas semanais\n" <<
		" (5) Horas de descanso\n\n";
	cout << " Escolha um opção!\n\n";

erro:
	char input = _getch();

	switch (input)
	{
	case '0':
	{
		cout << " Operação cancelada.\n";
		_getch();
		return;
	}
	case '1':
	{
		//Novo ID
		unsigned int new_id;
		string alt_id;

		cout << " ID? ";

	a_id:
		getline(cin, alt_id);

		switch (inputErrorHandling(alt_id, 'i'))
		{
		case 0:
			cerr << "Input inválido. Introduza novamente:";
			goto a_id;
		case 1:
			break;
		case 2:
			cerr << "Operação cancelada.\n";
			_getch();
			return;
		}

		istringstream stream_alt_id(alt_id);
		stream_alt_id >> new_id;

		if (inputExist(new_id, 'c'))
		{
			cerr << " Esse condutor já existe. Escolha outro: ";
			goto a_id;
		}

		it->second.setID(new_id);

		alterado_condutor = true;

		break;
	}
	case '2':
	{
		//Novo nome
		string new_nome;
		string new_nome1;
		string new_nome2;
		string alt_nome1;
		string alt_nome2;

		cout << " Primeiro nome? ";

	a_nome1:
		getline(cin, alt_nome1);

		switch (inputErrorHandling(alt_nome1, 's'))
		{
		case 0:
			cerr << "Input inválido. Introduza novamente:";
			goto a_nome1;
		case 1:
			break;
		case 2:
			cerr << "Operação cancelada.\n";
			_getch();
			return;
		}

		istringstream stream_nome1(alt_nome1);
		stream_nome1 >> new_nome1;
		new_nome = new_nome1 + " ";

		cout << " Segundo nome? ";

	a_nome2:
		getline(cin, alt_nome2);

		switch (inputErrorHandling(alt_nome2, 's'))
		{
		case 0:
			cerr << "Input inválido. Introduza novamente:";
			goto a_nome2;
		case 1:
			break;
		case 2:
			cerr << "Operação cancelada.\n";
			_getch();
			return;
		}

		istringstream stream_nome2(alt_nome2);
		stream_nome2 >> new_nome2;
		new_nome += new_nome2;

		it->second.setNome(new_nome);

		alterado_condutor = true;

		break;
	}
	case '3':
	{
		//Nova hora turno
		unsigned int new_hturno;
		string alt_hturno;

		cout << " Número de horas de trabalho por turno ? ";

	a_turno:
		getline(cin, alt_hturno);

		switch (inputErrorHandling(alt_hturno, 'n'))
		{
		case 0:
			cerr << "Input inválido. Introduza novamente:";
			goto a_turno;
		case 1:
			break;
		case 2:
			cerr << "Operação cancelada.\n";
			_getch();
			return;
		}

		istringstream stream_alt_hturno(alt_hturno);
		stream_alt_hturno >> new_hturno;

		it->second.setTurno(new_hturno);

		alterado_condutor = true;

		break;
	}
	case '4':
	{
		//Nova hora semanal
		unsigned int new_hsemana;
		string alt_hsemana;

		cout << " Número de horas de trabalho por semana? ";

	a_semana:
		getline(cin, alt_hsemana);

		switch (inputErrorHandling(alt_hsemana, 'n'))
		{
		case 0:
			cerr << "Input inválido. Introduza novamente:";
			goto a_semana;
		case 1:
			break;
		case 2:
			cerr << "Operação cancelada.\n";
			_getch();
			return;
		}

		istringstream stream_hsemana(alt_hsemana);
		stream_hsemana >> new_hsemana;

		it->second.setSemana(new_hsemana);

		alterado_condutor = true;

		break;
	}
	case '5':
	{
		//Nova hora descanso
		unsigned int new_hdescanso;
		string alt_hdescanso;

		cout << " Número de horas de descanso entre turnos? ";

	a_descanso:
		getline(cin, alt_hdescanso);

		switch (inputErrorHandling(alt_hdescanso, 'n'))
		{
		case 0:
			cerr << "Input inválido. Introduza novamente:";
			goto a_descanso;
		case 1:
			break;
		case 2:
			cerr << "Operação cancelada.\n";
			_getch();
			return;
		}

		istringstream stream_hdescanso(alt_hdescanso);
		stream_hdescanso >> new_hdescanso;

		it->second.setDescanso(new_hdescanso);

		alterado_condutor = true;

		break;
	}
	default:
		goto erro;
	}

	empresa.setCondutores(newCondutores);

	cout << " O condutor foi alterado com sucesso.\n.";
	_getch();

	return;
}
void Empresa::removeCondutor()
{
	string input_id;
	unsigned int c_id, contador = 0;

	mapCondutor cCondutores = empresa.getCondutores();

	cout << "Condutores existentes:" << endl;

	for (mapCondutor::iterator i = cCondutores.begin(); i != cCondutores.end(); i++)
	{
		cout << i->second.getID() << endl;
	}

	cout << " \nQue condutor pretende remover? ";

id:
	getline(cin, input_id);

	switch (inputErrorHandling(input_id, 'i'))
	{
	case 0:
		cerr << "Input inválido. Introduza novamente:";
		goto id;
	case 1:
		break;
	case 2:
		cerr << "Operação cancelada.\n";
		_getch();
		return;
	}

	istringstream stream_id(input_id);
	stream_id >> c_id;

	if (!inputExist(c_id, 'c'))
	{
		cerr << " Esse condutor não existe. Escolha outro: ";
		goto id;
	}

	mapCondutor newCondutores = empresa.getCondutores();
	newCondutores.erase(c_id);

	empresa.setCondutores(newCondutores);

	alterado_condutor = true;

	return;
}

void Empresa::horarioLinha()
{
	//Linha
	Linha l;

	unsigned int l_id, direc;
	string input_id;

	mapLinha lLinhas = empresa.getLinhas();

	cout << "Linhas existentes:" << endl;

	for (mapLinha::iterator i = lLinhas.begin(); i != lLinhas.end(); i++)
	{
		cout << i->second.getID() << endl;
	}

	cout << " \nQue linha pretende visualizar o horário? ";

id:
	getline(cin, input_id);

	switch (inputErrorHandling(input_id, 'i'))
	{
	case 0:
		cerr << "Input inválido. Introduza novamente:";
		goto id;
	case 1:
		break;
	case 2:
		cerr << "Operação cancelada.\n";
		_getch();
		return;
	}

	istringstream stream_id(input_id);
	stream_id >> l_id;

	if (!inputExist(l_id, 'l'))
	{
		cerr << " Essa linha não existe. Escolha outra: ";
		goto id;
	}

	l = empresa.getLinhas()[l_id];

	//Output inicial
	string sentido_normal = l.getParagens().at(0);
	string sentido_inverso = l.getParagens().at(l.getParagens().size() - 1);
	cout << endl << " (1) Partida de " << sentido_normal << "\n (2) Partida de " << sentido_inverso << "? \n\n";
	cout << " Escolha um opção! ";

erro:
	char input = _getch();

	switch (input)
	{
	case '0':
		cout << " Operação cancelada.\n";
		_getch();
		return;
	case '1':
		direc = 1;
		break;
	case '2':
		direc = 2;
		break;
	default:
		goto erro;
	}

	showHorario(l, direc);

	return;

}
void Empresa::horarioParagem()
{
	//Paragem
	string input_paragem;

	vector<Linha> linhas_com_a_paragem;

	typedef tuple <unsigned int, vector <Tempo>, vector <Tempo> > parNormInv;
	vector<parNormInv> vectorOutput;

	cout << " Paragem?";

paragem:
	getline(cin, input_paragem);

	switch (inputErrorHandling(input_paragem, 'p'))
	{
	case 0:
		cerr << "Input inválido. Introduza novamente:";
		goto paragem;
	case 1:
		break;
	case 2:
		cerr << "Operação cancelada.\n";
		_getch();
		return;
	}

	if (inputExist(input_paragem).size() == 0)
	{
		cerr << " Essa paragem não existe. Escolha outra: ";
		goto paragem;
	}

	mapLinha linhas = empresa.getLinhas();

	//Procurar paragem para ir buscar as linhas que contém as paragens
	for (mapLinha::iterator i = linhas.begin(); i != linhas.end(); i++)
	{
		for (size_t y = 0; y < i->second.getParagens().size(); y++)
		{
			if (compararCaseInsensitive(i->second.getParagens().at(y), input_paragem))
			{
				linhas_com_a_paragem.push_back(empresa.getLinhas()[i->first]);
				break;
			}
		}
	}

	//Para cada linha que contém a paragem
	for (size_t i = 0; i < linhas_com_a_paragem.size(); i++)
	{
		Linha l = linhas_com_a_paragem.at(i);
		vector<Tempo> horas_paragem_n; //horas a que passa na paragem, sentido normal
		vector<Tempo> horas_paragem_i; //horas a que passa na paragem, sentido inverso

		unsigned int index_linha_n, index_linha_i;

		//Descobrir onde está a paragem pretendida nos dois sentidos 
		for (size_t z = 0; z < l.getParagens().size(); z++)
		{
			if (compararCaseInsensitive(l.getParagens().at(z), input_paragem))
			{
				index_linha_n = z;
				index_linha_i = (l.getParagens().size() - 1) - z;
				break;
			}
		}

		//Tempo que demora a fazer um viagem (quer no sentido normal, quer no sentido inverso)
		unsigned int sum = 0;
		for (size_t e = 0; e < l.getTempos().size(); e++)
		{
			sum += l.getTempos().at(e);
		}

		//Tempo desde a paragem inicial até à final, sentido normal
		int sum_n = 0;
		for (size_t x = 0; x < index_linha_n; x++)
		{
			sum_n += l.getTempos().at(x);
		}

		//Tempo desde a paragem inicial até à final, sentido inverso
		int sum_i = 0;
		vector<unsigned int> t_inv = l.getTempos(); reverse(t_inv.begin(), t_inv.end());
		for (size_t w = 0; w < index_linha_i; w++)
		{
			sum_i += t_inv.at(w);
		}

		Tempo actualNormal = T_INICIO;
		Tempo actualInverso = T_INICIO; actualInverso.sumTempo(sum);

		//Acabar de preencher o vetor com tempos iniciais?
		bool acabarPreencher = false;

		//Vetores com os tempos iniciais dos dois sentidos
		vector <Tempo> temposNormais; temposNormais.push_back(actualNormal);
		vector <Tempo> temposInversos; temposInversos.push_back(actualInverso);

		while (!acabarPreencher)
		{
			actualNormal.sumTempo(l.getFreq());
			actualInverso.sumTempo(l.getFreq());

			if (actualNormal.getHora() > T_FIM.getHora() || (actualNormal.getHora() == T_FIM.getHora() && actualNormal.getMinuto() > T_FIM.getMinuto()))
				acabarPreencher = true;
			else
				temposNormais.push_back(actualNormal);

			if (actualInverso.getHora() > T_FIM.getHora() || (actualInverso.getHora() == T_FIM.getHora() && actualInverso.getMinuto() > T_FIM.getMinuto()))
				acabarPreencher = true;
			else
				temposInversos.push_back(actualInverso);
		}

		//Preencher sentido normal:
		for (size_t k = 0; k < temposNormais.size(); k++)
		{
			Tempo result = temposNormais.at(k);

			result.sumTempo(sum_n);

			horas_paragem_n.push_back(result);
		}

		//Preencher sentido inverso:
		for (size_t k = 0; k < temposInversos.size(); k++)
		{
			Tempo result = temposInversos.at(k);

			result.sumTempo(sum_i);

			horas_paragem_i.push_back(result);
		}

		//Output da linha
		parNormInv linhaOutput = { linhas_com_a_paragem.at(i).getID(), horas_paragem_n, horas_paragem_i };

		vectorOutput.push_back(linhaOutput);
	}

	//Output
	for (size_t p = 0; p < vectorOutput.size(); p++)
	{
		parNormInv outp = vectorOutput.at(p);

		//Propriedades (ID e vetores com os tempos do sentido normal e inverso)
		unsigned int id_outp = get<0>(outp);
		vector<Tempo> n_outp = get<1>(outp);
		vector<Tempo> i_outp = get<2>(outp);

		cout << " Linha: " << id_outp << endl;
		cout << " Sentido Normal" << "     " << " Sentido Inverso" << endl;

		for (size_t a = 0; a < n_outp.size(); a++)
		{
			cout << " " << n_outp.at(a).showTempo();

			if (a < i_outp.size())
				cout << setw(20) << i_outp.at(a).showTempo() << endl;
		}

		cout << endl << endl;
	}

	_getch();

	return;

}
void Empresa::percursoParagem()
{
	//Paragem inicial e final
	string start, finish;

	bool found_start = false, found_finish = false;
	unsigned index_start, index_finish;
	vector< vector<unsigned int> > linhasStartFinish;

	cout << " Qual a paragem inicial? ";

paragem_inicial:
	getline(cin, start);

	switch (inputErrorHandling(start, 'p'))
	{
	case 0:
		cerr << "Input inválido. Introduza novamente:";
		goto paragem_inicial;
	case 1:
		break;
	case 2:
		cerr << "Operação cancelada.\n";
		_getch();
		return;
	}

	if (inputExist(start).size() == 0)
	{
		cerr << " A paragem não existe. Paragem inicial? ";
		_getch();
		goto paragem_inicial;
	}

	cout << " Qual é a paragem final? ";

paragem_final:
	getline(cin, finish);

	switch (inputErrorHandling(finish, 'p'))
	{
	case 0:
		cerr << "Input inválido. Introduza novamente:";
		goto paragem_final;
	case 1:
		break;
	case 2:
		cerr << "Operação cancelada.\n";
		_getch();
		return;
	}

	if (inputExist(finish).size() == 0)
	{
		cerr << " A paragem não existe. Paragem final? ";
		_getch();
		goto paragem_final;
	}

	mapLinha lLinhas = empresa.getLinhas();

	for (mapLinha::iterator i = lLinhas.begin(); i != lLinhas.end(); i++)
	{
		for (size_t y = 0; y < i->second.getParagens().size(); y++)
		{
			if (compararCaseInsensitive(i->second.getParagens().at(y), start))
			{
				found_start = true;
				index_start = y;
			}
			else if (compararCaseInsensitive(i->second.getParagens().at(y), finish))
			{
				found_finish = true;
				index_finish = y;
			}
		}

		if (found_start && found_finish)
			linhasStartFinish.push_back({ i->first, index_start, index_finish });

		found_start = false;
		found_finish = false;
	}

	if (linhasStartFinish.size() == 0)
	{
		cerr << " Não existe nenhuma linha com essas paragens. Paragem inicial? ";
		_getch();
		goto paragem_inicial;
	}

	//Output
	int nrOpcao = 1;

	for (size_t i = 0; i < linhasStartFinish.size(); i++)
	{
		//Variaveis
		int idlinha = linhasStartFinish.at(i).at(0);
		unsigned int i1 = linhasStartFinish.at(i).at(1);
		unsigned int i2 = linhasStartFinish.at(i).at(2);
		int sumtempos = 0;
		string percurso = "";

		if (i2 > i1)
		{
			for (size_t z = i1; z < i2; z++)
			{
				//Último elemento
				if (z == i2 - 1)
				{
					sumtempos += lLinhas[idlinha].getTempos().at(z);
					percurso += lLinhas[idlinha].getParagens().at(z);
					percurso += " -> " + lLinhas[idlinha].getParagens().at(z + 1);

					cout << "\n Opção nº " << nrOpcao << endl;
					cout << " Linha: " << idlinha << endl;
					cout << " Percurso: " << percurso << endl;
					cout << " Tempo total: " << sumtempos << endl;

					nrOpcao++;
				}
				else
				{
					sumtempos += lLinhas[idlinha].getTempos().at(z);
					percurso += lLinhas[idlinha].getParagens().at(z);
					percurso += " -> ";
				}
			}
		}
		else
		{
			vector<string> inversoParagens = lLinhas[idlinha].getParagens();
			reverse(inversoParagens.begin(), inversoParagens.end());
			vector<unsigned int> inversoTempos = lLinhas[idlinha].getTempos();
			reverse(inversoTempos.begin(), inversoTempos.end());

			i1 = (inversoParagens.size() - 1) - i1;
			i2 = (inversoParagens.size() - 1) - i2;

			for (size_t z = i1; z < i2; z++)
			{
				if (z == i2 - 1)
				{
					sumtempos += inversoTempos.at(z);
					percurso += inversoParagens.at(z);
					percurso += " -> " + inversoParagens.at(z + 1);

					cout << "\n Opção nº " << nrOpcao << endl;
					cout << " Linha: " << idlinha << endl;
					cout << " Percurso: " << percurso << endl;
					cout << " Tempo total: " << sumtempos << endl;

					nrOpcao++;
				}
				else
				{
					sumtempos += inversoTempos.at(z);
					percurso += inversoParagens.at(z);
					percurso += " -> ";
				}
			}
		}
	}

	_getch();

	return;
}

void Empresa::showHorario(Linha l, unsigned int sentido)
{
	//Tempo que demora a fazer um viagem (quer no sentido normal, quer no sentido inverso)
	unsigned int sum = 0;
	for (size_t i = 0; i < l.getTempos().size(); i++)
	{
		sum += l.getTempos().at(i);
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
		actualNormal.sumTempo(l.getFreq());
		actualInverso.sumTempo(l.getFreq());

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
	vector<unsigned int> temp_normal = l.getTempos(), temp_reverso = l.getTempos();
	reverse(temp_reverso.begin(), temp_reverso.end());

	//Vetor com elementos vetores (cada um com um conjunto de tempos ordenados a que se vai fazer output)
	vector < vector <Tempo> > vectorOutput;

	//Contadores
	unsigned int p_index = 0;
	unsigned int t_index = 0;

	//Vetor com as valores para usar no setw (de modo a formatar o output conforme o número de carácteres das paragens)
	vector<unsigned int> width;
	unsigned int t_width = 0;

	cout << endl << endl;

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
			if (p_index == l.getParagens().size() - 1)
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
			if (p_index == l.getParagens().size() - 1)
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

		for (size_t i = 0; i < l.getParagens().size(); i++)
		{
			if (i == l.getParagens().size() - 1)
			{
				cout << l.getParagens().at(i) << endl;
				width.push_back(l.getParagens().at(i).length() + 5);
			}
			else
			{
				cout << l.getParagens().at(i) << "     ";
				width.push_back(l.getParagens().at(i).length() + 5);
			}
		}

		cout << endl;

		break;
	}
	case 2:
	{
		vector<string> inv = l.getParagens();
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

	_getch();

	return;
}

void Empresa::inquirirParagem()
{
	//Linhas que incluem a paragem
	string input_paragem;
	vector<unsigned int> linhas_com_paragem;

	cout << endl << " Qual paragem pretende procurar? ";

input:
	getline(cin, input_paragem);

	switch (inputErrorHandling(input_paragem, 'p'))
	{
	case 0:
		cerr << "Input inválido. Paragem que pretende procurar? ";
		goto input;
	case 1:
		break;
	case 2:
		cerr << "Operação cancelada.\n";
		_getch();
		return;
	}

	linhas_com_paragem = inputExist(input_paragem);

	if (linhas_com_paragem.size() == 0)
		cerr << " Nenhuma linha contém esta paragem.\n";
	else
	{
		cout << endl << " Linhas com a paragem: " << endl;

		for (size_t i = 0; i < linhas_com_paragem.size(); i++)
		{
			cout << "> " << linhas_com_paragem.at(i) << endl;
		}
	}

	_getch();

	return;

}