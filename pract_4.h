#include <iostream>
#include <fstream>
#include <vector>
using namespace std;
//psar flujos con &
class CONTENEDOR
{
private:
  int n_objetos;
  int capacidad;
  int n_contenedores_optimo;
  int* objeto;
  int* objeto_en_contenedor;
  string nombre_instancia;
  vector<int> contenedor;
public:
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
  void mostrar_contenido_ficheros(void);
  GRUPO_CONTENEDORES(char*);
};
