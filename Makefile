

INCLUDES=-Iinclude
SRC_DIR=src

SRCS=$(shell find $(SRC_DIR) -name *.cpp)
OBJS=$(SRCS:%.cpp=%.o)



objs : dash_line $(OBJS)

dash_line :
	@echo ----------------------------------

%.o : %.cpp
	g++ -c -g $< $(INCLUDES) -o $@

clean: clean_objs

clean_objs :
	find -name "*.o" -type f -delete

look:
	echo $(SRCS)
	echo $(OBJS)
