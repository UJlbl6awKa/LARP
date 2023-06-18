#include "FSM.h"

enum states FSM_table[3][3] = {
    [idle_state][sign0] = state_find, // провзаимодейсвовали с 1 якорем
    [idle_state][sign1] = NONE,
    [state_find][sign0] = NONE,  
    [state_find][sign1] = state_final,
    [state_final][sign0] = idle_state,
    [state_final][sign1] = idle_state
};

void doFSM_table()
{
    enum states current_state = idle_state;
    while (1)
    {
        enum signals current_signal = getSignal();
        current_state = FSM_table[current_state][current_signal];
    }
}