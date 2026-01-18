#ifndef DATA_H
#define DATA_H

enum MechClass {
    SZTURMOWY,
    WSPARCIA_OGNIOWEGO,
    REKONESANSOWY,
    OBRONNY
};

enum MechTechnicalCondition {
    SPRAWNY,
    WYMAGA_PRZEGLADU,
    USZKODZONY,
    W_NAPRAWIE,
    W_DEMONTAZU
};

typedef struct Mech {
    char model[101];
    enum MechClass class;
    int reactor_power;
    int armor_health;
    int ammo;
    char assigned_pilot[51];
    enum MechTechnicalCondition condition;   
} Mech;

typedef struct Node {
    struct Mech mech_object;
    struct Node* next;
} Node;

Node* push_back(Node* head, Mech mech_object);
Node* push_front(Node* head, Mech mech_object);
Node* free_list(Node* head);
void print_list(Node* head);

const char* mech_class_to_str(enum MechClass s);
const char* mech_technical_condition_to_str(enum MechTechnicalCondition s);

#endif
