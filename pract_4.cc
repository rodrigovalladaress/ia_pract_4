#include "pract_4.h"
///////////////////////////////////////////////////////////////////////////////////////////////////
//                                                                                     INSTANCIA //
///////////////////////////////////////////////////////////////////////////////////////////////////
//                                                                                       private //
///////////////////////////////////////////////////////////////////////////////////////////////////
void INSTANCIA::quitar_objeto_de_contenedor(int i)
{
  contenedor[objeto_en_contenedor[i]] -= objeto[i];
  objeto_en_contenedor[i] = -1;
}
void INSTANCIA::ordenar_objetos_segun_contenedor(vector<int>& auxiliar)
{
  //vector<int> auxiliar; //nuevo array de objetos
  for(int id_contenedor = 0; id_contenedor < contenedor.size(); id_contenedor++)
  {
    for(int i = 0; i < n_objetos; i++)
    {
      if(objeto_en_contenedor[i] == id_contenedor) //el objeto se encuentra en el contenedor
	auxiliar.push_back(objeto[i]); // se van introduciendo por orden en el nuevo array
    }
  }
}
void INSTANCIA::mover_objeto_menos_espacio_deje(int i)
{
  int min_espacio = INF;
  int pos_contenedor = objeto_en_contenedor[i]; //Si no se pone así da error
  quitar_objeto_de_contenedor(i);
  for(int j = 0; j < contenedor.size(); j++)
  {
    if((cabe_en_contenedor(i, j) == true)&&(min_espacio > espacio_sobrante_contenedor(j))) {
      min_espacio = espacio_sobrante_contenedor(j);
      pos_contenedor = j; //Problema, no pone el objeto donde debe
    }
  }
  meter_en_contenedor(i, pos_contenedor);
}
void INSTANCIA::borrar_contenedores_vacios(void)
{
  for(int i = 0; i < contenedor.size(); i++)
  {
    if(contenedor[i] == 0) {
      contenedor.erase(contenedor.begin() + i); //Comprobar si borra bien
      i--;
    }
  }
}
bool INSTANCIA::cabe_en_contenedor(int i, int cont)
{
  return espacio_sobrante_contenedor(cont) >= objeto[i] ? true : false;
}
int INSTANCIA::espacio_sobrante_total(void)
{
  int espacio_sobrante = 0;
  for(int i = 0; i < contenedor.size(); i++)
    espacio_sobrante += espacio_sobrante_contenedor(i);
  return espacio_sobrante;
}
int INSTANCIA::espacio_sobrante_contenedor(int cont)
{
  if(capacidad - contenedor[cont] < 0)
    cout << "Error. Espacio sobrante negativo." << endl;
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
    cout << "objeto[i] = " << objeto[i] << " no cabe en contenedor " << cont << " (";
    cout << espacio_sobrante_contenedor(cont) << ")" << endl;
    cout << endl;
  }
}
void INSTANCIA::reiniciar_contenedores(void)
{
  contenedor.clear();
  for(int i = 0; i < n_objetos; i++)
    objeto_en_contenedor[i] = -1;
}
///////////////////////////////////////////////////////////////////////////////////////////////////
//                                                                                        public //
///////////////////////////////////////////////////////////////////////////////////////////////////
bool INSTANCIA::distinta_solucion(INSTANCIA* p)
{
  int i = 0;
  while((i < n_objetos)&&(objeto_en_contenedor[i] == p->get_objeto_en_contenedor(i)))
    i++;
  return i == n_objetos ? false : true;
}
void INSTANCIA::integridad_instancia(void)
{
  for(int i = 0; i < n_objetos; i++)
    if(objeto_en_contenedor[i] == -1)
      cout << "No inicializado." << endl;
  /*
  int suma_objetos;
  cout << contenedor.size() << endl;
  for(int i = 0; i < contenedor.size(); i++)
  {
    cout << endl;
    suma_objetos = 0;
    if(contenedor[i] > capacidad)
      cout << "Error en las capacidades." << endl;
    for(int j = 0; j < n_objetos; j++)
    {
      if(objeto_en_contenedor[j] == i)
	suma_objetos += objeto[i];
      if((objeto_en_contenedor[j] < 0)||(objeto_en_contenedor[j] >= contenedor.size()))
	cout << "El objeto no ha sido introducido." << endl;
    }
    if(suma_objetos != contenedor[i]) {
      cout << "Los objetos introducidos no concuerdan con el espacio ocupado del contenedor.";
      cout << endl;
      cout << "El contenedor " << i << " tiene ocupado " << contenedor[i] << endl;
      cout << "La suma de los objetos en " << i << " es " << suma_objetos << endl;
    }
  }*/
}
///////////////////////////////////////////////////////////////////////////////////////////////////
//                                                                                           LS  //
///////////////////////////////////////////////////////////////////////////////////////////////////
void INSTANCIA::LS(void)
{
  vector<int> auxiliar;
  for(int i = 0; i < n_objetos; i++) {
    
    mover_objeto_menos_espacio_deje(i);
    borrar_contenedores_vacios();
  }
  ordenar_objetos_segun_contenedor(auxiliar);
  objeto = auxiliar;
  auxiliar.clear();
}
///////////////////////////////////////////////////////////////////////////////////////////////////
//                                                                    introducir en contenedores //
///////////////////////////////////////////////////////////////////////////////////////////////////
int INSTANCIA::antes_que_quepa(void)
{
  unsigned pos_contenedor = 0;
  int num_instrucciones = 0;
  contenedor.clear();
  for(int i = 0; i < n_objetos; i++)
  {
    pos_contenedor = 0;
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
  int num_instrucciones = 0, min_espacio;
  contenedor.clear();
  for(int i = 0; i < n_objetos; i++)
  {
    min_espacio = INF;
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
///////////////////////////////////////////////////////////////////////////////////////////////////
//                                                                               ordenar objetos //
///////////////////////////////////////////////////////////////////////////////////////////////////
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
void INSTANCIA::ordenar_menor_mayor(int primero_desordenado/*= 0*/)
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
    ordenar_menor_mayor(primero_desordenado + 1);
  }
}
void INSTANCIA::swap(int i, int j)
{
  int aux = objeto[j];
  objeto[j] = objeto[i];
  objeto[i] = aux;
}
///////////////////////////////////////////////////////////////////////////////////////////////////
//                                                                                          get_ //
///////////////////////////////////////////////////////////////////////////////////////////////////
int INSTANCIA::get_espacio_ocupado_en_contenedor(int i)
{
  return contenedor[i];
}
int INSTANCIA::get_objeto_en_contenedor(int i)
{
  return objeto_en_contenedor[i];
}
int INSTANCIA::get_num_contenedores(void)
{
  return contenedor.size();
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
///////////////////////////////////////////////////////////////////////////////////////////////////
//                                                                                      imprimir //
///////////////////////////////////////////////////////////////////////////////////////////////////
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
///////////////////////////////////////////////////////////////////////////////////////////////////
//                                                                                 constructores //
///////////////////////////////////////////////////////////////////////////////////////////////////
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
    objeto_en_contenedor[i] = -1;
  }
}
void INSTANCIA::igualar(INSTANCIA *p)
{
  n_objetos = p->get_n_objetos();
  capacidad = p->get_capacidad();
  n_contenedores_optimo = p->get_n_contenedores_optimo();
  objeto_en_contenedor = new int[n_objetos];
  nombre_instancia = p->get_nombre_instancia();
  for(int i = 0; i < n_objetos; i++) {
    objeto.push_back(p->get_objeto(i));
    objeto_en_contenedor[i] = p->get_objeto_en_contenedor(i);
  }
  for(int i = 0; i < p->get_num_contenedores(); i++) 
    contenedor.push_back(p->get_espacio_ocupado_en_contenedor(i));
}
INSTANCIA::INSTANCIA(INSTANCIA* p)
{
  n_objetos = p->get_n_objetos();
  capacidad = p->get_capacidad();
  n_contenedores_optimo = p->get_n_contenedores_optimo();
  objeto_en_contenedor = new int[n_objetos];
  nombre_instancia = p->get_nombre_instancia();
  for(int i = 0; i < n_objetos; i++) {
    objeto.push_back(p->get_objeto(i));
    objeto_en_contenedor[i] = p->get_objeto_en_contenedor(i);
  }
  for(int i = 0; i < p->get_num_contenedores(); i++) 
    contenedor.push_back(p->get_espacio_ocupado_en_contenedor(i));
  //for(int i = 0; ;)
    
}
INSTANCIA::INSTANCIA(void)
{
  n_objetos = 0;
  nombre_instancia = '0';
  objeto_en_contenedor = NULL;
}
INSTANCIA::~INSTANCIA(void)
{
  objeto.clear();
  contenedor.clear();
  if(objeto_en_contenedor != NULL)
    delete objeto_en_contenedor;
}
///////////////////////////////////////////////////////////////////////////////////////////////////
//                                                                               GRUPO_INSTANCIA //
///////////////////////////////////////////////////////////////////////////////////////////////////
//                                                                                        public //
///////////////////////////////////////////////////////////////////////////////////////////////////
void GRUPO_INSTANCIAS::integridad_instancia(int i)
{
  instancia[i]->integridad_instancia();
}
///////////////////////////////////////////////////////////////////////////////////////////////////
//                                                                                            LS //
///////////////////////////////////////////////////////////////////////////////////////////////////
void GRUPO_INSTANCIAS::LS(int i)
{
  int max_vecinas = 0, espacio_libre_anterior = INF;
  INSTANCIA p(instancia[i]);
  bool cambiado = true;
  while((p.get_num_contenedores() >= instancia[i]->get_num_contenedores())
	 &&(max_vecinas < MAX_VECINAS_LS)
         &&(cambiado == true)) {
    
    espacio_libre_anterior = p.espacio_sobrante_total(); //comprobar si cambia la solución
    p.LS();
    max_vecinas++;
    if(p.distinta_solucion(instancia[i]) == false)
      cambiado = false;
  }
  if(cambiado == false)
    cout << "No cambió la solución." << endl;
  if((p.get_num_contenedores() < instancia[i]->get_num_contenedores())
     ||(p.espacio_sobrante_total() < instancia[i]->espacio_sobrante_total())) {
    cout << "Mejor vecina, de " << instancia[i]->get_num_contenedores()  << " a ";
    cout << p.get_num_contenedores() << endl;
    instancia[i]->igualar(&p);
  }
  else
    cout << "No hay vecinas mejores." << endl;
}
///////////////////////////////////////////////////////////////////////////////////////////////////
//                                                                                  Estadísticas //
///////////////////////////////////////////////////////////////////////////////////////////////////
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
void GRUPO_INSTANCIAS::estadistica_instrucciones(void)
{
  int num_instrucciones, tiempo;
  cout << "Nom." << "\t";
  for(int i = 0; i < n_casos; i++)
    cout << instancia[i]->get_nombre_instancia() << "\t";
  cout << endl;
  cout << "MmAq" << "\t";
  for(int i = 0; i < n_casos; i++)
  {
    ordenar_mayor_menor(i);
    estadistica_antes_que_quepa(i, num_instrucciones, tiempo);
    cout << num_instrucciones << "\t";
  }
  cout << endl;
  cout << "AlAq" << "\t";
  for(int i = 0; i < n_casos; i++)
  {
    ordenar_aleatoriamente(i);
    estadistica_antes_que_quepa(i, num_instrucciones, tiempo);
    cout << num_instrucciones << "\t";
  }
  cout << endl;
  cout << "MmMe" << "\t";
  for(int i = 0; i < n_casos; i++)
  {
    ordenar_mayor_menor(i);
    estadistica_menos_espacio_deje(i, num_instrucciones, tiempo);
    cout << num_instrucciones << "\t";
  }
  cout << endl;
  cout << "AlMe" << "\t";
  for(int i = 0; i < n_casos; i++)
  {
    ordenar_aleatoriamente(i);
    estadistica_menos_espacio_deje(i, num_instrucciones, tiempo);
    cout << num_instrucciones << "\t";
  }
  cout << endl;
}
void GRUPO_INSTANCIAS::estadistica_num_contenedores(void)
{
  cout << "Nom." << "\t";
  for(int i = 0; i < n_casos; i++)
    cout << instancia[i]->get_nombre_instancia() << "\t";
  cout << endl;
  cout << "AlAq" << "\t";
  for(int i = 0; i < n_casos; i++)
  {
    //ordenar_mayor_menor(i);
    meter_antes_que_quepa(i);
    cout << instancia[i]->get_num_contenedores() << "\t";
  }
  cout << endl;
  cout << "MmAq" << "\t";
  for(int i = 0; i < n_casos; i++)
  {
    ordenar_mayor_menor(i);
    meter_antes_que_quepa(i);
    cout << instancia[i]->get_num_contenedores() << "\t";
  }
  cout << endl;
  cout << "AlMe" << "\t";
  for(int i = 0; i < n_casos; i++)
  {
    //ordenar_mayor_menor(i);
    meter_menos_espacio_deje(i);
    cout << instancia[i]->get_num_contenedores() << "\t";
  }
  cout << endl;
  cout << "MmMe" << "\t";
  for(int i = 0; i < n_casos; i++)
  {
    ordenar_mayor_menor(i);
    meter_menos_espacio_deje(i);
    cout << instancia[i]->get_num_contenedores() << "\t";
  }
  cout << endl;
}
///////////////////////////////////////////////////////////////////////////////////////////////////
//                                                               meter objetos y ordenar objetos //
///////////////////////////////////////////////////////////////////////////////////////////////////
int GRUPO_INSTANCIAS::meter_antes_que_quepa(int i)
{
  return instancia[i]->antes_que_quepa();
}
int GRUPO_INSTANCIAS::meter_menos_espacio_deje(int i)
{
  return instancia[i]->menos_espacio_deje();
}
void GRUPO_INSTANCIAS::ordenar_aleatoriamente(int i)
{
  instancia[i]->ordenar_aleatoriamente();
}
void GRUPO_INSTANCIAS::ordenar_mayor_menor(int i)
{
  int izq = 0, der = instancia[i]->get_n_objetos() - 1;
  instancia[i]->ordenar_menor_mayor(); //se ordena de menor a mayor
  while(izq < der) { //se cambian las posiciones para que sea de mayor a menor
    instancia[i]->swap(izq, der);
    izq++;
    der--;
  }
}
///////////////////////////////////////////////////////////////////////////////////////////////////
//                                                                                      imprimir //
///////////////////////////////////////////////////////////////////////////////////////////////////
void GRUPO_INSTANCIAS::mostrar_contenedores_instancia(int i)
{
  instancia[i]->imprimir_contenedores();
}
void GRUPO_INSTANCIAS::mostrar_contenido_instancia(int i)
{
  instancia[i]->imprimir_objetos();
}
void GRUPO_INSTANCIAS::mostrar_contenido_ficheros(void)
{
  INSTANCIA* p;
  cout << "Número de casos = " << n_casos << endl;
  for(int i = 0; i < n_casos; i++)
  {
    cout << "----------------------------------------------------------------------------" << endl;
    cout << endl;
    p = instancia[i];
    cout << p->get_nombre_instancia() << endl;
    cout << "c = " << p->get_capacidad() << " i = " << p->get_n_objetos() << endl;
    cout << "Contenedores óptimos = " << p->get_n_contenedores_optimo() << endl;
    cout << endl;
    p->imprimir_objetos();
  }
  cout << "----------------------------------------------------------------------------" << endl;
}
///////////////////////////////////////////////////////////////////////////////////////////////////
//                                                                                 constructores //
///////////////////////////////////////////////////////////////////////////////////////////////////
GRUPO_INSTANCIAS::GRUPO_INSTANCIAS(char *nombre_fichero)
{
  cout << "nombre_fichero = " << nombre_fichero << endl;
  ifstream flujo;
  flujo.open(nombre_fichero);
  if(flujo.fail())
    cout << "Error al abrir el fichero." << endl;
  else {
    flujo >> n_casos;
    instancia = new INSTANCIA*[n_casos];
    cout << "n_casos = " << n_casos << endl << endl;
    for(int i = 0; i < n_casos; i++) { //pasar el flujo a cada constructor de instancia
      instancia[i] = new INSTANCIA/*[n_casos]*/;
      instancia[i]->leer_fichero(flujo);
    }
  }
  flujo.close();
}
GRUPO_INSTANCIAS::~GRUPO_INSTANCIAS(void)
{
  for(int i = 0; i < n_casos; i++)
    delete instancia[i];
  delete instancia;
}