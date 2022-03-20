#include <stddef.h>
#include <string.h>
#include <malloc.h>
#include "DArray.h"


struct dArray {
    void *Arr;
    size_t itemSize;
    size_t capacity;
    size_t size;
};

void *darray_create(size_t itemSize) {

    if (itemSize == 0) {
        return NULL;
    }
    struct dArray *this = (struct dArray *) malloc(sizeof(struct dArray));
    void *data = malloc(itemSize * 5);
    if (this && data) {
        this->Arr = data;
        this->itemSize = itemSize;
        this->capacity = 5;
        this->size = 0;
    } else {
        free(this);
        free(data);
    }

    return this;
}

size_t darray_count(const void *darray) {
    if (darray == NULL) {
        return INVALID;
    }
    const struct dArray *this = darray;
    return this->size;
}

void darray_destroy(void *darray, void(*destroy)(void *)) {
    if (darray == NULL) {
        return;
    }
    struct dArray *this = darray;
    if (destroy) {
        for (size_t i = 0; i < this->size; i++) {
            void *curPtr = (char *) (this->Arr) + (this->itemSize * i);
            destroy(curPtr);
        }
    }
    free(this->Arr);
    free(this);

}

void *darray_add(void *darray) {

    if (darray == NULL) {
        return NULL;
    }
    struct dArray *this = darray;
    if (this->Arr && this->size == this->capacity) {
        size_t newMax = this->capacity * 2;
        void *newArr = malloc(newMax * this->itemSize);
        if (newArr) {
            size_t blockSize = this->size * this->itemSize;
            memcpy(newArr, this->Arr, blockSize);
            free(this->Arr);
            this->Arr = newArr;
            this->capacity = newMax;
        }
    }
    if (this->Arr && this->size < this->capacity) {
        void *ptr = (char *) this->Arr + (this->size * this->itemSize);
        this->size++;
        return ptr;
    }

    return NULL;
}

void *darray_item(void *darray, size_t i) {

    if (darray == NULL) {
        return NULL;
    }
    struct dArray *this = darray;
    if (i < this->size && this->Arr) {
        void *ptr = (char *) (this->Arr) + (this->itemSize * i);
        return ptr;
    }

    return NULL;
}
