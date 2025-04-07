#pragma once
#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>

#define DECLARE_LINKED_LIST(TYPE) \
    typedef struct Node_##TYPE { \
        TYPE data; \
        struct Node_##TYPE* next; \
    } Node_##TYPE; \
    Node_##TYPE* node_##TYPE##_create(TYPE); \
    Node_##TYPE* node_##TYPE##_destroy(Node_##TYPE*); \
    typedef struct { \
        Node_##TYPE* tail; \
        size_t length; \
    } List_##TYPE; \
    List_##TYPE* list_##TYPE##_create(void); \
    void list_##TYPE##_destroy(List_##TYPE*); \
    bool list_##TYPE##_insert(List_##TYPE*, TYPE, size_t); \
    bool list_##TYPE##_append(List_##TYPE*, TYPE); \
    bool list_##TYPE##_remove_at(List_##TYPE*, size_t); \
    bool list_##TYPE##_get(const List_##TYPE*, size_t, TYPE*); \
    size_t list_##TYPE##_length(const List_##TYPE*); \
    void list_##TYPE##_print(const List_##TYPE*, void (*print_fn)(TYPE));

#define IMPLEMENT_LINKED_LIST(TYPE) \
    Node_##TYPE* node_##TYPE##_create(TYPE data) { \
        Node_##TYPE* new_node = malloc(sizeof(Node_##TYPE)); \
        if (!new_node) return NULL; \
        new_node->data = data; \
        new_node->next = NULL; \
        return new_node; \
    } \
    Node_##TYPE* node_##TYPE##_destroy(Node_##TYPE* node) { \
        if (node) free(node); \
        return NULL; \
    } \
    List_##TYPE* list_##TYPE##_create(void) { \
        List_##TYPE* list = malloc(sizeof(List_##TYPE)); \
        if (!list) return NULL; \
        list->tail = NULL; \
        list->length = 0; \
        return list; \
    } \
    void list_##TYPE##_destroy(List_##TYPE* list) { \
        if (!list || !list->tail) return; \
        Node_##TYPE* current = list->tail->next; \
        for (size_t i = 0; i < list->length; ++i) { \
            Node_##TYPE* next = current->next; \
            free(current); \
            current = next; \
        } \
        free(list); \
    } \
    bool list_##TYPE##_insert(List_##TYPE* list, TYPE data, size_t pos) { \
        if (!list || pos > list->length) return false; \
        Node_##TYPE* new_node = node_##TYPE##_create(data); \
        if (!new_node) return false; \
        if (list->length == 0) { \
            new_node->next = new_node; \
            list->tail = new_node; \
        } else if (pos == 0) { \
            new_node->next = list->tail->next; \
            list->tail->next = new_node; \
        } else { \
            Node_##TYPE* current = list->tail->next; \
            for (size_t i = 0; i < pos - 1; ++i) \
                current = current->next; \
            new_node->next = current->next; \
            current->next = new_node; \
            if (pos == list->length) \
                list->tail = new_node; \
        } \
        list->length++; \
        return true; \
    } \
    bool list_##TYPE##_append(List_##TYPE* list, TYPE data) { \
        return list_##TYPE##_insert(list, data, list->length); \
    } \
    bool list_##TYPE##_remove_at(List_##TYPE* list, size_t pos) { \
        if (!list || list->length == 0 || pos >= list->length) return false; \
        Node_##TYPE* to_delete; \
        if (list->length == 1) { \
            to_delete = list->tail; \
            list->tail = NULL; \
        } else if (pos == 0) { \
            to_delete = list->tail->next; \
            list->tail->next = to_delete->next; \
        } else { \
            Node_##TYPE* current = list->tail->next; \
            for (size_t i = 0; i < pos - 1; ++i) \
                current = current->next; \
            to_delete = current->next; \
            current->next = to_delete->next; \
            if (to_delete == list->tail) \
                list->tail = current; \
        } \
        free(to_delete); \
        list->length--; \
        return true; \
    } \
    bool list_##TYPE##_get(const List_##TYPE* list, size_t pos, TYPE* out) { \
        if (!list || !out || pos >= list->length) return false; \
        Node_##TYPE* current = list->tail->next; \
        for (size_t i = 0; i < pos; ++i) \
            current = current->next; \
        *out = current->data; \
        return true; \
    } \
    size_t list_##TYPE##_length(const List_##TYPE* list) { \
        return list ? list->length : 0; \
    } \
    void list_##TYPE##_print(const List_##TYPE* list, void (*print_fn)(TYPE)) { \
        if (!list || !print_fn || list->length == 0) { printf("[]\n"); return; } \
        printf("["); \
        Node_##TYPE* current = list->tail->next; \
        for (size_t i = 0; i < list->length; ++i) { \
            print_fn(current->data); \
            if (i < list->length - 1) printf(", "); \
            current = current->next; \
        } \
        printf("]\n"); \
    }

// Declaración de listas para tipos básicos
DECLARE_LINKED_LIST(int)
DECLARE_LINKED_LIST(char)
DECLARE_LINKED_LIST(float)

#ifdef LINKED_LIST_IMPLEMENTATION
IMPLEMENT_LINKED_LIST(int)
IMPLEMENT_LINKED_LIST(char)
IMPLEMENT_LINKED_LIST(float)
#endif
