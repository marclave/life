/* State machine using function pointers
  For fun using: C best practices and function pointers
  instead of the naieve switch approach

  Developed by: Marc Laventure

  List of TODOs:
    - 
 */
#include "StateMachine.h"
#include "StateMachine_Types.h"

int main(void)
{
  state_state_E currentState = state_entry;
  state_ret_E returnCode;

  int (*stateFunctionPointer)(void);

  for (;;)
  {
    stateFunctionPointer = stateHandler[currentState];
    returnCode = stateFunctionPointer();
    if (returnCode == STATE_FAIL)
    {
      break;
    }
  }

  return 0;
}