#ifndef __SCHED_SJF__
#define __SCHED_SJF__

#include <vector>
#include <queue>
#include <algorithm>
#include <iostream>       // std::cout
#include <functional>     // std::greater
#include "basesched.h"

using namespace std;


class comparacion_sjf
{
  bool reverse;
  public:
 	 comparacion_sjf(const bool& revparam=false)
    	{reverse=revparam;}
  bool operator() (const int& lhs, const int&rhs) const
  {
    if (reverse) return (lhs>rhs);
    else return (lhs<rhs);
  }
};

typedef std::priority_queue<int,std::vector<int>,comparacion_sjf> cola_prioridad_sfj;

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
		int next(int cpu); //Se encarga de seleccionar al siguiente proceso que debe ingresar a la cpu.
};

#endif
