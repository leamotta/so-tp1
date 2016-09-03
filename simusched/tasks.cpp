#include "tasks.h"
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <algorithm>

using namespace std;

void TaskCPU(int pid, vector<int> params) { // params: n
	uso_CPU(pid, params[0] - 1); // Uso el CPU n milisegundos.
}

void TaskIO(int pid, vector<int> params) { // params: ms_pid, ms_io,
	uso_CPU(pid, params[0]); // Uso el CPU ms_pid milisegundos.
	uso_IO(pid, params[1]); // Uso IO ms_io milisegundos.
}

void TaskAlterno(int pid, vector<int> params) { // params: ms_pid, ms_io, ms_pid, ...
	for(int i = 0; i < (int)params.size(); i++) {
		if (i % 2 == 0) uso_CPU(pid, params[i] - 1);
		else uso_IO(pid, params[i]);
	}
}

void TaskConsola(int pid, vector<int> params) { // params: ms_pid, n, bmin, bmax
	srand (time(NULL)); // cambiamos la semilla del numero pseudoaleatorio

    for (int i = 0; i < params[0]; i++) {
        int ciclos = rand() % (params[2]+1-params[1]) + params[1];
        uso_IO(pid, ciclos);
        uso_CPU(pid, 1);
    }
    //exit(1);
}

void TaskBatch(int pid, vector<int> params){ // params: totalCPU, cantBloqueos
	int totalCPU = params[0];
	int cantBloqueos = params[1];
	int netoCPU = totalCPU-1-cantBloqueos;
	// cada bloqueo suma 1 al totalCPU por eso restamos cantBloqueos
	// restamos 1 porque el return consume 1 ciclo
	
	srand (time(NULL)); // cambiamos la semilla del numero pseudoaleatorio
	
	vector<int> tiempoCPU; 
	// este vector va a tener el tiempo que se va a usar la CPU hasta ser bloqueado

	for (int i = 0; i < cantBloqueos; i++){
		// posicionamos los bloqueos en lugares random usando mod
		tiempoCPU.push_back(rand()%netoCPU); 
	}

	/* Ordenamos las posiciones de los bloqueos para poder recorrerlas*/
	sort(tiempoCPU.begin(), tiempoCPU.end());

	for (int i = 0; i < cantBloqueos-1; i++){
		// para cada elemento del vector restamos el anterior (exceptuando el primero)
		// esto convierte a cada elemento i en el tiempo de uso de CPU hasta el bloqueo nro i+1
		tiempoCPU[cantBloqueos-1-i] -= tiempoCPU[cantBloqueos-2-i]; 
	}

	/* Recorremos el vector, usando la CPU según nos indique cada posición */
	for (int i = 0; i < cantBloqueos; i++){
		if (tiempoCPU[i]){
			uso_CPU(pid,tiempoCPU[i]);
			netoCPU -= tiempoCPU[i];
		}
		uso_IO(pid,2);
	}
	
	if (netoCPU){
		uso_CPU(pid,netoCPU);
	}
}


void tasks_init(void) {
	/* Todos los tipos de tareas se deben registrar acá para poder ser usadas.
	 * El segundo parámetro indica la cantidad de parámetros que recibe la tarea
	 * como un vector de enteros, o -1 para una cantidad de parámetros variable. */
	register_task(TaskCPU, 1);
	register_task(TaskIO, 2);
	register_task(TaskAlterno, -1);
    register_task(TaskConsola, 3);
	register_task(TaskBatch, 2);
}
