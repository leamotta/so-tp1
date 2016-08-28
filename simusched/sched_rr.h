#ifndef __SCHED_RR__
#define __SCHED_RR__

#include <vector>
#include <queue>
#include <algorithm>
#include "basesched.h"

using namespace std;

class SchedRR : public SchedBase {
	public:
		SchedRR(std::vector<int> argn);
        ~SchedRR();
		virtual void initialize() {};
		virtual void load(int pid);
		virtual void unblock(int pid);
		virtual int tick(int cpu, const enum Motivo m);	
	private:
		std::queue<int> cola; //Cola global de procesos listos.
		std::vector<int> cpu_quantum; //Llevar� la cuenta de el quantum consumido por el proceso que est� corriendo en esa cpu.
		std::vector<int> def_quantum; //Se guardar� el quantum definido por quien llam� al Scheduler para cada cpu.
		int next(int cpu); //Se encarga de seleccionar al siguiente proceso que debe ingresar a la cpu.
};

#endif
