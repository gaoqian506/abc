
CONFIG_FILE := Makefile.config
ifeq ($(wildcard $(CONFIG_FILE)),)
$(error $(CONFIG_FILE) not found.)
endif
include $(CONFIG_FILE)


CAFFE_CONFIG_FILE := $(CAFFE_ROOT)/Makefile.config
ifeq ($(wildcard $(CONFIG_FILE)),)
$(error $(CAFFE_CONFIG_FILE) not found. See $(CONFIG_FILE).example.)
endif
include $(CAFFE_CONFIG_FILE)



NAME=abc
SRC_DIR=src
EXM_DIR=example
LIB_DIR=lib
CUDA_ROOT=/usr/local/cuda


SO=$(LIB_DIR)/lib$(NAME).so

INCLUDES=-Iinclude
INCLUDES+=-I$(CAFFE_ROOT)/include
INCLUDES+=-I$(CAFFE_ROOT)/build/src
INCLUDES+=-I$(CUDA_ROOT)/include
LIBS=-Llib -labc
FLAGS=-g

ifeq ($(CPU_ONLY), 1)
	FLAGS += -DCPU_ONLY
endif


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
	g++ -g $< $(LIBS) $(INCLUDES) $(FLAGS) -o $@

$(SO) : $(OBJS)
	g++ -g -fPIC -shared $(FLAGS) $(OBJS)  -o $@

%.o : %.cpp
	g++ -c -g -fPIC $< $(FLAGS) $(INCLUDES) -o $@

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
