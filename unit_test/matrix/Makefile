CXX=g++

TARGET=matrix_wrapper
TARGET_LIB = $(TARGET)$(shell python3-config --extension-suffix)

MATRIX_LIB_PATH=../../src/matrix

CXXFLAGS+=-std=c++17 -O3 -g -Wall -Wno-unused-label -shared -fPIC
CXXFLAGS+=`python3 -m pybind11 --includes`

CXXFLAGS+=-I../../include

LDFLAGS=$(MKL_LDFLAGS) -lm

CSRC=matrix_basic.c \
	matrix_util.c
CXXSRC=pybind.cpp

COBJS=$(CSRC:.c=.o)
CXXOBJS=$(CXXSRC:.cpp=.o)

CDEPEND=$(CSRC:.c=.d)
CXXDEPEND=$(CXXSRC:.cpp=.d)

all: $(TARGET_LIB)
	@$(MAKE) -f matrix_test.mk build

$(TARGET_LIB): $(COBJS) $(CXXOBJS)
	@echo "LD" $@
	@$(CXX) $(CXXFLAGS) $^ $(LDFLAGS) -o $@

-include $(CDEPEND)
-include $(CPPDEPEND)

%.o: $(MATRIX_LIB_PATH)/%.c
	@echo "CXX" $@
	@$(CXX) $(CXXFLAGS) -MMD -MP -c $< -o $@

%.o: %.cpp
	@echo "CXX" $@
	@$(CXX) $(CXXFLAGS) -MMD -MP -c $< -o $@

clean:
	rm -rf $(TARGET_LIB)
	rm -rf $(COBJS)
	rm -rf $(CDEPEND)
	rm -rf $(CXXOBJS)
	rm -rf $(CXXDEPEND)
	@$(MAKE) -f matrix_test.mk clean

.PHONY: all clean
