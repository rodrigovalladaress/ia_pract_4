#include "pract_4.h"
void CONTENEDOR::ordenar_aleatoriamente(void)
{
  int pos_swap = 0, aux, i = 0, j = n_objetos - 1;
  srand(time(NULL));
  while((i < n_objetos)&&(j > 0)) {
    pos_swap = (i + 1) + rand() % (n_objetos - (i + 1));
    aux = objeto[i];
    objeto[i] = objeto[pos_swap];
    objeto[pos_swap] = aux;
    pos_swap = rand() % j;
    aux = objeto[j];
    objeto[j] = objeto[pos_swap];
    objeto[pos_swap] = aux;
    i++;
    j--;
  }
}
void CONTENEDOR::ordenar_mayor_menor(void)
{
  
}
int CONTENEDOR::get_n_objetos(void)
{
  return n_objetos;
}
int CONTENEDOR::get_capacidad(void)
{
  return capacidad;
}
int CONTENEDOR::get_n_contenedores_optimo(void)
{
  return n_contenedores_optimo;
}
int CONTENEDOR::get_objeto(int i)
{
  return objeto[i];
}
string CONTENEDOR::get_nombre_instancia(void)
{
  return nombre_instancia;
}
void CONTENEDOR::leer_fichero(ifstream &flujo)
{ 
  int aux;
  flujo >> nombre_instancia;
  flujo >> capacidad;
  flujo >> n_objetos;
  flujo >> n_contenedores_optimo;
  for(int i = 0; i < n_objetos; i++) {
    flujo >> aux;
    objeto.push_back(aux);
  }
}
CONTENEDOR::CONTENEDOR(void)
{
  n_objetos = 0;
  nombre_instancia = '0';
  objeto_en_contenedor = NULL;
}
void GRUPO_CONTENEDORES::ordenar_aleatoriamente(int i)
{
  contenedor[i].ordenar_aleatoriamente();
}
void GRUPO_CONTENEDORES::ordenar_mayor_menor(int i)
{
  contenedor[i].ordenar_mayor_menor();
}
void GRUPO_CONTENEDORES::mostrar_contenido_ficheros(void)
{
  int salto_linea;
  CONTENEDOR* p;
  cout << "Número de casos = " << n_casos << endl;
  for(int i = 0; i < n_casos; i++)
  {
    salto_linea = 0;
    cout << "----------------------------------------------------------------------------" << endl;
    p = &contenedor[i];
    cout << p->get_nombre_instancia() << endl;
    cout << "c = " << p->get_capacidad() << " i = " << p->get_n_objetos() << endl;
    cout << "Contenedores óptimos = " << p->get_n_contenedores_optimo() << endl;
    cout << endl;
    for(int j = 0; j < p->get_n_objetos(); j++) {
      cout << p->get_objeto(j) << "\t";
      salto_linea++;
      if(salto_linea > 9) {
	cout << endl;
	salto_linea = 0;
      }
    }
  }
  cout << "----------------------------------------------------------------------------" << endl;
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