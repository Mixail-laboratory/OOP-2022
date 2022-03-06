#include "Boy.h"
#include <stdarg.h>
#include <stdio.h>
#include "User.h"
#include "New.h"
#include "ChatArray.h"

#define name(user) (((const struct User *)(user)) -> name)
#define last_line(user) (((struct User *)(user)) -> last_line)


static void *Boy_ctor(void *_self, va_list *app) {

    struct Boy *self = ((const struct Class *) User)->ctor(_self, app);

    return self;
}

static const char *key_phrase = "I want a dress";
static const char *message = "U r such a girl! R u afraid of rats?";

static void Boy_type(void *_self, void *_chat) {

    struct Boy *self = _self;
    Chat *chat = _chat;

    ((const struct Class *) User)->type(_self, chat); // type hey as user
    if (chat_scan(chat, key_phrase)) {
        printf("%s: %s\n", name(self), message);
        chat_add(chat, message);

    }

}


static const struct Class _Boy = {

        sizeof(struct Boy),

        Boy_ctor,

        0,

        Boy_type
};

const void *Boy = &_Boy;
