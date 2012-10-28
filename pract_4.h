#include <iostream>
#include <fstream>
#include <vector>
#include <stdlib.h>
#define ALEATORIO 0
#define MAYOR_MENOR 1
using namespace std;
//psar flujos con &
class INSTANCIA
{
private:
  int n_objetos;
  int capacidad;
  int n_contenedores_optimo;
  vector<int> objeto;
  int* objeto_en_contenedor;
  string nombre_instancia;
  vector<int> contenedor;
  inline bool cabe_en_contenedor(int, int);
  inline int espacio_sobrante_contenedor(int);
  inline void meter_en_contenedor(int, int);
public:
  void antes_que_quepa(void);
  void menos_espacio_deje(void);
  void ordenar_aleatoriamente(void);
  void ordenar_mayor_menor(int primero_desordenado = 0);
  inline int get_n_objetos(void);
  inline int get_capacidad(void);
  inline int get_n_contenedores_optimo(void);
  inline int get_objeto(int);
  inline string get_nombre_instancia(void);
  void imprimir_objetos(int columnas = 9);
  void leer_fichero(ifstream&);
  INSTANCIA(void);
};
class GRUPO_INSTANCIAS
{
private:
  int n_casos;
  INSTANCIA* instancia;
public:
  void meter_antes_que_quepa(int);
  void ordenar_aleatoriamente(int);
  void ordenar_mayor_menor(int);
  void mostrar_contenido_instancia(int);
  void mostrar_contenido_ficheros(void);
  GRUPO_INSTANCIAS(char*);
};