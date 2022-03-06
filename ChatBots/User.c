#include <stdarg.h>
#include <stdlib.h>
#include <stdio.h>
#include "User.h"
#include "New.h"
#include "ChatArray.h"
#include "string.h"

static void *User_ctor(void *_self, va_list *app) {
    struct User *self = _self;
    char *name = va_arg(*app, char*);
    strcpy(self->name, name);
    return self;
}

static void User_type(void *_self,void* _chat) {
    struct User *self = _self;
    Chat* chat = _chat;
    printf("%s: %s\n", self->name, "Hey");
    chat_add(chat, "Hey");
}



static const struct Class _User = {
        sizeof(struct User),
        User_ctor,
        0,
        (void (*)(void *, void *)) User_type
};

const void *User = &_User;

