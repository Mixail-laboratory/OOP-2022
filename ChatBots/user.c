#include <stdarg.h>
#include <stdlib.h>
#include <stdio.h>
#include "user.h"
#include "new.h"
#include "message.h"

static void *User_ctor(void *_self, va_list *app) {
    struct User *self = _self;
    char *name = va_arg(*app, char*);
    self->name = name;
    self->num = 0;
    return self;
}

static void User_type(const void *_self, struct message *mes) {
    struct User const *self = _self;
    mes->current += self->num;
    printf("%s: ", self->name);
    puts("Hey!");
    message_insert(mes, "Hey!");

}

static void User_dtor(const void *_self) {
    struct User const *self = _self;
    free(self->name);
}

static const struct Class _User = {
        sizeof(struct User),
        User_ctor,
        (void *(*)(void *)) User_dtor,
        (int (*)(const void *, struct message *)) User_type
};

const void *User = &_User;
