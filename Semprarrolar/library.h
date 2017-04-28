#ifndef LIBRARY_H
#define LIBRARY_H

#include <string>
#include <vector>

using namespace std;

//Menus
void MenuPrincipal();
void MenuLinhas();
void MenuCondutores();
void MenuInformacao();

//QoL methods
bool compararCaseInsensitive(string strFirst, string strSecond);
unsigned int inputErrorHandling(string input, char propriedade);
bool inputExist(unsigned int propriedade, char objeto);
bool inputExist(string paragem);
bool inputExist(string paragem, vector<string> lista_paragens);

#endif