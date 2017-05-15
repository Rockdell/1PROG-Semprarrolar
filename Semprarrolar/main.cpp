#include <iostream>
#include <conio.h>

#include "library.h"
#include "global.h"

using namespace std;

//Horário de um dia de trabalho
const unsigned int H_INICIO = 8, M_INICIO = 0;
const Tempo T_INICIO = Tempo(H_INICIO, M_INICIO);
const unsigned int H_FIM = 16, M_FIM = 0;
const Tempo T_FIM = Tempo(H_FIM, M_FIM);

//Máximo

//Variáveis boleanas
bool file_open = false;
bool fail = false;

bool alterado_condutor = false;
bool alterado_linha = false;
bool alterado = true;

//Nova empresa
Empresa empresa;

int main()
{
	//Permitir fazer output de carácteres como 'ç' ou 'ã'
	setlocale(LC_ALL, "");
	locale::global(std::locale(""));
	cout.imbue(std::locale());

	MenuPrincipal();

	return 0;
}
