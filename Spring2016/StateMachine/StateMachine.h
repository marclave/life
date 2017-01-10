#ifndef STATEMACHINE_H_
#define STATEMACHINE_H_
#include "StateMachine_Types.h"

// Prototypes for all the states
state_ret_E state_entry(void);
state_ret_E state_foo(void);
state_ret_E state_bar(void);
state_ret_E state_end(void);

state_ret_E (*stateHandler)(void)[] = {state_entry, state_foo, state_bar, state_end};

// This is an enum for all the potential states of the fsm
typedef enum {
  state_entry,
  state_foo,
  state_bar,
  state_end,
} state_state_E;

// Struct for the transitions and types
struct transition_S
{
  state_state_E src_state;
  state_ret_E ret_code;
  state_state_E dst_state;
}

// Essentially a lookup table with transitions
struct transition_S state_transitions[] = {
    {state_entry, STATE_OK, state_foo},
    {state_entry, STATE_FAIL, state_end},
    {state_foo, STATE_OK, state_bar},
    {state_foo, STATE_FAIL, state_end},
    {state_foo, STATE_REPEAT, state_foo},
    {state_bar, STATE_OK, state_end},
    {state_bar, STATE_FAIL, state_end},
    {state_bar, STATE_REPEAT, state_foo}};

#endif