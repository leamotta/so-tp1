#ifndef __SCHED_SJF__
#define __SCHED_SJF__

#include <vector>
#include <queue>
#include <algorithm>
#include <iostream>       // std::cout
#include <functional>     // std::greater
#include "basesched.h"

using namespace std;

/*struct info_pid
{
	int pid;
	int tiempo;
};*/

class comparacion_sjf
{
  bool reverse;
  public:
 	 comparacion_sjf(const bool& revparam=false) { reverse = revparam; }

  bool operator() (const info_pid& lhs, const info_pid&rhs) const
  {
    if (reverse) return (lhs.tiempo > rhs.tiempo);
    else return (lhs.tiempo < rhs.tiempo);
  }
};

typedef std::priority_queue<info_pid,std::vector<info_pid>,comparacion_sjf> cola_prioridad_sfj;

class SchedSJF : public SchedBase {
	public:
		SchedSJF(std::vector<int> argn);
        ~SchedSJF();
		virtual void initialize() {};
		virtual void load(int pid);
		virtual void unblock(int pid);
		virtual int tick(int cpu, const enum Motivo m);	
	private:
		cola_prioridad_sfj cola; //Cola global de procesos listos.
		std::vector<int> pid_quantum;
		int next(int cpu); //Se encarga de seleccionar al siguiente proceso que debe ingresar a la cpu.
		int buscarTiempo(cola_prioridad_sfj cola, int pid);
};

#endif
