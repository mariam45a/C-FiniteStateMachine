#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>

typedef struct{
	char StateName;
	int StateName0;
	int StateName1;
	bool delete;
	
	}fsm_state;

fsm_state fsm[8]; // number of states in the fsm (A-H)

void transitions()
{

	fsm[0].StateName='F';
	fsm[0].StateName0=1;
	fsm[0].StateName1=2;
	
	fsm[1].StateName='C';
	fsm[1].StateName0=3;
	fsm[1].StateName1=4;
	
	fsm[2].StateName='A';
	fsm[2].StateName0=5;
	fsm[2].StateName1=6;
	
	fsm[3].StateName='D';
	fsm[3].StateName0=4 ;
	fsm[3].StateName1=5 ;
	
	fsm[4].StateName='E';
	fsm[4].StateName0=6;
	fsm[4].StateName1=0;
	
	fsm[5].StateName='H';
	fsm[5].StateName0=5;
	fsm[5].StateName1=7;
	
	fsm[6].StateName='G';
	fsm[6].StateName0=2;
	fsm[6].StateName1=3;
	
	fsm[7].StateName='B';
	fsm[7].StateName0=0;
	fsm[7].StateName1=1;
	
}

//will change state depending on 0 or 1
int transitioningstates(int current_state, int input)
{
	if(input==1)
	{ return fsm[current_state].StateName1; }
	
	if(input==0)
	{ return fsm[current_state].StateName0; }
	
	return -1;
}

//will change state based on command
void changeState(char command, char stateName)
{
int stateIndex=stateName-'A';

	if(stateIndex<0 || stateIndex>= 8)
	{
	printf("Invalid state name.\n");
	return;
	}
    
	if(command =='0') 
	{
	fsm[stateIndex].StateName0 = stateIndex;
	} 
	
	if(command=='1')
	{
	fsm[stateIndex].StateName1 = stateIndex;
	} 
	
	else
	{
	printf("Invalid command.\n");
	}
}

//will read the current state from a file
int readCurrentState(){
	FILE *file=fopen("currentState.txt", "r");
	if(file != NULL) 
	{
	int currentState;
	fscanf(file, "%d", &currentState);
	fclose(file);
	return currentState;
	}
	return 0;
}

//will write the current state to a file
void writeCurrentState(int currentState) 
{
	FILE *file= fopen("currentState.txt", "w");
	if(file != NULL) 
	{
	fprintf(file, "%d", currentState);
	fclose(file);
	}
}

//will determine if a state is reachable from the current state
bool isReachable(int currentState, int stateIndex, bool visited[])
{
	if(visited[stateIndex]) return false;
	visited[stateIndex] = true;
	if (currentState == stateIndex) return true;
	return isReachable(currentState, fsm[stateIndex].StateName0, visited) || isReachable(currentState, fsm[stateIndex].StateName1, visited);
}

//will identify garbage states
void identifyGarbage(int currentState) 
{
	bool visited[8]={false}; //will initialize all states as not visited
	isReachable(currentState, currentState, visited); //will mark reachable states

	bool hasGarbage= false;
	printf("Garbage: ");
	for(int i=0; i<8; ++i)
	{
	if(!visited[i]) 
	{
	hasGarbage = true;
	printf("%c ", fsm[i].StateName);
        }
        }
	
    if (!hasGarbage)
    {
	printf("No garbage");
    }
	printf("\n");
}

//will delete unreachable states
void deleteUnreachable(int currentState) {
	bool visited[8] = {false};
	isReachable(currentState, currentState, visited);

	bool anyDeleted = false;
	printf("Deleted: ");
	for(int i= 0; i<8; ++i) 
	{
        if(!visited[i] && !fsm[i].delete) 
	{
	anyDeleted= true;
	printf("%c ", fsm[i].StateName);
	fsm[i].delete=true;
	}
	}
	
	if(!anyDeleted) 
	{
	printf("No states deleted.\n");}
	
     else{
	printf("\n");}
}



int main(int argc, char * argv[])
{
	transitions();
	int currentState=readCurrentState(); //read the current state from file

	if(argc>1) 
	{

        if(argv[1][0]== 'c' && (argv[1][1]=='0' || argv[1][1]=='1') && argv[1][2] >='A' && argv[1][2]<='H')
        {
	changeState(argv[1][1], argv[1][2]);
	writeCurrentState(currentState);
	} 
	
	if(argv[1][0]=='1')
	{
	currentState=transitioningstates(currentState, 1);
	printf("Current state: %c\n", fsm[currentState].StateName);
	writeCurrentState(currentState);
	}
	
	if(argv[1][0]=='0')
	{
	currentState=transitioningstates(currentState, 0);
	printf("Current state: %c\n", fsm[currentState].StateName);
	writeCurrentState(currentState);
	}
	
	if(argv[1][0]=='p')
	{
	for(int i=0; i<8; ++i)
	{printf("%c %c %c\n", fsm[i].StateName, fsm[i].StateName0 + 'A', fsm[i].StateName1 + 'A'); }
	}
	
	if(argv[1][0]=='g')
	{
	identifyGarbage(currentState);
	}
	
	if(argv[1][0]=='d')
	{
	deleteUnreachable(currentState);
	}
	
	
	else{
	printf("Invalid command.\n");
	return 1; }
	}
	
	else{
	printf("Please provide input.\n");
	return 1; }
	

    exit(0);
}

