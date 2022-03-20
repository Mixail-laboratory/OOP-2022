#include <stdarg.h>
#include <stdio.h>
#include "User.h"
#include "New.h"
#include "ChatArray.h"
#include "string.h"

static void *User_ctor(void *_self, va_list *app) {
    struct User *self = _self;
    strcpy(self->name, va_arg(*app, char*));
    return self;
}

static void User_type(void *_self, void *_chat) {
    struct User *self = _self;
    struct Chat *chat = _chat;
    printf("%s: %s\n", self->name, "Hey");
    ChatPush(chat, "Hey");
}


static const struct Class _User = {
        sizeof(struct User),
        User_ctor,
        NULL,
        (void (*)(void *, void *)) User_type
};

const void *User = &_User;

