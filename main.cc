#include "pract_4.cc"
int main(void)
{
  char nombre_fichero[] = "BPP10.txt";
  GRUPO_CONTENEDORES grupo_contenedores(nombre_fichero);
  //grupo_contenedores.mostrar_contenido_ficheros();
  grupo_contenedores.ordenar_aleatoriamente(2);
}