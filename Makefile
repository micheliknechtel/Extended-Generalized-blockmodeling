SYSTEM     = x86-64_linux
LIBFORMAT  = static_pic

#------------------------------------------------------------
#
# When you adapt this makefile to compile your CPLEX programs
# please copy this makefile and set CPLEXDIR and CONCERTDIR to
# the directories where CPLEX and CONCERT are installed.
#
#------------------------------------------------------------

CPLEXDIR      = /usr/local/ibm/ILOG/CPLEX_Studio1261/cplex
CONCERTDIR    = /usr/local/ibm/ILOG/CPLEX_Studio1261/concert
# ---------------------------------------------------------------------
# Compiler selection 
# ---------------------------------------------------------------------

CCC = g++ -O0 -Wall -W -std=c++11
CC  = gcc -O0

# ---------------------------------------------------------------------
# Compiler options 
# ---------------------------------------------------------------------

CCOPT = -m64 -O -fPIC -fno-strict-aliasing -fexceptions -DNDEBUG -DIL_STD

# ---------------------------------------------------------------------
# Link options and libraries
# ---------------------------------------------------------------------

CPLEXBINDIR   = $(CPLEXDIR)/bin/$(BINDIST)
CPLEXLIBDIR   = $(CPLEXDIR)/lib/$(SYSTEM)/$(LIBFORMAT)
CONCERTLIBDIR = $(CONCERTDIR)/lib/$(SYSTEM)/$(LIBFORMAT)

CCLNDIRS  = -L$(CPLEXLIBDIR) -L$(CONCERTLIBDIR)
CLNDIRS   = -L$(CPLEXLIBDIR)
CCLNFLAGS = -lconcert -lilocplex -lcplex -lm -lpthread
CLNFLAGS  = -lcplex -lm -lpthread


all:
	make all_cpp

execute: all
	make execute_cpp
	
CONCERTINCDIR = $(CONCERTDIR)/include
ILCPLEXINCLUDE = $(CPLEXDIR)/include/ilcplex
CPLEXINCDIR   = $(CPLEXDIR)/include

EXDIR         = .
EXINC         = $(EXDIR)/include
EXDATA        = $(EXDIR)
EXSRCC        = $(EXDIR)/src/c
EXSRCCX       = $(EXDIR)/src/c_x
EXSRCCPP      = $(EXDIR)

CCFLAGS = $(CCOPT) -I$(CPLEXINCDIR) -I$(CONCERTINCDIR) 


#------------------------------------------------------------
#  make all      : to compile the examples. 
#  make execute  : to compile and execute the examples.
#------------------------------------------------------------


CPP_EX = GBlockModeling 

all_cpp: $(CPP_EX)


execute_cpp: $(CPP_EX)
	./GBlockModeling
	
# ------------------------------------------------------------

clean :
	/bin/rm -rf *.o *~ *.class
	/bin/rm -rf $(C_EX) $(CX_EX) $(CPP_EX)
	/bin/rm -rf *.mps *.ord *.sos *.lp *.sav *.net *.msg *.log *.clp

# ------------------------------------------------------------
#
# The examples
#

GBModeling: GBModeling.o DataManager.o ColDominant.o ColumnFunctional.o CompleteBlock.o Leg.o ConstraintManager.o Constraints.o LinearConstraints.o Extractor.o Graph.o LinearConstraints.o MultidimensionaIloArray.o NullBlock.o ObjectiveFunctions.o Parameters.o Preprocessing.o RegularBlock.o RowDominant.o RowRegular.o SharedConstraint.o TDDDev.o
	$(CCC) $(CCFLAGS) $(CCLNDIRS) -o GBModeling.o DataManager.o ColDominant.o ColumnFunctional.o CompleteBlock.o Leg.o ConstraintManager.o Constraints.o LinearConstraints.o Extractor.o Graph.o LinearConstraints.o MultidimensionaIloArray.o NullBlock.o ObjectiveFunctions.o Parameters.o Preprocessing.o RegularBlock.o RowDominant.o RowRegular.o SharedConstraint.o TDDDev.o $(CCLNFLAGS)


GBModeling.o: $(EXSRCCPP)/GBModeling.cpp
	$(CCC) -c $(CCFLAGS) $(EXSRCCPP)/GBModeling.cpp -o GBModeling.o

DataManager.o: $(EXSRCCPP)/DataManager.cpp
	$(CCC) -c $(CCFLAGS) $(EXSRCCPP)/DataManager.cpp -o DataManager.o

ColDominant.o: $(EXSRCCPP)/ColDominant.cpp
	$(CCC) -c $(CCFLAGS) $(EXSRCCPP)/ColDominant.cpp -o ColDominant.o

ColumnFunctional.o: $(EXSRCCPP)/ColumnFunctional.cpp
	$(CCC) -c $(CCFLAGS) $(EXSRCCPP)/ColumnFunctional.cpp -o ColumnFunctional.o

CompleteBlock.o: $(EXSRCCPP)/CompleteBlock.cpp
	$(CCC) -c $(CCFLAGS) $(EXSRCCPP)/CompleteBlock.cpp -o CompleteBlock.o

ConstraintManager.o: $(EXSRCCPP)/ConstraintManager.cpp
	$(CCC) -c $(CCFLAGS) $(EXSRCCPP)/ConstraintManager.cpp -o ConstraintManager.o

Constraints.o: $(EXSRCCPP)/Constraints.cpp
	$(CCC) -c $(CCFLAGS) $(EXSRCCPP)/Constraints.cpp -o Constraints.o

Extractor.o: $(EXSRCCPP)/Extractor.cpp
	$(CCC) -c $(CCFLAGS) $(EXSRCCPP)/Extractor.cpp -o Extractor.o

Graph.o: $(EXSRCCPP)/Graph.cpp
	$(CCC) -c $(CCFLAGS) $(EXSRCCPP)/Graph.cpp -o Graph.o

LinearConstraints.o: $(EXSRCCPP)/LinearConstraint.cpp
	$(CCC) -c $(CCFLAGS) $(EXSRCCPP)/LinearConstraints.cpp -o LinearConstraints.o
	
MultidimensionaIloArray.o: $(EXSRCCPP)/MultidimensionaIloArray.cpp
	$(CCC) -c $(CCFLAGS) $(EXSRCCPP)/MultidimensionaIloArray.cpp -o MultidimensionaIloArray.o

NullBlock.o: $(EXSRCCPP)/NullBlock.cpp
	$(CCC) -c $(CCFLAGS) $(EXSRCCPP)/NullBlock.cpp -o NullBlock.o

ObjectiveFunctions.o: $(EXSRCCPP)/ObjectiveFunctions.cpp
	$(CCC) -c $(CCFLAGS) $(EXSRCCPP)/ObjectiveFunctions.cpp -o ObjectiveFunctions.o

Parameters.o: $(EXSRCCPP)/Parameters.cpp
	$(CCC) -c $(CCFLAGS) $(EXSRCCPP)/Parameters.cpp -o Parameters.o

Preprocessing.o: $(EXSRCCPP)/Preprocessing.cpp
	$(CCC) -c $(CCFLAGS) $(EXSRCCPP)/Preprocessing.cpp -o Preprocessing.o

RegularBlock.o: $(EXSRCCPP)/RegularBlock.cpp
	$(CCC) -c $(CCFLAGS) $(EXSRCCPP)/RegularBlock.cpp -o RegularBlock.o

RowDominant.o: $(EXSRCCPP)/RowDominant.cpp
	$(CCC) -c $(CCFLAGS) $(EXSRCCPP)/RowDominant.cpp -o RowDominant.o

RowRegular.o: $(EXSRCCPP)/RowRegular.cpp
	$(CCC) -c $(CCFLAGS) $(EXSRCCPP)/RowRegular.cpp -o RowRegular.o

SharedConstraint.o: $(EXSRCCPP)/SharedConstraint.cpp
	$(CCC) -c $(CCFLAGS) $(EXSRCCPP)/SharedConstraint.cpp -o SharedConstraint.o

TDDDev.o: $(EXSRCCPP)/TDDDev.cpp
	$(CCC) -c $(CCFLAGS) $(EXSRCCPP)/TDDDev.cpp -o TDDDev.o

# Local Variables:
# mode: makefile
# End: