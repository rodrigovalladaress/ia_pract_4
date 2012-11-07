#include "milisegundo.cc"
#include <iostream>
#include <fstream>
#include <vector>
#include <stdlib.h>
#include <math.h>
#define INF 4000
#define e 2.7182
#define ORDEN_ALEATORIO 0
#define ORDEN_MAYOR_MENOR 1
#define NO_ORDENAR 3
#define MAX_VECINAS_LS 100
#define MAX_VECINAS_SA 100
#define MENOS_ESPACIO_DEJE 0
#define PROXIMO_10 1
#define SWAP_AZAR 2
#define MAX_ILS 10
#define LOCAL_ITERADA 0
#define MULTI_ARRANQUE 1
#define LCR_SIZE 5
using namespace std;
class INSTANCIA
{
private:
  int n_objetos;
  int capacidad;
  int n_contenedores_optimo;
  vector<int> pila_sacar_objetos;
  vector<int> objeto; //El orden de los objetos permanece constante
  int* objeto_en_contenedor;
  string nombre_instancia;
  vector<int> contenedor;
  int elegir_objeto_al_azar(void);
  void quitar_objeto_de_contenedor(int);
  void ordenar_objetos_segun_contenedor(vector<int>&); /* Ordena los objetos para que a la hora se introdu-
  cirlos en los contenedores, estos no cambien de contenedor*/
  int buscar_objeto_que_encaje_en(int, int a_partir_de = 0); //hueco, posicion a buscar
  //devuelve el mayor objeto que encaja en un hueco
  void mover_objeto_menos_espacio_deje(int);
  void borrar_contenedores_vacios(void);
  inline bool cabe_en_contenedor(int, int); //objeto, contenedor
  inline int espacio_sobrante_contenedor(int);
  inline void nuevo_contenedor(int);
  inline void meter_en_contenedor(int, int); //objeto, contenedor
  void reiniciar_contenedores(void);
  void ordenar_pila_mayor_menor(int = 0);
  void iniciar_pila_aleatoriamente(void);
  void iniciar_pila_mayor_menor(void);
  void iniciar_pila_sin_orden(void);
  int pop_pos(void);
public:
  bool distinta_solucion(INSTANCIA*);
  int espacio_sobrante_total(void);
  void GRASP(int);
  void LS_azar(void);
  void LS_proximo_10(void);
  void LS(void);
  int antes_que_quepa(int = NO_ORDENAR);
  int menos_espacio_deje(int = NO_ORDENAR);
  void ordenar_aleatoriamente(void);
  void ordenar_menor_mayor(int = 0);
  inline void swap(int, int); //intercambia el primer objeto por el segundo
  inline int get_espacio_ocupado_en_contenedor(int);
  inline int get_objeto_en_contenedor(int);
  inline int get_num_contenedores(void);
  inline int get_n_objetos(void);
  inline int get_capacidad(void);
  inline int get_n_contenedores_optimo(void);
  inline int get_objeto(int);
  inline string get_nombre_instancia(void);
  void imprimir_contenedores(void);
  void imprimir_objetos(int columnas = 9);
  void leer_fichero(ifstream&);
  void igualar(INSTANCIA*);
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
  float Pr(float, int);
  void GRASP(int, int = MENOS_ESPACIO_DEJE);
  void SA(int, int = MENOS_ESPACIO_DEJE, float = 1, float = 0.9);
  void ILS(int, int = MAX_ILS, int = MENOS_ESPACIO_DEJE, bool = false);
  void LS(int, int op = 0);
  void estadistica_antes_que_quepa(int, int&, int&); //se le pasa el objeto a comprobar
  //y dos enteros por variable (guarda el número de instrucciones y los microsegundos que tarda)
  void estadistica_menos_espacio_deje(int, int&, int&);
  void estadistica_instrucciones(void);
  void estadistica_num_contenedores(void);
  inline int meter_antes_que_quepa(int, int = NO_ORDENAR);
  inline int meter_menos_espacio_deje(int, int = NO_ORDENAR);
  inline void ordenar_aleatoriamente(int);
  inline void ordenar_mayor_menor(int);
  inline void mostrar_contenedores_instancia(int);
  inline void mostrar_contenido_instancia(int);
  void mostrar_objetos(int);
  void mostrar_contenido_ficheros(void);
  GRUPO_INSTANCIAS(char*);
  ~GRUPO_INSTANCIAS(void);
};