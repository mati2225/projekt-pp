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
} Node;

Node* push_back(Node* head, mech_object mechObj);
Node* push_front(Node* head, mech_object mechObj);
Node* free_list(Node* head);
void print_list(Node* head);

const char* mech_type_to_str(enum mech_type t);
const char* mech_condition_to_str(enum mech_condition c);

#endif
