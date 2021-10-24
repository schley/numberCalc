CPP	= clang++ 
CPPOPTS	= -g -Wall -Wextra -pedantic -pedantic-errors -std=c++20
CXXOPTS = 


LINK	= clang++
LINKOPTS= 
LIBS	= 


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
