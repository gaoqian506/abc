

INCLUDES=-Iinclude
SRC_DIR=src
EXM_DIR=example


#SRCS=$(shell find $(SRC_DIR) -name *.cpp)
#OBJS=$(SRCS:%.cpp=%.o)

OBJS=$(patsubst %.cpp,%.o,$(shell find $(SRC_DIR) -name *.cpp))

EXMS=$(patsubst %.cpp,%,$(shell find $(EXM_DIR) -name *.cpp))



objs : dash_line $(OBJS)

exms : dash_line $(EXMS)

dash_line :
	@echo ----------------------------------

$(EXMS) : % : %.cpp $(OBJS)
	g++ -g $< $(OBJS) $(INCLUDES) -o $@

%.o : %.cpp
	g++ -c -g $< $(INCLUDES) -o $@

clean: clean_objs

clean_objs :
	find -name "*.o" -type f -delete

look:
	echo $(OBJS)
	echo $(EXAMPLES)
