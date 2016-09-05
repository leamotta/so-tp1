#include <vector>
#include <queue>
#include "sched_mfq.h"
#include "basesched.h"

using namespace std;

SchedMFQ::SchedMFQ(vector<int> argn) {
	// MFQ recibe los quantums por parámetro
	for(size_t i = 1;i<argn.size();i++){
		this->quantums.push_back(argn[i]);
	}
	this->n = argn.size()-1; //resto el parametro de cant de cores
	this->colas = vector<queue<int> >(n);
	for (int i=0; i < argn[0]; i++){ //En argn[0] está la cantidad de cores.
		this->quantumActual.push_back(0);
		this->prioridadActual.push_back(-1);
	}
}

SchedMFQ::~SchedMFQ() {
}

void SchedMFQ::load(int pid) {
	colas[0].push(pid); // tarea nueva al final de la cola de prioridad mas alta
	bloqueados.push_back(-1); // hago lugar en el vector de bloqueados por si se llegara a bloquear
}

void SchedMFQ::unblock(int pid) {
	colas[bloqueados[pid]].push(pid); // Se encola la tarea en la cola correspondiente a su prioridad
}

int SchedMFQ::tick(int core, const enum Motivo m) {
	if (m == EXIT) {
		// La tarea actual no se encola nuevamente
		return next(core);
	} else if (m == BLOCK) {
		// La tarea se bloqueó y sube de prioridad	
		if (prioridadActual[core] > 0){
			prioridadActual[core]--;
		}
		// Se agrega en el vector de tareas bloqueadas
		bloqueados[current_pid(core)] = prioridadActual[core];
		return next(core);
	} else { // m == TICK
		if (quantumActual[core]) { 
			//Si todavía no consumió su quantum sigue el mismo proceso
			quantumActual[core]--;
			return current_pid(core);
		} else {
			// El proceso agotó su quantum y baja de prioridad
			if (current_pid(core) != IDLE_TASK) {
				if (prioridadActual[core] < n-1){
					prioridadActual[core]++;
				}
				colas[prioridadActual[core]].push(current_pid(core));
			}
			return next(core);
		}
	}
	return 0;
}

int SchedMFQ::next(int core) {
	// Elijo el nuevo pid
	int nuevo = IDLE_TASK;
	quantumActual[core] = 0; // El IDLE_TASK tiene quantum 0 para que al próximo tick vea si hay alguien esperando.
	for (int i = 0; i < n; i++) {
		if (!colas[i].empty()) {
			nuevo = colas[i].front();
			colas[i].pop();
			prioridadActual[core] = i;
			quantumActual[core] = quantums[i] - 1; // -1 porque contamos este tick
			return nuevo;
		}
	}
	return nuevo;
}
