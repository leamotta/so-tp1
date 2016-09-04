#include "sched_rsjf.h"

using namespace std;

SchedRSJF::SchedRSJF(vector<int> argn) {
    // Recibe la cantidad de cores y sus cpu_quantum por parámetro
	//Guardamos los quantum de cada cpu en el vector def_quantum. Inicializamos 
	if (argn.size() < argn[0]+1){
		cout <<"Faltan parámetros!!\n"<<endl;
		exit(EXIT_FAILURE);
	}

	for (int i=0; i < argn[0]; i++){ //En argn[0] está la cantidad de cores.
		def_quantum.push_back(argn[i+1]);
	}

	for (int i=argn[0]+1; i < argn.size(); i++){ 
		info_pid tupla; 
		tupla.pid = i - argn[0]; 
		tupla.tiempo = argn[i];
		cola.push(tupla);
		cpu_quantum.push_back(0); //Ponemos en 0 los quantum consumidos por cada pid.
	}
}

SchedRSJF::~SchedRSJF() {
/* llenar */
}

void SchedRSJF::load(int pid) {
	info_pid tupla; 
	tupla.pid = pid; 
	tupla.tiempo = buscarTiempo(cola, pid);
	cola.push(tupla); 
}

void SchedRSJF::unblock(int pid) {
	info_pid tupla; 
	tupla.pid = pid; 
	tupla.tiempo = buscarTiempo(cola, pid);
	cola.push(tupla); 
}

int SchedRSJF::tick(int core, const enum Motivo m) {
	if (m == TICK){
		if (current_pid(core) == IDLE_TASK && !cola.empty()) { //Si la CPU está libre se pone el próximo proceso de la cola si es que hay alguno.
			return next(core);
		}else{
			if(cpu_quantum[core] >= def_quantum[core]){ //Vemos si el proceso ya consumió su quantum.
				info_pid tupla; 
				tupla.pid = current_pid(core); 
				tupla.tiempo = buscarTiempo(cola, current_pid(core));
				cola.push(tupla); //Ponemos el proceso actual en la cola
				return next(core); //Llamamos al proceso siguiente. PUEDE PASAR QUE SEA EL PROCESO CON MENOR QUANTUM Y SE EJECUTE DEVUELTA.
			}else{  //Si todavía no consumió su quantum sigue el mismo proceso.
				cpu_quantum[current_pid(core)]++;
				return current_pid(core);
			}
		}
	}else{ //m = EXIT o m = BLOCK
		return next(core); //Ya sea porque el proceso actual terminó o porque se bloqueó llamamos al siguiente proceso para ocupar la CPU.
	}
}

int SchedRSJF::next (int cpu){
	if (cola.empty()){
		cpu_quantum[cpu] = 0; //Ponemos en cero el quantum consumido.
		return IDLE_TASK; //No hay procesos en la cola global.
	}else{
		int sig = cola.top().pid; //Tomamos el primer proceso de la cola.
		cola.pop(); //Sacamos al primer proceso de la cola.
		cpu_quantum[cpu] = 1; //Ponemos en uno el quantum consumido por ese proceso para esa cpu sumando el tick que está por realizar.
		return sig;
	}
}

int SchedRSJF::buscarTiempo(cola_prioridad_rsfj cola, int pid){
	
	while(!cola.empty()){
		if(cola.top().pid == pid){
			return cola.top().tiempo;
		}
		cola.pop();
	}
	return 0;
}