#include <vector>
#include <queue>
#include "sched_rr.h"
#include "basesched.h"
#include <iostream>

using namespace std;

SchedRR::SchedRR(vector<int> argn) {
	// Round robin recibe la cantidad de cores y sus cpu_quantum por parámetro
	//Guardamos los quantum de cada cpu en el vector def_quantum. Inicializamos 
	if (argn.size() < argn[0]+1){
		cout <<"Faltan parámetros!!\n"<<endl;
		exit(EXIT_FAILURE);
	}

	for (int i=0; i < argn[0]; i++){ //En argn[0] está la cantidad de cores.
		def_quantum.push_back(argn[i+1]);
		cpu_quantum.push_back(0); //Ponemos en 0 los quantum consumidos por cada cpu.
	}
}

SchedRR::~SchedRR() {
/* completar */
}


void SchedRR::load(int pid) {
	cola.push(pid); //Encolamos la tarea nueva que llega en la cola global de procesos ready.
}

void SchedRR::unblock(int pid) {
	cola.push(pid); //Encolamos la tarea que dejó de estar bloqueada en la cola global de procesos ready.
}

int SchedRR::tick(int cpu, const enum Motivo m) {
	if (m == TICK){
		//cerr << "TICK en cpu: " << cpu << ". Esta corriendo: " << current_pid(cpu) << ". Le quedan: " << cpu_quantum[cpu] << endl;
		if (current_pid(cpu) == IDLE_TASK && !cola.empty()) { //Si la CPU está libre se pone el próximo proceso de la cola si es que hay alguno.
			//cerr << "El proximo en cpu: " << cpu << " es: " << next(cpu) << endl;
			return next(cpu);
		}else{
			if(cpu_quantum[cpu] >= def_quantum[cpu]){ //Vemos si el proceso ya consumió su quantum.
				cola.push(current_pid(cpu)); //Ponemos el proceso actual en la cola
				//cerr << "El proximo en cpu: " << cpu << " es: " << next(cpu) << endl;
				return next(cpu); //Llamamos al proceso siguiente.
			}else{  //Si todavía no consumió su quantum sigue el mismo proceso.
				cpu_quantum[cpu]++;
				return current_pid(cpu);
			}
		}
	}else{ //m = EXIT o m = BLOCK
		//cerr << "EXIT en cpu " << cpu << ". El proximo es: " << next(cpu) << endl;
		return next(cpu); //Ya sea porque el proceso actual terminó o porque se bloqueó llamamos al siguiente proceso para ocupar la CPU.
	}
}

int SchedRR::next (int cpu){
	if (cola.empty()){
		cpu_quantum[cpu] = 0; //Ponemos en cero el quantum consumido.
		return IDLE_TASK; //No hay procesos en la cola global.
	}else{
		int sig = cola.front(); //Tomamos el primer proceso de la cola.
		cola.pop(); //Sacamos al primer proceso de la cola.
		cpu_quantum[cpu] = 1; //Ponemos en uno el quantum consumido por ese proceso para esa cpu sumando el tick que está por realizar.
		return sig;
	}
}