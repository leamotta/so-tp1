export LC_ALL=C
CXXFLAGS= -Wall -pedantic -g -ggdb
LDFLAGS= -lpthread

OBJS=main.o simu.o basesched.o basetask.o tasks.o sched_rr.o sched_fcfs.o sched_sjf.o sched_rsjf.o sched_mfq.o
MAIN=simusched

.PHONY: all clean new
all: $(MAIN)

$(MAIN): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LDFLAGS)

%.o: %.cpp %.h basesched.h
basesched.o: basesched.cpp basesched.h
basetask.o: basetask.cpp basetask.h
main.o: main.cpp simu.h basetask.h basesched.h tasks.h sched_fcfs.h \
	sched_mfq.h sched_rr.h sched_rsjf.h sched_sjf.h
simu.o: simu.cpp simu.h basetask.h basesched.h
simusched.o: simusched.cpp basetask.h basesched.h tasks.h
tasks.o: tasks.cpp tasks.h basetask.h

ejercicio3: 
	./simusched ej3.tsk 1 1 1 SchedFCFS | python graphsched.py > ej3.png

ejercicio5: 
	./simusched ej2.tsk 1 2 1 SchedRR 2 | python graphsched.py > ./imagenes/ej5-Quantum2.png
	./simusched ej2.tsk 1 2 1 SchedRR 5 | python graphsched.py > ./imagenes/ej5-Quantum5.png
	./simusched ej2.tsk 1 2 1 SchedRR 10 | python graphsched.py > ./imagenes/ej5-Quantum10.png
	./simusched ej2.tsk 1 2 1 SchedRR 2 > ej5-Quantum2.txt
	./simusched ej2.tsk 1 2 1 SchedRR 5 > ej5-Quantum5.txt
	./simusched ej2.tsk 1 2 1 SchedRR 10 > ej5-Quantum10.txt

ejercicio7: 
	./simusched ej7_SJF.tsk 1 1 1 SchedSJF 1 | python graphsched.py > ej7_SJF.png
	./simusched ej7_RSJF.tsk 1 1 1 SchedRSJF 3 | python graphsched.py > ej7_RSJF.png

clean:
	rm -f $(OBJS) $(MAIN)

new: clean all
