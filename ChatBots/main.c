#include <stdio.h>
#include "New.h"
#include "ChatArray.h"
#include "Parser.h"
#include "DArray.h"

void destroy(void **item) {
    if (item == NULL) {
        return;
    }
    delete(*item);
}

int main(int argc, char *argv[]) {
    char* filename = argv[1];
    if (filename == NULL) {
        printf("NULL filename\n");
        return -1;
    }
    struct Chat *chat = CreateChat();
    if (chat == NULL) {
        printf("chat can't be created\n");
        return -1;
    }
    void *users = parse_file(filename);
    if (users == NULL) {
        printf("can't parse the file\n");
        return -1;
    }
    size_t users_num = darray_count(users);
    for (size_t i = 0; i < users_num; i++) {
        void **curr_user = ((void **) darray_item(users, i));
        type(*curr_user, chat);
    }
    darray_destroy(users, (void (*)(void *)) destroy);
    DeleteChat(chat);

    return 0;
}