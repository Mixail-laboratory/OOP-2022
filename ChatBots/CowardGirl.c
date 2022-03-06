#include "CowardGirl.h"
#include <stdarg.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <assert.h>
#include "User.h"
#include "Girl.h"
#include "New.h"
#include "ChatArray.h"


#define name(user) (((const struct User *)(user)) -> name)
#define last_line(user) (((struct User *)(user)) -> last_line)

static void *CowardGirl_ctor(void *_self, va_list *app) {

    struct CowardGirl *self = ((const struct Class *) User)->ctor(_self, app);

    return self;
}

static const char *key_phrase = "rat";
static const char *second_key_phrase = "rats";
static const char *message = "AAAAaaa! No! No rats here, pls";

static void CowardGirl_type(void *_self, void *_chat) {

    struct CowardGirl *self = _self;
    Chat *chat = _chat;
    ((const struct Class *) Girl)->type(_self, chat); // type  as a girl

    if (chat_scan(chat, key_phrase) || chat_scan(chat, second_key_phrase)) {
        printf("%s: %s\n", name(self), message);
        chat_add(chat, message);
    }

}


static const struct Class _CowardGirl = {

        sizeof(struct CowardGirl),

        CowardGirl_ctor,

        0,

        CowardGirl_type
};

const void *CowardGirl = &_CowardGirl;
