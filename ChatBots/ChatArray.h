#ifndef CHATBOTS_CHATARRAY_H
#define CHATBOTS_CHATARRAY_H
#include <stdlib.h>
typedef struct {
    void* arr;
} Chat;

Chat* chat_create();

void chat_destroy(Chat* chat);

int chat_scan(Chat* chat, const char* key_phrase);

int chat_add(Chat* chat, const char* message);

int scan_phrase(const char* phrase, const char* key_word);

#endif //CHATBOTS_CHATARRAY_H
