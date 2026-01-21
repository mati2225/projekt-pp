#include <stdlib.h>
#include <stddef.h>
#include "data.h"

Node* push_back(Node* head, mech_object mechObj) {
    Node* n = calloc(1, sizeof(Node));
    n->mechObj = mechObj;

    if (head == NULL)
        return n;

    Node* p = head;
    while (p->next != NULL) {
        p = p->next;
    }
    p->next = n;
    return head;
}

Node* push_front(Node* head, mech_object mechObj) {
    Node* n = calloc(1, sizeof(Node));
    n->mechObj = mechObj;
    n->next = head;
    return n;
}

Node* free_list(Node* head) {
    Node* p = head;
    while (p != NULL) {
        Node* next = p->next;
        free(p);
        p = next;
    }
    return NULL;
}

void print_list(Node* head) {
    Node* p = head;
    while (p != NULL) {
    }
}

const char* mech_type_to_str(enum mech_type t) {
    switch (t) {
        case SZTURMOWY:             return "SZTURMOWY";
        case WSPARCIA_OGNIOWEGO:    return "WSPARCIA OGNIOWEGO";
        case REKONESANSOWY:         return "REKONESANSOWY";
        case OBRONNY:               return "OBRONNY";
        default:                    return "BRAK";
    }
}

const char* mech_condition_to_str(enum mech_condition c) {
    switch (c) {
        case SPRAWNY:           return "SPRAWNY";
        case WYMAGA_PRZEGLADU:  return "WYMAGA PRZEGLADU";
        case USZKODZONY:        return "USZKODZONY";
        case W_NAPRAWIE:        return "W NAPRAWIE";
        case W_DEMONTAZU:       return "W DEMONTAZU";
        default:                return "NIEZNANY";
    }
}