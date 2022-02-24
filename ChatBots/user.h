#ifndef CHATBOTS_USER_H
#define CHATBOTS_USER_H
struct User {
    const void *class;
    int num;
    char *name;
};
extern const void *User;
#endif //CHATBOTS_USER_H
