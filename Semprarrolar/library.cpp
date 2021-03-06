#include <iostream>
#include <conio.h>
#include <string>
#include <algorithm>

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
		cout << "(1) Linhas\n(2) Condutores\n(3) Informa��o\n";

	erro1:
		char input = _getch();

		switch (input)
		{
		case '0':
		{
			if (alterado_condutor || alterado_linha)
			{
				cout << "Pretende guardar as altera��es? (Y/N)\n";
			
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

					cout << "O programa fechou e guardou as altera��es";
					_getch();
					return;
				}
				case 'N':
					cout << "O programa fechou sem guardar as altera��es.\n";
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

	cout << "(1) Adicionar\n(2) Alterar\n(3) Remover\n";

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
	default:
		goto erro;
	}
	
	goto redo;
}
void MenuInformacao()
{
redo:

	clearScreen();

	cout << "---MENU INFORMA��O---\n";

	cout << " (1) Percurso entre duas paragens\n (2) Hor�rio de uma linha\n (3) Hor�rio de uma paragem\n\n";

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
	default:
		goto erro;
	}

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
			if (input.at(i) != ' ' && (!isalpha(input.at(i)) && !isdigit(input.at(i))))
				return 0;
		}
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
bool inputExist(string paragem)
{
	mapLinha lLinhas = empresa.getLinhas();

	for (mapLinha::iterator i = lLinhas.begin(); i != lLinhas.end(); i++)
	{
		for (size_t y = 0; y < i->second.getParagens().size(); y++)
		{
			if (compararCaseInsensitive(paragem, i->second.getParagens().at(y)))
				return true;
		}
	}
	return false;
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
