#if !defined(COLA_H)
#define COLA_H


typedef char DATOCOLA;

#define ERROR 1
#define BIEN 0

#define SI 1
#define NO 0

#define TAM 30
typedef struct eCola {
   DATOCOLA data[TAM];
   int entrada;//pos de entrada en en arreglo
   int salida;// pos de salida en el arreglo
   int peso;
} eCola;


void inicie_cola(eCola* c);   //inicia estructura "eCola"

char cola_add(eCola* c,DATOCOLA dato); //añadir un dato a la cola(?) retorna 1 si error 0 si bien

DATOCOLA cola_get(eCola* c);  //obtener el dato de la cola

int tam_cola(eCola* c); //retorna la cantidad de datos almacenados

int cola_llena(eCola* c);

int cola_vacia(eCola* c);

#endif