/*
ADDED TO GITHUB
PLZ NO TROLL

Faz as altera��es e depois faz commit com um coment�rio do que alteraste.

Acho que est� pronto boyyy!

*/


#include <iostream>
#include <conio.h>

#include "library.h"
#include "global.h"

using namespace std;

//Hor�rio de um dia de trabalho
const unsigned int H_INICIO = 8, M_INICIO = 0;
const Tempo T_INICIO = { H_INICIO, M_INICIO };
const unsigned int H_FIM = 12, M_FIM = 0;
const Tempo T_FIM = { H_FIM, M_FIM };

//Horas de um turno
const int duracao_turno = 1;

//Vari�veis boleanas
bool file_open = false;
bool alterado_condutor = false;
bool alterado_linha = false;
bool alterado;

//Nova empresa
Empresa empresa;

int main()
{
	//Permitir fazer output de car�cteres como '�' ou '�'
	setlocale(LC_ALL, "");
	locale::global(std::locale(""));
	cout.imbue(std::locale());

	MenuPrincipal();

	return 0;
}
