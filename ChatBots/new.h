#ifndef CHATBOTS_NEW_H
#define CHATBOTS_NEW_H

#include <stddef.h>
#include <stdarg.h>
#include "message.h"
struct Class {
    size_t size;
    void *(*ctor)(void *self, va_list *app);
    void *(*dtor)(void *self);
    int (*type)(const void *self,struct message * mes);
};

void *new(const void *class, ...);
void delete(void *item);
void type(const void *self,struct message * mes);
#endif //CHATBOTS_NEW_H
