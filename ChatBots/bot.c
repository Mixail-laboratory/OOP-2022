#include "bot.h"
#include <stdio.h>
#include <stdlib.h>
#include "user.h"
#include "boy.h"
#include "new.h"
#include "girl.h"
#include "richBoy.h"
#include "cowardGirl.h"
#include <string.h>

char *getName(char *from) {
    int i = 0;
    char *to = malloc(20 * sizeof(char));
    while (from[i] != ' '){
        to[i] = from[i];
        ++i;
    }
    return to;
}

int create_people(char **names, void **people, FILE *f) {
    char buffer[100];
    int num = 0;
    while (fgets(buffer, 100, f)) {

        if (strstr(buffer, " User")) {
            names[num] = getName(buffer);
            people[num] = new(User, names[num]);
            num++;
        }

        if (strstr(buffer, " Boy")){
            names[num] = getName(buffer);
            people[num] = new(Boy, names[num]);
            num++;
        }

        if (strstr(buffer, " Girl")){
            names[num] = getName(buffer);
            people[num] = new(Girl, names[num]);
            num++;
        }

        if (strstr(buffer, " RichBoy")){
            names[num] = getName(buffer);
            people[num] = new(RichBoy, names[num]);
            num++;
        }

        if (strstr(buffer, " CowardGirl")){
            names[num] = getName(buffer);
            people[num] = new(CowardGirl, names[num]);
            num++;
        }
    }
    return num;
}

struct message *logg(char **names, void **people, int size) {
    struct message *mes = message_create();

    for (int k = 0; k < size; k++) {
        type(people[k], mes);
    }

    return mes;
}

void destroy_people(char **names, void **people, struct message *mes, int size) {
    message_destroy(mes);
    for (int k = 0; k < size; k++) {
        delete(people[k]);
    }
    free(people);
    free(names);
}
