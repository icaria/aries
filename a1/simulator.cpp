//===================================================
//  ECE358 Lab 1
//  simulator.cpp
//  Created by Stephen Chen and Gabriella Grandilli on 12-05-29.
//
//  To compile and run:
//  g++ simulator.cpp
//  ./a.out T lamda L C K
//===================================================

#include <iostream>
#include <queue>
#include <sstream>
#include <cstdlib>
#include <math.h>
//#include "RandomForLab1.c"

using namespace std;

extern double genrand();
extern void sgenrand(unsigned long seed);

struct Packet
{
    long long arrivalTime;
};

// Input parameters

int T;
int lambda;  // number packets generated per number arrived (packets per second)
int L;      //length
int C;      // transmission rate of the output link (bits per second)
int K;      // size of the buffer (number of packets); if not specified, infinite

// Global variables

queue<Packet> packets;

long long t_arrival;
long long t_depart;
long long ticks;
bool bounded;
int numPackets;
int packetLoss;

//===================================================
// Packet handling methods
//===================================================

// Arrival is "M" -- memoryless;
// distribution of time between successive arrivals is identical, 
// is independent from one inter-arrival to another and is exponentially distributed

// Service process is "D" -- each packet will receive the same constant service time

void Arrival ( long long t ) {
    // Generate a packet as per the exponential distribution 
	// insert the packet in the queue (an array or a linked list)*/ 
	//queue.push(packet);
    
    numPackets++;
    
    if( bounded ) {
        if( packets.size() < K ) {
            Packet pack; 
            pack.arrivalTime = t;
            packets.push( pack );
        } else {
            packetLoss++;
        }
    } else {
        Packet pack;
        pack.arrivalTime = t;
        packets.push( pack );
    }
    
}

int Departure ( long long t ) {
    
	// If the head of the queue is empty/the queue is empty
    if(packets.empty()) {
        return 0;
    }
	else {
		// delete the packet from the queue after an elapse of the deterministic service time
        
        Packet pack = packets.front();
        
		int deleted_packet = 0;
   		return deleted_packet; 
	}
}

void Start_simulation (long long ticks) {
    
    long long t = 0;
    for (t=1; t<= ticks; t++) {
        Arrival(t);
        Departure(t);
    }
}

void Compute_performances () {
    /*Calculate and display the results such as average number of packets in queue, average delay in queue and idle time for the server. */
}

//========================================================
// Main
//========================================================

// Helper method to convert C string to integer
bool convert( int &val, char *buffer ) {
    std::stringstream ss( buffer );			// connect stream and buffer
    ss >> dec >> val;					// convert integer from buffer
    return ! ss.fail() &&				// conversion successful ?
	// characters after conversion all blank ?
	string( buffer ).find_first_not_of( " ", ss.tellg() ) == string::npos;
}

// Helper method for input parameters
void usage( char *argv[] ) {
    cerr << "Usage: " << argv[0] << " T  lamda  L  C  K (optional)" << endl;
    exit( EXIT_FAILURE );				// TERMINATE
}

int main(int argc, char* argv[]) {
        
    bounded = false;

    // Order of arguments: T lambda L C K
	switch(argc) {
		case 6: // M/D/1/K
            if (!convert(K, argv[5])) 
            {
                usage(argv);
            }
            bounded = true;
		case 5:
            if (!convert(C, argv[4]) || !convert(L, argv[3]) 
            || !convert(lambda, argv[2]) || !convert(T, argv[1])) {                   
               usage(argv);
            }
            break;
        case 4:         // three options is invalid
        case 3:         // two options is invalid
        case 2:         // one option is invalid
        case 1:         // zero options is invalid
		default:
	        usage(argv);
	}

   
    //----------------
   // Initialize variables
	float u = genrand();
    t_arrival = (-1/lambda)*log(u); //exponential random variable
	t_depart = t_arrival;  // first time departure will be called as soon as a packet arrives in the queue
    ticks = T * 1000000;
	numPackets = 0;  // shouldn't need because we can get the size from queue ??
  
   
   //----------------
   // Start simulation
    /*
    Start_simulation (ticks);
    Compute_performances ( );
	*/
}
