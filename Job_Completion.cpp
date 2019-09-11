/* Filename: Job_Completion.cpp
 * Description: The command line program, Job_Completion.cpp, takes in one
 * 		parameter, an input file name. The input file specified by
 * 		the input file name should contain a list of jobs with 
 * 		positive integral weights and lengths. The program runs two
 * 		greedy algorithms to determine the sum of the weighted 
 * 		completion times. The first greedy algorithm is non-optimal
 * 		and uses the score weight - length. The second greedy 
 * 		algorithm is optimal and uses the score weight/length.
 */

#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <queue>
#include "Job.hpp"
#include "JobPtrComp.hpp"

// argv index of input file
#define IN_IDX 1

// expected number of arguments
#define EXPECTED_ARGS 2

using namespace std;
 
/* Parses the input file and inputs each job into two different priority
 * queues according to the two different scores used. The priority queue
 * badQueue uses the non-optimal score weight - length while the priority
 * queue goodQueue uses the optimal score weight/length.
 */
void loadfromFile(const char* filename,
		  priority_queue<Job*, vector<Job*>, JobPtrComp>& badQueue,
		  priority_queue<Job*, vector<Job*>, JobPtrComp>& goodQueue) {

	// used to get each line from input file
	string line;

	// input file stream
	ifstream* in = new ifstream(filename);

	// Raise an error if file can't be read
	if (in->eof()) {
		cerr << "Failed to read " << filename << "!\n";
		delete in;
		exit(-1);
	}

	// store the total number of jobs
	getline(*in, line);
	unsigned int totalJobs = stoi(line);

	unsigned int count = 1;
	while(getline(*in, line)) {

		//used for parsing line
		stringstream ss;

		// Storing the line into stringstream
		ss << line;

		// used for parsing the line
		string temp;

		// current weight
		unsigned int weight;

		// current length
		unsigned int length;

		// extracting current weight
		ss >> temp;

		// check current weight is unsigned int
		if( stringstream(temp) >> weight ){
			
			// clear temp
			temp = "";

			// extract current length
			ss >> temp;

			if( stringstream(temp) >> length ){

				/* create bad and good Job pointers and push 
				 * them to badQueue and goodQueue respectively
				 */
				Job* badCurrent = new Job(count, weight, length, 0);
				badQueue.push(badCurrent);
				Job* goodCurrent = new Job(count, weight, length, 1);
				goodQueue.push(goodCurrent);
			}
		}

		// reset the string stream to be empty
		ss.str("");

		// increment the count
		count++;
	}

	// check that you read in the correct number of jobs
	if ( badQueue.size() != totalJobs || goodQueue.size() != totalJobs ) {
		cerr << "Incorrect Parse!\n";
		delete in;
		exit(-1);
	}

	// no memory leaks here
	delete in;
}

/* Computes the weighted sum of completion times according to two different 
 * scores. BQ is the bad priority queue that uses the non-optimal score
 * weight - length and GQ is the good priority queue that uses the optimal
 * score weight/length.
 */
pair<long,long> computeWeightedSum(priority_queue<Job*, vector<Job*>, JobPtrComp>& BQ,
		                   priority_queue<Job*, vector<Job*>, JobPtrComp>& GQ) {

	// weighted sum of completion times using non-optimal score 
	// weight - length
	long badWeightedSum = 0;

	// weighted sum of completion times using optimal score
	// weight/length
	long goodWeightedSum = 0;

	// current sum of job lengths
	unsigned int completionTime = 0;

	while( !BQ.empty() ){
		
		// get the highest priority job in bad queue
		Job* current = BQ.top();
		BQ.pop();

		/* add the product of the job's weight and
		 * completion time to the current sum
		 */
		completionTime += current->length;
		badWeightedSum += (current->weight)*(completionTime);

		// no memory leaks here
		delete current;
	}

	completionTime = 0;
	while( !GQ.empty() ) {

		// get the highest priority job in good queue 
		Job* current = GQ.top();
		GQ.pop();

		/* add the product of the job's weight and
		 * completion time to the current sum
		 */
		completionTime += current->length;
		goodWeightedSum += (current->weight)*(completionTime);

		// no memory leaks here
		delete current;
	}

	return make_pair(badWeightedSum, goodWeightedSum);

}

int main(int argc, char** argv) {

	// check for arguments
	if( argc != EXPECTED_ARGS ){
		cout << "This program requires 2 arguments!" << endl;
		return -1;
	}

	// uses the non-optimal score weight - length
	priority_queue<Job*, vector<Job*>, JobPtrComp> myBadQueue;

	// uses the optimal score weight/length
	priority_queue<Job*, vector<Job*>, JobPtrComp> myGoodQueue;
		
	// parse the text file and input each job into the 
	// two queues according to their respective scores
	loadfromFile(argv[IN_IDX], myBadQueue, myGoodQueue);

	// compute the weighted sum of completion times
	pair<long, long> completionSumPair = computeWeightedSum(myBadQueue, myGoodQueue);

	// return the weighted sums of completion times. 
	// The first sum uses the non-optimal score weight - length.
	// The second sum uses the optimal score weight/length.
	cout << "Bad Sum of Weighted Completion Times: " << completionSumPair.first << endl;

	cout << "Good Sum of Weighted Completion Times: " << completionSumPair.second << endl;
}


