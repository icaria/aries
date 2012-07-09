#include <stdio.h>
#include <stdlib.h>
#include "lab2.h"

struct Queue *Queue_Head = NULL;
int Start_Seq_Num = 0;
int Start_Pkt_Num = -1;
int End_Seq_Num = -1;
int End_Pkt_Num = 0;
int Last_Inorder_PktNum_Received = -1;
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

    if(Current_Event.Error == 0) {
        if(Current_Event.Type == START_SEND) {
            Channel(SEND_FRAME, Current_Event.Seq_Num, Current_Event.Pkt_Num, Current_Event.Time);
        } else if(Current_Event.Type == TIMEOUT) {
            //Dequeue(&Current_Event);
            Channel(SEND_FRAME, Current_Event.Seq_Num, Current_Event.Pkt_Num, Current_Event.Time);
        } else if(Current_Event.Type == RECEIVE_ACK) {
            Dequeue(&Current_Event);

            Current_Event.Seq_Num = (Current_Event.Seq_Num + 1) % 2;
            Current_Event.Pkt_Num = Current_Event.Pkt_Num + 1;
                
            if(Current_Event.Pkt_Num != N) {
                Channel(SEND_FRAME, Current_Event.Seq_Num, Current_Event.Pkt_Num, Current_Event.Time);
            }
        }
    }
}

void Receiver(Event Current_Event) {
	
	/* Your receiver code here */
    
    if(Current_Event.Error == 0) {
       // Dequeue(&Current_Event);
        Deliver(Current_Event, Current_Event.Time);
        Channel(SEND_ACK, Current_Event.Seq_Num, 0, Current_Event.Time);
    }
}

void GBN_Sender(Event Current_Event) {
    
    if(Current_Event.Type == START_SEND) {
        if(Start_Pkt_Num == -1) {
            Start_Pkt_Num = Current_Event.Pkt_Num;
            Start_Seq_Num = Current_Event.Seq_Num;
            End_Pkt_Num = Start_Pkt_Num;
            End_Seq_Num = Start_Seq_Num;
        } else {
            End_Pkt_Num++;
            End_Seq_Num = (End_Seq_Num + 1) % (Window_Size + 1);
        }
        
        Current_Event.Pkt_Num = End_Pkt_Num;
        Current_Event.Seq_Num = End_Seq_Num;

        Channel(SEND_FRAME, Current_Event.Seq_Num, Current_Event.Pkt_Num, Current_Event.Time);
        
    } else if(Current_Event.Type == TIMEOUT) {
        
        if(Current_Event.Pkt_Num == Start_Pkt_Num) {
            int i = 0;
            for(i = 0; i < Window_Size; i++) {
                Channel(SEND_FRAME, (Current_Event.Seq_Num + i) % (Window_Size + 1), Current_Event.Pkt_Num + i, Current_Event.Time);
            }
        }
        
    } else if(Current_Event.Type == RECEIVE_ACK) {
        
        if(Current_Event.Pkt_Num == Start_Pkt_Num) {
            Start_Pkt_Num++;
            Start_Seq_Num = (Start_Seq_Num + 1) % (Window_Size + 1);
            End_Pkt_Num++;
            End_Seq_Num = (End_Seq_Num + 1) % (Window_Size + 1);
            
            Current_Event.Seq_Num = End_Seq_Num;
            Current_Event.Pkt_Num = End_Pkt_Num;
            
            if(Current_Event.Pkt_Num != N) {
                Channel(SEND_FRAME, Current_Event.Seq_Num, Current_Event.Pkt_Num, Current_Event.Time);
            }
        }
    }
}

void GBN_Receiver(Event Current_Event) {

    if(Current_Event.Error == 0) {
        
        if(Current_Event.Pkt_Num == Last_Inorder_PktNum_Received + 1) {
            Last_Inorder_PktNum_Received++;
            Deliver(Current_Event, Current_Event.Time);
        }
        Channel(SEND_ACK, Current_Event.Seq_Num, 0, Current_Event.Time);
    }
}

void usage()
{
	printf("Usage: -f <FER as decimal> -p <PROP_DELAY as ms> -c <C as Mbs> -W <Window size>\n");
	exit(1);
}

void GetInput(int argc, char* argv[])
{
	while (argc > 1 && argv[1][0] == '-') {
		switch(argv[1][1])
		{
			case 'f':
			  FER = atof(argv[1]);
			  break;
			case 'p':
			  Prop_Delay = atof(argv[1]) / 1000;
			  break;
			case 'c':
			  C = atof(argv[1]) * 1000000;
			  break;
			case 'W':
			  Window_Size = atoi(argv[1]);
			  break;
			default:
			  usage();

		}

		++argv;
		--argc;

	}
}

int main(int argc, char* argv[])
{
	Event Current_Event;
	
	/**********************************************/
	/* Remember to change the following variables */
	
	N = 25;//10000;		
	C = 1000000;			/* bps */
	L = 1500*8;			/* bits, Avg length of pkts */
	A = 54*8;			/* bits */
	Prop_Delay = 0.05;		/* seconds */
	Window_Size = 5;
	FER = 0.01;
	Time_Out = ((L / C) + (A / C) + (2 * Prop_Delay)) * 1.07 ;
	/**********************************************/
	
	//GetInput(argc, argv);
	Initialization();
	
	while (Queue_Head != NULL)
	{
		Dequeue(&Current_Event);
		
		if (    (Current_Event.Type == RECEIVE_ACK)
			|| (Current_Event.Type == START_SEND)
			|| (Current_Event.Type == TIMEOUT))
		{
			Print(Current_Event);
			GBN_Sender(Current_Event);
		}
		else if (Current_Event.Type == RECEIVE_FRAME)
		{
			Print(Current_Event);
			GBN_Receiver(Current_Event);
		}
    	}

	return 0;
}
