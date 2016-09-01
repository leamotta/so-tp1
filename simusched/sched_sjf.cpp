#include <vector>
#include <queue>
#include <iostream>
#include "sched_sjf.h"

using namespace std;

SchedSJF::SchedSJF(vector<int> argn) {
    // Recibe la cantidad de cores y quantum de cada proceso
	//vector<int> pid_quantum(argn.size() - 1);

	for (int i=1; i < argn.size(); i++){ 
		info_pid tupla; 
		tupla.pid = i-1; 
		tupla.tiempo = argn[i];
		cola.push(tupla);
		pid_quantum.push_back(argn[i]);
	}
}

SchedSJF::~SchedSJF() {
/* llenar */
}

void SchedSJF::load(int pid) {
	info_pid tupla; 
	tupla.pid = pid; 
	tupla.tiempo = buscarTiempo(cola, pid);
	cola.push(tupla); 
}

void SchedSJF::unblock(int pid) {
	info_pid tupla; 
	tupla.pid = pid; 
	tupla.tiempo = buscarTiempo(cola, pid);
	cola.push(tupla); 
}

int SchedSJF::tick(int cpu, const enum Motivo m) {
	if (m == TICK){
		if (current_pid(cpu) == IDLE_TASK && !cola.empty()) { //Si la CPU está libre se pone el próximo proceso de la cola si es que hay alguno.
			return next(cpu);
		}else{
			if(buscarTiempo(cola, current_pid(cpu)) == 0){ //Vemos si el proceso ya consumió su quantum.
				return next(cpu); //Llamamos al proceso siguiente. PUEDE PASAR QUE SEA EL PROCESO CON MENOR QUANTUM Y SE EJECUTE DEVUELTA.
			}else{  //Si todavía no consumió su quantum sigue el mismo proceso.
				pid_quantum[current_pid(cpu)] = pid_quantum[current_pid(cpu)] - 1;
				return current_pid(cpu);
			}
		}
	}else{ //m = EXIT o m = BLOCK
		//cola.pop();
		return next(cpu); //Ya sea porque el proceso actual terminó o porque se bloqueó llamamos al siguiente proceso para ocupar la CPU.
	}
}

int SchedSJF::next (int cpu){
	if (cola.empty()){
		return IDLE_TASK; //No hay procesos en la cola global.
	}else{
		int sig = cola.top().pid; //Tomamos el primer proceso de la cola.
		cola.pop(); //Sacamos al primer proceso de la cola.
		return sig;
	}
}

int SchedSJF::buscarTiempo(cola_prioridad_sfj cola, int pid){
	
	while(!cola.empty()){
		if(cola.top().pid == pid){
			return cola.top().tiempo;
		}
		cola.pop();
	}
	return 0;
}