#include <stdlib.h>
#include <stddef.h>
#include "data.h"

List* global_list = NULL;

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
    n->prev - list->tail;

    if (list->tail != NULL) {
        list->tail->next = n;
    } else {
        list->head = n;
    }

    list->head = n;
}

void print_forward(const List* list) {
    const Node* p = list->head;
    while (p != NULL) {
        print_mech_object(p->mechObj);
        p = p->next;
    }
}

void print_backward(const List* list) {
    const Node* p = list->tail;
    while (p != NULL) {
        print_mech_object(p->mechObj);
        p = p->prev;
    }
}

void print_mech_object(mech_object mechObj) {
    printf("%s | %d | %d | %d | %d | %s | %d\n", mechObj.model, mechObj.type, mechObj.reactor_power, mechObj.armor_health, mechObj.ammo, mechObj.assigned_pilot, mechObj.condition);
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
        if (p->mechObj == mechObj) return p;
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

int remove_all(List* list, mech_object mechObj) {
    int count = 0;
    Node* p = list->head;

    while (p != NULL) {
        Node* next = p->next;

        if (p->mechObj == mechObj) {
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

//////////////

bool average_reactor_power(List* list, double* result) {
    int count = 0;
    double sum = 0;

    for (Node* p = list->head; p != NULL; p = p->next) {
        sum += p->mechObj.reactor_power;
        count++;
    }

    if (count == 0) return false;

    *result = sum / count;
    return true;
}

bool find_min_armor(List* list, double* result) {
    const Node* head = list->head;
    if (head == NULL) return false;

    double min = head->mechObj.armor_health;
    for (Node* p = head->next; p != NULL; p = p->next) {
        if (p->mechObj.armor_health < min) min = p->mechObj.armor_health;
    }

    *result = min;
    return true;
}

bool find_max_armor(List* list, double* result) {
    const Node* head = list->head;
    if (head == NULL) return false;

    double max = head->mechObj.armor_health;
    for (Node* p = head->next; p != NULL; p = p->next) {
        if (p->mechObj.armor_health > max) max = p->mechObj.armor_health;
    }

    *result = max;
    return 
}

List* filter_by_armor(List* list, int threshold) {
    List* filtered = NULL;

    for (Node* p = list->head; p != NULL; p = p->next) {
        if (p->mechObj.armor_health > threshold) {
            push_back(filtered, p->mechObj);
        }
    }

    return filtered;
}

List* sort_by_armor(List* list) {
    List* sorted = NULL;

    for (Node* p = list->head; p != NULL; p = p->next) {

    }

    return sorted;
}

List* sort_by_name(List* list) {
    List* sorted = NULL;

    for (Node* p = list->head; p != NULL; p = p->next) {

    }

    return sorted;
}

///////////////////////////////////

/*Node* insert_sorted(Node* head, int value) {
    Node* n = calloc(1, sizeof(Node));
    n->value = value;

    if (head == NULL || value <= head->value) {
        n->next = head;
        return n;
    }

    Node* p = head;
    while (p->next != NULL && (p->next)->value < value) {
        p = p->next;
    }

    n->next = p->next;
    p->next = n;

    return head;
}

Node* sort_list(Node* head) {
    Node* sorted = NULL;

    while (head != NULL) {
        Node* next = head->next;

        sorted = insert_sorted(sorted, head->value);

        free(head);
        head = next;
    }

    return sorted;
}

Node* insert_node_sorted(Node* sorted, Node* node) {
    if (sorted == NULL || node->value <= sorted->value) {
        node->next = sorted;
        return node;
    }

    Node* p = sorted;
    while (p->next != NULL && p->next->value < node->value) {
        p = p->next;
    }

    node->next = p->next;
    p->next = node;

    return sorted;
}

Node* sort_list_inplace(Node* head) {
    Node* sorted = NULL;

    while (head != NULL) {
        Node* next = head->next;

        head-> next = NULL;

        sorted = insert_node_sorted(sorted, head);

        head = next;
    }

    return sorted;
}

Node* remove_first(Node* head, int value) {
    if (head == NULL) return head;

    if (head->value == value) {
        Node* next = head->next;
        free(head);
        return next;
    }

    Node* p = head;
    while (p->next != NULL && (p->next)->value != value) {
        p = p->next;
    }

    if (p->next != NULL) {
        Node* to_delete = p->next;
        p->next = to_delete->next;
        free(to_delete);
    }

    return head;
}

Node* remove_all(Node* head, int value) {
    while (head != NULL && head->value == value) {
        Node* next = head->next;
        free(head);
        head = next;
    }

    if (head == NULL) return NULL;

    Node* p = head;
    while (p->next != NULL) {
        if (p->next->value == value) {
            Node* to_delete = p->next;
            p->next = to_delte->next;
            free(to_delete);
        } else {
            p = p->next;
        }
    }

    return head;
}*/

/////////////////////////////////
int cmp_int_asc(const void* a, const void* b) {
    const int* x = (const int*)a;
    const int* y = (const int*)b;
    if (*x < *y) return -1;
    if (*x > *y) return 1;
    return 0;
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