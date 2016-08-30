#ifndef __SCHED_RSJF__
#define __SCHED_RSJF__

#include <vector>
#include <queue>
#include <algorithm>
#include <iostream>       // std::cout
#include <functional>     // std::greater
#include "basesched.h"

using namespace std;

class comparacion_rsjf
{
  bool reverse;
  public:
 	 comparacion_rsjf(const bool& revparam=false)
    	{reverse=revparam;}
  bool operator() (const int& lhs, const int&rhs) const
  {
    if (reverse) return (lhs>rhs);
    else return (lhs<rhs);
  }
};

typedef std::priority_queue<int,std::vector<int>,comparacion_rsjf> cola_prioridad_rsfj;

class SchedRSJF : public SchedBase {
	public:
		SchedRSJF(std::vector<int> argn);
        ~SchedRSJF();
		virtual void initialize() {};
		virtual void load(int pid);
		virtual void unblock(int pid);
		virtual int tick(int cpu, const enum Motivo m);	
	private:
		cola_prioridad_rsfj cola; //Cola global de procesos listos.
		std::vector<int> cpu_quantum; //Llevar� la cuenta de el quantum consumido por el proceso que est� corriendo en esa cpu.
		std::vector<int> def_quantum; //Se guardar� el quantum definido por quien llam� al Scheduler para cada cpu.
		int next(int cpu); //Se encarga de seleccionar al siguiente proceso que debe ingresar a la cpu.
	
};

#endif
