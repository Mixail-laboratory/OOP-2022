#ifndef CHATBOTS_USER_H
#define CHATBOTS_USER_H

struct User {
    const void *class;
    char name[256];
};


extern const void *User;
#endif
