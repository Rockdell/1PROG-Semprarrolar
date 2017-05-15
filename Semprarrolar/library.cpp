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

		if (alterado)
		{
			empresa.beginAtribuicao();
			alterado = false;
		}

		cout << " [1] Linhas\n [2] Condutores\n [3] Informação\n [4] Atribuição de trabalho\n [0] Exit\n\n";

	erro1:
		char input = _getch();

		switch (input)
		{
		case '0':
		{
			if (alterado_condutor || alterado_linha)
			{
				cout << " Pretende guardar as alterações? [Y/N]\n";

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

					cout << "\n O programa fechou e guardou as alterações! ";
					_getch();
					return;
				}
				case 'N':
				{
					cout << "\n O programa fechou sem guardar as alterações! ";
					_getch();
					return;
				}
				default:
					goto erro3;
				}
			}
			else
			{
				cout << "\n O programa fechou! ";
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
				cout << "\n Ficheiro(s) não encontrado(s)\n";
				_getch();

				fail = false;

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

	cout << " [1] Adicionar linha\n [2] Alterar linha\n [3] Remover linha\n [0] Exit\n\n";

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

	cout << " [1] Adicionar condutor\n [2] Alterar condutor\n [3] Remover condutor\n [4] Ver trabalho do condutor\n [5] Ver horas semanais restantes\n [0] Exit\n\n";

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
	cout << " === MENU INFORMAÇÂO ===\n";
	cout << " =======================\n\n";

	cout << " [1] Percurso entre duas paragens\n [2] Horário da linha\n [3] Horário da paragem\n [4] Inquirir linhas sobre paragem\n " <<
		"[5] Informação da linha\n [6] Informação do autocarro\n [7] Autocarros sem condutor\n [0] Exit\n\n";

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
	cout << " === MENU ATRIBUIÇÃO ===\n";
	cout << " =======================\n\n";

	if (!day_open)
	{
		cout << " Que dia da semana pretende selecionar?\n";
		cout << " [1] Segunda-feira\n [2] Terça-feira\n [3] Quarta-feira\n [4] Quinta-feira\n [5] Sexta-feira\n [6] Sábado\n [7] Domingo\n [0] Exit\n\n";

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
		cout << " " << dia_da_semana << endl << endl;

		//Map da com as linhas e os autocarros de cada linha
		linhasDia linhas_com_autocarros = empresa.getTrabalho().at(index);

		//Linhas existentes
		mapLinha lLinhas = empresa.getLinhas();

		cout << " Linhas existentes:" << endl;

		for (mapLinha::iterator it = lLinhas.begin(); it != lLinhas.end(); it++)
		{
			cout << " " << it->second.getID() << endl;
		}

		cout << "\n Que linha pretende selecionar? ";

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
		{
			cerr << " Operação cancelada.\n";
			_getch();
			 
			day_open = false;
			goto redo;			
		}
		}

		istringstream stream_id(input_id);
		stream_id >> l_id;

		if (!inputExist(l_id, 'l'))
		{
			cerr << " Essa linha não existe. Escolha outra: ";
			goto id;
		}

		mapAutocarro autocarros_da_linha = linhas_com_autocarros[l_id];

		cout << "\n Linha: " << l_id << endl << endl;

		//Output dos autocarros da linha desse dia
		for (mapAutocarro::iterator it = autocarros_da_linha.begin(); it != autocarros_da_linha.end(); it++)
		{
			Autocarro ac = it->second;
			cout << " Autocarro - número " << it->first << ":\n";

			for (size_t i = 0; i < ac.getTrabalho().size(); i++)
			{
				cout << " Turno nº " << i + 1 << ": " << ac.getTrabalho().at(i).getInicio().showTempo() << " a " << ac.getTrabalho().at(i).getFim().showTempo() << endl;
			}

			if (ac.getCondutorID() == 0)
				cout << " Condutor atribuído: NULL " << endl << endl;
			else
				cout << " Condutor atribuído: " << empresa.getCondutores()[ac.getCondutorID()].getNome() << endl << endl;
		}

		cout << " [1] Atribuir condutor\n [2] Desatribuir condutor\n [0] Cancelar\n\n";

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
				cerr << " Input inválido. Introduza novamente: ";
				goto autocarro1;
			case 1:
				break;
			case 2:
				cerr << "\n Operação cancelada.\n";
				_getch();
			
				day_open = false;
				goto redo;
			}
			
			istringstream stream_autocarro(input_autocarro);
			stream_autocarro >> auto_id;
			
			//Autocarro existe?
			if (auto_id < 1 || auto_id > autocarros_da_linha.rbegin()->first)
			{
				cerr << " Esse autocarro não existe. Escolha outro: ";
				goto autocarro1;
			}
			else if (empresa.getTrabalho().at(index)[l_id][auto_id].getCondutorID() != 0)
			{
				cerr << " Esse autocarro já tem um condutor atribuído. Escolha outro: ";
				goto autocarro1;
			}
			
			cout << " Que condutor pretende atribuir o trabalho? ";
			
		condutor1:
			getline(cin, input_condutor);
			
			switch (inputErrorHandling(input_condutor, 'i'))
			{
			case 0:
				cerr << " Input inválido. Introduza novamente: ";
				goto condutor1;
			case 1:
				break;
			case 2:
				cerr << "\n Operação cancelada.\n";
				_getch();
			
				day_open = false;
				goto redo;
			}
			
			istringstream stream_condutor(input_condutor);
			stream_condutor >> c_id;
			
			if (!inputExist(c_id, 'c'))
			{
				cerr << " Esse condutor não existe. Escolha outro: ";
				goto condutor1;
			}
			
			//Variaveis mais acessiveis
			int turno = empresa.getCondutores()[c_id].getTurno();
			int semana = empresa.getCondutores()[c_id].getSemana();
			int descanso = empresa.getCondutores()[c_id].getDescanso();
			vector<Trabalho> trabalhos = empresa.getCondutores()[c_id].getTrabalho();
			vector<Trabalho> driver_trab;

			Autocarro bus = empresa.getTrabalho().at(index)[l_id][auto_id];
			vector<Trabalho> bus_trab = bus.getTrabalho();

			//Trabalhos existentes no dia que selecionou (condutor)
			for (unsigned int n = 0; n < trabalhos.size(); n++)
			{
				int dia = trabalhos.at(n).getDiaSemana();

				if (dia == index)
					driver_trab.push_back(trabalhos.at(n));
			}

			//Total de horas/minutos atribuidas ao condutor e ao autocarro
			unsigned int minutos_semana = semana * 60;
			unsigned int minutos_turno = turno * 60;
			unsigned int total_c = 0;
			unsigned int total_a = 0;

			//Tempo que o condutor trabalha durante a semana toda (tempo semanal atual do condutor)
			for (unsigned int n = 0; n < trabalhos.size(); n++)
			{
				Tempo inicio = trabalhos.at(n).getInicio();
				Tempo fim = trabalhos.at(n).getFim();

				total_c += fim.subtractTempo(inicio);
			}

			//Tempo dos turnos do autocarro
			for (unsigned int n = 0; n < bus_trab.size(); n++)
			{
				Tempo inicio = bus_trab.at(n).getInicio();
				Tempo fim = bus_trab.at(n).getFim();

				total_a += fim.subtractTempo(inicio);
			}

			//Verifica se ultrapassa as horas semanais e se o turno do autocarro é maior que o turno do condutor 
			if (total_c + total_a > minutos_semana /*|| total_a > minutos_turno*/)
			{
				cout << " Erro ao atribuir o trabalho a este condutor. Escolha outro: " << endl;
				goto condutor1;
			}

			//Verifica se existe conflito de turnos (horas)
			for (unsigned int n = 0; n < bus_trab.size(); n++)
			{
				Trabalho current_a = bus_trab.at(n);
				Tempo ti_a = current_a.getInicio();
				Tempo tf_a = current_a.getFim();

				for (unsigned int y = 0; y < driver_trab.size(); n++)
				{
					Trabalho current_c = driver_trab.at(y);
					Tempo ti_c = current_c.getInicio();
					ti_c.subtractTempo(descanso);
					Tempo tf_c = current_c.getFim();
					tf_c.sumTempo(descanso);

					if (tf_a.getHora() < ti_c.getHora() || (tf_a.getHora() == ti_c.getHora()) && (tf_a.getMinuto() <= ti_c.getMinuto()))
						goto valid;
					else if (ti_a.getHora() > tf_c.getHora() || (ti_a.getHora() == tf_c.getHora()) && (ti_a.getMinuto() >= tf_c.getMinuto()))
						goto valid;
					else
					{
						if (tf_c.getHora() < ti_a.getHora() || (tf_c.getHora() == ti_a.getHora()) && (tf_c.getMinuto() <= ti_a.getMinuto()))
							goto valid;
						else if (ti_c.getHora() > tf_a.getHora() || (ti_c.getHora() == tf_a.getHora()) && (ti_c.getMinuto() >= tf_a.getMinuto()))
							goto valid;
					}

					cout << "Erro ao atribuir o trabalho a este condutor. Escolha outro: ";
					goto condutor1;
				}
			}

		valid:			
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
				cerr << " Input inválido. Introduza novamente:";
				goto autocarro2;
			case 1:
				break;
			case 2:
				cerr << " Operação cancelada.\n";
				_getch();

				day_open = false;
				goto redo;
			}

			istringstream stream_autocarro(input_autocarro);
			stream_autocarro >> auto_id;

			//Autocarro existe?
			if (auto_id < 1 || auto_id > autocarros_da_linha.rbegin()->first)
			{
				cerr << " Esse autocarro não existe. Escolha outro: ";
				goto autocarro2;
			}
			else if (empresa.getTrabalho().at(index)[l_id][auto_id].getCondutorID() == 0)
			{
				cerr << " Esse autocarro não tem nenhum condutor atribuído. Escolha outro: ";
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
string intDay(unsigned int day)
{
	switch (day)
	{
	case 0:
		return "Segunda-feira";
	case 1:
		return "Terça-feira";
	case 2:
		return "Quarta-feira";
	case 3:
		return "Quinta-feira";
	case 4:
		return "Sexta-feira";
	case 5:
		return "Sábado";
	case 6:
		return "Domingo";
	default:
		return "null";
	}
}