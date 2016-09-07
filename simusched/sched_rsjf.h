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
 	 comparacion_rsjf(const bool& revparam = true) { reverse = revparam; }

  bool operator() (const info_pid& lhs, const info_pid&rhs) const
  {
    if (reverse) return (lhs.tiempo > rhs.tiempo);
    else return (lhs.tiempo < rhs.tiempo);
  }
};

typedef std::priority_queue<info_pid,std::vector<info_pid>,comparacion_rsjf> cola_prioridad_rsfj;

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
		std::vector<int> pid_quantum;
		std::vector<int> consumido_quantum;
		std::vector<int> def_quantum; 
		int next(int cpu); //Se encarga de seleccionar al siguiente proceso que debe ingresar a la cpu.
};

#endif
