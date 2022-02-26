#include "boy.h"
#include <stdio.h>
#include "boy.h"
#include "new.h"
#include <string.h>


#define num(p) ((( struct User *)(p)) -> num)
#define name(p) ((( struct User *)(p)) -> name)

static void *Boy_ctor(void *_self, va_list *app) {

    struct Boy *self = ((const struct Class *) User)->ctor(_self, app);

    return self;
}

static void Boy_dtor(void *_self) {
    ((const struct Class *) User)->dtor(_self);
}


static void Boy_type(const void *_self,struct message *mes) {

    int counter = 0;
    const struct Boy *self = _self;
    int size = mes->size;
    mes->current += num(self);
    printf("%s: ", name(self));
    puts("Hey!");
    counter++;
    message_insert(mes, "Hey");

    for (int i = mes->current; i < size; i++) {
        if ((strstr(mes->log[i], "I want a dress") != NULL) && (counter <= 1)) {
            printf("%s: ", name(self));
            puts("U r such a girl!R u afraid of rats?");
            counter++;
            message_insert(mes, "U r such a girl!R u afraid of rats?");
        }
    }
    num(self) = counter;
}

static const struct Class _Boy = {
        sizeof(struct Boy),
        Boy_ctor,
        (void *(*)(void *)) Boy_dtor,
        (int (*)(const void *, struct message *)) Boy_type
};


const void *Boy = &_Boy;

