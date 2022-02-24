#include <stdio.h>
#include<stdlib.h>
#include "new.h"

#include "bot.h"


int main(int argc, char **argv) {
    void **people = malloc(sizeof(void *) * 100);
    char **names = malloc(sizeof(char *) * 100);
    FILE *f = fopen("peoples.txt", "r");
    if (f == NULL) {
        return -1;
    }
    int num = create_people(names, people, f);
    struct message *mes = logg(names, people, num);
    destroy_people(names, people, mes, num);
    fclose(f);
    return 0;
}