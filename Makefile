# LLVM_DIR := /home/bill/hdisk/usr/local/llvm
CPP	= clang++ 
CPPOPTS	= -g -Wall -Wextra -pedantic -pedantic-errors -std=c++20
CXXOPTS = # -I$(LLVM_DIR)/include  -fPIC


LINK	= clang++
LINKOPTS= -g -Wall -Wextra -pedantic -std=c++20
# LINKLLVM= -L$(LLVM_DIR)/lib 
LIBS	= -lrt -ldl -lpthread -lm 


OUT	= t6calc 

SOURCE	= numberCalc.cxx \
	Token.cxx \
	Parser.cxx \
	Logger.cxx

OBJECTS	= $(addsuffix .o, $(basename $(SOURCE)))

%.o	: %.cxx
	$(CPP) $(CPPOPTS) $(CXXOPTS) -c $^ -o $@

$(OUT)	: $(OBJECTS)
	$(LINK) $(LINKOPTS) $(OBJECTS) $(LIBS) -o $@

clean	:
	rm -f $(OBJECTS)
	rm -f $(OUT)
	rm -f core*
	rm -f *debug.log
