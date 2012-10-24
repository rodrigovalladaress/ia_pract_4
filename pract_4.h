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
  void leer_fichero(ifstream&);
  CONTENEDOR(void);
};
class GRUPO_CONTENEDORES
{
private:
  int n_casos;
  CONTENEDOR* contenedor;
public:
  GRUPO_CONTENEDORES(char*);
};
