#include <iostream>
#include <fstream>
#include <vector>
#define ALEATORIO 0
#define MAYOR_MENOR 1
using namespace std;
//psar flujos con &
class CONTENEDOR
{
private:
  int n_objetos;
  int capacidad;
  int n_contenedores_optimo;
  vector<int> objeto;
  int* objeto_en_contenedor;
  string nombre_instancia;
  vector<int> contenedor;
public:
  void ordenar_aleatoriamente(void);
  void ordenar_mayor_menor(void);
  int get_n_objetos(void);
  int get_capacidad(void);
  int get_n_contenedores_optimo(void);
  int get_objeto(int);
  string get_nombre_instancia(void);
  void leer_fichero(ifstream&);
  CONTENEDOR(void);
};
class GRUPO_CONTENEDORES
{
private:
  int n_casos;
  CONTENEDOR* contenedor;
public:
  void ordenar_aleatoriamente(int);
  void ordenar_mayor_menor(int);
  void mostrar_contenido_ficheros(void);
  GRUPO_CONTENEDORES(char*);
};