//
//  simulator.cpp
//  
//
//  Created by Stephen Chen on 12-05-29.
//  Copyright 2012 __MyCompanyName__. All rights reserved.
//

#include <iostream>
#include <queue>
#include <sstream>
#include <fstream>
#include <cstdlib>
using namespace std;

queue<int> *packets;
int TICKS = 5000; 

void Arrival ( int t ) {
    /* Generate a packet as per the exponential distribution and insert the packet in the queue (an array or a linked list)*/ 
}

int Departure ( int t ) {
    /* Check the queue for the packet, if head of the queue is empty, return 0 else if the queue is non-empty delete the packet from the queue after an elapse of the deterministic service time. */
    
    if(packets->empty()) {
        return 0;
    }
    
   	return 0; 
}

void Start_simulation (int ticks) {
    
    for (int t=1; t<= ticks; t++) {
        Arrival (t); /* call the arrival procedure*/
        Departure (t); /*call the departure procedure*/
    }
}

void Compute_performances () {
    /*Calculate and display the results such as average number of packets in queue, average delay in queue and idle time for the server. */
}

//========================================================
// Main


bool convert( int &val, char *buffer ) {		// convert C string to integer
    std::stringstream ss( buffer );			// connect stream and buffer
    ss >> dec >> val;					// convert integer from buffer
    return ! ss.fail() &&				// conversion successful ?
	// characters after conversion all blank ?
	string( buffer ).find_first_not_of( " ", ss.tellg() ) == string::npos;
} // convert

void usage( char *argv[] ) {
    cerr << "Usage: " << argv[0]
	 << " n "
	 << " lamda "
	 << " L "
	 << " C " 
	 << " K (optional)" << endl;
    exit( EXIT_FAILURE );				// TERMINATE
} // usage

int main(int argc, char* argv[]) {
	int n, lamda, l, c, k;

	switch(argc) {
		case 5: // M/D/1/K
		   if (!convert(k, argv[4])) 
                   usage(argv);
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
    
    packets = new queue<int>();
    
    Start_simulation (TICKS);
    Compute_performances ( );
}
