#ifndef CHATBOTS_CHATARRAY_H
#define CHATBOTS_CHATARRAY_H

struct Chat {
    void *Array;
};

struct Chat *CreateChat();

void DeleteChat(struct Chat *chat);

int FindPhrase(struct Chat *chat, const char *key_phrase);

const char* ChatPush(struct Chat *chat, const char *message);

int scan_phrase(const char *phrase, const char *key_word);

#endif
