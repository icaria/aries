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

using namespace std;

extern double genrand();
extern void sgenrand(unsigned long seed);

struct Packet
{
    unsigned long long arrivalTime;
};

// Input parameters

long T;
long lambdaPerSecond;  // number packets generated per number arrived (packets per second)
double lambda;
long L;      //length
long C;      // transmission rate of the output link (bits per second)
long K;      // size of the buffer (number of packets); if not specified, infinite

// Global variables

queue<Packet> packets;

unsigned long long t_arrival;
unsigned long long t_depart;

// Ticks
unsigned long long ticks;
unsigned long long idle_ticks;
unsigned long long total_ticks;

bool bounded;
int numPackets;
int serviceTime;
int remainingServiceTime;

unsigned long long packetsLost;

unsigned long long totalQueueDelay;
unsigned long long totalSojournTime; // Sum of sojourn times
unsigned long long totalPacketCount; // Sum of packet counts.


//===================================================
// Packet handling methods
//===================================================

void UpdateArrivalTime()
{
    double u = genrand();
    t_arrival = (unsigned long long)(((2 / lambda) * u) + 1);
}

void Arrival ( long long t ) {
    // Generate a packet as per the exponential distribution 
	// insert the packet in the queue (an array or a linked list)*/ 
	//queue.push(packet);
    
    numPackets++;
    UpdateArrivalTime();
    
    if (bounded && packets.size() == K) {
        packetsLost++;
    }
    else {
        Packet pack;
        pack.arrivalTime = t_arrival;
        packets.push( pack );
    }
}

int Departure ( long long t ) {
	// If the head of the queue is empty/the queue is empty
    if(packets.empty()) {
        remainingServiceTime = 0;
        t_depart++;
        idle_ticks ++;
        return 0;
    } 
    else {
        // delete the packet from the queue after an elapse of the deterministic service time
        Packet pack = packets.front();
        totalQueueDelay += t - pack.arrivalTime;
        remainingServiceTime = serviceTime;
        t_depart += serviceTime;
   		return 1; 
	}
}

void Start_simulation (long long ticks) {
    
    unsigned long long t = 0;
    serviceTime = (int)(L/C);
    remainingServiceTime = 0;
    
    for (t=1; t<= ticks; t++) {
        
        // If it is time for the packet to enter the queue, call arrive
        if (t == t_arrival) {
            Arrival(t);
        }
        else if (t == t_depart) {
            Departure(t);
        }
        
        if ( remainingServiceTime > 0 ) {
            
            remainingServiceTime--;
            t_depart++;
             
            if( remainingServiceTime == 0 ) {
                Packet pack = packets.front();
                totalSojournTime += t - pack.arrivalTime;
                packets.pop();
                
            }
        }
        
        totalPacketCount += numPackets;
    }
}

void Compute_performances () {
    /*Calculate and display the results such as average number of packets in queue, average delay in queue and idle time for the server. */
    
    double propIdle = idle_ticks / total_ticks;
    double probLoss = packetsLost / numPackets;
    double avgPacketsInQueue = totalPacketCount / total_ticks;
    double avgQueueDelay = totalQueueDelay / numPackets;
    double avgSojournTime = totalSojournTime / numPackets;
    double totalSojournTime = totalSojournTime;

    
    cout << "t is:" << ticks << endl;
    
    cout << "Avg. packets in queue: " << totalPacketCount / ticks << endl;
    
    cout << "Avg. queue delay: " << totalQueueDelay / numPackets << endl;
    cout << "Total sojourn time: " << totalSojournTime << endl;
    
    cout << "Avg. sojourn time: " << totalSojournTime / numPackets << endl;
    
    cout << "Probability of packet loss: " << packetsLost / numPackets << endl;
    cout << endl;
}

//========================================================
// Main
//========================================================

// Helper method to convert C string to integer
bool convert( long &val, char *buffer ) {
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
            || !convert(lambdaPerSecond, argv[2]) || !convert(T, argv[1])) {                   
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
    lambda = lambdaPerSecond / 1000000;
    
    t_arrival = (unsigned long long)((2 / lambda) * genrand()); //exponential random variable
	t_depart = 1;  // first time departure will be called as soon as a packet arrives in the queue
    ticks = T * 1;
    idle_ticks = 0;
	numPackets = 0;  // shouldn't need because we can get the size from queue ??
    totalQueueDelay = 0;
    totalSojournTime = 0;
    totalPacketCount = 0;
  
   
   //----------------
   // Start simulation
    
    Start_simulation(ticks);
    Compute_performances();
	
}
