#include "pract_4.cc"
int main(void)
{
  char nombre_fichero[] = "BPP10.txt";
  GRUPO_INSTANCIAS grupo_instancias(nombre_fichero);
  //grupo_instancias.mostrar_contenido_ficheros();
  grupo_instancias.ordenar_aleatoriamente(9);
  //grupo_instancias.mostrar_contenido_instancia(9);
}