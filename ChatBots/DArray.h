#pragma once

#include <stdbool.h> // bool
#include <stddef.h>  // size_t

static const size_t INVALID = ~((size_t)0);

void* darray_create(size_t itemSize);
void darray_destroy(void* darray, void(*destroy)(void*));



size_t darray_count(const void* darray);
void* darray_item(void* darray, size_t i);
void* darray_add(void* darray);
