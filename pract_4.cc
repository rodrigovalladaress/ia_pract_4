#include "pract_4.h"
void CONTENEDOR::ordenar_objetos(int)
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


void GRUPO_CONTENEDORES::ordenar_objetos_de_contenedor(int opcion)
{
  //if(opcion == MAYOR_MENOR)
    
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