#ifndef LIBRARY_H
#define LIBRARY_H

#include "global.h"
#include <string>
#include <vector>

using namespace std;

//Menus
void MenuPrincipal();
void MenuLinhas();
void MenuCondutores();
void MenuInformacao();
void MenuAtribuicao();

//QoL methods
bool compararCaseInsensitive(string strFirst, string strSecond);
unsigned int inputErrorHandling(string input, char propriedade);
bool inputExist(unsigned int propriedade, char objeto);
vector<unsigned int> inputExist(string paragem);
bool inputExist(string paragem, vector<string> lista_paragens);
string intDay(unsigned int day);

//void sortTrabalho(vector<Trabalho> &trab);

#endif