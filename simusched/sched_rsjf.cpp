#include "sched_rsjf.h"

using namespace std;

SchedRSJF::SchedRSJF(vector<int> argn) {
    // Recibe la cantidad de cores y sus cpu_quantum por parámetro
	if (argn.size() < argn[0]+1){
		cout <<"Faltan parámetros!!\n"<<endl;
		exit(EXIT_FAILURE);
	}

	for (int i=1; i < argn[0] + 1; i++){ //En argn[0] está la cantidad de cores.
		//cerr << "i1: " << i << endl;
		def_quantum.push_back(argn[i]);
	}

	for (int i=argn[0]+1; i < argn.size(); i++){
		//cerr << "i2: " << i << endl;
		consumido_quantum.push_back(0); 
		pid_quantum.push_back(argn[i]); 
		//cerr << "la pos " << i-argn[0]-1 << "tiene quantum " << pid_quantum[i-argn[0]-1] << endl;
	}
}

SchedRSJF::~SchedRSJF() {
/* llenar */
}

void SchedRSJF::load(int pid) {
	info_pid tupla; 
	tupla.pid = pid; 
	tupla.tiempo = pid_quantum[pid];
	cola.push(tupla); 
	//cerr << "LOAD el pid " << tupla.pid << " tiene quantum " << tupla.tiempo << endl;
	//cerr << "tam cola " << cola.size() << endl;
}

void SchedRSJF::unblock(int pid) {
	info_pid tupla; 
	tupla.pid = pid; 
	tupla.tiempo = pid_quantum[pid];	// TODO: QUE HACER EN ESTE CASO?
	cola.push(tupla); 
	//cerr << "UNBLOCK el pid " << tupla.pid << " tiene quantum " << tupla.tiempo << endl;
	//cerr << "tam cola " << cola.size() << endl;
}

int SchedRSJF::tick(int cpu, const enum Motivo m) {
	if (m == TICK){
		//cerr << "TICK en cpu: " << cpu << ". Esta corriendo el pid: " << current_pid(cpu) << ". Le quedan: " << pid_quantum[current_pid(cpu)] << endl;
		if (current_pid(cpu) == IDLE_TASK) { //Si la CPU está libre se pone el próximo proceso de la cola
			//cerr << "Tarea IDLE o Cola VACIA." << endl;
			//cerr << "tam cola " << cola.size() << endl;
			return next(cpu);
		}else{
			if(consumido_quantum[current_pid(cpu)] >= def_quantum[cpu]){ //Vemos si el proceso ya consumió su quantum.
				//cerr << "El pid " << current_pid(cpu) << " consumio su quantum" << endl;
				info_pid tupla; 
				tupla.pid = current_pid(cpu); 
				tupla.tiempo = pid_quantum[current_pid(cpu)];	
				//cerr << "agrego el pid " << tupla.pid << " tiene quantum " << tupla.tiempo << endl;
				//cerr << "tam cola " << cola.size() << endl;
				cola.push(tupla);
				//cerr << "agrego de nuevo el pid a la cola" << endl;
				return next(cpu); 
			}else{  //Si todavía no consumió su quantum sigue el mismo proceso.
				pid_quantum[current_pid(cpu)]--;
				consumido_quantum[current_pid(cpu)]++;
				return current_pid(cpu);
			}
		}
	}else{ //m = EXIT o m = BLOCK
		//cerr << "EXIT en cpu " << cpu << ". El pid " << current_pid(cpu) << " consumio su quantum" << endl;
		//cerr << "tam cola " << cola.size() << endl;
		return next(cpu); //Ya sea porque el proceso actual terminó o porque se bloqueó llamamos al siguiente proceso para ocupar la CPU.
	}
}

int SchedRSJF::next (int cpu){
	if (cola.empty()){
		//cerr << "el siguiente pid es la tarea IDLE" << endl;
		return IDLE_TASK; //No hay procesos en la cola global.
	}else{
		//cerr << "tam cola " << cola.size() << endl;
		int sig = cola.top().pid; //Tomamos el primer proceso de la cola.
		cola.pop(); //Sacamos al primer proceso de la cola.
		pid_quantum[sig]--;
		consumido_quantum[sig] = 1;
		//cerr << "el siguiente pid es " << sig << endl;
		return sig;
	}
}
