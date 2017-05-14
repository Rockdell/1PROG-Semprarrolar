#ifndef GLOBAL_H
#define GLOBAL_H

#include "condutor.h"
#include "linha.h"
#include "tempo.h"
#include "empresa.h"

using namespace std;

extern char ESC_CHAR;

//Inicio e fim do horário de trabalho
extern const unsigned int H_INICIO, M_INICIO;
extern const Tempo T_INICIO;
extern const unsigned int H_FIM, M_FIM;
extern const Tempo T_FIM;

//Variáveis boleanas
extern bool file_open;
extern bool fail;

extern bool alterado_condutor;
extern bool alterado_linha;
extern bool alterado;

extern Empresa empresa;

#endif