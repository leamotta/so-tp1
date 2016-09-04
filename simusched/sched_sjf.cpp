#include <vector>
#include <queue>
#include <iostream>
#include "sched_sjf.h"

using namespace std;

SchedSJF::SchedSJF(vector<int> argn) {
    // Recibe la cantidad de cores y quantum de cada proceso
	for (int i=1; i < argn.size() - 1; i++){ 
		pid_quantum.push_back(argn[i+1]);
		cerr << "la pos " << i-1 << "tiene quantum " << pid_quantum[i-1] << endl;
	}
}

SchedSJF::~SchedSJF() {
/* llenar */
}

void SchedSJF::load(int pid) {
	info_pid tupla; 
	tupla.pid = pid; 
	tupla.tiempo = pid_quantum[pid];
	cola.push(tupla); 
	cerr << "LOAD el pid " << tupla.pid << " tiene quantum " << tupla.tiempo << endl;
}

void SchedSJF::unblock(int pid) {
	info_pid tupla; 
	tupla.pid = pid; 
	tupla.tiempo = pid_quantum[pid];
	cola.push(tupla); 
	cerr << "UNBLOCK el pid " << tupla.pid << " tiene quantum " << tupla.tiempo << endl;
}

int SchedSJF::tick(int cpu, const enum Motivo m) {
	if (m == TICK){
		cerr << "TICK en cpu: " << cpu << ". Esta corriendo el pid: " << current_pid(cpu) << ". Le quedan: " << pid_quantum[current_pid(cpu)] << endl;
		if (current_pid(cpu) == IDLE_TASK && !cola.empty()) { //Si la CPU está libre se pone el próximo proceso de la cola si es que hay alguno.
			cerr << "Tarea IDLE o Cola VACIA." << endl;
			return next(cpu);
		}else{
			if(pid_quantum[current_pid(cpu)] == 0){ //Vemos si el proceso ya consumió su quantum.
				cerr << "El pid " << current_pid(cpu) << " consumio su quantum" << endl;
				cola.pop();
				return next(cpu); //Llamamos al proceso siguiente. PUEDE PASAR QUE SEA EL PROCESO CON MENOR QUANTUM Y SE EJECUTE DEVUELTA.
			}else{  //Si todavía no consumió su quantum sigue el mismo proceso.
				pid_quantum[current_pid(cpu)]--;
				cola.pop();
				info_pid tupla; 
				tupla.pid = current_pid(cpu); 
				tupla.tiempo = pid_quantum[current_pid(cpu)];
				cola.push(tupla); 
				return current_pid(cpu);
			}
		}
	}else{ //m = EXIT o m = BLOCK
		cerr << "EXIT en cpu " << cpu << ". El pid " << current_pid(cpu) << " consumio su quantum" << endl;
		return next(cpu); //Ya sea porque el proceso actual terminó o porque se bloqueó llamamos al siguiente proceso para ocupar la CPU.
	}
}

int SchedSJF::next (int cpu){
	if (cola.empty()){
		cerr << "el siguiente pid es la tarea IDLE" << endl;
		return IDLE_TASK; //No hay procesos en la cola global.
	}else{
		cerr << "tam cola " << cola.size() << endl;
		int sig = cola.top().pid; //Tomamos el primer proceso de la cola.
		cola.pop(); //Sacamos al primer proceso de la cola.
		pid_quantum[sig]--;
		cerr << "el siguiente pid es " << sig << endl;
		return sig;
	}
}