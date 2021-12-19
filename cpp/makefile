TARGET = main
BUILD_DIR = build
DEBUG = 1

OPT = -O2
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
-I inc

CPP_FLAGS = $(CPP_INCLUDES) $(OPT) -Wall -MMD -MP -MF"$(@:%.o=%.d)"

ifeq ($(DEBUG), 1)
	CPP_FLAGS += -ggdb
endif

OBJECTS = $(addprefix $(BUILD_DIR)/,$(notdir $(CPP_SOURCES:.cpp=.o)))
vpath %.cpp $(sort $(dir $(CPP_SOURCES)))

all: $(BUILD_DIR)/$(TARGET).elf

$(BUILD_DIR)/$(TARGET).elf: $(OBJECTS) | $(BUILD_DIR)
	@echo ""
	$(CC) $(OBJECTS) -o $@
	@echo ""
	@$(SZ) $@
	@echo ""

$(BUILD_DIR)/%.o: ./src/%.cpp | $(BUILD_DIR)
	$(CC) -c $(CPP_FLAGS) $< -o $@

$(BUILD_DIR):
	mkdir $@
	@echo ""

clean:
	rm -rf $(BUILD_DIR)
