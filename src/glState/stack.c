#include "stack.h"

void stack_init(gls_Stack* stack, uint64_t elemSize, uint64_t capacity)
{
	stack->elemSize = elemSize;
	stack->capacity = capacity;
	stack->data = malloc(stack->elemSize * stack->capacity);
	stack->length = 0;
}

void stack_grow(gls_Stack* stack)
{
	stack->capacity *= 2;
	void* ptr = realloc(stack->data, stack->capacity * stack->elemSize);
	if (ptr)
		stack->data = ptr;
	else
		stack_free(stack);
}

void stack_push(gls_Stack* stack, void* data)
{
	if (stack->length + 1 >= stack->capacity)
		stack_grow(stack);

	memcpy_s(((uint8_t*)stack->data + (stack->length * stack->elemSize)),
		stack->elemSize, data, stack->elemSize);
	stack->length++;
}

void* stack_last(const gls_Stack* stack)
{
	return stack_index(stack, stack->length - 1);
}

void* stack_index(const gls_Stack* stack, uint64_t index)
{
	return (uint8_t*)stack->data + (index * stack->elemSize);
}

void stack_pop(gls_Stack* stack)
{
	if (stack->length > 0)
		stack->length--;
}

void stack_free(gls_Stack* stack)
{
	free(stack->data);
	stack->data = NULL;
	stack->capacity = 0;
	stack->elemSize = 0;
	stack->length = 0;
}
