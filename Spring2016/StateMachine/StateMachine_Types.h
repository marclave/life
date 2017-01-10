#ifndef STATEMACHINE_TYPES_H_
#define STATEMACHINE_TYPES_H_

// This is an enum that holds the two return types
typedef enum {
  STATE_OK,
  STATE_REPEAT,
  STATE_FAIL,
} state_ret_E;

#endif