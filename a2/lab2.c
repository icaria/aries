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

void Sender(Event Current_Event) {
	
	/* You sender code here */
    
    //printf(Current_Event.Time);
    
    if(Current_Event.Type == START_SEND) {
        //printf("START_SEND Packet Number:%d", Current_Event.Pkt_Num);
        Channel(SEND_FRAME, Current_Event.Seq_Num, Current_Event.Pkt_Num, Current_Event.Time);
    } else if(Current_Event.Type == RECEIVE_ACK) {
        printf("RECEIVED ACK");
    } else if(Current_Event.Type == TIMEOUT) {
        //printf("TIME_OUT Packet Number:%d", Current_Event.Pkt_Num);
        Channel(SEND_FRAME, Current_Event.Seq_Num, Current_Event.Pkt_Num, Current_Event.Time);
    }
}

void Receiver(Event Current_Event) {
	
	/* Your receiver code here */
    
    Deliver(Current_Event, Current_Event.Time);
    Channel(SEND_ACK, Current_Event.Seq_Num, Current_Event.Pkt_Num, Current_Event.Time);
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
