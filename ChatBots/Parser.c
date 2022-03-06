#include "Parser.h"
#include "darray.h"

void *parse_file(const char *filename) {
    {
        if (filename == NULL) {
            printf("parse_file err: NULL filename\n");
            return NULL;
        }

        FILE *file = fopen(filename, "r");
        if (!file) {
            printf("parse_file err: file can't be opened\n");
            return NULL;
        }
        void *users = darray_create(sizeof(void *));
        void **tmp;
        char line[256];
        void *curr_user = NULL;
        if (users == NULL) {
            printf("parse_file err: users arr can't be created\n");
            fclose(file);
            return NULL;
        }
        while (fgets(line, 256, file)) {
            curr_user = parse_line(line);
            if (curr_user == NULL) {
                printf("parse_file warning: %s - incorrect line\n", line);
                continue;
            }
            tmp = darray_add(users);
            *tmp = curr_user;
        }
        fclose(file);
        return users;
    }
}

void *parse_line(const char *line) {
    void *curr_user = NULL;
    char name[256] = {0};
    sscanf(line, "%s", name);


    if (strstr(line, " User")) {
        curr_user = new(User, name);
    } else if (strstr(line, " Boy")) {
        curr_user = new(Boy, name);
    }
    else if (strstr(line, " Girl")){
        curr_user = new(Girl, name);
    }
    else if (strstr(line, " RichBoy")){
        curr_user = new(RichBoy, name);
    }
    else if (strstr(line, " CowardGirl")){
        curr_user = new(CowardGirl, name);
    }
    else {
        printf("parse_line err: incorrect input role\n");
        return NULL;
    }

    return curr_user;


}