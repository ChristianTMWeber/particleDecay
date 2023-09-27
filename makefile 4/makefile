##---------------------------------------
##          makefile for problem 4
##---------------------------------------



# set compilation macros
CXX=g++
RM=rm -rf
PRODUCTFLAGS=-Wall -pedantic 
DEBUGFLAGS=-g

# set the default action
.DEFAULT_GOAL := production

# set source, object, target macros
SRCS=ParticleDecay.cxx myRandom.cxx
OBJS=$(SRCS:.cxx=.o)
DOBJS=$(SRCS:.cxx=.do)
TARGET=ParticleDecay

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
ParticleDecay.o: ThreeVector.h LorentzVector.h myRandom.h
ThreeVector.o: ThreeVector.h 
LorentzVector.o: LorentzVector.h
myRandom.o: myRandom.h
# create executables
production: $(OBJS)
	$(CXX) $(PRODUCTFLAGS) -o $(TARGET) $(OBJS)

debug: $(DOBJS)
	$(CXX) $(DEBUGFLAGS) -o $(TARGET).db $(OBJS)

clean:
	$(RM) *.o *.~ $(TARGET) $(TARGET).db