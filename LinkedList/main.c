#include <assert.h>
#include <math.h>
#include <stdlib.h>
#include "slist.h"


int main(int argc, char *argv[]) {
    //Создаем односвязный список с элементами типа Value;
    void *slist = slist_create(sizeof(int *));

    assert(0 == slist_count(slist));
    assert(slist_stop(slist) == slist_first(slist));

    //Создаем объект для односвязного списка
    slist = slist_init(slist, sizeof(char), NULL);
    char array = 'f';
    slist_insert(slist, (size_t) array);
    //Добавляем новый элемент в односвязный список
    slist_erase(slist, (size_t)(slist_first(slist)), NULL);
    slist_destroy(slist, NULL);

    return 0;
}