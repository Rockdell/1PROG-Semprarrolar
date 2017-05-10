#include <iostream>
#include <conio.h>
#include <string>
#include <algorithm>
#include <iomanip>
#include <sstream>

#include "linha.h"
#include "library.h"
#include "global.h"

#ifdef _WIN32
#define clearScreen() system("cls");
#else
#define clearScreen() system("clear");
#endif

using namespace std;

//Menus
void MenuPrincipal()
{
redo:

	clearScreen();

	cout << "---MENU PRINCIPAL---\n";

	if (file_open)
	{
		cout << "(1) Linhas\n(2) Condutores\n(3) Informação\n(4) Atribuição de trabalho\n";

	erro1:
		char input = _getch();

		switch (input)
		{
		case '0':
		{
			if (alterado_condutor || alterado_linha)
			{
				cout << "Pretende guardar as alterações? (Y/N)\n";

			erro3:
				char input = _getch();

				switch (toupper(input))
				{
				case 'Y':
				{
					string filename_condutor, filename_linha;

					if (alterado_condutor)
					{
						cout << "Ficheiro para guardar os condutores?"; getline(cin, filename_condutor);
						empresa.saveCondutores(filename_condutor);
					}

					if (alterado_linha)
					{
						cout << "Ficheiro para guardar as linhas?"; getline(cin, filename_linha);
						empresa.saveLinhas(filename_linha);
					}

					cout << "O programa fechou e guardou as alterações";
					_getch();
					return;
				}
				case 'N':
					cout << "O programa fechou sem guardar as alterações.\n";
					_getch();
					return;
				default:
					goto erro3;
				}
			}
			else
			{
				cout << "O programa fechou.\n";
				_getch();
				return;
			}

		}
		case '1':
			MenuLinhas();
			break;
		case '2':
			MenuCondutores();
			break;
		case '3':
			MenuInformacao();
			break;
		case '4':
			MenuAtribuicao();
			break;
		default:
			goto erro1;
		}

		goto redo;
	}
	else
	{
		cout << "(1) Abrir ficheiro de condutor e linha\n";

	erro2:
		char input = _getch();

		switch (input)
		{
		case '0':
			return;
		case '1':
		{
			string filename_condutor, filename_linha;

			cout << "Ficheiro de condutores?"; getline(cin, filename_condutor);
			cout << "Ficheiro de linhas?"; getline(cin, filename_linha);

			empresa.fillCondutores(filename_condutor);
			empresa.fillLinhas(filename_linha);

			cout << "Condutores e linhas loaded!\n";
			_getch();

			file_open = true;

			break;
		}
		default:
			goto erro2;
		}

		goto redo;
	}

}
void MenuLinhas()
{
redo:

	clearScreen();

	cout << "---MENU LINHAS---\n";

	cout << "(1) Adicionar\n(2) Alterar\n(3) Remover\n";

erro:
	char input = _getch();

	switch (input)
	{
	case '0':
		return;
	case '1':
		empresa.createLinha();
		break;
	case '2':
		empresa.modifyLinha();
		break;
	case '3':
		empresa.removeLinha();
		break;
	default:
		goto erro;
	}

	goto redo;
}
void MenuCondutores()
{
redo:

	clearScreen();

	cout << "---MENU CONDUTORES---\n";

	cout << "(1) Adicionar\n(2) Alterar\n(3) Remover\n(4) Visualizar trabalho\n(5) Visualizar horas semanais\n";

erro:
	char input = _getch();

	switch (input)
	{
	case '0':
		return;
	case '1':
		empresa.createCondutor();
		break;
	case '2':
		empresa.modifyCondutor();
		break;
	case '3':
		empresa.removeCondutor();
		break;
	case '4':
		empresa.infoTrabalho();
		break;
	case '5':
		empresa.infoService();
		break;
	default:
		goto erro;
	}

	goto redo;
}
void MenuInformacao()
{
redo:

	clearScreen();

	cout << "---MENU INFORMAÇÂO---\n";

	cout << " (1) Percurso entre duas paragens\n (2) Horário de uma linha\n (3) Horário de uma paragem\n (4) Inquirir paragem\n " <<
		"(5) Informação de uma linha\n (6) Informação de um autocarro\n\n";

erro:
	char input = _getch();

	switch (input)
	{
	case '0':
		return;
	case '1':
		empresa.percursoParagem();
		break;
	case '2':
		empresa.horarioLinha();
		break;
	case '3':
		empresa.horarioParagem();
		break;
	case '4':
		empresa.inquirirParagem();
		break;
	case '5':
		empresa.infoLinha();
		break;
	default:
		goto erro;
	}

	goto redo;
}
void MenuAtribuicao()
{
	beginAtribuicao();

	unsigned int index = 0;
	string dia_da_semana;

redo:

	clearScreen();
	cout << "---MENU ATRIBUIÇÃO---\n";

	if (!day_open)
	{
		cout << " Que dia da semana pretende selecionar? ";
		cout << "\n (1) Segunda-feira\n (2) Terça-feira\n (3) Quarta-feira\n (4) Quinta-feira\n (5) Sexta-feira\n (6) Sábado\n (7) Domingo\n\n";

	erro1:
		char input = _getch();

		switch (input)
		{
		case '0':
			return;
		case '1':
			dia_da_semana = "Segunda-feira";
			index = 0;
			break;
		case '2':
			dia_da_semana = "Terça-feira";
			index = 1;
			break;
		case '3':
			dia_da_semana = "Quarta-feira";
			index = 2;
			break;
		case '4':
			dia_da_semana = "Quinta-feira";
			index = 3;
			break;
		case '5':
			dia_da_semana = "Sexta-feira";
			index = 4;
			break;
		case '6':
			dia_da_semana = "Sábado";
			index = 5;
			break;
		case '7':
			dia_da_semana = "Domingo";
			index = 6;
			break;
		default:
			goto erro1;
		}

		day_open = true;

		goto redo;
	}
	else
	{
		string input_id;
		string input_autocarro;
		string input_condutor;
		unsigned int l_id;
		unsigned int auto_id;
		unsigned int c_id;

		//Dia da semana
		cout << "\n " << dia_da_semana << endl << endl;

		//Map da com as linhas e os autocarros de cada linha
		mapTrabalho	linhas_com_autocarros = empresa.getTrabalho().at(index);

		//Linhas existentes
		mapLinha lLinhas = empresa.getLinhas();

		cout << "Linhas existentes:" << endl;

		for (mapLinha::iterator i = lLinhas.begin(); i != lLinhas.end(); i++)
		{
			cout << i->second.getID() << endl;
		}

		cout << " \nQue linha pretende selecionar? ";

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
		{
			cerr << "Operação cancelada.\n";

			vector<mapTrabalho> resetTrabalho(7);
			empresa.setTrabalho(resetTrabalho);
			_getch();
			return;
		}
		}

		istringstream stream_id(input_id);
		stream_id >> l_id;

		if (!inputExist(l_id, 'l'))
		{
			cerr << " Essa linha não existe. Escolha outro: ";
			goto id;
		}

		mapAutocarro autocarros_da_linha = linhas_com_autocarros[l_id];

		cout << "\n Linha: " << l_id << endl;

		//Output dos autocarros da linha desse dia
		for (mapAutocarro::iterator it = autocarros_da_linha.begin(); it != autocarros_da_linha.end(); it++)
		{
			Autocarro ac = it->second;
			cout << " Autocarro - número " << it->first << ":\n";
			cout << " Turno: " << ac.getTrabalho().getInicio().showTempo() << " às " << ac.getTrabalho().getFim().showTempo() << endl;

			if (ac.getCondutorID() == 0)
				cout << " Condutor atribuído: NULL " << endl << endl;
			else
				cout << " Condutor atribuído: " << empresa.getCondutores()[ac.getCondutorID()].getNome() << endl << endl;
		}

		cout << " A que autocarro pretende atribuir o condutor? ";

	autocarro:
		getline(cin, input_autocarro);

		switch (inputErrorHandling(input_autocarro, 'i'))
		{
		case 0:
			cerr << "Input inválido. Introduza novamente:";
			goto autocarro;
		case 1:
			break;
		case 2:
			cerr << "Operação cancelada.\n";
			_getch();
			return;
		}

		istringstream stream_autocarro(input_autocarro);
		stream_autocarro >> auto_id;

		//Autocarro existe?
		if (auto_id < 1 || auto_id > autocarros_da_linha.rbegin()->first)
		{
			cerr << " Esse autocarro não existe. Escolha outro: ";
			goto autocarro;
		}

		cout << " Que condutor pretende atribuir o trabalho? ";

	condutor:
		getline(cin, input_condutor);

		switch (inputErrorHandling(input_condutor, 'i'))
		{
		case 0:
			cerr << "Input inválido. Introduza novamente:";
			goto condutor;
		case 1:
			break;
		case 2:
			cerr << "Operação cancelada.\n";
			_getch();
			return;
		}

		istringstream stream_condutor(input_condutor);
		stream_condutor >> c_id;

		if (!inputExist(c_id, 'c'))
		{
			cerr << " Esse condutor não existe. Escolha outro: ";
			goto condutor;
		}

		cout << " Até este ponto, o condutor é válido, o autocarro é válido. Falta confirmar se é possível atribuir o trabalho ao condutor!|\n\n";
	}

	_getch();

	day_open = false;
	index = 0;
	dia_da_semana = "";

	goto redo;
}

//QoL methods
bool compararCaseInsensitive(string strFirst, string strSecond)
{
	// Convert both strings to upper case by transfrom() before compare.
	transform(strFirst.begin(), strFirst.end(), strFirst.begin(), toupper);
	transform(strSecond.begin(), strSecond.end(), strSecond.begin(), toupper);

	if (strFirst == strSecond)
		return true;
	else
		return false;
}
unsigned int inputErrorHandling(string input, char propriedade)
{
	/*
	PROPRIEDADES:
	'i' : id;
	'p' : paragem;
	'n' : número;
	's' : nome

	RETURN:
	0 : Input inválido
	1 : Continuar operação
	2 : Cancelar operação
	*/

	//Variável de validação no caso de ser uma paragem (case 'p')
	//Se invalid = true (no final de o loop em case 'p') significa que só é composta por números e não é aceitável
	bool invalid = true;

	if (cin.eof() || input.length() == 0)
	{
		cin.clear();
		return 0;
	}
	else if (input.length() == 1 && input == "0")
		return 2;

	switch (propriedade)
	{
	case 'i':
		if (input.length() > 3)
			return 0;
		else {
			for (size_t i = 0; i < input.length(); i++)
			{
				if (!isdigit(input.at(i)))
					return 0;
			}
		}
		break;
	case 'p':
		for (size_t i = 0; i < input.length(); i++)
		{
			if (input.at(i) == ' ' || isdigit(input.at(i)))
				invalid = invalid && true;
			else
				invalid = false;

			if (input.at(i) != ' ' && (!isalpha(input.at(i)) && !isdigit(input.at(i))))
				return 0;
		}
		//Se invalid = true significa que só é composta por números e não é aceitável
		if (invalid)
			return 0;
		break;
	case 'n':
		for (size_t i = 0; i < input.length(); i++)
		{
			if (!isdigit(input.at(i)))
				return 0;
		}
		break;
	case 's':
		for (size_t i = 0; i < input.length(); i++)
		{
			if (!isalpha(input.at(i)))
				return 0;
		}
		break;
	}

	return 1;

}
bool inputExist(unsigned int id, char objeto)
{
	switch (objeto)
	{
	case 'c':
		if (empresa.getCondutores().count(id))
			return true;
		else
			return false;
	case 'l':
		if (empresa.getLinhas().count(id))
			return true;
		else
			return false;
	default:
		return false;
	}
}
bool inputExist(string paragem, vector<string> lista_paragens)
{
	for (size_t i = 0; i < lista_paragens.size(); i++)
	{
		if (compararCaseInsensitive(paragem, lista_paragens.at(i)))
			return true;
	}

	return false;
}
vector<unsigned int> inputExist(string paragem)
{
	vector<unsigned int> result;

	for each (pair<unsigned int, Linha> var in empresa.getLinhas())
	{
		for (size_t i = 0; i < var.second.getParagens().size(); i++)
		{
			if (compararCaseInsensitive(var.second.getParagens().at(i), paragem))
			{
				result.push_back(var.first);
				break;
			}
		}
	}

	return result;
}

void beginAtribuicao()
{
	mapLinha linhas_existentes = empresa.getLinhas();

	vector<mapTrabalho> newVector;

	//Para cada dia da semana
	for (size_t i = 0; i < 7; i++)
	{
		mapTrabalho newTrabalho;

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
			tempos_saida.push_back(actual);

			//Número de autocarros e hora de saída
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

			//Preencher newAutocarro
			for (size_t c = 1; c <= nr_autocarros; c++)
			{
				//Inicio e fim do turno
				Tempo inicio = tempos_saida.at(c - 1);
				Tempo fim = inicio;
				fim.sumTempo(tempo_ida_volta);

				Trabalho turno = Trabalho(inicio, fim);
				Autocarro ac = Autocarro(it->first, 0, c, turno);
				newAutocarros[c] = ac;
			}

			newTrabalho[it->first] = newAutocarros;
		}

		newVector.push_back(newTrabalho);
	}

	empresa.setTrabalho(newVector);

	return;
}