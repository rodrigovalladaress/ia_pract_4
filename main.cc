#include "pract_4.cc"
int main(void)
{
  char nombre_fichero[] = "BPP10.txt";
  int inst;
  int time;
  GRUPO_INSTANCIAS grupo_instancias(nombre_fichero);
  //grupo_instancias.mostrar_contenido_ficheros();
  grupo_instancias.ordenar_aleatoriamente(9);
  //grupo_instancias.mostrar_contenido_instancia(9);
  //grupo_instancias.meter_antes_que_quepa(9);
  //grupo_instancias.mostrar_contenedores_instancia(9);
  grupo_instancias.estadistica_antes_que_quepa(9, inst, time);
  cout << "inst = " << inst << endl;
  cout << "time = " << time << endl;
}