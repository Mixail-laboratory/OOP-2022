#include <stdio.h>
#include "User.h"
#include "Boy.h"
#include "New.h"
#include "ChatArray.h"

#define name(user) (((const struct User *)(user)) -> name)



static void *Boy_ctor(void *_self, va_list *app) {
    struct Boy *self = ((const struct Class *) User)->ctor(_self, app);
    return self;
}

static const char *GirlTrigger = "I want a dress";
static const char *FlirtMessage = "U r such a girl! R u afraid of rats?";

static void Boy_type(void *_self, void *_chat) {

    struct Boy *self = _self;
    struct Chat *chat = _chat;

    ((const struct Class *) User)->type(_self, chat);
    if (FindPhrase(chat, GirlTrigger)) {
        printf("%s: %s\n", name(self), FlirtMessage);
        ChatPush(chat, FlirtMessage);
    }

}


static const struct Class _Boy = {
        sizeof(struct Boy),
        Boy_ctor,
        NULL,
        Boy_type
};

const void *Boy = &_Boy;
