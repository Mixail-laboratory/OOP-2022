#include "richBoy.h"
#include "new.h"
#include <string.h>
#include <stdio.h>


#define num(p) ((( struct User *)(p)) -> num)
#define name(p) ((( struct User *)(p)) -> name)

static void *RichBoy_ctor(void *_self, va_list *app) {
    struct RichBoy *self = ((const struct Class *) Boy)->ctor(_self, app);
    return self;
}

static void RichBoy_dtor(void *_self) {
    ((const struct Class *) Boy)->dtor(_self);
}

static void RichBoy_type(const void *_self, struct message *mes) {
    int counter = 0;
    const struct RichBoy *self = _self;
    int size = mes->size;
    mes->current += num(self);

    printf("%s: ", name(self));
    puts("Hey");
    counter++;
    printf("%s: ", name(self));
    puts("I have a supercar");
    message_insert(mes, "Hey");
    message_insert(mes, "I have a supercar");

    for (int i = mes->current; i < size; i++) {
        if ((strstr(mes->log[i], "I want a dress") != NULL) && (counter <= 1)) {
            printf("%s: ", name(self));
            puts("Of course, baby. I'm the richest boy in the world!");
            counter++;
            message_insert(mes, "Of course, baby. I'm the richest boy in the world!");
        }
    }
    num(self) = counter;
}

static const struct Class _RichBoy = {
        sizeof(struct RichBoy),
        RichBoy_ctor,
        (void *(*)(void *)) RichBoy_dtor,
        (int (*)(const void *, struct message *)) RichBoy_type
};

const void *RichBoy = &_RichBoy;