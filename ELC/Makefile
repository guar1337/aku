# 6He data analysis code


NAME := Eloss


INCLUDES = -I`root-config --incdir`

SHAREDLIBS = $(addprefix -l, gsl Physics MathCore Core)
CLASSLIST := AELC ELC
FORTRAN_FILES = ELOSS
#miss_mass  generator

HEADERS := $(addsuffix .h,  $(CLASSLIST) linkdef)

all: ./lib$(NAME).so

LGEN = ./linkdef-gen.sh

ROOTLIBS = `root-config --libdir`

CXX := g++
FC:= gfortran

CPPFLAGS := -Wall -g --std=c++11 -MMD -MP $(INCLUDES)
CXXFLAGS := -O3 -fPIC -g


$(NAME).cpp: $(HEADERS)
	$(info Pre-building $@ with headers $^)
	rootcling  -f $@ -c -p $(INCLUDES) $^


./lib$(NAME).so: $(NAME).o $(addsuffix .o,$(CLASSLIST) $(FORTRAN_FILES))
	$(CXX) -Wall `pkg-config --cflags gsl` -L . -L$(ROOTLIBS) $(SHAREDLIBS) -shared -o $@ $^

linkdef.h:
	$(LGEN) $(CLASSLIST) >  $@


%.o: %.f90
	$(FC) -c -fPIC -Wall -fdefault-real-8 -o $@ $<

clean:
	$(RM) -f ./*Cint.h ./*Cint.cpp ./*.o ./*.d ./*~ linkdef.h



.PHONY: all clean

print:
	@echo $(CPATH)
