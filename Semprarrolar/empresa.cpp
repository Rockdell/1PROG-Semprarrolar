#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <conio.h>
#include <queue>
#include <tuple>

#include "empresa.h"
#include "library.h"
#include "global.h"

using namespace std;

Empresa::Empresa()
{
	mapCondutor newCondutor;
	mapLinha newLinha;
	vector<linhasDia> newTrabalho(7);

	this->listaCondutores = newCondutor;
	this->listaLinhas = newLinha;
	this->vectorTrabalho = newTrabalho;
}

void Empresa::setCondutores(mapCondutor lcondutores)
{
	this->listaCondutores = lcondutores;
}
void Empresa::setLinhas(mapLinha llinhas)
{
	this->listaLinhas = llinhas;
}
void Empresa::setTrabalho(vector<linhasDia> vtrabalho)
{
	this->vectorTrabalho = vtrabalho;
}

mapCondutor Empresa::getCondutores() const
{
	return listaCondutores;
}
mapLinha Empresa::getLinhas() const
{
	return listaLinhas;
}
vector<linhasDia> Empresa::getTrabalho() const
{
	return vectorTrabalho;
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
	else
	{		
		fail = true;

		return;
	}

	empresa.setCondutores(newCondutores);

	return;
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
	else
	{
		fail = true;

		return;
	}

	empresa.setLinhas(newLinhas);

	return;
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

	cout << " ID? ";

id:
	getline(cin, input_id);

	switch (inputErrorHandling(input_id, 'i'))
	{
	case 0:
		cerr << " Input inválido. Introduza novamente: ";
		goto id;
	case 1:
		break;
	case 2:
		cerr << "\n Operação cancelada.\n";
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
		cerr << " Input inválido. Introduza novamente:";
		goto frequencia;
	case 1:
		break;
	case 2:
		cerr << " Operação cancelada.\n";
		_getch();
		return;
	}

	istringstream stream_freq(input_freq);
	stream_freq >> l_freq;

	cout << "\n Lista de paragens (CTRL-Z para terminar): " << endl;
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
		cerr << " Input inválido. Introduza novamente:";
		goto paragens;
	case 1:
		break;
	case 2:
		cerr << "\n Operação cancelada.\n";
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
	cout << "\n Lista dos tempos entre paragens: " << endl;
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
			cerr << " Input inválido. Introduza novamente:";
			goto tempo;
		case 1:
			break;
		case 2:
			cerr << "\n Operação cancelada.\n";
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
	alterado = true;

	return;

}
void Empresa::modifyLinha()
{
	string input_id;
	unsigned int l_id;

	mapLinha lLinhas = empresa.getLinhas();

	cout << " Linhas existentes:" << endl;

	for (mapLinha::iterator i = lLinhas.begin(); i != lLinhas.end(); i++)
	{
		cout << " " << i->second.getID() << endl;
	}

	cout << "\n Que linha pretende alterar? ";

id:
	getline(cin, input_id);

	switch (inputErrorHandling(input_id, 'i'))
	{
	case 0:
		cerr << " Input inválido. Introduza novamente:";
		goto id;
	case 1:
		break;
	case 2:
		cerr << "\n Operação cancelada.\n";
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

	mapLinha::iterator it = newLinhas.find(l_id);
	it->second.showLinha();

	cout << " Que propriedade pretende alterar?\n\n" <<
		" [1] ID\n" <<
		" [2] Frequência\n" <<
		" [3] Paragens\n" <<
		" [4] Tempos\n\n";
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
			cerr << " Input inválido. Introduza novamente: ";
			goto a_id;
		case 1:
			break;
		case 2:
			cerr << "\n Operação cancelada.\n";
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

		Linha temp = it->second;
		temp.setID(new_id);

		newLinhas.erase(it->first);

		newLinhas[new_id] = temp;

		alterado_linha = true;
		alterado = true;

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
			cerr << " Input inválido. Introduza novamente: ";
			goto a_frequencia;
		case 1:
			break;
		case 2:
			cerr << "\n Operação cancelada.\n";
			_getch();
			return;
		}

		istringstream stream_alt_freq(alt_freq);
		stream_alt_freq >> new_freq;

		it->second.setFreq(new_freq);

		alterado_linha = true;
		alterado = true;

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
			cerr << " Input inválido. Introduza novamente: ";
			goto a_paragem;
		case 1:
			break;
		case 2:
			cerr << "\n Operação cancelada.\n";
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
		alterado = true;

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
			cerr << " Input inválido. Introduza novamente: ";
			goto a_tempos;
		case 1:
		{
			cont_t++;
			unsigned int temp;
			istringstream t(alt_tempos); t >> temp;
			new_tempo.push_back(temp);
			goto a_tempos;
		}
		case 2:
			cerr << "\n Operação cancelada.\n";
			_getch();
			return;
		}

	endtempos:
		if (new_tempo.size() != it->second.getParagens().size() - 1)
		{
			vector<string> temp(new_tempo.size() + 1, "null");
			it->second.setParagens(temp);

			cout << "\n Reset das paragens desta linha! Não se esqueça de preenchê-las.\n";
		}

		it->second.setTempos(new_tempo);

		alterado_linha = true;
		alterado = true;

		break;
	}
	default:
		goto erro;
	}

	empresa.setLinhas(newLinhas);

	cout << "\n A linha foi alterada com sucesso. \n";
	_getch();

	return;
}
void Empresa::removeLinha()	
{
	string input_id;
	unsigned int l_id, contador = 0;

	mapLinha lLinhas = empresa.getLinhas();

	cout << " Linhas existentes: \n";

	for (mapLinha::iterator i = lLinhas.begin(); i != lLinhas.end(); i++)
	{
		cout << " " << i->second.getID() << endl;
	}

	cout << "\n Que linha pretende remover? ";

id:
	getline(cin, input_id);

	switch (inputErrorHandling(input_id, 'i'))
	{
	case 0:
		cerr << " Input inválido. Introduza novamente:";
		goto id;
	case 1:
		break;
	case 2:
		cerr << "\n Operação cancelada.\n";
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

	cout << "\n Tem a certeza que quer eliminar esta linha? [Y/N] \n";

confirmation:
	char input_confirmation = _getch();

	switch (toupper(input_confirmation))
	{
	case 'Y':
		break;
	case 'N':
		cout << "\n Operação cancelada.\n";
		_getch();
		return;
	default:
		goto confirmation;
	}

	mapLinha newLinhas = empresa.getLinhas();
	newLinhas.erase(l_id);

	empresa.setLinhas(newLinhas);

	alterado_linha = true;
	alterado = true;

	//Retirar os turnos desta linha (agr inexistente) aos condutores
	mapCondutor newCondutores = empresa.getCondutores();

	//Para cada condutor
	for (mapCondutor::iterator it = newCondutores.begin(); it != newCondutores.end(); it++)
	{
		//Trabalho do condutor
		vector<Trabalho> t_temp = it->second.getTrabalho();

		//Para cada trabalho do condutor
		for (size_t i = 0; i < t_temp.size(); i++)
		{
			if (t_temp.at(i).getLinhaID() == l_id)
			{
				t_temp.erase(t_temp.begin() + i);
			}
		}

		it->second.setTrabalho(t_temp);
	}

	empresa.setCondutores(newCondutores);

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
		cerr << " Input inválido. Introduza novamente: ";
		goto id;
	case 1:
		break;
	case 2:
		cerr << "\n Operação cancelada.\n";
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
		cerr << " Input inválido. Introduza novamente:";
		goto nome1;
	case 1:
		break;
	case 2:
		cerr << "\n Operação cancelada.\n";
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
		cerr << " Input inválido. Introduza novamente:";
		goto nome2;
	case 1:
		break;
	case 2:
		cerr << "\n Operação cancelada.\n";
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
		cerr << " Input inválido. Introduza novamente:";
		goto turno;
	case 1:
		break;
	case 2:
		cerr << "\n Operação cancelada.\n";
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
		cerr << " Input inválido. Introduza novamente:";
		goto semana;
	case 1:
		break;
	case 2:
		cerr << "\n Operação cancelada.\n";
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
		cerr << " Input inválido. Introduza novamente:";
		goto descanso;
	case 1:
		break;
	case 2:
		cerr << "\n Operação cancelada.\n";
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
	alterado = true;

	return;
}
void Empresa::modifyCondutor()
{
	string input_id;
	unsigned int c_id;

	mapCondutor cCondutores = empresa.getCondutores();

	cout << " Condutores existentes:" << endl;

	for (mapCondutor::iterator i = cCondutores.begin(); i != cCondutores.end(); i++)
	{
		cout << " " << i->second.getID() << endl;
	}

	cout << "\n Que condutor pretende alterar? ";

id:
	getline(cin, input_id);

	switch (inputErrorHandling(input_id, 'i'))
	{
	case 0:
		cerr << " Input inválido. Introduza novamente:";
		goto id;
	case 1:
		break;
	case 2:
		cerr << "\n Operação cancelada.\n";
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
	it->second.showCondutor();

	cout << " Que propriedade pretende alterar?\n\n" <<
		" [1] ID\n" <<
		" [2] Nome\n" <<
		" [3] Horas turno\n" <<
		" [4] Horas semanais\n" <<
		" [5] Horas de descanso\n\n";
	cout << " Escolha um opção!\n\n";

erro:
	char input = _getch();

	switch (input)
	{
	case '0':
	{
		cout << "\n Operação cancelada.\n";
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
			cerr << " Input inválido. Introduza novamente:";
			goto a_id;
		case 1:
			break;
		case 2:
			cerr << "\n Operação cancelada.\n";
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

		Condutor temp = it->second;
		temp.setID(new_id);

		newCondutores.erase(it->first);

		newCondutores[new_id] = temp;

		alterado_condutor = true;
		alterado = true;

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
			cerr << " Input inválido. Introduza novamente:";
			goto a_nome1;
		case 1:
			break;
		case 2:
			cerr << "\n Operação cancelada.\n";
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
			cerr << " Input inválido. Introduza novamente:";
			goto a_nome2;
		case 1:
			break;
		case 2:
			cerr << "\n Operação cancelada.\n";
			_getch();
			return;
		}

		istringstream stream_nome2(alt_nome2);
		stream_nome2 >> new_nome2;
		new_nome += new_nome2;

		it->second.setNome(new_nome);

		alterado_condutor = true;
		alterado = true;

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
			cerr << " Input inválido. Introduza novamente:";
			goto a_turno;
		case 1:
			break;
		case 2:
			cerr << "\n Operação cancelada.\n";
			_getch();
			return;
		}

		istringstream stream_alt_hturno(alt_hturno);
		stream_alt_hturno >> new_hturno;

		it->second.setTurno(new_hturno);

		alterado_condutor = true;
		alterado = true;

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
			cerr << " Input inválido. Introduza novamente:";
			goto a_semana;
		case 1:
			break;
		case 2:
			cerr << "\n Operação cancelada.\n";
			_getch();
			return;
		}

		istringstream stream_hsemana(alt_hsemana);
		stream_hsemana >> new_hsemana;

		it->second.setSemana(new_hsemana);

		alterado_condutor = true;
		alterado = true;

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
			cerr << " Input inválido. Introduza novamente:";
			goto a_descanso;
		case 1:
			break;
		case 2:
			cerr << "\n Operação cancelada.\n";
			_getch();
			return;
		}

		istringstream stream_hdescanso(alt_hdescanso);
		stream_hdescanso >> new_hdescanso;

		it->second.setDescanso(new_hdescanso);

		alterado_condutor = true;
		alterado = true;

		break;
	}
	default:
		goto erro;
	}

	empresa.setCondutores(newCondutores);

	cout << "\n O condutor foi alterado com sucesso.\n";
	_getch();

	return;
}
void Empresa::removeCondutor()
{
	string input_id;
	unsigned int c_id, contador = 0;

	mapCondutor cCondutores = empresa.getCondutores();

	cout << " Condutores existentes:" << endl;

	for (mapCondutor::iterator i = cCondutores.begin(); i != cCondutores.end(); i++)
	{
		cout << i->second.getID() << endl;
	}

	cout << "\n Que condutor pretende remover? ";

id:
	getline(cin, input_id);

	switch (inputErrorHandling(input_id, 'i'))
	{
	case 0:
		cerr << " Input inválido. Introduza novamente:";
		goto id;
	case 1:
		break;
	case 2:
		cerr << "\n Operação cancelada.\n";
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

	cout << "\n Tem a certeza que quer eliminar este condutor? [Y/N]\n";

confirmation:
	char input_confirmation = _getch();

	switch (toupper(input_confirmation))
	{
	case 'Y':
		break;
	case 'N':
		cout << "\n Operação cancelada.\n";
		_getch();
		return;
	default:
		goto confirmation;
	}

	mapCondutor newCondutores = empresa.getCondutores();
	newCondutores.erase(c_id);

	empresa.setCondutores(newCondutores);

	alterado_condutor = true;
	alterado = true;

	return;
}

void Empresa::horarioLinha()
{
	//Linha
	Linha l;

	unsigned int l_id, direc;
	string input_id;

	mapLinha lLinhas = empresa.getLinhas();

	cout << " Linhas existentes:" << endl;

	for (mapLinha::iterator i = lLinhas.begin(); i != lLinhas.end(); i++)
	{
		cout << " " << i->second.getID() << endl;
	}

	cout << "\n Que linha pretende visualizar o horário? ";

id:
	getline(cin, input_id);

	switch (inputErrorHandling(input_id, 'i'))
	{
	case 0:
		cerr << " Input inválido. Introduza novamente:";
		goto id;
	case 1:
		break;
	case 2:
		cerr << "\n Operação cancelada.\n";
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
	cout << endl << " [1] Partida de " << sentido_normal << "\n [2] Partida de " << sentido_inverso << "? \n\n";
	cout << " Escolha um opção! \n\n";

erro:
	char input = _getch();

	switch (input)
	{
	case '0':
		cout << "\n Operação cancelada.\n";
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

	l.showHorario(direc);

	return;

}
void Empresa::horarioParagem()
{
	//Paragem
	string input_paragem;

	vector<Linha> linhas_com_a_paragem;

	typedef tuple <unsigned int, vector <Tempo>, vector <Tempo> > parNormInv;
	vector<parNormInv> vectorOutput;

	cout << " Paragem? ";

paragem:
	getline(cin, input_paragem);

	switch (inputErrorHandling(input_paragem, 'p'))
	{
	case 0:
		cerr << " Input inválido. Introduza novamente:";
		goto paragem;
	case 1:
		break;
	case 2:
		cerr << "\n Operação cancelada.\n";
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
		unsigned int sum_n = 0;
		for (size_t x = 0; x < index_linha_n; x++)
		{
			sum_n += l.getTempos().at(x);
		}

		//Tempo desde a paragem inicial até à final, sentido inverso
		unsigned int sum_i = 0;
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

	cout << endl;

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
	vector< vector<unsigned int> > sameLine;

	vector< vector<unsigned int>> differentLine;
	vector<unsigned int> linhas_start;
	vector<unsigned int> linhas_finish;

	cout << " Qual a paragem inicial? ";

paragem_inicial:
	getline(cin, start);

	switch (inputErrorHandling(start, 'p'))
	{
	case 0:
		cerr << " Input inválido. Introduza novamente:";
		goto paragem_inicial;
	case 1:
		break;
	case 2:
		cerr << "\n Operação cancelada.\n";
		_getch();
		return;
	}

	if (inputExist(start).size() == 0)
	{
		cerr << " A paragem não existe. Paragem inicial? ";
		_getch();
		goto paragem_inicial;
	}

	cout << "\n Qual é a paragem final? ";

paragem_final:
	getline(cin, finish);

	switch (inputErrorHandling(finish, 'p'))
	{
	case 0:
		cerr << " Input inválido. Introduza novamente:";
		goto paragem_final;
	case 1:
		break;
	case 2:
		cerr << "\n Operação cancelada.\n";
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

	///As duas paragens estão na mesma paragem?
	for (mapLinha::iterator it = lLinhas.begin(); it != lLinhas.end(); it++)
	{
		for (size_t i = 0; i < it->second.getParagens().size(); i++)
		{
			if (compararCaseInsensitive(it->second.getParagens().at(i), start))
			{
				found_start = true;
				index_start = i;
			}
			else if (compararCaseInsensitive(it->second.getParagens().at(i), finish))
			{
				found_finish = true;
				index_finish = i;
			}
		}

		if (found_start && found_finish)
			sameLine.push_back({ it->first, index_start, index_finish });

		found_start = false;
		found_finish = false;
	}

	//Preencher linhas_start e linhas_finish
	for (mapLinha::iterator it = lLinhas.begin(); it != lLinhas.end(); it++)
	{
		//Para start
		for (size_t i = 0; i < it->second.getParagens().size(); i++)
		{
			if (compararCaseInsensitive(it->second.getParagens().at(i), start))
			{
				linhas_start.push_back(it->first);
				break;
			}
		}

		//Para finish
		for (size_t i = 0; i < it->second.getParagens().size(); i++)
		{
			if (compararCaseInsensitive(it->second.getParagens().at(i), finish))
			{
				linhas_finish.push_back(it->first);
				break;
			}
		}
	}

	///As duas paragens estão a 1 linha de distância?
	for (size_t i = 0; i < linhas_start.size(); i++)
	{
		Linha l_s = lLinhas[linhas_start.at(i)];

		//Index da paragem inicial na linha inicial
		for (size_t y = 0; y < l_s.getParagens().size(); y++)
		{
			if (compararCaseInsensitive(l_s.getParagens().at(y), start))
				index_start = y;
		}

		for (size_t y = 0; y < linhas_finish.size(); y++)
		{
			Linha l_f = lLinhas[linhas_finish.at(y)];

			//Index da paragem final na linha final
			for (size_t c = 0; c < l_f.getParagens().size(); c++)
			{
				if (compararCaseInsensitive(l_f.getParagens().at(c), finish))
					index_finish = c;
			}

			//Caso sejam a mesma linha
			if (l_s.getID() == l_f.getID())
				continue;

			for (size_t a = 0; a < l_s.getParagens().size(); a++)
			{
				for (size_t b = 0; b < l_f.getParagens().size(); b++)
				{
					if (compararCaseInsensitive(l_s.getParagens().at(a), l_f.getParagens().at(b)))
					{
						differentLine.push_back({ linhas_start.at(i), index_start, a, linhas_finish.at(y), index_finish, b });
					}
				}
			}
		}
	}

	if (sameLine.size() == 0 && differentLine.size() == 0)
	{
		cerr << " Não é possível projectar um percurso para essas paragens. Paragem inicial? ";
		_getch();
		goto paragem_inicial;
	}

	//Processamento
	typedef map <unsigned int, string> mapPercurso;

	//Automaticamente faz sort com base no tempo total
	mapPercurso opcoes;

	//Mesma linha
	for (size_t i = 0; i < sameLine.size(); i++)
	{
		//Variaveis
		unsigned int idlinha = sameLine.at(i).at(0);
		unsigned int i1 = sameLine.at(i).at(1);
		unsigned int i2 = sameLine.at(i).at(2);

		unsigned int sumTempos = 0;
		string percurso = "";

		if (i2 > i1)
		{
			for (size_t z = i1; z < i2; z++)
			{
				//Último elemento
				if (z == i2 - 1)
				{
					sumTempos += lLinhas[idlinha].getTempos().at(z);
					percurso += lLinhas[idlinha].getParagens().at(z);
					percurso += " -> " + lLinhas[idlinha].getParagens().at(z + 1);
;
					string output = "\n Linha: " + to_string(idlinha) + "\n Percurso: " + percurso + "\n Tempo total: " + to_string(sumTempos) + "\n";

					opcoes[sumTempos] = output;
				}
				else
				{
					sumTempos += lLinhas[idlinha].getTempos().at(z);
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
					sumTempos += inversoTempos.at(z);
					percurso += inversoParagens.at(z);
					percurso += " -> " + inversoParagens.at(z + 1);

					string output = "\n Linha: " + to_string(idlinha) + "\n Percurso: " + percurso + "\n Tempo total: " + to_string(sumTempos) + "\n";

					opcoes[sumTempos] = output;
				}
				else
				{
					sumTempos += inversoTempos.at(z);
					percurso += inversoParagens.at(z);
					percurso += " -> ";
				}
			}
		}
	}

	//Linhas diferentes
	for (size_t i = 0; i < differentLine.size(); i++)
	{
		//Variáveis
		unsigned int idLinha_start = differentLine.at(i).at(0);
		unsigned int i1 = differentLine.at(i).at(1);
		unsigned int i_s = differentLine.at(i).at(2);
		unsigned int idLinha_finish = differentLine.at(i).at(3);
		unsigned int i2 = differentLine.at(i).at(4);
		unsigned int i_f = differentLine.at(i).at(5);

		unsigned int sumTempos = 0;
		string percurso = "";

		//Viagem na linha start
		if (i_s > i1)
		{
			for (size_t z = i1; z < i_s; z++)
			{
				//Último elemento
				if (z == i_s - 1)
				{
					sumTempos += lLinhas[idLinha_start].getTempos().at(z);
					percurso += lLinhas[idLinha_start].getParagens().at(z);
					percurso += " -> ";
				}
				else
				{
					sumTempos += lLinhas[idLinha_start].getTempos().at(z);
					percurso += lLinhas[idLinha_start].getParagens().at(z);
					percurso += " -> ";
				}
			}

			//Viagem na linha finish
			if (i_f > i2)
			{
				vector<string> inversoParagens = lLinhas[idLinha_finish].getParagens();
				reverse(inversoParagens.begin(), inversoParagens.end());
				vector<unsigned int> inversoTempos = lLinhas[idLinha_finish].getTempos();
				reverse(inversoTempos.begin(), inversoTempos.end());

				i2 = (inversoParagens.size() - 1) - i2;
				i_f = (inversoParagens.size() - 1) - i_f;

				for (size_t z = i_f; z < i2; z++)
				{
					if (z == i2 - 1)
					{
						sumTempos += inversoTempos.at(z);
						percurso += inversoParagens.at(z);
						percurso += " -> " + inversoParagens.at(z + 1);

						string output = "\n Linha: " + to_string(idLinha_start) + " e " + to_string(idLinha_finish) + "\n Percurso: " + percurso + "\n Tempo total: " + to_string(sumTempos) + "\n";

						opcoes[sumTempos] = output;
					}
					else
					{
						sumTempos += inversoTempos.at(z);
						percurso += inversoParagens.at(z);
						percurso += " -> ";
					}
				}
			}
			else
			{
				for (size_t z = i_f; z < i2; z++)
				{
					//Último elemento
					if (z == i2 - 1)
					{
						sumTempos += lLinhas[idLinha_finish].getTempos().at(z);
						percurso += lLinhas[idLinha_finish].getParagens().at(z);
						percurso += " -> " + lLinhas[idLinha_finish].getParagens().at(z + 1);

						string output = "\n Linha: " + to_string(idLinha_start) + " e " + to_string(idLinha_finish) + "\n Percurso: " + percurso + "\n Tempo total: " + to_string(sumTempos) + "\n";

						opcoes[sumTempos] = output;

					}
					else
					{
						sumTempos += lLinhas[idLinha_finish].getTempos().at(z);
						percurso += lLinhas[idLinha_finish].getParagens().at(z);
						percurso += " -> ";
					}
				}
			}
		}
		else
		{
			vector<string> inversoParagens = lLinhas[idLinha_start].getParagens();
			reverse(inversoParagens.begin(), inversoParagens.end());
			vector<unsigned int> inversoTempos = lLinhas[idLinha_start].getTempos();
			reverse(inversoTempos.begin(), inversoTempos.end());

			i1 = (inversoParagens.size() - 1) - i1;
			i_s = (inversoParagens.size() - 1) - i_s;

			for (size_t z = i1; z < i_s; z++)
			{
				if (z == i_s - 1)
				{
					sumTempos += inversoTempos.at(z);
					percurso += inversoParagens.at(z);
					percurso += " -> ";
				}
				else
				{
					sumTempos += inversoTempos.at(z);
					percurso += inversoParagens.at(z);
					percurso += " -> ";
				}
			}

			//Viagem na linha finish
			if (i_f > i2)
			{
				vector<string> inversoParagens = lLinhas[idLinha_finish].getParagens();
				reverse(inversoParagens.begin(), inversoParagens.end());
				vector<unsigned int> inversoTempos = lLinhas[idLinha_finish].getTempos();
				reverse(inversoTempos.begin(), inversoTempos.end());

				i2 = (inversoParagens.size() - 1) - i2;
				i_f = (inversoParagens.size() - 1) - i_f;

				for (size_t z = i_f; z < i2; z++)
				{
					if (z == i2 - 1)
					{
						sumTempos += inversoTempos.at(z);
						percurso += inversoParagens.at(z);
						percurso += " -> " + inversoParagens.at(z + 1);

						string output = "\n Linha: " + to_string(idLinha_start) + " e " + to_string(idLinha_finish) + "\n Percurso: " + percurso + "\n Tempo total: " + to_string(sumTempos) + "\n";

						opcoes[sumTempos] = output;

					}
					else
					{
						sumTempos += inversoTempos.at(z);
						percurso += inversoParagens.at(z);
						percurso += " -> ";
					}
				}
			}
			else
			{
				for (size_t z = i_f; z < i2; z++)
				{
					//Último elemento
					if (z == i2 - 1)
					{
						sumTempos += lLinhas[idLinha_finish].getTempos().at(z);
						percurso += lLinhas[idLinha_finish].getParagens().at(z);
						percurso += " -> " + lLinhas[idLinha_finish].getParagens().at(z + 1);

						string output = "\n Linha: " + to_string(idLinha_start) + " e " + to_string(idLinha_finish) + "\n Percurso: " + percurso + "\n Tempo total: " + to_string(sumTempos) + "\n";

						opcoes[sumTempos] = output;

					}
					else
					{
						sumTempos += lLinhas[idLinha_finish].getTempos().at(z);
						percurso += lLinhas[idLinha_finish].getParagens().at(z);
						percurso += " -> ";
					}
				}
			}

		}
	}

	//Output
	for (mapPercurso::iterator it = opcoes.begin(); it != opcoes.end(); it++)
	{
		cout << it->second;
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
		cerr << " Input inválido. Paragem que pretende procurar? ";
		goto input;
	case 1:
		break;
	case 2:
		cerr << "\n Operação cancelada.\n";
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
			cout << " " << linhas_com_paragem.at(i) << endl;
		}
	}

	_getch();

	return;

}

void Empresa::infoLinha()
{
	string input_id;
	unsigned int l_id;

	mapLinha lLinhas = empresa.getLinhas();

	cout << " Linhas existentes:" << endl;

	for (mapLinha::iterator i = lLinhas.begin(); i != lLinhas.end(); i++)
	{
		cout << " " << i->second.getID() << endl;
	}

	cout << "\n Que linha pretende pretende visualizar? ";

id:
	getline(cin, input_id);

	switch (inputErrorHandling(input_id, 'i'))
	{
	case 0:
		cerr << " Input inválido. Introduza novamente:";
		goto id;
	case 1:
		break;
	case 2:
		cerr << "\n Operação cancelada.\n";
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

	Linha l = newLinhas[l_id];
	l.showLinha();
	l.showHorario(1);
	l.showHorario(2);

	return;

}
void Empresa::trabalhoCondutor()
{
	string input_id;
	unsigned int c_id, contador = 0;

	mapCondutor cCondutores = empresa.getCondutores();

	cout << " Condutores existentes:" << endl;

	for (mapCondutor::iterator i = cCondutores.begin(); i != cCondutores.end(); i++)
	{
		cout << " " << i->second.getID() << endl;
	}

	cout << "\n Pretende visualizar o trabalho de qual condutor? ";

id:
	getline(cin, input_id);

	switch (inputErrorHandling(input_id, 'i'))
	{
	case 0:
		cerr << " Input inválido. Introduza novamente:";
		goto id;
	case 1:
		break;
	case 2:
		cerr << "\n Operação cancelada.\n";
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
	Condutor c = newCondutores[c_id];

	cout << "\n Trabalho atribuído a " << c.getNome() << ": \n\n";

	c.showTrabalho();

	_getch();

	return;
}
void Empresa::trabalhoCondutorLeft()
{
	mapCondutor temp_c = empresa.getCondutores();

	for (mapCondutor::iterator i = temp_c.begin(); i != temp_c.end(); i++)
	{
		vector<Trabalho> temp_trab = i->second.getTrabalho();

		cout << " " << i->second.getNome() << " - ";

		if (temp_trab.size() == 0)
		{
			cout << " nenhum trabalho atribuido!";
			goto fim;
		}
		else
		{
			unsigned int total = 0;

			for (unsigned int n = 0; n < temp_trab.size(); n++)
			{
				Tempo inicio = temp_trab.at(n).getInicio();
				Tempo fim = temp_trab.at(n).getFim();

				total += fim.subtractTempo(inicio);
			}

			unsigned int min_semana = i->second.getSemana() * 60;

			if (total == min_semana)
			{
				cout << " Semana Completa!";
			}
			else if (total < min_semana)
			{
				cout << " Faltam  aproximadamente " << (min_semana - total) / 60 << " horas (" << min_semana - total << " minutos) para completar a semana.";
			}

			cout << endl;
		}
	}

fim:

	_getch();

	return;
}
void Empresa::infoAutocarro()
{
	string input_dia = "";
	string input_linha;
	string input_auto;
	unsigned int dia_semana;
	unsigned int linha_id;
	unsigned int auto_id;

	cout << " Que dia da semana pretende selecionar?\n";
	cout << " [1] Segunda-feira\n [2] Terça-feira\n [3] Quarta-feira\n [4] Quinta-feira\n [5] Sexta-feira\n [6] Sábado\n [7] Domingo\n [0] Cancelar\n\n";

input_d:
	char input = _getch();

	input_dia += input;

	switch (inputErrorHandling(input_dia, 'n'))
	{
	case 0:
		cerr << " Input inválido. Introduza novamente:";
		goto input_d;
	case 1:
		break;
	case 2:
		cerr << "\n Operação cancelada.\n";
		_getch();
		return;
	}

	istringstream stream_dia(input_dia);
	stream_dia >> dia_semana;

	if (dia_semana <= 0 || dia_semana >= 8)
	{
		cerr << " Input inválido. Introduza novamente: ";
		goto input_d;
	}

	//Map da com as linhas e os autocarros de cada linha
	linhasDia linhas_com_autocarros = empresa.getTrabalho().at(dia_semana - 1);

	cout << endl;

	//Linhas existentes
	mapLinha lLinhas = empresa.getLinhas();

	cout << " Linhas existentes:" << endl;

	for (mapLinha::iterator it = lLinhas.begin(); it != lLinhas.end(); it++)
	{
		cout << " " << it->second.getID() << endl;
	}

	cout << "\n Qual a linha do autocarro? ";

input_l:
	getline(cin, input_linha);

	switch (inputErrorHandling(input_linha, 'i'))
	{
	case 0:
		cerr << " Input inválido. Introduza novamente:";
		goto input_l;
	case 1:
		break;
	case 2:
		cerr << "\n Operação cancelada.\n";
		_getch();
		return;
	}

	istringstream stream_linha(input_linha);
	stream_linha >> linha_id;

	if (!inputExist(linha_id, 'l'))
	{
		cerr << " Essa linha não existe. Escolha outra: ";
		goto input_l;
	}

	mapAutocarro autocarros_da_linha = linhas_com_autocarros[linha_id];

	cout << endl;

	//Output dos autocarros da linha desse dia
	for (mapAutocarro::iterator it = autocarros_da_linha.begin(); it != autocarros_da_linha.end(); it++)
	{
		cout << " Autocarro nº " << it->first << endl;
	}
	
	cout << "\n Qual o autocarro que pretende visualizar? ";

input_a:
	getline(cin, input_auto);

	switch (inputErrorHandling(input_auto, 'i'))
	{
	case 0:
		cerr << " Input inválido. Introduza novamente:";
		goto input_a;
	case 1:
		break;
	case 2:
		cerr << "\n Operação cancelada.\n";
		_getch();
		return;
	}

	istringstream stream_auto(input_auto);
	stream_auto >> auto_id;

	//Autocarro existe?
	if (auto_id < 1 || auto_id > autocarros_da_linha.rbegin()->first)
	{
		cerr << " Esse autocarro não existe. Escolha outro: ";
		goto input_a;
	}

	Autocarro ac = autocarros_da_linha[auto_id];

	cout << endl;

	//Informação do autocarro
	cout << " Autocarro nº " << ac.getOrdem() << endl;
	cout << " Dia da semana: " << intDay(dia_semana - 1) << endl;
	cout << " Linha: " << ac.getLinhaID() << endl;

	if (ac.getCondutorID() == 0)
		cout << " Condutor atribuído: NULL " << endl;
	else
		cout << " Condutor atribuído: " << empresa.getCondutores()[ac.getCondutorID()].getNome() << endl;

	//Output dos turnos
	for (size_t i = 0; i < ac.getTrabalho().size(); i++)
	{
		cout << " Turno nº " << i + 1 << ": " << ac.getTrabalho().at(i).getInicio().showTempo() << " às " << ac.getTrabalho().at(i).getFim().showTempo() << endl;
	}

	_getch();

	return;
}
void Empresa::trabalhoAutocarroLeft()
{
	string input_dia = "";
	unsigned int dia_semana;

	cout << " Que dia da semana pretende selecionar?\n";
	cout << " [1] Segunda-feira\n [2] Terça-feira\n [3] Quarta-feira\n [4] Quinta-feira\n [5] Sexta-feira\n [6] Sábado\n [7] Domingo\n [0] Cancelar\n\n";

input_d:
	char input = _getch();

	input_dia += input;

	switch (inputErrorHandling(input_dia, 'n'))
	{
	case 0:
		cerr << " Input inválido. Introduza novamente:";
		goto input_d;
	case 1:
		break;
	case 2:
		cerr << "\n Operação cancelada.\n";
		_getch();
		return;
	}

	istringstream stream_dia(input_dia);
	stream_dia >> dia_semana;

	if (dia_semana <= 0 || dia_semana >= 8)
	{
		cerr << " Input inválido. Introduza novamente: ";
		goto input_d;
	}

	dia_semana--;

	cout << " " << intDay(dia_semana) << " - Condutores não atribuídos: \n\n";

	linhasDia temp = empresa.getTrabalho().at(dia_semana);

	for (linhasDia::iterator it = temp.begin(); it != temp.end(); it++)
	{
		cout << " " << it->first << ": " << endl;

		for (mapAutocarro::iterator a = it->second.begin(); a != it->second.end(); a++)
		{
			if (a->second.getCondutorID() == 0)
			{
				cout << " Autocarro nº " << a->second.getOrdem() << endl;
			}
		}
		cout << endl;
	}


	_getch();

	return;
}

void Empresa::beginAtribuicao()
{
	mapLinha linhas_existentes = empresa.getLinhas();

	vector<linhasDia> newVector;

	//Para cada dia da semana
	for (size_t i = 0; i < 7; i++)
	{
		linhasDia newTrabalho;

		//Para cada linha do dia
		for (mapLinha::iterator it = linhas_existentes.begin(); it != linhas_existentes.end(); it++)
		{
			mapAutocarro newAutocarros;

			//Hora de inicio
			Tempo actual = T_INICIO;
			bool acabarPreencher = false;

			unsigned int nr_autocarros = 0;
			unsigned int tempo_ida_volta = 0;
			vector<Tempo> tempos_saida;
			vector<Tempo> tempos_chegada;

			tempos_saida.push_back(actual);

			//Hora de saída
			while (true)
			{
				actual.sumTempo(empresa.getLinhas()[it->first].getFreq());

				if (actual.getHora() > T_FIM.getHora() || (actual.getHora() == T_FIM.getHora() && actual.getMinuto() > T_FIM.getMinuto()))
					break;
				else
				{
					tempos_saida.push_back(actual);
					nr_autocarros++;
				}
			}

			//Tempo que o autocarro demora a ir e vir
			for (size_t a = 0; a < empresa.getLinhas()[it->first].getTempos().size(); a++)
			{
				tempo_ida_volta += empresa.getLinhas()[it->first].getTempos().at(a);
			}
			tempo_ida_volta *= 2;

			//Hora de chegada
			for (size_t a = 0; a < tempos_saida.size(); a++)
			{
				Tempo temp = tempos_saida.at(a);

				temp.sumTempo(tempo_ida_volta);

				tempos_chegada.push_back(temp);
			}

			//Preencher newAutocarro
			for (size_t a = 0; a < tempos_saida.size(); a++)
			{
				//Inicio e fim do turno
				Tempo inicio = tempos_saida.at(a);
				Tempo fim = inicio;
				fim.sumTempo(tempo_ida_volta);
				
				//Primeiro autocarro a ser criado
				if (newAutocarros.size() == 0)
				{
					Trabalho turno = Trabalho(i, it->first, 0, inicio, fim);

					vector<Trabalho> newTurnos;

					newTurnos.push_back(turno);
					Autocarro ac = Autocarro(it->first, 0, a + 1, newTurnos);
					newAutocarros[a + 1] = ac;
				}
				else
				{
					//Verificar se algum autocarro já existente, está disponível para este turno
					for (mapAutocarro::iterator ot = newAutocarros.begin(); ot != newAutocarros.end(); ot++)
					{
						//O último turno do autocarro acaba antes deste?
						if (ot->second.getTrabalho().back().getFim().getHora() < inicio.getHora() || (ot->second.getTrabalho().back().getFim().getHora() == inicio.getHora()) && (ot->second.getTrabalho().back().getFim().getMinuto() <= inicio.getMinuto()))
						{
							vector<Trabalho> trabalhoAutocarro = ot->second.getTrabalho();

							Trabalho turno = Trabalho(i, it->first, ot->second.getOrdem(), inicio, fim);

							trabalhoAutocarro.push_back(turno);

							ot->second.setTrabalho(trabalhoAutocarro);

							break;
						}

						//Caso nenhum autocarro esteja disponível, é criado um novo
						if (ot->first == newAutocarros.rbegin()->first)
						{
							vector<Trabalho> newTurnos;

							Trabalho turno = Trabalho(i, it->first, a + 1, inicio, fim);

							newTurnos.push_back(turno);
							Autocarro ac = Autocarro(it->first, 0, a + 1, newTurnos);
							newAutocarros[a + 1] = ac;

							break;
						}
					}
				}
			}

			newTrabalho[it->first] = newAutocarros;
		}

		newVector.push_back(newTrabalho);
	}

	empresa.setTrabalho(newVector);

	//A estrutura básica está criada. Agora falta adicionar os condutores já atribuidos

	mapCondutor condutoresActual = empresa.getCondutores();

	for (mapCondutor::iterator it = condutoresActual.begin(); it != condutoresActual.end(); it++)
	{
		vector<Trabalho> trabalhoCondutor = it->second.getTrabalho();

		for (size_t i = 0; i < trabalhoCondutor.size(); i++)
		{
			Trabalho trabalhoActual = trabalhoCondutor.at(i);

			//Caso o condutor tenho dois trabalhos no mesmo autocarro (pois o autocarro pode ter turnos diferentes), avança
			if (newVector.at(trabalhoActual.getDiaSemana())[trabalhoActual.getLinhaID()][trabalhoActual.getAutocarroID()].getCondutorID() != 0)
				continue;
			else
				newVector.at(trabalhoActual.getDiaSemana())[trabalhoActual.getLinhaID()][trabalhoActual.getAutocarroID()].setCondutorID(it->first);

		}
	}

	empresa.setTrabalho(newVector);

	return;
}
void Empresa::atribuirCondutor(unsigned int idCondutor, unsigned int dia, unsigned int idLinha, unsigned int idAutocarro)
{
	//Vetor com o trabalho dos dias
	vector<linhasDia> trabalhoActual = empresa.getTrabalho();

	//Atribuir o condutor ao autocarro
	trabalhoActual.at(dia)[idLinha][idAutocarro].setCondutorID(idCondutor);
	empresa.setTrabalho(trabalhoActual);

	//Map de condutores actuais e vector do trabalho do condutor
	mapCondutor condutoresActual = empresa.getCondutores();

	//Atribuir o turno ao condutor
	vector<Trabalho> trabalhoCondutor = condutoresActual[idCondutor].getTrabalho();

	for (size_t i = 0; i < empresa.getTrabalho().at(dia)[idLinha][idAutocarro].getTrabalho().size(); i++)
	{
		trabalhoCondutor.push_back(empresa.getTrabalho().at(dia)[idLinha][idAutocarro].getTrabalho().at(i));
	}

	condutoresActual[idCondutor].setTrabalho(trabalhoCondutor);
	empresa.setCondutores(condutoresActual);

	cout << " Condutor atribuído com sucesso! \n";

	return;
}
void Empresa::desatribuirCondutor(unsigned int idCondutor, unsigned int dia, unsigned int idLinha, unsigned int idAutocarro)
{
	//Vetor com o trabalho dos dias
	vector<linhasDia> trabalhoActual = empresa.getTrabalho();

	//Desatribuir o condutor ao autocarro
	trabalhoActual.at(dia)[idLinha][idAutocarro].setCondutorID(0);
	empresa.setTrabalho(trabalhoActual);

	//Map de condutores actuais e vector do trabalho do condutor
	mapCondutor condutoresActual = empresa.getCondutores();

	//Desatribuir o turno ao condutor
	vector<Trabalho> trabalhoCondutor = condutoresActual[idCondutor].getTrabalho();

	for (size_t i = 0; i < trabalhoCondutor.size(); i++)
	{
		Trabalho trabalho_temp = trabalhoCondutor.at(i);

		if (trabalho_temp.getDiaSemana() == dia && trabalho_temp.getLinhaID() == idLinha && trabalho_temp.getAutocarroID() == idAutocarro)
		{
			trabalhoCondutor.erase(trabalhoCondutor.begin() + i);
			break;
		}
		else
			continue;
	}

	condutoresActual[idCondutor].setTrabalho(trabalhoCondutor);
	empresa.setCondutores(condutoresActual);

	cout << " Condutor desatribuído com sucesso! \n";

	return;
}