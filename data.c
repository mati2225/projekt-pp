#include <stdlib.h>
#include <stddef.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "data.h"

List global_list;

void init_list(List* list) {
    list->head = NULL;
    list->tail = NULL;
}

Node* create_node(mech_object mechObj) {
    Node* n = (Node*) malloc(sizeof(Node));
    if (n == NULL) return NULL;

    n->mechObj = mechObj;
    n->next = NULL;
    n->prev = NULL;
    return n;
}

void push_front(List* list, mech_object mechObj) {
    Node* n = create_node(mechObj);
    if (n == NULL) return;

    n->prev = NULL;
    n->next = list->head;

    if (list->head != NULL) {
        list->head->prev = n;
    } else {
        list->tail = n;
    }

    list->head = n;
}

void push_back(List* list, mech_object mechObj) {
    Node* n = create_node(mechObj);
    if (n == NULL) return;

    n->next = NULL;
    n->prev = list->tail;

    if (list->tail != NULL) {
        list->tail->next = n;
    } else {
        list->head = n;
    }

    list->tail = n;
}

void print_forward(const List* list) {
    const Node* p = list->head;
    int index = 0;
    while (p != NULL) {
        index++;
        print_mech_object(index, p->mechObj);
        p = p->next;
    }
}

void print_backward(const List* list) {
    const Node* p = list->tail;
    int index = 0;
    while (p != NULL) {
        index++;
        print_mech_object(index, p->mechObj);
        p = p->prev;
    }
}

void print_mech_object(int index, mech_object mechObj) {
    const char* type_converted = mech_type_to_str(mechObj.type);
    const char* condition_converted = mech_condition_to_str(mechObj.condition);
    printf("[%d] %s: [Klasa: %s | Moc reaktora: %d MW | Pancerz: %d | Amunicja: %d | Pilot: %s | Stan: %s]\n", index, mechObj.model, type_converted, mechObj.reactor_power, mechObj.armor_health, mechObj.ammo, mechObj.assigned_pilot, condition_converted);
}

void free_list(List* list) {
    Node* p = list->head;
    while (p != NULL) {
        Node* next = p->next;
        free(p);
        p = next;
    }
    list->head = NULL;
    list->tail = NULL;
}

Node* find_first(const List* list, mech_object mechObj) {
    Node* p = list->head;
    while (p != NULL) {
        if (compare_objects_by_model(p->mechObj, mechObj)) return p;
        p = p->next;
    }
    return NULL;
}

Node* find_first_single(const List* list, mech_object mechObj) {
    Node* p = list->head;
    while (p != NULL) {
        if (partial_match_single(p->mechObj, mechObj)) return p;
        p = p->next;
    }
    return NULL;
}

void remove_node(List* list, Node* node) {
    if (node == NULL) return;

    if (node->prev != NULL) {
        node->prev->next = node->next;
    } else {
        list->head = node->next;
    }

    if (node->next != NULL) {
        node->next->prev = node->prev;
    } else {
        list->tail = node->prev;
    }

    free(node);
}

int remove_first(List* list, mech_object mechObj) {
    Node* node = find_first(list, mechObj);
    if (node == NULL) return 0;

    remove_node(list, node);
    return 1;
}

int remove_first_single(List* list, mech_object mechObj) {
    Node* node = find_first_single(list, mechObj);
    if (node == NULL) return 0;

    remove_node(list, node);
    return 1;
}

int remove_exact(List* list, mech_object mechObj) {
    Node* p = list->head;
    int c = 0;

    while (p != NULL) {
        Node* next = p->next;

        if (compare_objects_by_model(p->mechObj, mechObj)) {
            remove_node(list, p);
            c++;
        }

        p = next;
    }

    return c;
}

int remove_all_single(List* list, mech_object mechObj) {
    int count = 0;
    Node* p = list->head;

    while (p != NULL) {
        Node* next = p->next;

        if (partial_match_single(p->mechObj, mechObj)) {
            remove_node(list, p);
            count++;
        }

        p = next;
    }

    return count;
}

int count_elements(List* list) {
    int count = 0;
    Node* p = list->head;
    while (p != NULL) {
        count++;
        p = p->next;
    }
    return count;
}

int list_by_model(List* list, const char* model) {
    Node* p = list->head;
    int count = 0;
    while (p != NULL) {
        if (strcmp(p->mechObj.model, model) == 0 || strstr(p->mechObj.model, model) != NULL) {
            count++;
            print_mech_object(count, p->mechObj);
        }
        p = p->next;
    }
    return count;
}

mech_object* find_by_exact_model(List* list, const char* model) {
    Node* p = list->head;
    while (p != NULL) {
        if (strcmp(p->mechObj.model, model) == 0) {
            return &p->mechObj;
        }
        p = p->next;
    }
    return NULL;
}

mech_object* list_to_array(List* list, size_t* out_size) {
    Node* head = list->head;
    if (head == NULL || out_size == NULL) {
        return NULL;
    }

    size_t size = (size_t)count_elements(list);
    mech_object* array = malloc(size * sizeof(mech_object));
    if (array == NULL) {
        return NULL;
    }

    Node* cur = head;
    for (size_t i = 0; i < size; i++) {
        array[i] = cur->mechObj;
        cur = cur->next;
    }

    *out_size = size;
    return array;
}

bool compare_objects_by_model(const mech_object a, const mech_object b) {
    int model = strcmp(a.model, b.model);
    return (model == 0);
}

bool partial_match_single(const mech_object a, const mech_object b) {
    int pilot = strcmp(a.assigned_pilot, b.assigned_pilot);
    return (pilot == 0) || a.type == b.type || a.reactor_power == b.reactor_power || a.armor_health == b.armor_health || a.ammo == b.ammo || a.condition == b.condition;
}

List* filter_by_reactor_power(List* list, int threshold) {
    if (list == NULL) return NULL;

    List* filtered = malloc(sizeof(List));
    if (filtered == NULL) return NULL;

    filtered->head = NULL;
    filtered->tail = NULL;

    for (Node* p = list->head; p != NULL; p = p->next) {
        if (p->mechObj.reactor_power >= threshold) {
            push_back(filtered, p->mechObj);
        }
    }

    return filtered;
}

List* filter_by_armor(List* list, int threshold) {
    if (list == NULL) return NULL;

    List* filtered = malloc(sizeof(List));
    if (filtered == NULL) return NULL;

    filtered->head = NULL;
    filtered->tail = NULL;

    for (Node* p = list->head; p != NULL; p = p->next) {
        if (p->mechObj.armor_health >= threshold) {
            push_back(filtered, p->mechObj);
        }
    }

    return filtered;
}

List* filter_by_ammo(List* list, int threshold) {
    if (list == NULL) return NULL;

    List* filtered = malloc(sizeof(List));
    if (filtered == NULL) return NULL;

    filtered->head = NULL;
    filtered->tail = NULL;

    for (Node* p = list->head; p != NULL; p = p->next) {
        if (p->mechObj.ammo >= threshold) {
            push_back(filtered, p->mechObj);
        }
    }

    return filtered;
}

List copy_list(const List *src) {
    List dst = { NULL, NULL };

    for (Node *n = src->head; n; n = n->next) {
        Node *newNode = create_node(n->mechObj);

        if (!dst.head) {
            dst.head = dst.tail = newNode;
        } else {
            dst.tail->next = newNode;
            newNode->prev = dst.tail;
            dst.tail = newNode;
        }
    }
    return dst;
}

List* copy_list_ptr(const List* list) {
    if (list == NULL) return NULL;

    List* copy = malloc(sizeof(List));
    if (!copy) return NULL;

    copy->head = NULL;
    copy->tail = NULL;

    for (Node* p = list->head; p != NULL; p = p->next) {
        Node* n = malloc(sizeof(Node));
        if (!n) continue;

        n->mechObj = p->mechObj;
        n->next = NULL;
        n->prev = copy->tail;

        if (copy->tail)
            copy->tail->next = n;
        else
            copy->head = n;

        copy->tail = n;
    }

    return copy;
}

Node* split(Node *head, int n) {
    while (--n && head)
        head = head->next;

    if (!head)
        return NULL;

    Node *second = head->next;
    head->next = NULL;

    if (second)
        second->prev = NULL;

    return second;
}

int alpha_case_compare(const char *s1, const char *s2) {
    while (*s1 && *s2) {
        char c1 = tolower((unsigned char)*s1);
        char c2 = tolower((unsigned char)*s2);
        if (c1 != c2)
            return c1 - c2;
        if (*s1 != *s2)
            return *s2 - *s1;
        s1++;
        s2++;
    }
    return *s1 - *s2;
}

Node* merge(Node *a, Node *b, Node **outTail) {
    Node *head = NULL, *curr = NULL;

    while (a && b) {
        Node *next;
        if (alpha_case_compare(a->mechObj.model, b->mechObj.model) <= 0) {
            next = a; a = a->next;
        } else {
            next = b; b = b->next;
        }

        next->prev = curr;
        next->next = NULL;

        if (!head) head = next;
        else curr->next = next;

        curr = next;
    }

    Node *rest = a ? a : b;
    while (rest) {
        Node *next = rest;
        rest = rest->next;

        next->prev = curr;
        next->next = NULL;

        if (!head) head = next;
        else curr->next = next;

        curr = next;
    }

    *outTail = curr;
    return head;
}

void merge_sort_in_place(List *list) {
    int n = count_elements(list);
    if (n < 2) return;

    for (int size = 1; size < n; size *= 2) {
        Node *curr = list->head;
        Node *newHead = NULL;
        Node *newTail = NULL;

        while (curr) {
            Node *left = curr;
            Node *right = split(left, size);
            curr = right ? split(right, size) : NULL;

            Node *mergedTail;
            Node *mergedHead = merge(left, right, &mergedTail);

            if (!newHead) {
                newHead = mergedHead;
                newTail = mergedTail;
            } else {
                newTail->next = mergedHead;
                mergedHead->prev = newTail;
                newTail = mergedTail;
            }
        }

        list->head = newHead;
        list->tail = newTail;
    }
}

List merge_sort_list(const List *src) {
    List sorted = copy_list(src);
    merge_sort_in_place(&sorted);
    return sorted;
}

List* sort_by_reactor_power(const List* list, sort_order order) {
    if (list == NULL)
        return NULL;

    List* sorted = copy_list_ptr(list);
    if (sorted == NULL || sorted->head == NULL)
        return sorted;

    Node* current = sorted->head->next;

    while (current != NULL) {
        Node* next = current->next;
        Node* pos = current->prev;

        if (current->next)
            current->next->prev = current->prev;
        else
            sorted->tail = current->prev;

        current->prev->next = current->next;

        while (pos != NULL &&
              ((order == SORT_ASC  && current->mechObj.reactor_power < pos->mechObj.reactor_power) ||
               (order == SORT_DESC && current->mechObj.reactor_power > pos->mechObj.reactor_power))) {
            pos = pos->prev;
        }

        if (pos == NULL) {
            current->next = sorted->head;
            current->prev = NULL;
            sorted->head->prev = current;
            sorted->head = current;
        } else {
            current->next = pos->next;
            current->prev = pos;

            if (pos->next)
                pos->next->prev = current;
            else
                sorted->tail = current;

            pos->next = current;
        }

        current = next;
    }

    return sorted;
}

List* sort_by_armor(const List* list, sort_order order) {
    if (list == NULL)
        return NULL;

    List* sorted = copy_list_ptr(list);
    if (sorted == NULL || sorted->head == NULL)
        return sorted;

    Node* current = sorted->head->next;

    while (current != NULL) {
        Node* next = current->next;
        Node* pos = current->prev;

        if (current->next)
            current->next->prev = current->prev;
        else
            sorted->tail = current->prev;

        current->prev->next = current->next;

        while (pos != NULL &&
              ((order == SORT_ASC  && current->mechObj.armor_health < pos->mechObj.armor_health) ||
               (order == SORT_DESC && current->mechObj.armor_health > pos->mechObj.armor_health))) {
            pos = pos->prev;
        }

        if (pos == NULL) {
            current->next = sorted->head;
            current->prev = NULL;
            sorted->head->prev = current;
            sorted->head = current;
        } else {
            current->next = pos->next;
            current->prev = pos;

            if (pos->next)
                pos->next->prev = current;
            else
                sorted->tail = current;

            pos->next = current;
        }

        current = next;
    }

    return sorted;
}

List* sort_by_ammo(const List* list, sort_order order) {
    if (list == NULL)
        return NULL;

    List* sorted = copy_list_ptr(list);
    if (sorted == NULL || sorted->head == NULL)
        return sorted;

    Node* current = sorted->head->next;

    while (current != NULL) {
        Node* next = current->next;
        Node* pos = current->prev;

        if (current->next)
            current->next->prev = current->prev;
        else
            sorted->tail = current->prev;

        current->prev->next = current->next;

        while (pos != NULL &&
              ((order == SORT_ASC  && current->mechObj.ammo < pos->mechObj.ammo) ||
               (order == SORT_DESC && current->mechObj.ammo > pos->mechObj.ammo))) {
            pos = pos->prev;
        }

        if (pos == NULL) {
            current->next = sorted->head;
            current->prev = NULL;
            sorted->head->prev = current;
            sorted->head = current;
        } else {
            current->next = pos->next;
            current->prev = pos;

            if (pos->next)
                pos->next->prev = current;
            else
                sorted->tail = current;

            pos->next = current;
        }

        current = next;
    }

    return sorted;
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
        case WYMAGA_PRZEGLADU:  return "WYMAGA PRZEGLĄDU";
        case USZKODZONY:        return "USZKODZONY";
        case W_NAPRAWIE:        return "W NAPRAWIE";
        case W_DEMONTAZU:       return "W DEMONTAŻU";
        default:                return "NIEZNANY";
    }
}