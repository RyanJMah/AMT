SHELL = bash

TARGET = sp-lib
BUILD_DIR = build
LIB_DIR = ../lib
DEBUG = 1

OPT = -O0
OS = linux

ifeq ($(OS), linux)
	CC = g++ -std=c++17
else ifeq ($(OS), macos)
	CC = g++-11 -std=c++17
endif

CP = objcopy
SZ = size

CPP_SOURCES = $(wildcard src/*.cpp)

CPP_INCLUDES = \
-I inc \
-I /usr/local/include \
-I /usr/include/python3.8

CPP_FLAGS = $(CPP_INCLUDES) $(OPT) -fPIC -Wall -MMD -MP -MF"$(@:%.o=%.d)"

ifeq ($(DEBUG), 1)
	CPP_FLAGS += -ggdb
endif

BOOST_PY_VER = 38
BOOST_LIB = /usr/lib/x86_64-linux-gnu

PY_VER = 3.8
PY_LIB = /usr/lib/python$(PY_VER)

LIBS = \
-l boost_python$(BOOST_PY_VER) \
-l python$(PY_VER)
# -L /usr/include/boost/python -l boost_python-3.8

OBJECTS = $(addprefix $(BUILD_DIR)/,$(notdir $(CPP_SOURCES:.cpp=.o)))
vpath %.cpp $(sort $(dir $(CPP_SOURCES)))

all: binaries distribute

binaries: $(BUILD_DIR)/$(TARGET).so

$(BUILD_DIR)/$(TARGET).so: $(OBJECTS) | $(BUILD_DIR)
	@echo ""
	$(CC) -shared $(OBJECTS) $(LIBS) -o $@
	@echo ""
	@$(SZ) $@
	@echo ""

$(BUILD_DIR)/%.o: ./src/%.cpp | $(BUILD_DIR)
	$(CC) -c $(CPP_FLAGS) $< -o $@

$(BUILD_DIR):
	mkdir $@
	@echo ""

distribute: $(BUILD_DIR)/$(TARGET).so
	cp $(BUILD_DIR)/$(TARGET).so $(LIB_DIR)

clean:
	rm -rf $(BUILD_DIR)
	rm $(LIB_DIR)/$(TARGET).so
