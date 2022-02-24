#ifndef CHATBOTS_BOT_H
#define CHATBOTS_BOT_H

#include<stdio.h>
#include "message.h"

char *getName(char *from);

int create_people(char **names, void **people, FILE *f);

struct message *logg(char **names, void **people, int size);

void destroy_people(char **names, void **people, struct message *mes, int size);

#endif //CHATBOTS_BOT_H
