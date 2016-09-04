#include <vector>
#include <queue>
#include "sched_mfq.h"
#include "basesched.h"
#include <iostream>
#include <fstream>

using namespace std;

SchedMFQ::SchedMFQ(vector<int> argn) {
	// MFQ recibe los quantums por parámetro
	for(size_t i = 1;i<argn.size();i++){
		this->quantums.push_back(argn[i]);
	}
	this->n = argn.size()-1; //resto el parametro de cant de cores
	this->colas = vector<queue<int> >(n);
	this->quantumActual = 0;
	this->prioridadActual = -1;
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
		return next();
	} else if (m == BLOCK) {
		// La tarea se bloqueó y sube de prioridad
		if (prioridadActual > 0){
			prioridadActual--;
		}
		// Se agrega en el vector de tareas bloqueadas
		bloqueados[current_pid(core)] = prioridadActual;
		return next();
	} else { // m == TICK
		if (quantumActual) { 
			//Si todavía no consumió su quantum sigue el mismo proceso
			quantumActual--;
			return current_pid(core);
		} else {
			// El proceso agotó su quantum y baja de prioridad
			if (current_pid(core) != IDLE_TASK) {
				if (prioridadActual < n-1){
					prioridadActual++;
				}
				colas[prioridadActual].push(current_pid(core));
			}
			return next();
		}
	}
	return 0;
}

int SchedMFQ::next() {
	// Elijo el nuevo pid
	int nuevo = IDLE_TASK;
	quantumActual = 0; // El IDLE_TASK tiene quantum 0 para que al próximo tick vea si hay alguien esperando.
	for (prioridadActual = 0; prioridadActual < n; prioridadActual++) {
		if (!colas[prioridadActual].empty()) {
			nuevo = colas[prioridadActual].front();
			colas[prioridadActual].pop();
			quantumActual = quantums[prioridadActual] - 1; // -1 porque contamos este tick
			return nuevo;
		}
	}
	return nuevo;
}
