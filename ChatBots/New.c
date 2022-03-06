#include "New.h"
#include <stdlib.h>

void *new(const void *_class, ...) {
    const struct Class *class = _class;


    void *p = calloc(1, class->size);

    if (p == NULL) {
        return NULL;
    }


    *(const struct Class **) p = class;


    if (class->ctor) {
        va_list ap;


        va_start(ap, _class);


        p = class->ctor(p, &ap);

        // Î÷èùàåì ap
        va_end(ap);
    }


    return p;
}


void delete(void *self) {

    const struct Class **cp = self;


    if (self && *cp && (*cp)->dtor)

        self = (*cp)->dtor(self);


    free(self);
}


void type(void *self, void *chat) {

    const struct Class *const *cp = self;


    if (self && *cp && (*cp)->type) {
        (*cp)->type(self, chat);
    }


}