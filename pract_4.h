#include "milisegundo.cc"
#include <iostream>
#include <fstream>
#include <vector>
#include <stdlib.h>
#define INF 4000
using namespace std;
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
  inline void nuevo_contenedor(int);
  inline void meter_en_contenedor(int, int);
public:
  int antes_que_quepa(void);
  int menos_espacio_deje(void);
  void ordenar_aleatoriamente(void);
  void ordenar_menor_mayor(int primero_desordenado = 0);
  inline void swap(int, int); //intercambia el primer objeto por el segundo
  inline int get_num_contenedores(void);
  inline int get_n_objetos(void);
  inline int get_capacidad(void);
  inline int get_n_contenedores_optimo(void);
  inline int get_objeto(int);
  inline string get_nombre_instancia(void);
  void imprimir_contenedores(void);
  void imprimir_objetos(int columnas = 9);
  void leer_fichero(ifstream&);
  INSTANCIA(INSTANCIA*); //Constructor de copia para LS
  INSTANCIA(void);
  ~INSTANCIA(void);
};
class GRUPO_INSTANCIAS
{
private:
  int n_casos;
  INSTANCIA** instancia; //array de punteros a instancia
public:
  void LS(int);
  void estadistica_antes_que_quepa(int, int&, int&); //se le pasa el objeto a comprobar
  //y dos enteros por variable (guarda el número de instrucciones y los microsegundos que tarda)
  void estadistica_menos_espacio_deje(int, int&, int&);
  void estadistica_instrucciones(void);
  void estadistica_num_contenedores(void);
  inline int meter_antes_que_quepa(int);
  inline int meter_menos_espacio_deje(int);
  inline void ordenar_aleatoriamente(int);
  inline void ordenar_mayor_menor(int);
  inline void mostrar_contenedores_instancia(int);
  inline void mostrar_contenido_instancia(int);
  void mostrar_contenido_ficheros(void);
  GRUPO_INSTANCIAS(char*);
  ~GRUPO_INSTANCIAS(void);
};