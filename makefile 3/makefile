##---------------------------------------
##          makefile for problem 3
##---------------------------------------



# set compilation macros
CXX=g++
RM=rm -rf
PRODUCTFLAGS=-Wall -pedantic 
DEBUGFLAGS=-g

# set the default action
.DEFAULT_GOAL := production

# set source, object, target macros
SRCS=LorentzVectorTest.cxx
OBJS=$(SRCS:.cxx=.o)
DOBJS=$(SRCS:.cxx=.do)
TARGET=LorentzVectorTest

# pattern rules to redefine implicit rules:

# rule for creating production object files
%.o: %.cxx
	$(CXX) $(PRODUCTFLAGS) -c $<
	
# rule for creating debug object files
%.do: %.cxx
	$(CXX) $(DEBUGFLAGS) -c $<

# list object file dependencies (source files
# are omitted because Make is smart enough to
# know that, e.g. main.o depends on main.cxx, 
# and it will consequently use the pattern rule
# we defined above; however not all compilers 
# can deduce header or "include" dependencies, 
# so we list them here explicitly)
LorentzVectorTest.o: ThreeVector.h VectorTestFunctions.h LorentzVector.h
ThreeVector.o: ThreeVector.h 
VectorTestFunctions.o:VectorTestFunctions.h
LorentzVector.o: LorentzVector.h
# create executables
production: $(OBJS)
	$(CXX) $(PRODUCTFLAGS) -o $(TARGET) $(OBJS)

debug: $(DOBJS)
	$(CXX) $(DEBUGFLAGS) -o $(TARGET).db $(OBJS)

clean:
	$(RM) *.o *.~ $(TARGET) $(TARGET).db