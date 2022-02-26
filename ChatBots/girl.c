#include "girl.h"
#include <stdio.h>
#include "girl.h"
#include "new.h"

#define num(p) ((( struct User *)(p)) -> num)
#define name(p) ((( struct User *)(p)) -> name)


static void *Girl_ctor(void *_self, va_list *app) {
    struct Girl *self = ((const struct Class *)User)->ctor(_self, app);
    return self;
}
static void Girl_dtor(void *_self) {
    ((const struct Class *)User)->dtor(_self);
}
static void Girl_type(const void * _self,struct message* mes)
{
    int counter = 0;
    const struct Girl *self = _self;
    mes->current += num(self);

        printf("%s: ", name(self));
        puts("Hey");
        counter++;
        printf("%s: ", name(self));
        puts("I want a dress.Will somebody buy it for me?");
        counter++;
        message_insert(mes, "Hey");
        message_insert(mes, "I want a dress.Will somebody buy it for me?");

    num(self) = counter;
}

static const struct Class _Girl = {
        sizeof(struct Girl),
        Girl_ctor,
        (void *(*)(void *)) Girl_dtor,
        (int (*)(const void *, struct message *)) Girl_type
};

const void *Girl = &_Girl;
