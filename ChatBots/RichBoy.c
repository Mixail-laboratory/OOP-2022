#include "RichBoy.h"
#include <stdarg.h>
#include <stdio.h>
#include "User.h"
#include "Boy.h"
#include "New.h"
#include "ChatArray.h"

#define name(user) (((const struct User *)(user)) -> name)


static void *RichBoy_ctor(void *_self, va_list *app) {
    struct RichBoy *self = ((const struct Class *) User)->ctor(_self, app);
    return self;
}

static const char *defaultMessage = "I have a supercar";
static const char *GirlTrigger = "I want a dress";
static const char *FlirtMessage = "Of course, baby. I'm the richest boy in the world!";

static void RichBoy_type(void *_self, void *_chat) {
    struct RichBoy *self = _self;
    struct Chat *chat = _chat;
    ((const struct Class *) User)->type(_self, chat);
    printf("%s: %s\n", name(self), defaultMessage);
    ChatPush(chat, defaultMessage);
    if (FindPhrase(chat, GirlTrigger)) {
        printf("%s: %s\n", name(self), FlirtMessage);
        ChatPush(chat, FlirtMessage);
    }
}

static const struct Class _RichBoy = {
        sizeof(struct RichBoy),
        RichBoy_ctor,
        NULL,
        RichBoy_type
};

const void *RichBoy = &_RichBoy;
