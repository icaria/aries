#include <stdio.h>
#include <stdlib.h>
#include "lab2.h"

struct Queue *Queue_Head = NULL;
double C;
double A;
double L;  /* Avg length of packets */
double Prop_Delay;
double Time_Out;
double FER;
int Window_Size;
int N; /* Total number of packets */

<<<<<<< HEAD:a2/lab2.c
void Sender(Event Current_Event) {
	
	/* You sender code here */
=======
//===============================================
// Sender/Receiver Methods

void Sender(Event Current_Event) {
	
	/* Your sender code here 
    
    if(Current_Event.Type == START_SEND) {

        //Current_Event.Time = 
        Channel(SEND_FRAME, Current_Event.Seq_Num, Current_Event.Pkt_Num, Current_Event.Time);
        Queue_Head->Type = RECEIVE_FRAME;
    
        if(Counter == 0) {
            Queue_Head->Type = TIMEOUT;
        } else if(Queue_Head->Type == SEND_ACK) {
            Queue_Head->Type = RECEIVE_ACK;
        } 
    } else if (Current_Event.Type == RECEIVE_ACK) {
        Queue_Head = Queue_Head->Next;
    }*/
>>>>>>> b1bd75bb69fd790bad923e2de07ffa36f061535d:a2/lab2.cc
}

void Receiver(Event Current_Event) {
	
	/* Your receiver code here 

    Current_Event.Type = SEND_ACK;
    Queue_Head = *Current_Event;*/
    
}

int main()
{
	Event Current_Event;
	
	/**********************************************/
	/* Remember to change the following variables */
	
	N = 25;		
	C = 1000000;			/* bps */
	L = 1500*8;			/* bits, Avg length of pkts */
	A = 54*8;			/* bits */
	Prop_Delay = 0.05;		/* seconds */
	Window_Size = 5;
	FER = 0.01;
	Time_Out = 10;
	/**********************************************/
	
	Initialization();
	
	while (Queue_Head != NULL)
	{
		Dequeue(&Current_Event);
		//printf("blah");		
		if (    (Current_Event.Type == RECEIVE_ACK)
			|| (Current_Event.Type == START_SEND)
			|| (Current_Event.Type == TIMEOUT))
		{
			Print(Current_Event);
			Sender_SRP(Current_Event);
		}
		else if (Current_Event.Type == RECEIVE_FRAME)
		{
			Print(Current_Event);
			Receiver_SRP(Current_Event);
		}
	}
	
	return 0;
}
