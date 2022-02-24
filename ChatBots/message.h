#ifndef CHATBOTS_MESSAGE_H
#define CHATBOTS_MESSAGE_H
struct message {
    int current;
    int size;
    int almem;
    char **log;
};

struct message *message_create();

void message_destroy(struct message *mes);

void message_insert(struct message *mes, char *text);

#endif //CHATBOTS_MESSAGE_H
