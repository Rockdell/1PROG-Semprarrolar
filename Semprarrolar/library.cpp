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

	cout << " ======================\n";
	cout << " === MENU PRINCIPAL ===\n";
	cout << " ======================\n\n";

	if (file_open)
	{
		//Sempre que inicia o menu principal, actualiza o vectorTrabalho
		empresa.beginAtribuicao();

		cout << " [1] Linhas\n [2] Condutores\n [3] Informa��o\n [4] Atribui��o de trabalho\n [0] Cancelar\n\n";

	erro1:
		char input = _getch();

		switch (input)
		{
		case '0':
		{
			if (alterado_condutor || alterado_linha)
			{
				cout << " Pretende guardar as altera��es? [Y/N]\n";

			erro3:
				char input = _getch();

				switch (toupper(input))
				{
				case 'Y':
				{
					string filename_condutor, filename_linha;

					if (alterado_condutor)
					{
						cout << " Ficheiro para guardar os condutores: "; getline(cin, filename_condutor);
						empresa.saveCondutores(filename_condutor);
					}

					if (alterado_linha)
					{
						cout << " Ficheiro para guardar as linhas: "; getline(cin, filename_linha);
						empresa.saveLinhas(filename_linha);
					}

					cout << " O programa fechou e guardou as altera��es! ";
					_getch();
					return;
				}
				case 'N':
				{
					cout << " O programa fechou sem guardar as altera��es! ";
					_getch();
					return;
				}
				default:
					goto erro3;
				}
			}
			else
			{
				cout << " O programa fechou! ";
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
		cout << " [1] Abrir ficheiro de condutor e linha\n\n";

	erro2:
		char input = _getch();

		switch (input)
		{
		case '0':
			cout << " O programa fechou! ";
			_getch();
			return;
		case '1':
		{
			string filename_condutor, filename_linha;

			cout << " Ficheiro de condutores: "; getline(cin, filename_condutor);
			cout << " Ficheiro de linhas: "; getline(cin, filename_linha);

			empresa.fillCondutores(filename_condutor);
			empresa.fillLinhas(filename_linha);

			if (fail)
			{
				cout << "\n Ficheiro(s) n�o encontrado(s)\n";
				_getch();

				goto redo;
			}

			cout << "\n Condutores e linhas loaded! \n";
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

	cout << " ===================\n";
	cout << " === MENU LINHAS ===\n";
	cout << " ===================\n\n";

	cout << " [1] Adicionar linha\n [2] Alterar linha\n [3] Remover linha\n [0] Cancelar\n\n";

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

	cout << " =======================\n";
	cout << " === MENU CONDUTORES ===\n";
	cout << " =======================\n\n";

	cout << " [1] Adicionar condutor\n [2] Alterar condutor\n [3] Remover condutor\n [4] Ver trabalho do condutor\n [5] Ver horas semanais restantes\n [0] Cancelar\n\n";

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
		empresa.trabalhoCondutor();
		break;
	case '5':
		empresa.trabalhoCondutorLeft();
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

	cout << " =======================\n";
	cout << " === MENU INFORMA��O ===\n";
	cout << " =======================\n\n";

	cout << " [1] Percurso entre duas paragens\n [2] Hor�rio da linha\n [3] Hor�rio da paragem\n [4] Inquirir linhas sobre paragem\n " <<
		"[5] Informa��o da linha\n [6] Informa��o do autocarro\n [7] Autocarros sem condutor\n\n";

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
	case '6':
		empresa.infoAutocarro();
		break;
	case '7':
		empresa.trabalhoAutocarroLeft();
		break;
	default:
		goto erro;
	}

	goto redo;
}
void MenuAtribuicao()
{
	unsigned int index = 0;
	bool day_open = false;
	string dia_da_semana;

redo:

	clearScreen();

	cout << " =======================\n";
	cout << " === MENU ATRIBUI��O ===\n";
	cout << " =======================\n\n";

	if (!day_open)
	{
		cout << " Que dia da semana pretende selecionar?\n";
		cout << " [1] Segunda-feira\n [2] Ter�a-feira\n [3] Quarta-feira\n [4] Quinta-feira\n [5] Sexta-feira\n [6] S�bado\n [7] Domingo\n\n";

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
			dia_da_semana = "Ter�a-feira";
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
			dia_da_semana = "S�bado";
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
		linhasDia linhas_com_autocarros = empresa.getTrabalho().at(index);

		//Linhas existentes
		mapLinha lLinhas = empresa.getLinhas();

		cout << " Linhas existentes:" << endl;

		for (mapLinha::iterator it = lLinhas.begin(); it != lLinhas.end(); it++)
		{
			cout << it->second.getID() << endl;
		}

		cout << "\n Que linha pretende selecionar? ";

	id:
		getline(cin, input_id);

		switch (inputErrorHandling(input_id, 'i'))
		{
		case 0:
			cerr << " Input inv�lido. Introduza novamente: ";
			goto id;
		case 1:
			break;
		case 2:
		{
			cerr << " Opera��o cancelada.\n";
			_getch();
			 
			day_open = false;
			goto redo;			
		}
		}

		istringstream stream_id(input_id);
		stream_id >> l_id;

		if (!inputExist(l_id, 'l'))
		{
			cerr << " Essa linha n�o existe. Escolha outra: ";
			goto id;
		}

		mapAutocarro autocarros_da_linha = linhas_com_autocarros[l_id];

		cout << "\n Linha: " << l_id << endl << endl;

		//Output dos autocarros da linha desse dia
		for (mapAutocarro::iterator it = autocarros_da_linha.begin(); it != autocarros_da_linha.end(); it++)
		{
			Autocarro ac = it->second;
			cout << " Autocarro - n�mero " << it->first << ":\n";

			for (size_t i = 0; i < ac.getTrabalho().size(); i++)
			{
				cout << " Turno n� " << i + 1 << ": " << ac.getTrabalho().at(i).getInicio().showTempo() << " a " << ac.getTrabalho().at(i).getFim().showTempo() << endl;
			}

			if (ac.getCondutorID() == 0)
				cout << " Condutor atribu�do: NULL " << endl << endl;
			else
				cout << " Condutor atribu�do: " << empresa.getCondutores()[ac.getCondutorID()].getNome() << endl << endl;
		}

		cout << " [1] Atribuir condutor\n [2] Desatribuir condutor\n\n";

	input:
		char input = _getch();

		switch (input)
		{
		case '0':
			return;
		case '1':
		{
			cout << " A que autocarro pretende atribuir o condutor? ";
			
		autocarro1:
			getline(cin, input_autocarro);
			
			switch (inputErrorHandling(input_autocarro, 'i'))
			{
			case 0:
				cerr << " Input inv�lido. Introduza novamente: ";
				goto autocarro1;
			case 1:
				break;
			case 2:
				cerr << "\n Opera��o cancelada.\n";
				_getch();
			
				day_open = false;
				goto redo;
			}
			
			istringstream stream_autocarro(input_autocarro);
			stream_autocarro >> auto_id;
			
			//Autocarro existe?
			if (auto_id < 1 || auto_id > autocarros_da_linha.rbegin()->first)
			{
				cerr << " Esse autocarro n�o existe. Escolha outro: ";
				goto autocarro1;
			}
			else if (empresa.getTrabalho().at(index)[l_id][auto_id].getCondutorID() != 0)
			{
				cerr << " Esse autocarro j� tem um condutor atribu�do. Escolha outro: ";
				goto autocarro1;
			}
			
			cout << " Que condutor pretende atribuir o trabalho? ";
			
		condutor1:
			getline(cin, input_condutor);
			
			switch (inputErrorHandling(input_condutor, 'i'))
			{
			case 0:
				cerr << " Input inv�lido. Introduza novamente: ";
				goto condutor1;
			case 1:
				break;
			case 2:
				cerr << "\n Opera��o cancelada.\n";
				_getch();
			
				day_open = false;
				goto redo;
			}
			
			istringstream stream_condutor(input_condutor);
			stream_condutor >> c_id;
			
			if (!inputExist(c_id, 'c'))
			{
				cerr << " Esse condutor n�o existe. Escolha outro: ";
				goto condutor1;
			}
			
			//Confirma��o aqui:

			//Adicionar aqui o algoritmo que deixa (ou n�o) atribuir o autocarro ao condutor
			//ATEN�AO -  os autocarros tem v�rios turnos. � preciso contar os minutos totais do autocarro e depois ver se o condutor pode aceita-lo

			//Confirma��es a fazer (pelo menos)
			//1 - Daily_Max_Time >= New_Shift_Time + other_same_day_shit_times;
			//2 - Max_week_time >= new_shift_time + other_shifts_times;
			//3 - Driver can't have any shifts in the same day that conflict;
			//4 - Rest Time between shifts must be respected;
			
			//Adicionar o condutor
			empresa.atribuirCondutor(c_id, index, l_id, auto_id);

			break;
		}
		case '2':
		{
			cout << " Qual o autocarro que pretende desatribuir o condutor? ";
			
		autocarro2:
			getline(cin, input_autocarro);

			switch (inputErrorHandling(input_autocarro, 'i'))
			{
			case 0:
				cerr << " Input inv�lido. Introduza novamente:";
				goto autocarro2;
			case 1:
				break;
			case 2:
				cerr << " Opera��o cancelada.\n";
				_getch();

				day_open = false;
				goto redo;
			}

			istringstream stream_autocarro(input_autocarro);
			stream_autocarro >> auto_id;

			//Autocarro existe?
			if (auto_id < 1 || auto_id > autocarros_da_linha.rbegin()->first)
			{
				cerr << " Esse autocarro n�o existe. Escolha outro: ";
				goto autocarro2;
			}
			else if (empresa.getTrabalho().at(index)[l_id][auto_id].getCondutorID() == 0)
			{
				cerr << " Esse autocarro n�o tem nenhum condutor atribu�do. Escolha outro: ";
				goto autocarro2;
			}

			c_id = empresa.getTrabalho().at(index)[l_id][auto_id].getCondutorID();

			empresa.desatribuirCondutor(c_id, index, l_id, auto_id);

			break;
		}
		default:
			goto input;
		}
	}

	_getch();

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
	'n' : n�mero;
	's' : nome

	RETURN:
	0 : Input inv�lido
	1 : Continuar opera��o
	2 : Cancelar opera��o
	*/

	//Vari�vel de valida��o no caso de ser uma paragem (case 'p')
	//Se invalid = true (no final de o loop em case 'p') significa que s� � composta por n�meros e n�o � aceit�vel
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
		//Se invalid = true significa que s� � composta por n�meros e n�o � aceit�vel
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
string intDay(unsigned int day)
{
	switch (day)
	{
	case 0:
		return "Segunda-feira";
	case 1:
		return "Ter�a-feira";
	case 2:
		return "Quarta-feira";
	case 3:
		return "Quinta-feira";
	case 4:
		return "Sexta-feira";
	case 5:
		return "S�bado";
	case 6:
		return "Domingo";
	default:
		return "null";
	}
}

//void sortTrabalho(vector<Trabalho> &trab)
//{
//	vector<Trabalho> newVector;
//
//	for (size_t i = 0; true; i++)
//	{
//		if (trab.at(i).getInicio() < trab.at(i + 1).getInicio())
//			continue;
//	}
//}


