#pragma once
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdint.h>

#include "../glState/stack.h"
#include "../glState/glState.h"

gls_Stack obj_readVerts(const char* filename);