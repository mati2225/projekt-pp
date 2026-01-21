#ifndef DATA_H
#define DATA_H

enum mech_type {
    SZTURMOWY,
    WSPARCIA_OGNIOWEGO,
    REKONESANSOWY,
    OBRONNY
};

enum mech_condition {
    SPRAWNY,
    WYMAGA_PRZEGLADU,
    USZKODZONY,
    W_NAPRAWIE,
    W_DEMONTAZU
};

typedef struct mech_object {
    char model[101];
    enum mech_type type;
    int reactor_power;
    int armor_health;
    int ammo;
    char assigned_pilot[51];
    enum mech_condition condition;   
} mech_object;

typedef struct Node {
    struct mech_object mechObj;
    struct Node* next;
    struct Node* prev;
} Node;

typedef struct {
    Node* head;
    Node* tail;
} List;

extern List* global_list;

void init_list(List* list);
Node* create_node(mech_object mechObj);
void push_front(List* list, mech_object mechObj);
void push_back(List* list, mech_object mechObj);
void print_forward(const List* list);
void print_backward(const List* list);
void print_mech_object(mech_object mechObj);
void free_list(List* list);
Node* find_first(const List* list, mech_object mechObj);
void remove_node(List* list, Node* node);
int remove_first(List* list, mech_object mechObj);
int remove_all(List* list, mech_object mechObj);
int count_elements(List* list);
bool average_reactor_power(List* list, double* result);
bool find_min_armor(List* list, double* result);
bool find_max_armor(List* list, double* result);
List* filter_by_armor(List* list, int threshold);
List* sort_by_armor(List* list);
List* sort_by_name(List* list);

const char* mech_type_to_str(enum mech_type t);
const char* mech_condition_to_str(enum mech_condition c);

#endif
