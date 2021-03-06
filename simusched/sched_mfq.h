#ifndef __SCHED_MFQ__
#define __SCHED_MFQ__

#include <vector>
#include <queue>
#include "basesched.h"

using namespace std;
class SchedMFQ : public SchedBase {
	public:
		SchedMFQ(std::vector<int> argn);
        ~SchedMFQ();
		virtual void initialize() {};
		virtual void load(int pid);
		virtual void unblock(int pid);
		virtual int tick(int n, const enum Motivo m);
	
	private:
		vector<std::queue<int> > colas; // vector de colas de prioridad
		vector<int> quantums; // vector de quantums (que recibimos por parámetro) 
		vector<int> bloqueados;  //	vector key=>value de tareas bloqueadas. Key = pid. Value = Prioridad.
		vector<int> quantumActual; // quantum actual por cpu
		vector<int> prioridadActual; // prioridad actual por cpu
		int n;
		
		int next(int core);
};

#endif
