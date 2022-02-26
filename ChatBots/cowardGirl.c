#include <stdio.h>
#include "cowardGirl.h"
#include "new.h"
#include <string.h>

#define num(p) ((( struct User *)(p)) -> num)
#define name(p) ((( struct User *)(p)) -> name)


static void *CowardGirl_ctor(void *_self, va_list *app) {
    struct CowardGirl *self = ((const struct Class *) Girl)->ctor(_self, app);
    return self;
}

static void CowardGirl_dtor(void *_self) {
    ((const struct Class *) Girl)->dtor(_self);
}

static void CowardGirl_type(const void *_self, struct message *mes) {
    int counter = 0;
    const struct CowardGirl *self = _self;
    mes->current += num(self);
    int size = mes->size;

    printf("%s: ", name(self));
    puts("Hey");
    counter++;
    printf("%s: ", name(self));
    puts("I want a dress.Will somebody buy it for me?");
    message_insert(mes, "Hey");
    message_insert(mes, "I want a dress.Will somebody buy it for me?");

    for (int i = mes->current; i < size; i++) {
        if (strstr(mes->log[i], "rat") && (counter <= 1)) {
            printf("%s: ", name(self));
            puts("AAAAaaa! No! No rats here, pls");
            counter++;
            message_insert(mes, "AAAAaaa! No! No rats here, pls");
        }
    }
    num(self) = counter;
}


static const struct Class _CowardGirl = {
        sizeof(struct CowardGirl),
        CowardGirl_ctor,
        (void *(*)(void *)) CowardGirl_dtor,
        (int (*)(const void *, struct message *)) CowardGirl_type
};

const void *CowardGirl = &_CowardGirl;