/*
COMENTÁRIOS IMPORTANTES:

- Adicionar foreach em vez de for para fazer iterate nos maps
- O showHorario vai para a library ou fica na empresa?

04/Maio/2017
- Alterei a classe trabalho para "tempo"

*/

#include <iostream>
#include <conio.h>

#include "library.h"
#include "global.h"

using namespace std;

//Horário de um dia de trabalho
const unsigned int H_INICIO = 8, M_INICIO = 0;
const Tempo T_INICIO = Tempo(H_INICIO, M_INICIO);
const unsigned int H_FIM = 12, M_FIM = 0;
const Tempo T_FIM = Tempo(H_FIM, M_FIM);

//Variáveis boleanas
bool file_open = false;
bool day_open = false;

bool alterado_condutor = false;
bool alterado_linha = false;
bool alterado;

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
