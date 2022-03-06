#include <stddef.h>
#include <string.h>
#include <malloc.h>
#include "darray.h"


struct dArray {
    void *pArr;
    size_t elemSize;
    size_t capacity;
    size_t size;
};

void *darray_create(size_t itemSize) {
    struct dArray *dArr = NULL;
    if (itemSize > 0) {
        dArr = (struct dArray *) malloc(sizeof(struct dArray));
        void *data = malloc(itemSize * 5);
        if (dArr && data) {
            dArr->pArr = data;
            dArr->elemSize = itemSize;
            dArr->capacity = 5;
            dArr->size = 0;
        } else {
            free(dArr);
            free(data);
            dArr = NULL;
        }
    }
    return dArr;
}

size_t darray_count(const void *darray) {
    if (darray) {
        const struct dArray *dArr = darray;
        return dArr->size;
    }
    return INVALID;
}

void darray_destroy(void *darray, void(*destroy)(void *)) {
    if (darray) {
        struct dArray *dArr = darray;
        if (destroy) {
            for (size_t i = 0; i < dArr->size; i++) {
                void *curPtr = (char *) (dArr->pArr) + (dArr->elemSize * i);
                destroy(curPtr);
            }
        }
        free(dArr->pArr);
        free(dArr);
    }
}

void *darray_add(void *darray) {
    void *ptr = NULL;
    if (darray) {
        struct dArray *dArr = darray;
        if (dArr->pArr && dArr->size == dArr->capacity) {
            size_t newMax = dArr->capacity * 2;
            void *newArr = malloc(newMax * dArr->elemSize);
            if (newArr) {
                size_t blockSize = dArr->size * dArr->elemSize;
                memcpy(newArr, dArr->pArr, blockSize);
                free(dArr->pArr);
                dArr->pArr = newArr;
                dArr->capacity = newMax;
            }
        }
        if (dArr->pArr && dArr->size < dArr->capacity) {
            ptr = (char *) dArr->pArr + (dArr->size * dArr->elemSize);
            dArr->size++;
        }
    }
    return ptr;
}

void *darray_item(void *darray, size_t i) {
    void *ptr = NULL;
    if (darray) {
        struct dArray *dArr = darray;
        if (i < dArr->size && dArr->pArr) {
            ptr = (char *) (dArr->pArr) + (dArr->elemSize * i);
        }
    }
    return ptr;
}
