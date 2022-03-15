#include <stdlib.h>
#include <assert.h>
struct Node {
    void *data;
    struct Node *next;
};

struct LinkedList {
    size_t itemSize;
    size_t listSize;
    struct Node *head;
};

//Создать новый пустой односвязный список. Размер элемента -- itemSize байт.
void *slist_create(size_t itemSize) {
    if (itemSize == 0)
        return NULL;
    struct LinkedList *this = malloc(sizeof(struct LinkedList));
    if (this == NULL)
        return NULL;
    this->itemSize = itemSize;
    this->head = NULL;
    this->listSize = 0;
    return this;
}

//Количество элементов в списке. В случае, если slist равен NULL, возвращает INVALID константу.
size_t slist_count(const void *slist) {
    if (slist == NULL)
        return INVALID;
    const struct LinkedList *this = slist;
    return this->listSize;

}

static void *createNode(size_t itemSize) {
    struct Node *currNode = malloc(sizeof(struct Node));
    if (currNode == NULL) {
        return NULL;
    }
    currNode->data = malloc(itemSize);
    if (currNode->data == NULL) {
        free(currNode);
        return NULL;
    }
    currNode->next = NULL;
    return currNode;

}

static void destroyNodes(void *linkedList, void (*destroy)(void *)) {
    struct LinkedList *this = linkedList;
    struct Node *currNode = this->head;
    struct Node *next;
    if (this->listSize == 0) {
        return;
    }

    for (size_t i = 0; i < this->listSize; ++i) {
        if (destroy != NULL && currNode->data != NULL) {
            destroy(currNode->data);
        }
        next = currNode->next;
        free(currNode->data);
        free(currNode);
        currNode = next;
    }

    this->head = NULL;
}

//Удалить существующий односвязный список. Если указана функция destroy, то вызвать её для каждого удаляемого элемента.
void slist_destroy(void *slist, void (*destroy)(void *)) {
    if (slist == NULL)
        return;
    struct LinkedList *this = slist;
    destroyNodes(this, destroy);
    free(this);
}

//Инициализировать односвязный список новыми параметрами.
// Если slist содержит элементы, то сначала удалить все элементы,
// потом инициализировать односвязный список с учетом новых параметров. Размер элемента -- itemSize байт.
// Если указана функция destroy, то вызвать её для каждого удаляемого элемента.
void *slist_init(void *slist, size_t itemSize, void (*destroy)(void *)) {
    if ((slist == NULL) || (itemSize == 0))
        return NULL;
    struct LinkedList *this = slist;
    if (this->listSize == 0) {
        this->itemSize = itemSize;
        return this;
    }
    destroyNodes(this, destroy);
    free(this);
    this = slist_create(itemSize);
    return this;
}

//Удалить все элементы из односвязного списка. Если указана функция destroy, то вызвать её для каждого удаляемого элемента.
void slist_clear(void *slist, void (*destroy)(void *)) {
    struct LinkedList *this = slist;
    if (this == NULL)
        return;
    destroyNodes(this, destroy);
    this->listSize = 0;
}

//Идентификатор, получаемый при попытке обратиться к элементу за пределами списка.
size_t slist_stop(const void *slist) {
    return (size_t) NULL;
}

void *slist_item(void *slist, size_t i) {
    if (slist == NULL)
        return NULL;
    const struct LinkedList *this = slist;
    if (this->listSize <= i)
        return NULL;
    struct Node *currNode = this->head;
    for (size_t j = 0; j < i; ++j) {
        if (currNode == NULL)
            return NULL;
        currNode = currNode->next;
    }
    return currNode->data;
}

//Добавить элемент в голову односвязного списка.
// В случае успеха, функция возвращает указатель на добавленный элемент, иначе -- NULL
void *slist_prepend(void *slist) {
    if (slist == NULL)
        return NULL;
    struct LinkedList *this = slist;
    struct Node *newHead = createNode(this->itemSize);
    if (newHead == NULL)
        return NULL;
    if (this->listSize != 0) {
        newHead->next = this->head;
    }
    this->head = newHead;
    assert(this->head == newHead);
    this->listSize++;
    return this->head->data;
}

///slist_remove -- Удалить элемент из головы односвязного списка.
///Если указана функция destroy, то вызвать её для удаляемого элемента.
void slist_remove(void *slist, void (*destroy)(void *)) {
    if (slist == NULL)
        return;
    struct LinkedList *this = slist;
    if (this->listSize == 0)
        return;
    if (destroy) {
        destroy(this->head->data);
    }
    free(this->head->data);
    if (this->head->next) {
        struct Node *newHead = this->head->next;
        free(this->head);
        this->head = newHead;
    } else {
        free(this->head);
    }
    this->listSize--;
}

//Получить указатель на элемент списка по его идентификатору.
void *slist_current(const void *slist, size_t item_id) {
    if (slist == NULL)
        return NULL;
    const struct LinkedList *this = slist;
    if ((item_id == INVALID) || (item_id == slist_stop(this)))
        return NULL;
    struct Node *currNode = (struct Node *) item_id;
    return currNode->data;
}

//Идентификатор для первого элемента из односвязного списка. Идентификатор может стать невалидным при модификации списка.
size_t slist_first(const void *slist) {
    if (slist == NULL)
        return slist_stop(slist);
    const struct LinkedList *this = slist;
    if (this->listSize == 0)
        return slist_stop(slist);
    return (size_t) this->head;
}

size_t slist_next(const void *slist, size_t item_id) {
    if (slist == NULL)
        return slist_stop(slist);
    const struct LinkedList *this = slist;
    if ((item_id == INVALID) || (item_id == slist_stop(slist)) ||
        (this->listSize == 0))
        return slist_stop(this);
    struct Node const *currNode = (struct Node const *) (item_id);
    if (currNode == NULL || currNode->next == NULL)
        return slist_stop(this);
    return (size_t) currNode->next;
}

//Вставка нового элемента списка после указанного по идентификатору.
// Когда список пустой, для успешной вставки элемента в качестве item_id должен указываться идентификатор,
// возвращаемый функцией slist_stop. В остальных случаях, item_id должен однозначно соответствовать элементу списка.
// В случае успеха, функция возвращает указатель на вставленный элемент, иначе -- NULL.
void *slist_insert(void *slist, size_t item_id) {
    if (slist == NULL || item_id == INVALID)
        return NULL;
    struct LinkedList *this = slist;
    if (this->listSize == 0)
        return slist_prepend(slist);
    if (item_id == slist_stop(slist))
        return NULL;
    struct Node *currNode = (struct Node *) (item_id);
    struct Node *new_node = createNode(this->itemSize);
    if (new_node == NULL)
        return NULL;
    if (currNode->next != NULL) {
        new_node->next = currNode->next;
    }
    currNode->next = new_node;
    this->listSize++;
    return new_node->data;
}

void slist_erase(void *slist, size_t item_id, void(*destroy)(void *)) {
    if ((slist == NULL) || (item_id == slist_stop(slist))) {
        return;
    }

    struct LinkedList *this = slist;
    struct Node *remNode = (struct Node *) item_id;
    if (remNode == this->head) {
        slist_remove(this, destroy);
        return;
    }
    struct Node *currNode = (struct Node *) slist_first(this);
    for (size_t item = slist_first(slist); item != item_id; item = slist_next(slist, item)) {
        if (currNode == remNode)
            break;
        currNode = (struct Node *) (item);
    }
    currNode->next = remNode->next;
    if (destroy != NULL)
        destroy(remNode->data);
    free(remNode);
    this->listSize--;

}
