Summary:

	The purpose of this lab is to create and implement a finite state machine using c programming. The first thing done to implement 	this was to create a structure (fsm_state) that will represent the states in the machine. The an array fsm of "fsm_state" 	structures is initialized with 8 states. 

	transistions() function
	The purpose of this is to intialize the transitions of each state, and each state is assigned a name and what transitions occur 	when '0' or '1' is inputted.

	transitioningstates(int current_state, int input) function
	this function will calculate the next state based on the input and current state, it will then return the index.

	changestate(char comman, char stateName) function
	This will modify the current state of the machine and will change the configuration of the fsm.

	readCurrentState() and writeCurrentState(int currentState) functions
	The purpose of the "readCurrentState() function is to read the state from a file (currentstate.txt), after commands that alter 	this state are used, it will update the current state in the file using "writeCurrentState."

	identifygarbage(int currentState) function
	it will identify all states that are reachable and unreachable from the current function. The unreachable states are deemed as 	"garbage."

	deleteUnreacable() function
	This function will delete all the unreachable states when called.