#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "DArray.h"
#include "ChatArray.h"


struct Chat *CreateChat() {
    struct Chat *chat = malloc(sizeof(struct Chat));
    if (chat == NULL) {
        printf("Chat_create err: can't create the chat\n");
        return NULL;
    }
    chat->Array = darray_create(sizeof(char *));
    if (chat->Array == NULL) {
        printf("Chat_create err: can't create the chat array\n");
        free(chat);
        return NULL;
    }
    return chat;
}

void DeleteChat(struct Chat *chat) {
    if (chat == NULL) {
        return;
    }
    darray_destroy(chat->Array, NULL);
    free(chat);
}

int FindPhrase(struct Chat *chat, const char *key_phrase) {
    if (chat == NULL || key_phrase == NULL) {
        printf("FindPhrase err: NULL input\n");
        return 0;
    }
    size_t count = darray_count(chat->Array);

    for (size_t i = 0; i < count; i++) {
        char* curr_phrase = *((char **) darray_item(chat->Array, i));
        if (curr_phrase && scan_phrase(curr_phrase, key_phrase)) {
            return 1;
        }
    }
    return 0;
}

int scan_phrase(const char *phrase, const char *key_word) {
    if (phrase == NULL || key_word == NULL) {
        printf("scan_phrase err: NULL input\n");
        return 0;
    }
    return (strstr(phrase, key_word)) ? 1 : 0;
}

const char* ChatPush(struct Chat *chat, const char *message) {
    if (chat == NULL || message == NULL) {
        printf("Chat_add err: NULL input\n");
        exit(1);
    }
    const char **inserted_value = (const char **) darray_add(chat->Array);
    *inserted_value = message;
    return *inserted_value;
}



