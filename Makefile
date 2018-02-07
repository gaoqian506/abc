
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
TEST_DIR=test
LIB_DIR=lib
DOC_DIR=doc
CUDA_ROOT=/usr/local/cuda


SO=$(LIB_DIR)/lib$(NAME).so

INCLUDES=-Iinclude
INCLUDES+=-I$(CAFFE_ROOT)/include
INCLUDES+=-I$(CAFFE_ROOT)/build/src
INCLUDES+=-I$(CUDA_ROOT)/include
LIBS=-Llib -labc -lcaffe -lopencv_core -lopencv_highgui -lopencv_imgproc
LIBS+=-lglog
LIBS+=-L$(CAFFE_ROOT)/build/lib
LIBS+=-Wl,-rpath,lib
LIBS+=-Wl,-rpath,$(CAFFE_ROOT)/build/lib
FLAGS=-pthread -std=c++0x

ifeq ($(CPU_ONLY), 1)
	FLAGS += -DCPU_ONLY
endif

# Debugging
ifeq ($(DEBUG), 1)
	FLAGS += -DDEBUG -g -O0
else
	FLAGS += -DNDEBUG -O2
endif

ifeq ($(OPENCV_VERSION), 3)
	LIBS += -lopencv_imgcodecs
	LIBS += -L/usr/local/lib
endif



HEADERS = $(shell find $(SRC_DIR) -name *.h)
OBJS = $(patsubst %.cpp,%.o,$(shell find $(SRC_DIR) -name *.cpp))
EXMS = $(patsubst %.cpp,%,$(shell find $(EXM_DIR) -name *.cpp))
TESTS = $(patsubst %.cpp,%,$(shell find $(TEST_DIR) -name *.cpp))
PDFS = $(patsubst %.tex,%.pdf,$(shell find $(DOC_DIR) -name *.tex))



all : dash_line $(EXMS) $(TESTS)

objs : dash_line $(OBJS)

exms : dash_line $(EXMS)

so : dash_line $(SO)

pdfs : dash_line $(PDFS)

dash_line :
	@echo ----------------------------------

$(EXMS) : % : %.cpp $(SO)
	g++ $< $(LIBS) $(INCLUDES) $(FLAGS) -o $@

$(TESTS) : % : %.cpp $(SO)
	g++ $< $(LIBS) $(INCLUDES) $(FLAGS) -o $@

$(SO) : $(OBJS)
	g++ -fPIC -shared $(FLAGS) $(OBJS)  -o $@

%.o : %.cpp
	g++ -c -fPIC $< $(FLAGS) $(INCLUDES) -o $@

%.pdf : %.tex %.bib
	# xelatex -output-directory=$(dir $<) $<
	xelatex -output-directory=$(dir $<) $<
	@echo ----------------------------------
	bibtex $(basename $<).aux
	@echo ----------------------------------
	xelatex -output-directory=$(dir $<) $<
	@echo ----------------------------------
	xelatex -output-directory=$(dir $<) $<
	# pdftotext $(basename $<).pdf	

clean: clean_objs clean_sos clean_log clean_aux
	rm -f $(EXMS)
	rm -f $(TESTS)
	# rm -f $(PDFS)

clean_objs :
	find -name "*.o" -type f -delete

clean_sos :
	find -name "*.so" -type f -delete

clean_tex :
	find -name "*.log" -type f -delete
	find -name "*.aux" -type f -delete
	find -name "*.bbl" -type f -delete
	find -name "*.blg" -type f -delete
	find -name "*.pdf" -type f -delete

run_mark :
	./example/mark example/data/mark/mark.config

debug_markdetect :
	gdb ./example/markdetect


run_test : 
	$(foreach test,$(TESTS), $(test))

debug_test :
	$(foreach test,$(TESTS), gdb $(test))


look: dash_line
	@ echo PDFS:
	@ echo $(PDFS)
	@ echo OBJS:
	@ echo $(OBJS)
	@ echo TESTS:
	@ echo $(TESTS)
	@ echo EXMS:
	@ echo $(EXMS)
	@ echo EXMOBJS:
	@ echo $(SO)
	@ echo EXMOBJS:
	@ echo $(SO)

#	echo $(VPATH)
