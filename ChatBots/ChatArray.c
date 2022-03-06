#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "darray.h"
#include "ChatArray.h"


Chat *chat_create() {
    Chat *chat = malloc(sizeof(Chat));
    if (chat == NULL) {
        printf("chat_create err: can't create the chat\n");
        return NULL;
    }
    chat->arr = darray_create(sizeof(char *));
    if (chat->arr == NULL) {
        printf("chat_create err: can't create the chat array\n");
        free(chat);
        return NULL;
    }
    return chat;
}

void chat_destroy(Chat *chat) {
    if (chat == NULL) {
        return;
    }
    darray_destroy(chat->arr, NULL);
    free(chat);
}

int chat_scan(Chat *chat, const char *key_phrase) {
    if (chat == NULL || key_phrase == NULL) {
        printf("chat_scan err: NULL input\n");
        return false;
    }
    size_t count = darray_count(chat->arr);
    char *curr_phrase = NULL;

    for (size_t i = 0; i < count; i++) {
        curr_phrase = *((char **) darray_item(chat->arr, i));
        if (curr_phrase != NULL && scan_phrase(curr_phrase, key_phrase)) {
            return true;
        }
    }
    return false;
}

int scan_phrase(const char *phrase, const char *key_word) {
    if (phrase == NULL || key_word == NULL) {
        printf("scan_phrase err: NULL input\n");
        return false;
    }
    const char *allowed_followed_symbols = " \t.?!\n";
    char *curr_scan_ptr = strstr(phrase, key_word);
    size_t key_word_len = strlen(key_word);
    while (curr_scan_ptr) {
        char curr_followed_symbol = curr_scan_ptr[key_word_len];
        if (strchr(allowed_followed_symbols, curr_followed_symbol) || curr_followed_symbol == 0) {
            return true;
        }
        curr_scan_ptr = strstr(curr_scan_ptr + key_word_len, key_word);
    }
    return false;
}

int chat_add(Chat *chat, const char *message) {
    if (chat == NULL || message == NULL) {
        printf("chat_add err: NULL input\n");
        return false;
    }

    const char **inserted_value = (const char **) darray_add(chat->arr);
    if (inserted_value == NULL) {
        printf("chat_add err: can't add new element\n");
        return false;
    }
    *inserted_value = message;
    return true;
}



