#ifndef CHATBOTS_NEW_H
#define CHATBOTS_NEW_H

#include <stddef.h>
#include <stdarg.h>


struct Class {

    size_t size;


    void *(*ctor)(void *self, va_list *app);

    void *(*dtor)(void *self);

    void (*type)(void *self, void *chat);
};

void *new(const void *class, ...);

void delete(void *item);

void type(void *self, void *chat);

#endif
