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

ejercicio1: 
	./simusched ej1.tsk 4 1 10 SchedFCFS | python graphsched.py > ./imagenes/ej1.png

ejercicio2: 
	./simusched ej2.tsk 1 2 2 SchedFCFS | python graphsched.py > ./imagenes/ej2_1.png
	./simusched ej2.tsk 2 2 2 SchedFCFS | python graphsched.py > ./imagenes/ej2_2.png
	./simusched ej2.tsk 4 2 2 SchedFCFS | python graphsched.py > ./imagenes/ej2_4.png

ejercicio3: 
	./simusched ej3.tsk 1 1 1 SchedFCFS | python graphsched.py > ./imagenes/ej3.png

ejercicio5: 
	./simusched ej2.tsk 1 2 1 SchedRR 2 | python graphsched.py > ./imagenes/ej5-Quantum2.png
	./simusched ej2.tsk 1 2 1 SchedRR 5 | python graphsched.py > ./imagenes/ej5-Quantum5.png
	./simusched ej2.tsk 1 2 1 SchedRR 10 | python graphsched.py > ./imagenes/ej5-Quantum10.png

ejercicio8: 
	./simusched ej8.tsk 1 2 2 SchedSJF 1 5 9 2 7 | python graphsched.py > ./imagenes/ej8-SJF.png
	./simusched ej8.tsk 1 2 2 SchedRSJF 3 5 9 2 7 | python graphsched.py > ./imagenes/ej8-RSJF.png
	./simusched ej8.tsk 1 2 2 SchedFCFS | python graphsched.py > ./imagenes/ej8-FCFS.png
	./simusched ej8.tsk 1 2 2 SchedRR 3 | python graphsched.py > ./imagenes/ej8-RR.png
	./simusched ej8-2.tsk 2 1 1 SchedFCFS | python graphsched.py > ./imagenes/ej8-2FCFS.png
	./simusched ej8-2.tsk 2 1 1 SchedRR 6 6 | python graphsched.py > ./imagenes/ej8-2RR.png
	./simusched ej8-3.tsk 1 1 1 SchedSJF 1 12 3 2 1 | python graphsched.py > ./imagenes/ej8-3SJF.png
	./simusched ej8-3.tsk 1 1 1 SchedRSJF 3 12 3 2 1 | python graphsched.py > ./imagenes/ej8-3RSJF.png
	./simusched ej8-4.tsk 2 2 2 SchedRR 2 2 | python graphsched.py > ./imagenes/ej8-4RR.png
	./simusched ej8-4.tsk 2 2 2 SchedFCFS | python graphsched.py > ./imagenes/ej8-4FCFS.png
	./simusched ej8-5.tsk 1 3 3 SchedSJF 1 7 5 3 1 | python graphsched.py > ./imagenes/ej8-5SJF.png
	./simusched ej8-5.tsk 1 3 3 SchedRSJF 1 7 5 3 1| python graphsched.py > ./imagenes/ej8-5RSJF.png


ejercicio9:
	./simusched ej9.tsk 1 1 1 SchedMFQ 2 3 | python graphsched.py > ./imagenes/ej9.png
	./simusched ej9.tsk 2 1 1 SchedMFQ 2 3 | python graphsched.py > ./imagenes/ej9b.png

clean:
	rm -f $(OBJS) $(MAIN)

new: clean all
