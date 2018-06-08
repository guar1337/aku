# 6he data analysis code
NAME := Mr_Blue_Sky
ELC_dir = /home/guar/aku/eloss
INCLUDES = -I`root-config --incdir` 

SHAREDLIBS = $(addprefix -l, gsl Physics MathCore Core)
CLASSLIST := TOOL dE_E_angle


HEADERS := $(addsuffix .h, $(CLASSLIST) linkdef)

all: ./lib$(NAME).so
LGEN = ./linkdef-gen.sh

ROOTLIBS = `root-config --libdir`

CXX := g++
CPPFLAGS := -Wall -g --std=c++11 -MMD -MP $(INCLUDES)
CXXFLAGS := -O3 -fPIC -g


$(NAME).cpp: $(HEADERS)
	$(info Pre-building $@ with headers $^)
	rootcling  -f $@ -c -p $(INCLUDES) $^ 

./lib$(NAME).so: $(NAME).o $(addsuffix .o,$(CLASSLIST))
	$(CXX) -Wall -L . -L$(ROOTLIBS) $(SHAREDLIBS) -shared -o $@ $^

linkdef.h:
	$(LGEN) $(CLASSLIST) >  $@

#%.o: %.f90
#	$(FC) -c -fPIC -Wall -fdefault-real-8 -o $@ $<

clean:
	@$(RM) -f ./*.o ./*.d ./*~ linkdef.h


.PHONY: new
new:
	@make clean --no-print-directory
	@clear --no-print-directory
	@make --no-print-directory

print:
	@echo $(CPATH)
