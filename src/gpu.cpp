#include <stdio.h>
#include <cstdint>
#include "GPU.h"

using namespace std;

GPU::GPU(MEM* MEM) {
	mem = MEM;
}

GPU::~GPU() {}