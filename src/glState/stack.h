#pragma once
#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

typedef struct gls_Stack
{
	void* data;
	uint64_t length;
	uint64_t elemSize;
	uint64_t capacity;
} gls_Stack;

void stack_init(gls_Stack* stack, uint64_t elemSize, uint64_t capacity);
void stack_grow(gls_Stack* stack);
void stack_push(gls_Stack* stack, void* data);
void* stack_last(const gls_Stack* stack);
void* stack_index(const gls_Stack* stack, uint64_t index);
void stack_pop(gls_Stack* stack);
void stack_free(gls_Stack* stack);