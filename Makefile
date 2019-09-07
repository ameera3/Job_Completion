# Change the CXX variable assignment at your own risk.
CXX ?= g++ 
CXXFLAGS=-std=c++11 -Wall 
LDFLAGS=-g

all: Job_Completion   

Job_Completion: JobPtrComp.hpp Job.hpp

clean:
	rm -f Job_Completion *.o core* *~

