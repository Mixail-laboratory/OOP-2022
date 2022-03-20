#include "CowardGirl.h"
#include <stdio.h>
#include "User.h"
#include "Girl.h"
#include "New.h"
#include "ChatArray.h"


#define name(user) (((const struct User *)(user)) -> name)


static void *CowardGirl_ctor(void *_self, va_list *app) {
    struct CowardGirl *self = ((const struct Class *) User)->ctor(_self, app);
    return self;
}


static const char *BoyTrigger = "rat";
static const char *message = "AAAAaaa! No! No rats here, pls";

static void CowardGirl_type(void *_self, void *_chat) {

    struct CowardGirl *self = _self;
    struct Chat *chat = _chat;
    ((const struct Class *) Girl)->type(_self, chat);

    if (FindPhrase(chat, BoyTrigger)) {
        printf("%s: %s\n", name(self), message);
        ChatPush(chat, message);
    }

}


static const struct Class _CowardGirl = {
        sizeof(struct CowardGirl),
        CowardGirl_ctor,
        0,
        CowardGirl_type
};

const void *CowardGirl = &_CowardGirl;
