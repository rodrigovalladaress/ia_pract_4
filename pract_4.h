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
#define NUM_SOLUCIONES 100
#define MAX_VECINAS_LS 100
#define MENOS_ESPACIO_DEJE 0
#define REDUCIR_C 7
#define LCR_SIZE 7
#define TABU_SIZE 7
#define T 7
#define POBLACION_INICIAL 5
#define LIMITE_POBLACION 10
#define MAX_NUM_MUTACIONES 5
#define UMBRAL_MEDIAS_REPETIDAS 10
#define MAX_LS_AZAR 10
using namespace std;
class INSTANCIA
{
private:
  //ATRIBUTOS //
  int n_objetos;
  int capacidad;
  int n_contenedores_optimo;
  unsigned tam_cola_tabu;
  vector<INSTANCIA*> poblacion;
  vector<int> cola_tabu;
  vector<int> pila_sacar_objetos;
  vector<int> objeto; //El orden de los objetos permanece constante
  int* objeto_en_contenedor;
  string nombre_instancia;
  vector<int> contenedor;
  // MÉTODOS //
  // mover objetos //
  inline int elegir_objeto_al_azar(void);
  inline void quitar_objeto_de_contenedor(int);
  int buscar_objeto_que_encaje_en(int, int a_partir_de = 0); //hueco, posicion a buscar
  //devuelve el mayor objeto que encaja en un hueco
  void mover_objeto_antes_que_quepa(int);
  void mover_objeto_menos_espacio_deje(int);
  void meter_objeto_menos_espacio_deje(int);
  // contenedores //
  void borrar_contenedores_vacios(void);
  inline bool cabe_en_contenedor(int, int); //objeto, contenedor
  inline int espacio_sobrante_contenedor(int);
  inline void nuevo_contenedor(int);
  inline void meter_en_contenedor(int, int); //objeto, contenedor
  void reiniciar_contenedores(void);
  // Métodos privados del Algoritmo Genético //
  void mutacion(void);
  void integridad_genetica(void);
  void cruzar(int, int);
  void reproduccion(void);
  // Cola para la población del Algoritmo Genético //
  void ordenar_poblacion(unsigned = 0);
  // Cola para la búsqueda tabú  //
  void push_cola_tabu(int);
  bool comp_no_esta_en_cola(int);
  int TS_obj_azar(void);
  // Pila de posiciones de objetos  //
  void ordenar_pila_mayor_menor(int = 0);
  void iniciar_pila_aleatoriamente(void);
  void iniciar_pila_mayor_menor(void);
  void iniciar_pila_sin_orden(void);
  int pop_pos(void);
  int pop_pos_grasp(int);//Saca al azar entre las 7 primeras posiciones
public:
  // Heurísticas  //
  unsigned media_poblacion(void);
  
  void inicializar_poblacion(int);
  void GA(int);
  void inicializar_cola_tabu(int);
  void TS(void);
  void GRASP(int = T);
  void LS_azar(void);
  void LS(void);
  // Comparación de instancias  //
  int espacio_sobrante_total(void);
  bool distinta_solucion(INSTANCIA*);
  // introducir en contenedores //
  void antes_que_quepa(int = NO_ORDENAR);
  void menos_espacio_deje(int = NO_ORDENAR);
  // get_ //
  inline int get_espacio_ocupado_en_contenedor(int);
  inline int get_objeto_en_contenedor(int);
  inline void set_objeto_en_contenedor(int, int);
  inline int get_num_contenedores(void);
  inline int get_n_objetos(void);
  inline int get_capacidad(void);
  inline int get_n_contenedores_optimo(void);
  inline int get_objeto(int);
  inline string get_nombre_instancia(void);
  // imprimir //
  void imprimir_contenedores(void);
  void imprimir_objetos(int columnas = 9);
  // constructores //
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
  bool poblacion_estancada(unsigned&, unsigned&);
  void GA(int, int = POBLACION_INICIAL, int = LIMITE_POBLACION);
  //dos opciones, limite poblacion = 10 y límite = 20
  void TS(int, int = T); //dos opciones, t = 7 o t = 10
  float Pr(float, int);
  void GRASP(int, int = T); //dos opciones, t = 7 o t = 10
  void SA(int, int = MENOS_ESPACIO_DEJE, float = 1, float = 0.9, int = REDUCIR_C); 
  //dos opciones, reducir c cada 7 o 10 iteraciones
  void ILS(int, int = NO_ORDENAR); //dos opciones mayor menor o aleatorio
  void LS(int, int = 0);
  inline void meter_antes_que_quepa(int, int = NO_ORDENAR);
  inline void meter_menos_espacio_deje(int, int = NO_ORDENAR);
  inline void mostrar_contenedores_instancia(int);
  inline void mostrar_contenido_instancia(int);
  void mostrar_objetos(int);
  void mostrar_contenido_ficheros(void);
  GRUPO_INSTANCIAS(char*);
  ~GRUPO_INSTANCIAS(void);
};