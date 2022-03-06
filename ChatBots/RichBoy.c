#include "RichBoy.h"
#include <stdarg.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <assert.h>
#include "User.h"
#include "RichBoy.h"
#include "Boy.h"
#include "New.h"
#include "ChatArray.h"

#define name(user) (((const struct User *)(user)) -> name)
#define last_line(user) (((struct User *)(user)) -> last_line)

static void *RichBoy_ctor(void *_self, va_list *app)
{

    struct RichBoy *self = ((const struct Class *)User)->ctor(_self, app);

    return self;
}
static const char* message = "I have a supercar";
static const char* key_phrase = "I want a dress";
static const char* new_message = "Of course, baby. I'm the richest boy in the world!";
static void RichBoy_type(void *_self, void* _chat)
{

    struct RichBoy *self = _self;

    Chat* chat = _chat;

    ((const struct Class*)Boy)->type(_self, chat); // type  as a boy

    printf("%s: %s\n", name(self), message);
    chat_add(chat, message);


    if (chat_scan(chat, key_phrase)){
        printf("%s: %s\n", name(self), new_message);
        chat_add(chat, new_message);

    }
}

static const struct Class _RichBoy = {

        sizeof(struct RichBoy),

        RichBoy_ctor,

        0,

        RichBoy_type
};

const void *RichBoy = &_RichBoy;
