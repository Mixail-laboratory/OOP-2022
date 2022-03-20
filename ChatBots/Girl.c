#include <stdarg.h>
#include <stdio.h>
#include "User.h"
#include "Girl.h"
#include "New.h"
#include "ChatArray.h"

#define name(user) (((const struct User *)(user)) -> name)

static void *Girl_ctor(void *_self, va_list *app) {
    struct Girl *self = ((const struct Class *) User)->ctor(_self, app);
    return self;
}

static const char *message = "I want a dress. Will somebody buy it for me?";

static void Girl_type(void *_self, void *_chat) {

    struct Girl *self = _self;
    struct Chat *chat = _chat;
    ((const struct Class *) User)->type(_self, chat);
    printf("%s: %s\n", name(self), message);
    ChatPush(chat, message);

}


static const struct Class _Girl = {
        sizeof(struct Girl),
        Girl_ctor,
        NULL,
        Girl_type
};

const void *Girl = &_Girl;
