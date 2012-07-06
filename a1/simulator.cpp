//===================================================
//  ECE358 Lab 1
//  simulator.cpp
//  Created by Stephen Chen and Gabriella Grandilli on 12-05-29.
//
//  To compile and run:
//  make
//  ./a.out T lamda L C K
//  T = number to be multiplied by 10^6
//  lamda is in seconds
//  L is in bits
//  C is in Mbits/sec
//  K is size of queue in packets; is an optional parameter
//===================================================

#include <iostream>
#include <queue>
#include <sstream>
#include <cstdlib>
#include <math.h>

using namespace std;

extern double genrand();
extern void sgenrand(unsigned long seed);

// Struct to simulate a packet.
struct Packet
{
    unsigned long long arrivalTime;
};

// Input parameters

long T; //
long lambdaPerSecond;  // number packets generated per number arrived (packets per second)
double lambda;
long L;      //length
long CinMegaBits;      // transmission rate of the output link (bits per second)
double C;
long K;      // size of the buffer (number of packets); if not specified, infinite

// Global variables

queue<Packet> packets;

unsigned long long t_arrival;
unsigned long long t_depart;

// Ticks
unsigned long long ticks;
unsigned long long idle_ticks;

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
    t_arrival += (unsigned long long)(((2 / lambda) * u) + 1);
}

void Arrival ( long long t ) {
    // Generate a packet as per the exponential distribution 
	// insert the packet in the queue (an array or a linked list)*/ 
	    
    numPackets++;
    UpdateArrivalTime();
    
    if (bounded && (long)packets.size() == K) {
        packetsLost++;
    }
    else {
        Packet pack;
        pack.arrivalTime = t;
        packets.push( pack );
    }
}

int Departure ( long long t ) {
	// If the head of the queue is empty/the queue is empty
    if(packets.size() == 0) {
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
    serviceTime = (int)(((double)L/(double)C));
    remainingServiceTime = 0;
    
    for (t=1; t<= ticks; t++) {
        
        // If it is time for the packet to enter the queue, call arrive
        if (t == t_arrival) {
            Arrival(t);
        }
        
        if (t == t_depart) {
            Departure(t);
        }
        
        if ( remainingServiceTime > 0 ) {
            remainingServiceTime--;
             
            if( remainingServiceTime == 0 ) {
                Packet pack = packets.front();
                totalSojournTime += (t - pack.arrivalTime);
                packets.pop();
                
            }
        }
        
        totalPacketCount += packets.size();
    }
}

void Compute_performances () {
       
    double propIdle = ((long double)idle_ticks / ticks) * 100;
    double probLoss = ((long double)packetsLost / numPackets) * 100 ;
    double avgPacketsInQueue = (long double)totalPacketCount / ticks;
    double avgQueueDelay = (long double)totalQueueDelay / numPackets;
    double avgSojournTime = (long double)totalSojournTime / numPackets;
    
// Scripting output
   
    if( bounded ) {
        cout << totalPacketCount << "," << totalSojournTime << "," << probLoss << "," << propIdle << "," ;
    }
    else {    
        cout << avgPacketsInQueue << "," << avgSojournTime << "," << propIdle << "," ;
    }

  /*  
    cout << "Number of ticks is: " << ticks << endl;
    cout << "Number of packets: " << numPackets << endl;
    cout << "N (sum of number of packets): " << totalPacketCount << endl;
    cout << "E[N] (Avg. number of packets in queue): " << avgPacketsInQueue << endl;

    cout << "T (total sojourn times): " << totalSojournTime << endl;
    cout << "E[T] (Avg. sojourn time): " << avgSojournTime << endl;

    cout << "Ploss (Probability of packet loss): " << probLoss << " %" << endl;
    cout << "Pidle (Proportion of idle time): " << propIdle << " %" << endl;
    */
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
            if (!convert(CinMegaBits, argv[4]) || !convert(L, argv[3]) 
            || !convert(lambdaPerSecond, argv[2]) || !convert(T, argv[1])) {                   
               usage(argv);
            }
            lambda = ((double)lambdaPerSecond / 1000000); // convert to microseconds
            C = ((double)CinMegaBits ); //convert to bits per microseconds
            
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
    sgenrand(time(NULL)); // init random seed
    t_arrival = (unsigned long long)((2 / lambda) * genrand()); //exponential random variable
	t_depart = 1;  // first time departure will be called as soon as a packet arrives in the queue
    ticks = ((unsigned long long)T * 1000000);
    idle_ticks = 0;
	numPackets = 0; 
    packetsLost = 0;
    totalQueueDelay = 0;
    totalSojournTime = 0;
    totalPacketCount = 0;
  
   //----------------
   // Start simulation
    
    Start_simulation(ticks);
    Compute_performances();
	
}
