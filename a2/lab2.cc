#include <stdio.h>
#include <stdlib.h>
#include "lab2.h"

// Global Variables

struct Queue *Queue_Head = NULL;
double C;
double A;
double L;  /* Avg length of packets */
double Prop_Delay;
double Time_Out;
double FER;
int Window_Size;
int N; /* Total number of packets */

//===============================================
// Helper Methods

void Initialization() {

}

void Print(Event e) {

}

void Dequeue(Event* Current_Event) {

}

void Channel(int Type, int SeqNum, int PktNum, double CTime) {

}

//===============================================
// Sender/Receiver Methods

void Sender(Event Current_Event) {
	
	/* Your sender code here */
}

void Receiver(Event Current_Event) {
	
	/* Your receiver code here */
}


//===============================================
// Main

int main()
{
	Event Current_Event;
	
	/**********************************************/
	/* Remember to change the following variables */
	
	N = 25;		
	C = 1000000;			/* bps */
	L = 1500*8;			/* bits, Avg length of pkts */
	A = 54*8;			/* bits */
	Prop_Delay = 50;		/* seconds */
	Window_Size = 5;
	FER = 0.01;
	Time_Out = 10;
	/**********************************************/
	
	Initialization();
	
	while (Queue_Head != NULL)
	{
		Dequeue(&Current_Event);
		
		if (    (Current_Event.Type == RECEIVE_ACK)
			|| (Current_Event.Type == START_SEND)
			|| (Current_Event.Type == TIMEOUT))
		{
			Print(Current_Event);
			Sender(Current_Event);
		}
		else if (Current_Event.Type == RECEIVE_FRAME)
		{
			Print(Current_Event);
			Receiver(Current_Event);
		}
	}
	
	return 0;
}
