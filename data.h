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

typedef enum {
    SORT_ASC,
    SORT_DESC
} sort_order;

extern List global_list;

void init_list(List* list);
Node* create_node(mech_object mechObj);
void push_front(List* list, mech_object mechObj);
void push_back(List* list, mech_object mechObj);
void print_forward(const List* list);
void print_backward(const List* list);
void print_mech_object(int index, mech_object mechObj);
void free_list(List* list);
Node* find_first(const List* list, mech_object mechObj);
Node* find_first_single(const List* list, mech_object mechObj);
Node* find_first_multi(const List* list, mech_object mechObj);
void remove_node(List* list, Node* node);
int remove_first(List* list, mech_object mechObj);
int remove_first_single(List* list, mech_object mechObj);
int remove_first_multi(List* list, mech_object mechObj);
int remove_all_single(List* list, mech_object mechObj);
int remove_all_multi(List* list, mech_object mechObj);
int count_elements(List* list);
int count_nodes(Node* node);
int list_by_model(List* list, const char* model);
mech_object* find_by_exact_model(List* list, const char* model);
mech_object* list_to_array(List* list, size_t* out_size);
bool compare_objects_by_model(const mech_object a, const mech_object b);
bool partial_match_single(const mech_object a, const mech_object b);
bool partial_match_multi(const mech_object a, const mech_object b);
List* filter_by_reactor_power(List* list, int threshold);
List* filter_by_armor(List* list, int threshold);
List* filter_by_ammo(List* list, int threshold);
List copy_list(const List *src);
List* copy_list_ptr(const List* list);
Node* split(Node *head, int n);
Node* merge(Node *a, Node *b, Node **outTail);
void merge_sort_in_place(List *list);
List merge_sort_list(const List *src);
List* sort_by_reactor_power(const List* list, sort_order order);
List* sort_by_armor(const List* list, sort_order order);
List* sort_by_ammo(const List* list, sort_order order);

const char* mech_type_to_str(enum mech_type t);
const char* mech_condition_to_str(enum mech_condition c);

#endif
