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
  void ordenar_mayor_menor(int primero_desordenado = 0);
  inline int get_n_objetos(void);
  inline int get_capacidad(void);
  inline int get_n_contenedores_optimo(void);
  inline int get_objeto(int);
  inline string get_nombre_instancia(void);
  void imprimir_contenedores(void);
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
  void estadistica_antes_que_quepa(int, int&, int&); //se le pasa el objeto a comprobar
  //y dos enteros por variable (guarda el número de instrucciones y los microsegundos que tarda)
  
  //Crear una funcion estadistica que calcule varios ejemplos
  //en los ejemplos se comprueba el numero de contenedores
  //con el numero de contenedores óptimo
  inline int meter_antes_que_quepa(int);
  inline void ordenar_aleatoriamente(int);
  inline void ordenar_mayor_menor(int);
  inline void mostrar_contenedores_instancia(int);
  inline void mostrar_contenido_instancia(int);
  void mostrar_contenido_ficheros(void);
  GRUPO_INSTANCIAS(char*);
};