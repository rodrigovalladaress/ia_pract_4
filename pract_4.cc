#include "pract_4.h"
bool INSTANCIA::cabe_en_contenedor(int i, int cont)
{
  return espacio_sobrante_contenedor(cont) >= objeto[i] ? true : false;
}
int INSTANCIA::espacio_sobrante_contenedor(int cont)
{
  return capacidad - contenedor[cont];
}
void INSTANCIA::nuevo_contenedor(int i)
{
  contenedor.push_back(objeto[i]);
  objeto_en_contenedor[i] = contenedor.size() - 1;
}
void INSTANCIA::meter_en_contenedor(int i, int cont)
{
  if(cabe_en_contenedor(i, cont) == true) {
    contenedor[cont] += objeto[i];
    objeto_en_contenedor[i] = cont;
  }
  else {
    cout << "Error en las capacidades de los contenedores." << endl;
    cout << "objeto[i] = " << objeto[i] << endl;
  }
}
int INSTANCIA::antes_que_quepa(void)
{
  unsigned pos_contenedor = 0;
  int num_instrucciones = 0;
  contenedor.clear();
  for(int i = 0; i < n_objetos; i++)
  {
    while((pos_contenedor < contenedor.size())&&(cabe_en_contenedor(i, pos_contenedor) == false)) {
      pos_contenedor++;
      num_instrucciones++;
    }
    if(pos_contenedor == contenedor.size())
      nuevo_contenedor(i);
    else
      meter_en_contenedor(i, pos_contenedor);
    num_instrucciones++;
  }
  return num_instrucciones;
}
int INSTANCIA::menos_espacio_deje(void)
{
  unsigned pos_contenedor;
  int num_instrucciones = 0, min_espacio = INF;
  contenedor.clear();
  for(int i = 0; i < n_objetos; i++)
  {
    pos_contenedor = INF; //Si no cambia no se ha encontrado contenedor en el que quepa
    for(int j = 0; j < contenedor.size(); j++)
    {
      if((cabe_en_contenedor(i, j) == true)
	  &&(min_espacio > espacio_sobrante_contenedor(j))) {
	min_espacio = espacio_sobrante_contenedor(j);
	pos_contenedor = j;
	num_instrucciones++;
      }
      num_instrucciones++;
    }
    if(pos_contenedor == INF)
      nuevo_contenedor(i);
    else
      meter_en_contenedor(i, pos_contenedor);
    num_instrucciones++;
  }
  return num_instrucciones;
}
void INSTANCIA::ordenar_aleatoriamente(void)
{
  int pos_swap = 0, aux, i = 0, j = n_objetos - 1;
  srand(time(NULL));
  while((i < n_objetos)&&(j > 0)) {
    //Se ordena aleatoriamente el vector de abajo a arriba
    pos_swap = (i + 1) + rand() % (n_objetos - (i + 1));
    aux = objeto[i];
    objeto[i] = objeto[pos_swap];
    objeto[pos_swap] = aux;
    //Se ordena aleatoriamente el vector de arriba a abajo
    pos_swap = rand() % j;
    aux = objeto[j];
    objeto[j] = objeto[pos_swap];
    objeto[pos_swap] = aux;
    i++;
    j--;
  }
}
void INSTANCIA::ordenar_mayor_menor(int primero_desordenado/*= 0*/)
{
  int pos, aux;  
  if(primero_desordenado < n_objetos) {
    pos = 0;
    while(objeto[primero_desordenado] > objeto[pos])
      pos++;
    for(int i = pos; i < primero_desordenado; i++)
    {
      aux = objeto[i];
      objeto[i] = objeto[primero_desordenado];
      objeto[primero_desordenado] = aux;
    }
    ordenar_mayor_menor(primero_desordenado + 1);
  }
}
int INSTANCIA::get_n_objetos(void)
{
  return n_objetos;
}
int INSTANCIA::get_capacidad(void)
{
  return capacidad;
}
int INSTANCIA::get_n_contenedores_optimo(void)
{
  return n_contenedores_optimo;
}
int INSTANCIA::get_objeto(int i)
{
  return objeto[i];
}
string INSTANCIA::get_nombre_instancia(void)
{
  return nombre_instancia;
}
void INSTANCIA::imprimir_contenedores(void)
{
  for(unsigned i = 0; i < contenedor.size(); i++)
  {
    cout << "Contenedor [" << i << "] (" << espacio_sobrante_contenedor(i) << ")" << endl;
    cout << endl;
    for(int j = 0; j < n_objetos; j++)
      if(objeto_en_contenedor[j] == i)
	cout << objeto[j] << endl;
    cout << "---------------------" << endl;
  }
  cout << "Número de contenedores óptimo = " << n_contenedores_optimo << endl;
}
void INSTANCIA::imprimir_objetos(int columnas/*= 9*/)
{
  int salto_linea = 0;
  for(int i = 0; i < n_objetos; i++) {
    cout << objeto[i] << "\t";
    salto_linea++;
    if(salto_linea > columnas) {
      cout << endl;
      salto_linea = 0;
    }
  }
}
void INSTANCIA::leer_fichero(ifstream &flujo)
{ 
  int aux;
  flujo >> nombre_instancia;
  flujo >> capacidad;
  flujo >> n_objetos;
  objeto_en_contenedor = new int[n_objetos];
  flujo >> n_contenedores_optimo;
  for(int i = 0; i < n_objetos; i++) {
    flujo >> aux;
    objeto.push_back(aux);
  }
}
INSTANCIA::INSTANCIA(void)
{
  n_objetos = 0;
  nombre_instancia = '0';
  objeto_en_contenedor = NULL;
}

void GRUPO_INSTANCIAS::estadistica_antes_que_quepa(int i, int& num_instrucciones, int& tiempo)
{
  cronousec(1);
  num_instrucciones = meter_antes_que_quepa(i);
  tiempo = cronousec(0);
}
void GRUPO_INSTANCIAS::estadistica_menos_espacio_deje(int i, int& num_instrucciones, int& tiempo)
{
  cronousec(1);
  num_instrucciones = meter_menos_espacio_deje(i);
  tiempo = cronousec(0);
}
int GRUPO_INSTANCIAS::meter_antes_que_quepa(int i)
{
  return instancia[i].antes_que_quepa();
}
int GRUPO_INSTANCIAS::meter_menos_espacio_deje(int i)
{
  return instancia[i].menos_espacio_deje();
}
void GRUPO_INSTANCIAS::ordenar_aleatoriamente(int i)
{
  instancia[i].ordenar_aleatoriamente();
}
void GRUPO_INSTANCIAS::ordenar_mayor_menor(int i)
{
  instancia[i].ordenar_mayor_menor();
}
void GRUPO_INSTANCIAS::mostrar_contenedores_instancia(int i)
{
  instancia[i].imprimir_contenedores();
}
void GRUPO_INSTANCIAS::mostrar_contenido_instancia(int i)
{
  instancia[i].imprimir_objetos();
}
void GRUPO_INSTANCIAS::mostrar_contenido_ficheros(void)
{
  INSTANCIA* p;
  cout << "Número de casos = " << n_casos << endl;
  for(int i = 0; i < n_casos; i++)
  {
    cout << "----------------------------------------------------------------------------" << endl;
    cout << endl;
    p = &instancia[i];
    cout << p->get_nombre_instancia() << endl;
    cout << "c = " << p->get_capacidad() << " i = " << p->get_n_objetos() << endl;
    cout << "Contenedores óptimos = " << p->get_n_contenedores_optimo() << endl;
    cout << endl;
    p->imprimir_objetos();
  }
  cout << "----------------------------------------------------------------------------" << endl;
}
GRUPO_INSTANCIAS::GRUPO_INSTANCIAS(char *nombre_fichero)
{
  cout << "nombre_fichero = " << nombre_fichero << endl;
  ifstream flujo;
  flujo.open(nombre_fichero);
  if(flujo.fail())
    cout << "Error al abrir el fichero." << endl;
  else {
    flujo >> n_casos;
    instancia = new INSTANCIA[n_casos];
    cout << "n_casos = " << n_casos << endl;
    for(int i = 0; i < n_casos; i++) //pasar el flujo a cada constructor de instancia
      instancia[i].leer_fichero(flujo);
  }
}