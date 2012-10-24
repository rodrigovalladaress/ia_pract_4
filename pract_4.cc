#include "pract_4.h"
void CONTENEDOR::leer_fichero(ifstream &flujo)
{ 
  flujo >> nombre_instancia;
  flujo >> capacidad;
  flujo >> n_objetos;
  objeto = new int[n_objetos];
  flujo >> n_contenedores_optimo;
  for(int i = 0; i < n_objetos; i++)
    flujo >> objeto[i];
}
CONTENEDOR::CONTENEDOR(void)
{
  n_objetos = 0;
  objeto = NULL;
  nombre_instancia = '0';
  objeto_en_contenedor = NULL;
}
GRUPO_CONTENEDORES::GRUPO_CONTENEDORES(char *nombre_fichero)
{
  cout << "nombre_fichero = " << nombre_fichero << endl;
  ifstream flujo;
  flujo.open(nombre_fichero);
  if(flujo.fail())
    cout << "Error al abrir el fichero." << endl;
  else {
    flujo >> n_casos;
    contenedor = new CONTENEDOR[n_casos];
    cout << "n_casos = " << n_casos << endl;
    for(int i = 0; i < n_casos; i++) //pasar el flujo a cada constructor de contenedor
      contenedor[i].leer_fichero(flujo);
  }
}