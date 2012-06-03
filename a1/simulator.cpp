//  ECE358 Lab 1
//  simulator.cpp
//
//  Created by Stephen Chen and Gabriella Grandilli on 12-05-29.
//  Copyright 2012 __MyCompanyName__. All rights reserved.
//

#include <iostream>
#include <queue>
#include <sstream>
#include <fstream>
#include <cstdlib>
using namespace std;

struct packet
{
    long long arrivalTime;
};

queue<packet> packets;
long long TICKS = 5000; //5000000000

void Arrival ( long long t ) {
    // Generate a packet as per the exponential distribution 
	// insert the packet in the queue (an array or a linked list)*/ 
	//queue.push(packet);
}

int Departure ( long long t ) {
    
	// If the head of the queue is empty/the queue is empty
    if(packets.empty()) {
        return 0;
    }
	else {
		// delete the packet from the queue after an elapse of the deterministic service time
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
    cerr << "Usage: " << argv[0]
	 << " n "
	 << " lamda "
	 << " L "
	 << " C " 
	 << " K (optional)" << endl;
    exit( EXIT_FAILURE );				// TERMINATE
}

int main(int argc, char* argv[]) {
	int lamda; // number packets generated per number arrived (packets per second)
    int l; //length
    int c; // transmission rate of the output link (bits per second)
    int n;
    int k; // size of the buffer (number of packets); if not specified, infinite
    
    bool isK = false;

	switch(argc) {
		case 5: // M/D/1/K
            if (!convert(k, argv[4])) 
            {
                usage(argv);
            }
            isK = true;
		case 4:
            if (!convert(k, argv[3])) {                   
               usage(argv);
            }
            break;
        case 3:         // two options is invalid
        case 2:         // one option is invalid
        case 1:         // zero options is invalid
		default:
	           usage(argv);
	}

    /*Initialise important terms such as t_arrival = exponential r.v, # of pkts in queue = 0, t_departure = t_arrival ( this implies that first time departure will be called as soon as a packet arrives in the queue*/
    

   //----------------
   // Initialize variables
	int t_arrival = 0;
	int t_depart = t_arrival;
	//int numPackets  // shouldn't need because we can get the size from queue
  
   
   //----------------
   // Start simulation
    /*
    Start_simulation (TICKS);
    Compute_performances ( );
	*/
}
