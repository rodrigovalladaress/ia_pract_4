#include "pract_4.h"
///////////////////////////////////////////////////////////////////////////////////////////////////
//                                                                                     INSTANCIA //
///////////////////////////////////////////////////////////////////////////////////////////////////
//                                                                                       private //
///////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////
//                                                                                 mover objetos //
///////////////////////////////////////////////////////////////////////////////////////////////////
int INSTANCIA::elegir_objeto_al_azar(void)
{
  return rand() % objeto.size();
}
void INSTANCIA::quitar_objeto_de_contenedor(int i)
{
  if(objeto_en_contenedor[i] != -1) {
    contenedor[objeto_en_contenedor[i]] -= objeto[i];
    objeto_en_contenedor[i] = -1;
  }
}
int INSTANCIA::buscar_objeto_que_encaje_en(int hueco, int a_partir_de/*= 0*/)
{
  int encaja = -1, mayor_objeto_que_encaja = 0;
  for(int i = a_partir_de; i < n_objetos; i++)//buscar objeto que quepa o sea menor que el hueco
  {
    if((objeto[i] <= hueco)&&(objeto[i] > mayor_objeto_que_encaja)) {
      encaja = i;
      mayor_objeto_que_encaja = objeto[i];
    }
  }
  return encaja;
}
void INSTANCIA::mover_objeto_antes_que_quepa(int i)
{
  unsigned pos_contenedor = 0;
  quitar_objeto_de_contenedor(i);
  while((pos_contenedor < contenedor.size())&&
        (cabe_en_contenedor(i, pos_contenedor) == false)) {
    pos_contenedor++;
  }
  if(pos_contenedor == contenedor.size())
    nuevo_contenedor(i);
  else
    meter_en_contenedor(i, pos_contenedor);
  borrar_contenedores_vacios();
}
void INSTANCIA::mover_objeto_menos_espacio_deje(int i)
{
  int min_espacio = INF;
  int pos_contenedor = objeto_en_contenedor[i]; //Si no se pone así da error
  quitar_objeto_de_contenedor(i);
  for(unsigned j = 0; j < contenedor.size(); j++)
  {
    if((cabe_en_contenedor(i, j) == true)&&(min_espacio > espacio_sobrante_contenedor(j))) {
      min_espacio = espacio_sobrante_contenedor(j);
      pos_contenedor = j;
    }
  }
  meter_en_contenedor(i, pos_contenedor);
  borrar_contenedores_vacios();
}
void INSTANCIA::meter_objeto_menos_espacio_deje(int i)
{
  int min_espacio = INF;
  int pos_contenedor = -1;
  quitar_objeto_de_contenedor(i);
  for(unsigned j = 0; j < contenedor.size(); j++)
  {
    if((cabe_en_contenedor(i, j) == true)&&(min_espacio > espacio_sobrante_contenedor(j))) {
      min_espacio = espacio_sobrante_contenedor(j);
      pos_contenedor = j;
    }
  }
  if(pos_contenedor != -1) //si no se encuentra contenedor donde quepa
    meter_en_contenedor(i, pos_contenedor);
  else 
    nuevo_contenedor(i);
}
///////////////////////////////////////////////////////////////////////////////////////////////////
//                                                                                  contenedores //
///////////////////////////////////////////////////////////////////////////////////////////////////
void INSTANCIA::borrar_contenedores_vacios(void)
{
  for(unsigned i = 0; i < contenedor.size(); i++)
  {
    if(contenedor[i] == 0) {
      contenedor.erase(contenedor.begin() + i);
      i--;
    }
  }
}
bool INSTANCIA::cabe_en_contenedor(int i, int cont)
{
  return espacio_sobrante_contenedor(cont) >= objeto[i] ? true : false;
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
//                                                      Métodos privados del Algoritmo Genético  //
///////////////////////////////////////////////////////////////////////////////////////////////////
void INSTANCIA::mutacion(void)
{
  int pos = ((int)poblacion.size() / 2) + (rand() % (int)poblacion.size() / 2);
  poblacion[pos]->LS_azar();
}
void INSTANCIA::integridad_genetica(void)
{
  vector<int> posiciones_marcadas; //se marcan los objetos que no caben en los contenedores
  for(int i = 0; i < n_objetos; i++)
  {
    if(cabe_en_contenedor(i, objeto_en_contenedor[i]) == true)
      meter_en_contenedor(i, objeto_en_contenedor[i]);
    else
      posiciones_marcadas.push_back(i);//se marcan los objetos
  }
  for(unsigned i = 0; i < posiciones_marcadas.size(); i++)
  { //se intenta meter los objetos que no cabían en los contenedores o se crea uno nuevo
    meter_objeto_menos_espacio_deje(posiciones_marcadas.back());
    posiciones_marcadas.pop_back();
  }
}
void INSTANCIA::cruzar(int padre, int madre)
{
  int corte = rand() % n_objetos;
  INSTANCIA* hijo1 = new INSTANCIA(poblacion[padre]);
  INSTANCIA* hijo2 = new INSTANCIA(poblacion[madre]);
  for(int i = 0; i < corte; i++)
  {
    hijo1->set_objeto_en_contenedor(i, poblacion[padre]->get_objeto_en_contenedor(i));
    hijo2->set_objeto_en_contenedor(i, poblacion[madre]->get_objeto_en_contenedor(i));
  }
  for(int i = corte; i < n_objetos; i++)
  {
    hijo1->set_objeto_en_contenedor(i, poblacion[padre]->get_objeto_en_contenedor(i));
    hijo2->set_objeto_en_contenedor(i, poblacion[madre]->get_objeto_en_contenedor(i));
  }
  hijo1->integridad_genetica();
  hijo2->integridad_genetica();
  //Si un hijo es mejor que algún padre, entra en la población
  if((hijo1->espacio_sobrante_total() < poblacion[padre]->espacio_sobrante_total())||
     (hijo1->espacio_sobrante_total() < poblacion[madre]->espacio_sobrante_total()))
    poblacion.push_back(hijo1);
  if((hijo2->espacio_sobrante_total() < poblacion[padre]->espacio_sobrante_total())||
     (hijo2->espacio_sobrante_total() < poblacion[madre]->espacio_sobrante_total()))
    poblacion.push_back(hijo2);
}
///////////////////////////////////////////////////////////////////////////////////////////////////
//                                                Cola para la población del Algoritmo Genético  //
///////////////////////////////////////////////////////////////////////////////////////////////////
void INSTANCIA::reproduccion(void)
{
  unsigned i = 0, j = 1;
  while(j < poblacion.size()) {
    cruzar(i, j);
    i++;
    j++;
  }
}
void INSTANCIA::ordenar_poblacion(unsigned primero_desordenado)
{
  unsigned pos;
  INSTANCIA* aux;  
  if(primero_desordenado < poblacion.size()) {
    pos = 0;
    while(poblacion[primero_desordenado]->espacio_sobrante_total() > 
          poblacion[pos]->espacio_sobrante_total())
    //while(objeto[pila_sacar_objetos[primero_desordenado]] > objeto[pila_sacar_objetos[pos]])
      pos++;
    for(unsigned i = pos; i < primero_desordenado; i++)
    {
      aux = poblacion[i];
      poblacion[i] = poblacion[primero_desordenado];
      poblacion[primero_desordenado] = aux;
    }
    ordenar_poblacion(primero_desordenado + 1);
  }
}
///////////////////////////////////////////////////////////////////////////////////////////////////
//                                                                   Cola para la búsqueda tabú  //
///////////////////////////////////////////////////////////////////////////////////////////////////
void INSTANCIA::push_cola_tabu(int obj)
{
  cola_tabu.push_back(obj);
  if(cola_tabu.size() > tam_cola_tabu)
    cola_tabu.erase(cola_tabu.begin());
}
bool INSTANCIA::comp_no_esta_en_cola(int obj)
{
  unsigned i = 0;
  bool r = false;
  while((i < cola_tabu.size())&&(obj != cola_tabu[i]))
    i++;
  if(i == cola_tabu.size())
    r = true;
  else
    r = false;
  return r;
}
int INSTANCIA::TS_obj_azar(void)
{
  int obj, i = 0;
  bool no_esta_en_cola = false;
  while((no_esta_en_cola == false)&&(i < 100)) {
    obj = rand() % n_objetos;
    no_esta_en_cola = comp_no_esta_en_cola(obj);
    i++;
  }
  if(no_esta_en_cola == true)
    push_cola_tabu(obj);
  return no_esta_en_cola == true ? obj : -1;
}
///////////////////////////////////////////////////////////////////////////////////////////////////
//                                                                Pila de posiciones de objetos  //
///////////////////////////////////////////////////////////////////////////////////////////////////
void INSTANCIA::ordenar_pila_mayor_menor(int primero_desordenado)
{
  int pos, aux;  
  if(primero_desordenado < n_objetos) {
    pos = 0;
    while(objeto[pila_sacar_objetos[primero_desordenado]] > objeto[pila_sacar_objetos[pos]])
      pos++;
    for(int i = pos; i < primero_desordenado; i++)
    {
      aux = pila_sacar_objetos[i];
      pila_sacar_objetos[i] = pila_sacar_objetos[primero_desordenado];
      pila_sacar_objetos[primero_desordenado] = aux;
    }
    ordenar_pila_mayor_menor(primero_desordenado + 1);
  }
}
void INSTANCIA::iniciar_pila_aleatoriamente(void)
{
  int pos_swap = 0, aux, i = 0, j = n_objetos - 1;
  iniciar_pila_sin_orden();
  while((i < n_objetos)&&(j > 0)) {
    //Se ordena aleatoriamente el vector de abajo a arriba
    pos_swap = (i + 1) + rand() % (n_objetos - (i + 1));
    aux = pila_sacar_objetos[i];
    pila_sacar_objetos[i] = pila_sacar_objetos[pos_swap];
    pila_sacar_objetos[pos_swap] = aux;
    //Se ordena aleatoriamente el vector de arriba a abajo
    pos_swap = rand() % j;
    aux = pila_sacar_objetos[j];
    pila_sacar_objetos[j] = pila_sacar_objetos[pos_swap];
    pila_sacar_objetos[pos_swap] = aux;
    i++;
    j--;
  }
}
void INSTANCIA::iniciar_pila_mayor_menor(void)
{
  iniciar_pila_sin_orden();
  ordenar_pila_mayor_menor();
}
void INSTANCIA::iniciar_pila_sin_orden(void)
{
  if(pila_sacar_objetos.size() != 0)
    cout << "La pila anterior no estaba vacía. Error en los métodos de sacar de la pila." << endl;
  pila_sacar_objetos.clear();
  for(int i = 0; i < n_objetos; i++)
    pila_sacar_objetos.push_back(i); //inicializar pila
}
int INSTANCIA::pop_pos(void)
{
  int pop = pila_sacar_objetos.back();
  pila_sacar_objetos.pop_back();
  return pop;
}
int INSTANCIA::pop_pos_grasp(int t)
{
  int pop, pos;
  if(pila_sacar_objetos.size() >= (unsigned)t)
    pos = pila_sacar_objetos.size() - (rand() % t) - 1;
  else
    pos = rand() % pila_sacar_objetos.size();
  pop = pila_sacar_objetos[pos];
  pila_sacar_objetos.erase(pila_sacar_objetos.begin() + pos);
  return pop;
}
///////////////////////////////////////////////////////////////////////////////////////////////////
//                                                                                        public //
///////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////
//                                                                            Algoritmo genético //
///////////////////////////////////////////////////////////////////////////////////////////////////
INSTANCIA* INSTANCIA::mejor_individuo(void)
{
  return poblacion[0];
}
void INSTANCIA::destruir_poblacion(void)
{
  poblacion.clear();
}
unsigned INSTANCIA::media_poblacion(void)
{
  int suma = 0;
  for(unsigned i = 0; i < poblacion.size(); i++)
    suma += poblacion[i]->espacio_sobrante_total();
  return suma / poblacion.size();
}
void INSTANCIA::inicializar_poblacion(int pob_inicial)
{
  for(int i = 0; i < pob_inicial; i++)
  {
    INSTANCIA *p = new INSTANCIA(this);
    p->antes_que_quepa(ORDEN_ALEATORIO);
    poblacion.push_back(p);
  }
  ordenar_poblacion();
}
void INSTANCIA::GA(int lim_pob)
{
  reproduccion();
  ordenar_poblacion();
  for(int aux = 0; aux < rand() % MAX_NUM_MUTACIONES; aux++)
  {
    mutacion();
    ordenar_poblacion();
  }
  while(poblacion.size() > (unsigned)lim_pob)//se eliminan las peores soluciones
    poblacion.pop_back();  
}
///////////////////////////////////////////////////////////////////////////////////////////////////
//                                                                                          VNS  //
///////////////////////////////////////////////////////////////////////////////////////////////////
void INSTANCIA::agitar(int k)
{
  int obj, cont;
  unsigned contador;
  bool movido_objeto = false;
  for(int i = 0; i < k; i++)
  {
    contador = 0; //evita que se vuelvan a comparar los contenedores del principio
    obj = rand() % n_objetos;
    cont = rand() % contenedor.size();
    do {
      if(cabe_en_contenedor(obj, cont)) {
	quitar_objeto_de_contenedor(obj);
	meter_en_contenedor(obj, cont);
	movido_objeto = true;
      }
      else {//comprobar uno a uno si cabe en un contenedor desde el cont al azar del principio
	cont++;
	cont = cont % contenedor.size();
	contador++;
      }
    }while((movido_objeto == false)&&(contador < contenedor.size()));
  }
}
void INSTANCIA::VNS(void)
{
  
}
///////////////////////////////////////////////////////////////////////////////////////////////////
//                                                                                           TS  //
///////////////////////////////////////////////////////////////////////////////////////////////////
void INSTANCIA::inicializar_cola_tabu(int t)
{
  cola_tabu.clear();
  tam_cola_tabu = t;
}
void INSTANCIA::TS(void)
{
  int obj;
  obj = TS_obj_azar();
  if(obj != -1)
    mover_objeto_menos_espacio_deje(obj);
  else
    cout << "TS Error: no se encontró objeto que no esté en la cola tabú." << endl;
}
///////////////////////////////////////////////////////////////////////////////////////////////////
//                                                                                        GRASP  //
///////////////////////////////////////////////////////////////////////////////////////////////////
void INSTANCIA::GRASP(int t)
{
  reiniciar_contenedores();
  iniciar_pila_mayor_menor();
  for(int i = 0; i < n_objetos; i++)
    mover_objeto_antes_que_quepa(pop_pos_grasp(t));
}
///////////////////////////////////////////////////////////////////////////////////////////////////
//                                                                                           LS  //
///////////////////////////////////////////////////////////////////////////////////////////////////
void INSTANCIA::LS_azar(void)
{
  int obj, cont, j = 0;
  for(int i = 0; i < MAX_LS_AZAR; i++)
  {
    j = 0;
    do {
      j++;
      obj = rand() % n_objetos;
      cont = rand() % (int)contenedor.size();
    }while((cabe_en_contenedor(obj, cont) == false)&&(j < 10));
    if(cabe_en_contenedor(obj, cont) == true) {
      quitar_objeto_de_contenedor(obj);
      meter_en_contenedor(obj, cont);
    }
  }
}
void INSTANCIA::LS(void)
{
  int obj = rand() % n_objetos;
  mover_objeto_menos_espacio_deje(obj);
}
///////////////////////////////////////////////////////////////////////////////////////////////////
//                                                                    Comparación de instancias  //
///////////////////////////////////////////////////////////////////////////////////////////////////
int INSTANCIA::espacio_sobrante_total(void)
{
  int espacio_sobrante = 0;
  for(unsigned i = 0; i < contenedor.size(); i++)
    espacio_sobrante += espacio_sobrante_contenedor(i) * espacio_sobrante_contenedor(i);
  return espacio_sobrante;
}
bool INSTANCIA::distinta_solucion(INSTANCIA* p)
{
  int i = 0;
  while((i < n_objetos)&&(objeto_en_contenedor[i] == p->get_objeto_en_contenedor(i)))
    i++;
  return i == n_objetos ? false : true;
}
///////////////////////////////////////////////////////////////////////////////////////////////////
//                                                                    introducir en contenedores //
///////////////////////////////////////////////////////////////////////////////////////////////////
void INSTANCIA::antes_que_quepa(int op)
{
  unsigned pos_contenedor = 0;
  int pos_objeto;
  reiniciar_contenedores();
  if(op == ORDEN_ALEATORIO) {
    iniciar_pila_aleatoriamente();
  }
  else if(op == ORDEN_MAYOR_MENOR)
    iniciar_pila_mayor_menor();
  else if(op == NO_ORDENAR)
    iniciar_pila_sin_orden();
  else
    cout << "Solución no válida, no se ordenarán los objetos." << endl;
  for(int i = 0; i < n_objetos; i++)
  {
    pos_contenedor = 0;
    pos_objeto = pop_pos();//se saca un objeto de la pila
    while((pos_contenedor < contenedor.size())&&
          (cabe_en_contenedor(pos_objeto, pos_contenedor) == false)) {
      pos_contenedor++;
    }
    if(pos_contenedor == contenedor.size())
      nuevo_contenedor(pos_objeto);
    else
      meter_en_contenedor(pos_objeto, pos_contenedor);
  }
}
void INSTANCIA::menos_espacio_deje(int op)
{
  unsigned pos_contenedor;
  int min_espacio, pos_objeto;
  reiniciar_contenedores();
  if(op == ORDEN_ALEATORIO)
    iniciar_pila_aleatoriamente();
  else if(op == ORDEN_MAYOR_MENOR)
    iniciar_pila_mayor_menor();
  else if(op == NO_ORDENAR)
    iniciar_pila_sin_orden();
  else
    cout << "Solución no válida, no se ordenarán los objetos." << endl;
  for(int i = 0; i < n_objetos; i++)
  {
    pos_objeto = pop_pos();
    min_espacio = INF;
    pos_contenedor = INF; //Si no cambia no se ha encontrado contenedor en el que quepa
    for(unsigned j = 0; j < contenedor.size(); j++)
    {
      if((cabe_en_contenedor(pos_objeto, j) == true)
	  &&(min_espacio > espacio_sobrante_contenedor(j))) {
	min_espacio = espacio_sobrante_contenedor(j);
	pos_contenedor = j;
      }
    }
    if(pos_contenedor == INF)
      nuevo_contenedor(pos_objeto);
    else
      meter_en_contenedor(pos_objeto, pos_contenedor);
  }
}
///////////////////////////////////////////////////////////////////////////////////////////////////
//                                                                                   get_ y set_ //
///////////////////////////////////////////////////////////////////////////////////////////////////
int INSTANCIA::get_espacio_ocupado_en_contenedor(int i)
{
  return contenedor[i];
}
void INSTANCIA::set_objeto_en_contenedor(int i, int c)
{
  objeto_en_contenedor[i] = c;
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
      if(objeto_en_contenedor[j] == (int)i)
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
  reiniciar_contenedores();
  objeto.clear();
  if(objeto_en_contenedor != NULL)
    delete objeto_en_contenedor;
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
//                                                                              GRUPO_INSTANCIAS //
///////////////////////////////////////////////////////////////////////////////////////////////////
//                                                                                        public //
///////////////////////////////////////////////////////////////////////////////////////////////////
void GRUPO_INSTANCIAS::llamar_heuristicas(int heuristica)
{
  long long tiempo;
  float media_tiempo = 0, diferencia_optima = 0;
  int veces_optima = 0;
  switch(heuristica)
  {
    case 0: 
      cout << "ILS\t";
      break;
    case 1:
      cout << "ILS2\t";
      break;
    case 2:
      cout << "SA\t";
      break;
    case 3:
      cout << "SA2\t";
      break;
    case 4:
      cout << "GA\t";
      break;
    case 5: 
      cout << "GA2\t";
      break;
    case 6:
      cout << "GRASP\t";
      break;
    case 7:
      cout << "GRASP2\t";
      break;
    case 8:
      cout << "TS\t";
      break;
    case 9:
      cout << "TS2\t";
      break;
    case 10:
      cout << "VNS\t";
      break;
    case 11:
      cout << "VNS2\t";
      break;
  }
  for(int i = 0; i < n_casos; i++)
  {
    meter_antes_que_quepa(i, ORDEN_MAYOR_MENOR);
    cronousec(1);
    switch(heuristica)
    {
      case 0: 
        ILS(i, ORDEN_ALEATORIO);
        break;
      case 1:
        ILS(i, ORDEN_MAYOR_MENOR);
        break;
      case 2:
        SA(i);
        break;
      case 3:
        SA(i, MENOS_ESPACIO_DEJE, 1, 0.9, 10);
        break;
      case 4:
        GA(i);
        break;
      case 5: 
        GA(i, 20, 20);
        break;
      case 6:
        GRASP(i);
        break;
      case 7:
        GRASP(i, 10);
        break;
      case 8:
        TS(i);
        break;
      case 9:
        TS(i, 10);
        break;
      case 10:
        VNS(i);
        break;
      case 11:
        VNS(i, 10);
        break;
    }
    tiempo = cronousec(0);
    media_tiempo += tiempo;
    if(instancia[i]->get_num_contenedores() == instancia[i]->get_n_contenedores_optimo())
      veces_optima++;
    else
      diferencia_optima += instancia[i]->get_num_contenedores() - 
                           instancia[i]->get_n_contenedores_optimo();
    cout << tiempo << "\t";
  }
  cout << media_tiempo / n_casos << "   \t" << veces_optima << "\t\t";
  cout << diferencia_optima / (float)n_casos << endl;
}
void GRUPO_INSTANCIAS::estadistica(void)
{
  cout << "   \t"; 
  for(int i = 0; i < n_casos; i++)
    cout << instancia[i]->get_nombre_instancia() << "\t";
  // Media de los tiempos, número de veces que alcanza la solución óptima y la diferencia de 
  // contenedores media  de las soluciones con el número de contenedores óptimo
  cout << "Media   \tV.óptima\tDiferencia con óptima" << endl;
  for(int heuristica = 0; heuristica < NUM_HEURISTICAS; heuristica++)
    llamar_heuristicas(heuristica);
  cout << endl;
  cout << "(Tiempo en µs)" << endl;
}
///////////////////////////////////////////////////////////////////////////////////////////////////
//                                                                            Algoritmo genético //
///////////////////////////////////////////////////////////////////////////////////////////////////
bool GRUPO_INSTANCIAS::poblacion_estancada(unsigned& a, unsigned& b)
{
  bool r = true;
  if(a != b)
    r = false;
  return r;
}
void GRUPO_INSTANCIAS::GA(int i, int pob_inicial, int lim_pob)
{
  int j = 0, medias_repetidas = 0;
  unsigned media_poblacion_anterior, media_poblacion_actual = INF;
  instancia[i]->inicializar_poblacion(pob_inicial);
  while((j < NUM_SOLUCIONES / pob_inicial)&&(medias_repetidas < UMBRAL_MEDIAS_REPETIDAS))
  {
    media_poblacion_anterior = media_poblacion_actual;
    instancia[i]->GA(lim_pob);
    media_poblacion_actual = instancia[i]->media_poblacion();
    if(poblacion_estancada(media_poblacion_anterior, media_poblacion_actual) == true)
      medias_repetidas++;
    else
      medias_repetidas = 0;
    j++;
  }
  if(instancia[i]->mejor_individuo()->espacio_sobrante_total() < 
     instancia[i]->espacio_sobrante_total())
    instancia[i]->igualar(instancia[i]->mejor_individuo());
  instancia[i]->destruir_poblacion();
}
void GRUPO_INSTANCIAS::VNS(int i, int k_max)
{
  int k = 1, j = 0;
  INSTANCIA* sol_vecina;
  sol_vecina = new INSTANCIA(instancia[i]);
  while((k < k_max)&&(j < NUM_SOLUCIONES)) {
    sol_vecina->agitar(k);
    sol_vecina->LS();
    if(sol_vecina->espacio_sobrante_total() < instancia[i]->espacio_sobrante_total()) {
      instancia[i]->igualar(sol_vecina);
      k++;
    }
    else
      k = 1;
    j++;
  }
}
///////////////////////////////////////////////////////////////////////////////////////////////////
//                                                                                 Búsqueda Tabú //
///////////////////////////////////////////////////////////////////////////////////////////////////
void GRUPO_INSTANCIAS::TS(int i, int t/*= 7*/)
{
  INSTANCIA auxiliar(instancia[i]);
  auxiliar.inicializar_cola_tabu(t);
  for(int j = 0; j < NUM_SOLUCIONES; j++)
  {
    auxiliar.TS();
    if(auxiliar.espacio_sobrante_total() < instancia[i]->espacio_sobrante_total())
      instancia[i]->igualar(&auxiliar); 
  }
}
///////////////////////////////////////////////////////////////////////////////////////////////////
//                                                                                         GRASP //
///////////////////////////////////////////////////////////////////////////////////////////////////
void GRUPO_INSTANCIAS::GRASP(int i, int t/*= 7*/)
{
  INSTANCIA auxiliar(instancia[i]);
  for(int j = 0; j < NUM_SOLUCIONES; j++)
  {
    auxiliar.GRASP(t);
    if(auxiliar.espacio_sobrante_total() < instancia[i]->espacio_sobrante_total())
      instancia[i]->igualar(&auxiliar); 
  }
}
///////////////////////////////////////////////////////////////////////////////////////////////////
//                                                                           Simulated Annealing //
///////////////////////////////////////////////////////////////////////////////////////////////////
float GRUPO_INSTANCIAS::Pr(float c, int delta)
{
  if(delta > 0)
    return 1;
  else
    return exp(((float)delta) / c);
}
void GRUPO_INSTANCIAS::SA(int i, int op, float c, float alfa, int reducir_c/*= 7*/)
{
  INSTANCIA sol_actual(instancia[i]), mejor_sol(instancia[i]), sol_vecina(instancia[i]);
  int max_vecinas = 0, contador = 0;
  float rand_f;
  while(max_vecinas < NUM_SOLUCIONES) {
    //sol_vecina.antes_que_quepa(op);
    sol_vecina.LS(); // da error
    rand_f = fmod((float)rand(), (float)1.0);
    if(Pr(c, sol_actual.espacio_sobrante_total() - sol_vecina.espacio_sobrante_total()) > rand_f)
      sol_actual.igualar(&sol_vecina);
    if(sol_actual.espacio_sobrante_total() < mejor_sol.espacio_sobrante_total())
      mejor_sol.igualar(&sol_actual);
    if(contador == reducir_c) {
      contador = -1;
      c *= alfa;
    }
    max_vecinas++;
    contador++;
  }
  if(mejor_sol.espacio_sobrante_total() < instancia[i]->espacio_sobrante_total())
    instancia[i]->igualar(&mejor_sol);
}
///////////////////////////////////////////////////////////////////////////////////////////////////
//                                                                                  Local Search //
///////////////////////////////////////////////////////////////////////////////////////////////////
void GRUPO_INSTANCIAS::ILS(int i, int op)
{
  int max_vecinas;
  INSTANCIA p(instancia[i]);
  for(int j = 0; j < NUM_SOLUCIONES; j++) {
    max_vecinas = 0;
    p.antes_que_quepa(op);//se ordena la instancia de prueba aleatoriamente o mayor menor
    do {
      p.LS();
      max_vecinas++;
    } while(p.espacio_sobrante_total() > instancia[i]->espacio_sobrante_total()
           &&(max_vecinas < MAX_VECINAS_LS));
    if((p.get_num_contenedores() < instancia[i]->get_num_contenedores())
      ||(p.espacio_sobrante_total() < instancia[i]->espacio_sobrante_total()))
      instancia[i]->igualar(&p);
  }
}
void GRUPO_INSTANCIAS::LS(int i, int op/*= false*/)
{
    instancia[i]->LS();
}
///////////////////////////////////////////////////////////////////////////////////////////////////
//                                                                                  Estadísticas //
///////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////
//                                                               meter objetos y ordenar objetos //
///////////////////////////////////////////////////////////////////////////////////////////////////
void GRUPO_INSTANCIAS::meter_antes_que_quepa(int i, int op)
{
  instancia[i]->antes_que_quepa(op);
}
void GRUPO_INSTANCIAS::meter_menos_espacio_deje(int i, int op)
{
  instancia[i]->menos_espacio_deje(op);
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
void GRUPO_INSTANCIAS::mostrar_objetos(int i)
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
  srand(time(NULL));
  cout << "nombre_fichero = " << nombre_fichero << endl;
  ifstream flujo;
  flujo.open(nombre_fichero);
  if(flujo.fail())
    cout << "Error al abrir el fichero." << endl;
  else {
    flujo >> n_casos;
    instancia = new INSTANCIA*[n_casos];
    cout << "n_casos = " << n_casos << endl;
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