CPP_FILES := $(wildcard source/*.cpp)
OBJ_FILES := $(addprefix obj/,$(notdir $(CPP_FILES:.cpp=.o)))
LD_FLAGS := 
CC_FLAGS :=

VGBC: $(OBJ_FILES)
   gcc $(LD_FLAGS) -o $@ $^

obj/%.o: src/%.cpp
   gcc $(CC_FLAGS) -c -o $@ $<