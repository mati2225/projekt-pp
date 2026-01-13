#include "data.h"

const char* mech_class_to_str(enum MechClass s) {
    switch (s) {
        case SZTURMOWY:             return "SZTURMOWY";
        case WSPARCIA_OGNIOWEGO:    return "WSPARCIA OGNIOWEGO";
        case REKONESANSOWY:         return "REKONESANSOWY";
        case OBRONNY:               return "OBRONNY";
        default:                    return "BRAK";
    }
}

const char* mech_technical_condition_to_str(enum MechTechnicalCondition s) {
    switch (s) {
        case SPRAWNY:           return "SPRAWNY";
        case WYMAGA_PRZEGLADU:  return "WYMAGA PRZEGLADU";
        case USZKODZONY:        return "USZKODZONY";
        case W_NAPRAWIE:        return "W NAPRAWIE";
        case W_DEMONTAZU:       return "W DEMONTAZU";
        default:                return "NIEZNANY";
    }
}