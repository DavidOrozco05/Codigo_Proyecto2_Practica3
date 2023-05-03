#if !defined(FSM_H)
#define FSM_H

#define MEMORYCONFIG 0x50

typedef struct variable{
	int estados;
	char add[4];
	char wb_val[1];
	char rs_num[1];
	char ws_data[16];
	int lectura_add;
	int lectura_data;
	char flag;
    char ban;
	char contador;
    char instruccion[4];

}variable;


void lectura(char,variable* est);
void Iniciarlizar(variable* est);

#endif