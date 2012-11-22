#include "pract_4.cc"
int main(void)
{
  char nombre_fichero[] = "BPP10.txt";
  GRUPO_INSTANCIAS grupo_instancias(nombre_fichero);
  cout << "Número de soluciones = " << NUM_SOLUCIONES << endl << endl;
  grupo_instancias.estadistica();
}