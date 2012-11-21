#include "pract_4.cc"
int main(void)
{
  char nombre_fichero[] = "BPP10.txt";
  GRUPO_INSTANCIAS grupo_instancias(nombre_fichero);
  //grupo_instancias.mostrar_contenido_ficheros();
  //grupo_instancias.ordenar_mayor_menor(9);
  //grupo_instancias.mostrar_contenido_instancia(9);
  //grupo_instancias.meter_antes_que_quepa(9);
  //grupo_instancias.mostrar_contenedores_instancia(9);
  //grupo_instancias.estadistica_antes_que_quepa(9, inst, time);
  //grupo_instancias.ordenar_mayor_menor(6);
  //grupo_instancias.meter_menos_espacio_deje(6);
  //grupo_instancias.estadistica_num_contenedores();
  //grupo_instancias.ordenar_aleatoriamente(2);
  //grupo_instancias.ordenar_mayor_menor(0);
  
  

  grupo_instancias.meter_antes_que_quepa(0, ORDEN_ALEATORIO);
  grupo_instancias.GA(0);
  
  cout << "main" << endl;
  
  //grupo_instancias.mostrar_contenedores_instancia(0);
  //for(int i = 0; i < 1; i++)
  //grupo_instancias.GRASP(0);//(0, PROXIMO_10, 1, 0.99);
  /*
  for(int i = 0; i < 1000; i++)
  {
    grupo_instancias.ordenar_aleatoriamente(2);
    grupo_instancias.meter_antes_que_quepa(2);
    //cout << "LS -------------------------------------->" << endl;
    //for(int j = 0; j < 100; j++)
    grupo_instancias.LS(2);
    //rupo_instancias.integridad_instancia(2);
  }*/
  
}