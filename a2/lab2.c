//---------------------------------------------------------------
// ECE 358 Assignment 2
// Stephen Chen		20274003 s38chen
// Gabriella Grandilli  20294003 gggrandi
//
//
//
// to compile: 	make
// to run: 	./a.out
//
//
// Our ABP functions: Sender(Event) and Receiver(Event)
// Our GBN functions: GBN_Sender(Event) and GBN_Receiver(Event)
//---------------------------------------------------------------


#include <stdio.h>
#include <stdlib.h>
#include "lab2.h"


//---------------------------------------------------------------

struct Queue *Queue_Head = NULL;
int Start_Seq_Num = 0;
int Start_Pkt_Num = -1;
int End_Seq_Num = -1;
int End_Pkt_Num = 0;
int Last_Seq_Num = 0;
int hasStarted = 0;

double C;
double A;
double L;  /* Avg length of packets */
double Prop_Delay;
double Time_Out;
double FER;
int Window_Size;
int N; /* Total number of packets */

//GBN counter
int counter = 0;


//---------------------------------------------------------------
// ABP Sender
void Sender(Event Current_Event) {

    if(Current_Event.Error == 0) {
        if(Current_Event.Type == START_SEND) {
            Channel(SEND_FRAME, Current_Event.Seq_Num, Current_Event.Pkt_Num, Current_Event.Time);
        } else if(Current_Event.Type == TIMEOUT) {
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

// ABP Receiver
void Receiver(Event Current_Event) {
	
    if(Current_Event.Error == 0) {
        Deliver(Current_Event, Current_Event.Time);
        Channel(SEND_ACK, Current_Event.Seq_Num, 0, Current_Event.Time);
    }
}

//-------------------------------------------------------------

void GBN_Sender(Event Current_Event) {

    if (Current_Event.Pkt_Num >= N) { return; }
    
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
        
        if(Current_Event.Pkt_Num >= Start_Pkt_Num && counter == 0) {
            counter = End_Pkt_Num - Current_Event.Pkt_Num;
            
            int i = 0;
            double nodal_delay = L/C;
            for(i = Start_Pkt_Num; i <= End_Pkt_Num; i++) {
                Channel(SEND_FRAME, (i) % (Window_Size + 1), i, Current_Event.Time + (i - Start_Pkt_Num)*nodal_delay);
            }
            
            
        }
        else if(Current_Event.Pkt_Num >= Start_Pkt_Num && counter > 0) {
            counter --;
        }
        
    } else if(Current_Event.Type == RECEIVE_ACK) {
        
        if(Current_Event.Seq_Num == Start_Seq_Num) {
            Start_Pkt_Num++;
            Start_Seq_Num = (Start_Seq_Num + 1) % (Window_Size + 1);
            End_Pkt_Num++;
            End_Seq_Num = (End_Seq_Num + 1) % (Window_Size + 1);
            
            Current_Event.Seq_Num = End_Seq_Num;
            Current_Event.Pkt_Num = End_Pkt_Num;
            
            if(Current_Event.Pkt_Num < N) {
                Channel(SEND_FRAME, Current_Event.Seq_Num, Current_Event.Pkt_Num, Current_Event.Time);
            }
        }
    }
}

void GBN_Receiver(Event Current_Event) {

    if (Current_Event.Pkt_Num >= N) { return; }
    
    if(Current_Event.Error == 0) {

             
        if(Current_Event.Seq_Num == (Last_Seq_Num) % (Window_Size + 1)) {
	    hasStarted = 1;
	    Last_Seq_Num = (Last_Seq_Num + 1) % (Window_Size + 1);
            Deliver(Current_Event, Current_Event.Time);
        }

	if (hasStarted == 1) {
            Channel(SEND_ACK, Current_Event.Seq_Num, 0, Current_Event.Time);
        }
     }
}

//-------------------------------------------------------------

void usage()
{
	printf("Usage: -f <FER as decimal> -p <PROP_DELAY as ms> -c <C as Mbs> -W <Window size> -N <num packets>\n");
	exit(1);
}

// Get commandline input to customize parameters
void GetInput(int argc, char* argv[])
{
	while (argc > 1 && argv[1][0] == '-') {
		switch(argv[1][1])
		{
			case 'f':
			  FER = atof(argv[2]);
			  break;
			case 'p':
			  Prop_Delay = atof(argv[2]) / 1000;
			  break;
			case 'c':
			  C = atof(argv[2]) * 1000000;
			  break;
			case 'W':
			  Window_Size = atoi(argv[2]);
			  break;
			case 'N':
			  N = atoi(argv[2]);
			  break;		  
			default:
			  usage();

		}

		++argv;
		--argc;
		++argv;
		--argc;

	}

	// Recalculate Time_Out in case C or Prop_Delay changed
	Time_Out = ((L / C) + (A / C) + (2 * Prop_Delay)) * 1.07 ;
	
//printf("FER: %f PROP: %f C: %f W: %d N: %d Timeout: %f\n", FER, Prop_Delay, C, Window_Size, N, Time_Out);
}

//-----------------------------------------------------------------

int main(int argc, char* argv[])
{
	Event Current_Event;
	
	
	/**********************************************/
	/* Remember to change the following variables */
	
	N = 10000;		
	C = 1000000;			/* bps */
	L = 1500*8;			/* bits, Avg length of pkts */
	A = 54*8;			/* bits */
	Prop_Delay = 0.05;		/* seconds */
	Window_Size = 1;
	FER = 0.01;
	Time_Out = ((L / C) + (A / C) + (2 * Prop_Delay)) * 1.07 ;
	/**********************************************/
	
	// Run this AFTER the above variables are set
	GetInput(argc, argv);	

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
