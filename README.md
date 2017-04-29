# Semprarrolar

A empresa de transportes Semprarrolar pretende desenvolver um programa informático para fazer o
escalonamento interativo dos seus condutores. A empresa é obrigada a assegurar o transporte de
passageiros num conjunto de linhas (percursos).
Uma linha é caraterizada pelos seguintes atributos: número identificador único; frequência de circulação
dos autocarros (pode ser diferente de linha para linha mas não varia com o dia da semana); uma lista com a
sequência das paragens que a constituem; uma lista com os tempos de viagem entre paragens; e um
número de autocarros nesessários para assegurar o serviço da linha. Cada autocarro de uma linha funciona
de modo bidirecional (da paragem inicial para a paragem final e de volta à paragem inicial). Uma paragem é
identificada por um nome único e pode pertencer a várias linhas. Todos os autocarros partem da paragem
inicial da linha a que pertencem.
Cada condutor da empresa é caraterizado por um nome, um número identificador único, por um número
máximo de horas consecutivas que pode conduzir (um turno), pelo número máximo de horas que pode
conduzir por semana, pelo número mínimo de horas de descanso obrigatório entre turnos e pelo conjunto de
turnos que lhe estão atribuídos.
Um turno é caraterizado pela linha onde é realizado, pelo identificador do autocarro em que vai ser
realizado, pelo identificador do condutor alocado, pelo instante de início e pelo instante de fim do turno.
Um autocarro é caraterizado plo identificador da linha onde circula, pelo número de ordem na linha, pelo
identificador do seu condutor e pelos turnos que tem que realizar.
