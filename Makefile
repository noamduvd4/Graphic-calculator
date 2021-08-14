CXX=/usr/local/bin/g++
OBJS = Utilitis.o Graph.o PythonGraph.o Calculator.o gcalc.o  
EXEC = gcalc
DEBUG_FLAG = -g
COMP_FLAG = -std=c++11 -Wall -Werror -fPIC -g -pedantic-errors -DNDEBUG
$(EXEC) : $(OBJS)
	$(CXX) $(DEBUG_FLAG) $(OBJS) -o $@

Utilitis.o: Utilitis.cpp Utilitis.h
	$(CXX) -c $(DEBUG_FLAG) $(COMP_FLAG) $*.cpp
Graph.o: Graph.cpp Graph.h Exception.h Utilitis.h
	$(CXX) -c $(DEBUG_FLAG) $(COMP_FLAG) $*.cpp
PythonGraph.o: PythonGraph.cpp PythonGraph.h Graph.h Exception.h
	$(CXX) -c $(DEBUG_FLAG) $(COMP_FLAG) $*.cpp
Calculator.o: Calculator.cpp Calculator.h Graph.h Utilitis.h Exception.h
	$(CXX) -c $(DEBUG_FLAG) $(COMP_FLAG) $*.cpp
gcalc.o: gcalc.cpp Utilitis.h Exception.h Calculator.h Graph.h
	$(CXX) -c $(DEBUG_FLAG) $(COMP_FLAG) $*.cpp
libgraph.a: Utilitis.o Graph.o PythonGraph.o
	ar -rs $@ $^
make tar:
	zip -r9T gcalc design.pdf  gcalc.cpp Utilitis.cpp Utilitis.h Exception.h Graph.cpp Graph.h Calculator.cpp Calculator.h PythonGraph.cpp PythonGraph.h  graph.i test_in.txt test_out.txt unrecognize_file.gc Makefile  
clean:
	rm -f $(OBJS) libgraph.a gcalc.zip $(EXEC)
