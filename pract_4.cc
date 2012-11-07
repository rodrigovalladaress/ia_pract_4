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
  contenedor[objeto_en_contenedor[i]] -= objeto[i];
  objeto_en_contenedor[i] = -1;
}
void INSTANCIA::ordenar_objetos_segun_contenedor(vector<int>& auxiliar)
{
  
  cout << "No se usa ordenar objetos segun contenedor" << endl;
  
  /*
  //vector<int> auxiliar; //nuevo array de objetos
  for(int id_contenedor = 0; id_contenedor < contenedor.size(); id_contenedor++)
  {
    for(int i = 0; i < n_objetos; i++)
    {
      if(objeto_en_contenedor[i] == id_contenedor) //el objeto se encuentra en el contenedor
	auxiliar.push_back(objeto[i]); // se van introduciendo por orden en el nuevo array
    }
  }*/
}
int INSTANCIA::buscar_objeto_que_encaje_en(int hueco, int a_partir_de/*= 0*/)
{
  int encaja = -1, mayor_objeto_que_encaja = 0;
  for(int i = a_partir_de; i < n_objetos; i++)//buscar objeto que quepa o que sea menor que el hueco
  {
    if((objeto[i] <= hueco)&&(objeto[i] > mayor_objeto_que_encaja)) {
      encaja = i;
      mayor_objeto_que_encaja = objeto[i];
    }
  }
  return encaja;
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
///////////////////////////////////////////////////////////////////////////////////////////////////
//                                                                                  contenedores //
///////////////////////////////////////////////////////////////////////////////////////////////////
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
///////////////////////////////////////////////////////////////////////////////////////////////////
//                                                                                        GRASP  //
///////////////////////////////////////////////////////////////////////////////////////////////////
void INSTANCIA::GRASP(int i)
{
  int pos_contenedor = objeto_en_contenedor[i]; //Si no se pone así da error
  vector<int> contendedor_candidato;
  vector<int> espacio_sobrante;
  quitar_objeto_de_contenedor(i);
  for(int j = 0; j < contenedor.size(); j++)
  {
    if(cabe_en_contenedor(i, j) == true) {
      if(contendedor_candidato.size() < LCR_SIZE) { //si no se ha sobrepasado LCR_size se mete
	contendedor_candidato.push_back(j);
	espacio_sobrante.push_back(espacio_sobrante_contenedor(j));
      }
      else { //comprobamos si el menor espacio en los candidatos es mayor que colocar el objeto
	     //en el contenedor j
	int min_espacio = INF, pos;
	for(int k = 0; k < espacio_sobrante.size(); k++)
	{
	  if(espacio_sobrante[k] < min_espacio) {
	    pos = k;
	    min_espacio = espacio_sobrante[k];
	  }
	}
	if(min_espacio > espacio_sobrante_contenedor(j)) {
	  contendedor_candidato[pos] = j;
	  espacio_sobrante[pos] = espacio_sobrante_contenedor(j);
	}
      }
    }
  }
  meter_en_contenedor(i, contendedor_candidato[rand() % contendedor_candidato.size()]);
  /*
  int pos, aux;
  vector<int> candidatos;
  if(primero_desordenado < n_objetos) {
    pos = 0;
    while(objeto[primero_desordenado] > objeto[pos]) {
      candidatos.push_back(pos);
      pos++;
    }
    if(candidatos.size() > 0)
      pos = candidatos[rand() % candidatos.size()];
    for(int i = pos; i < primero_desordenado; i++)
    {
      aux = objeto[i];
      objeto[i] = objeto[primero_desordenado];
      objeto[primero_desordenado] = aux;
    }
    ordenar_GRASP(primero_desordenado + 1);
  }*/
}
///////////////////////////////////////////////////////////////////////////////////////////////////
//                                                                                           LS  //
///////////////////////////////////////////////////////////////////////////////////////////////////
void INSTANCIA::LS_azar(void)
{
  int mitad = objeto.size() / 2;
  int izq, der;
  int max = rand() % (mitad / 3);
  for(int i = 0; i < max; i++) //intercambiar x objetos al azar
  {
    izq = rand() % mitad;
    der = mitad + (rand() % (objeto.size() - mitad));
    swap(izq, der);
  }
  reiniciar_contenedores();
  antes_que_quepa();  
}
void INSTANCIA::LS_proximo_10(void)
{
  int suma, i, obj_para_swap = INF/*objeto para intercambiar por otro*/;
  int hueco;
  vector<int> auxiliar;
  bool cambiado_un_objeto = false; //cambiar un solo objeto
  for(i = 0; i < n_objetos; i++)
  {
    suma = 0;
    while((i < n_objetos)&&(suma < capacidad)) { //va sumando los objetos por orden
      suma += objeto[i];
      i++;
    }
    if((i < n_objetos)&&(suma > capacidad)){ //si se sobrepasa de la capacidad
      hueco = capacidad - (suma - objeto[i - 1]);
      while((hueco > 0)&&(obj_para_swap != -1)) {
	obj_para_swap = buscar_objeto_que_encaje_en(hueco, i);//si es -1 no ha encontrado objeto
	if(obj_para_swap != -1) {
	  swap(obj_para_swap, i - 1);
	  hueco -= objeto[obj_para_swap];//intenta llenar el hueco con varios objetos
	}
	//else
	  //cout << "No se encontró objeto para llenar el hueco" << endl;
	i++;
      }
      //i--;
    }
    i--;
  }
  reiniciar_contenedores();
  antes_que_quepa();
}
void INSTANCIA::LS(void)
{
  vector<int> auxiliar;
  int pos = elegir_objeto_al_azar();
  //Cambiar solo un objeto
  //for(int i = 0; i < n_objetos; i++) {
    mover_objeto_menos_espacio_deje(pos);
    borrar_contenedores_vacios();
  //}
  ordenar_objetos_segun_contenedor(auxiliar);
  objeto = auxiliar;
  auxiliar.clear();
}
///////////////////////////////////////////////////////////////////////////////////////////////////
//                                                                    introducir en contenedores //
///////////////////////////////////////////////////////////////////////////////////////////////////
int INSTANCIA::antes_que_quepa(int op)
{
  unsigned pos_contenedor = 0;
  int num_instrucciones = 0;
  int pos_objeto;
  contenedor.clear();
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
    pos_contenedor = 0;
    pos_objeto = pop_pos();//se saca un objeto de la pila
    while((pos_contenedor < contenedor.size())&&
          (cabe_en_contenedor(pos_objeto, pos_contenedor) == false)) {
      pos_contenedor++;
      num_instrucciones++;
    }
    if(pos_contenedor == contenedor.size())
      nuevo_contenedor(pos_objeto);
    else
      meter_en_contenedor(pos_objeto, pos_contenedor);
    num_instrucciones++;
  }
  return num_instrucciones;
}
int INSTANCIA::menos_espacio_deje(int op)
{
  unsigned pos_contenedor;
  int num_instrucciones = 0, min_espacio;
  contenedor.clear();
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
    for(int j = 0; j < contenedor.size(); j++)
    {
      if((cabe_en_contenedor(pos_objeto, j) == true)
	  &&(min_espacio > espacio_sobrante_contenedor(j))) {
	min_espacio = espacio_sobrante_contenedor(j);
	pos_contenedor = j;
	num_instrucciones++;
      }
      num_instrucciones++;
    }
    if(pos_contenedor == INF)
      nuevo_contenedor(pos_objeto);
    else
      meter_en_contenedor(pos_objeto, pos_contenedor);
    num_instrucciones++;
  }
  return num_instrucciones;
}
///////////////////////////////////////////////////////////////////////////////////////////////////
//                                                                               ordenar objetos //
///////////////////////////////////////////////////////////////////////////////////////////////////

void INSTANCIA::ordenar_aleatoriamente(void)
{
  cout << "hay que cambiar el método" << endl;
}

void INSTANCIA::ordenar_menor_mayor(int primero_desordenado/*= 0*/)
{
  
  
  cout << "hay que cambiar el método" << endl;
  
  /*
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
  }*/
}
void INSTANCIA::swap(int i, int j)
{
  cout << "no se usa swap para desordenar objeto" << endl;
  /*
  int aux = objeto[j];
  objeto[j] = objeto[i];
  objeto[i] = aux;*/
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
    //objeto.push_back(aux);
    objeto_en_contenedor[i] = -1;
  }  
}
void INSTANCIA::igualar(INSTANCIA *p)
{
  reiniciar_contenedores();
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

///////////////////////////////////////////////////////////////////////////////////////////////////
//                                                                                         GRASP //
///////////////////////////////////////////////////////////////////////////////////////////////////
void GRUPO_INSTANCIAS::GRASP(int i, int op)
{
  
  /*
  INSTANCIA** LCR = new INSTANCIA*[LCR_SIZE];
  int izq, der;
  for(int j = 0; j < LCR_SIZE; j++)
  {
    izq = 0;
    der = instancia[i]->get_n_objetos() - 1;
    LCR[j] = new INSTANCIA(instancia[i]);
    LCR[j]->ordenar_aleatoriamente();
    //LCR[j]->ordenar_GRASP();
    while(izq < der) {
      LCR[j]->swap(izq, der);
      izq++;
      der--;
    }
    LCR[j]->antes_que_quepa();*/
    /*
    if(op == PROXIMO_10)
      LCR[j]->LS_proximo_10();
    else if(op == MENOS_ESPACIO_DEJE)
      LCR[j]->LS();
    else
      LCR[j]->LS_azar();*/
    /*LCR->ordenar_aleatoriamente();
    LCR->meter_antes_que_quepa();
  }  
  instancia[i]->igualar(LCR[rand() % LCR_SIZE]);*/
}
///////////////////////////////////////////////////////////////////////////////////////////////////
//                                                                                            SA //
///////////////////////////////////////////////////////////////////////////////////////////////////
float GRUPO_INSTANCIAS::Pr(float c, int delta)
{
  if(delta > 0)
    return 1;
  else
    return exp(((float)delta) / c);
}
void GRUPO_INSTANCIAS::SA(int i, int op, float c, float alfa)
{
  INSTANCIA sol_actual(instancia[i]), mejor_sol(instancia[i]), sol_vecina(instancia[i]);
  sol_actual.ordenar_aleatoriamente();
  sol_actual.antes_que_quepa();
  mejor_sol.igualar(&sol_actual);
  int max_vecinas = 0;
  float rand_f;
  while(max_vecinas < MAX_VECINAS_SA) {
    if(op == PROXIMO_10)
      sol_vecina.LS_proximo_10();
    else if(op == MENOS_ESPACIO_DEJE)
      sol_vecina.LS();
    else
      sol_vecina.LS_azar();
    rand_f = (float)rand()/(float)RAND_MAX;
    if(Pr(c, sol_actual.get_num_contenedores() - sol_vecina.get_num_contenedores()) > rand_f)
      sol_actual.igualar(&sol_vecina);
    if(sol_actual.get_num_contenedores() < mejor_sol.get_num_contenedores())
      mejor_sol.igualar(&sol_actual);
    c *= alfa;
    max_vecinas++;
  }
  if(mejor_sol.get_num_contenedores() < instancia[i]->get_num_contenedores())
    instancia[i]->igualar(&mejor_sol);
}
///////////////////////////////////////////////////////////////////////////////////////////////////
//                                                                                            LS //
///////////////////////////////////////////////////////////////////////////////////////////////////
void GRUPO_INSTANCIAS::ILS(int i, int it, int op, bool tipo)
{
  int max_vecinas = 0;
  INSTANCIA p(instancia[i]);
  bool cambiado = true;  
  for(int j = 0; j < it; j++)
  {
    if(tipo == MULTI_ARRANQUE) {
      p.ordenar_aleatoriamente();
      p.menos_espacio_deje();
    }
    else
      p.igualar(instancia[i]);
    while((p.get_num_contenedores() >= instancia[i]->get_num_contenedores())
	  &&(max_vecinas < MAX_VECINAS_LS)
	  &&(cambiado == true)) {
      if(op == PROXIMO_10)
	p.LS_proximo_10();
      else if(op == MENOS_ESPACIO_DEJE)
	p.LS();
      else
	p.LS_azar();
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
  }
}
void GRUPO_INSTANCIAS::LS(int i, int op/*= false*/)
{
  if(op == PROXIMO_10)
    instancia[i]->LS_proximo_10();
  else if(op == MENOS_ESPACIO_DEJE)
    instancia[i]->LS();
  else
    instancia[i]->LS_azar();
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
int GRUPO_INSTANCIAS::meter_antes_que_quepa(int i, int op)
{
  return instancia[i]->antes_que_quepa(op);
}
int GRUPO_INSTANCIAS::meter_menos_espacio_deje(int i, int op)
{
  return instancia[i]->menos_espacio_deje(op);
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