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
