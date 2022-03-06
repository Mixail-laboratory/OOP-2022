
#include <stdarg.h>
#include <stdlib.h>
// Äëÿ printf
#include <stdio.h>
#include <stdbool.h>
#include <assert.h>
#include "User.h"
#include "Girl.h"
// Äëÿ struct Class
#include "New.h"
#include "ChatArray.h"

#define name(user) (((const struct User *)(user)) -> name)
#define last_line(user) (((struct User *)(user)) -> last_line)

static void *Girl_ctor(void *_self, va_list *app) {

    struct Girl *self = ((const struct Class *) User)->ctor(_self, app);

    return self;
}

static const char *message = "I want a dress. Will somebody buy it for me?";

static void Girl_type(void *_self, void *_chat) {

    struct Girl *self = _self;

    Chat *chat = _chat;

    ((const struct Class *) User)->type(_self, chat); // type hey as user

    printf("%s: %s\n", name(self), message);
    chat_add(chat, message);

}


static const struct Class _Girl = {
        // Ðàçìåð ñòðóêòóðû äàííûõ îáúåêòà
        sizeof(struct Girl),
        // Óêàçàòåëü íà ôóíêöèþ-êîíñòðóêòîð
        Girl_ctor,
        // Äåñòðóêòîð îòñóòñòâóåò
        0,
        // Óêàçàòåëü íà âèðòóàëüíóþ ôóíêöèþ type
        Girl_type
};

const void *Girl = &_Girl;
