#include <vector>
#include <queue>
#include <iostream>
#include "sched_sjf.h"

using namespace std;

SchedSJF::SchedSJF(vector<int> argn) {
        // Recibe la cantidad de cores 
/* llenar */
}

SchedSJF::~SchedSJF() {
/* llenar */
}

void SchedSJF::load(int pid) {
	cola.push(pid); //Encolamos la tarea nueva que llega en la cola global de procesos ready.
}

void SchedSJF::unblock(int pid) {
	cola.push(pid); //Encolamos la tarea nueva que llega en la cola global de procesos ready.
}

int SchedSJF::tick(int cpu, const enum Motivo m) {
	if (m == TICK){
		if (current_pid(cpu) == IDLE_TASK && !cola.empty()) { //Si la CPU está libre se pone el próximo proceso de la cola si es que hay alguno.
			return next(cpu);
		}else{
			return current_pid(cpu);
		}
	}else{ //m = EXIT o m = BLOCK
		return next(cpu); //Ya sea porque el proceso actual terminó o porque se bloqueó llamamos al siguiente proceso para ocupar la CPU.
	}
}

int SchedSJF::next (int cpu){
	if (cola.empty()){
		return IDLE_TASK; //No hay procesos en la cola global.
	}else{
		int sig = cola.top(); //Tomamos el primer proceso de la cola.
		cola.pop(); //Sacamos al primer proceso de la cola.
		return sig;
	}
}