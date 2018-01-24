
NAME=abc
SRC_DIR=src
EXM_DIR=example
LIB_DIR=lib
CAFFE_ROOT=/home/gq/Documents/tools/caffe
CUDA_ROOT=/usr/local/cuda


SO=$(LIB_DIR)/lib$(NAME).so

INCLUDES=-Iinclude
INCLUDES+=-I$(CAFFE_ROOT)/include
INCLUDES+=-I$(CAFFE_ROOT)/build/src
INCLUDES+=-I$(CUDA_ROOT)/include
LIBS=-Llib -labc


#SRCS=$(shell find $(SRC_DIR) -name *.cpp)
#OBJS=$(SRCS:%.cpp=%.o)

OBJS=$(patsubst %.cpp,%.o,$(shell find $(SRC_DIR) -name *.cpp))


EXMS=$(patsubst %.cpp,%,$(shell find $(EXM_DIR) -name *.cpp))

all : dash_line $(EXMS)


objs : dash_line $(OBJS)

exms : dash_line $(EXMS)

so : dash_line $(SO)

dash_line :
	@echo ----------------------------------

$(EXMS) : % : %.cpp $(SO)
	g++ -g $< $(LIBS) $(INCLUDES) -o $@

$(SO) : $(OBJS)
	g++ -g -fPIC -shared -o $@ $(OBJS) 

%.o : %.cpp
	g++ -c -g -fPIC $< $(INCLUDES) -o $@

clean: clean_objs clean_sos
	rm -f $(EXMS)

clean_objs :
	find -name "*.o" -type f -delete

clean_sos :
	find -name "*.so" -type f -delete

look: dash_line
	echo $(TEST)
	echo $(EXAMPLES)
	echo $(VPATH)
