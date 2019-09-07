/* Filename: Job.hpp
 * Description: Implements a job class for the problem of minimizing
 *              the weighted sum of job completion times. The score
 *		is weight - length.
 */

#ifndef JOB_HPP
#define JOB_HPP

#include <iostream>
#include <iomanip>

using namespace std;

/*
 * Class Name: Job
 * Instance Variables:
 * Description: Implements a job class for the problem of minimizing
 *              the weighted sum of job completion times. The score is
 *		weight minus length.
 * Public Methods:
 * Private Methods: None
 */

class Job {

public:
	unsigned int number; // job number
	unsigned int weight; // job weight
	unsigned int length; // job length
	unsigned int flag;   // which score to use
	int badScore; 	     // job score weight - length
	double goodScore;    // job score weight/length

	// constructor
	Job(unsigned int number, unsigned int weight, unsigned int length, 
			unsigned int flag)
		: number(number), weight(weight), length(length), flag(flag),
		  badScore(weight - length),
		  goodScore( ((double) weight)/((double) length) ) { }

	/* Less-than comparison, so that jobs will work in a priority queue
	 * We want larger scores to have higher priority. If the scores are
	 * the same, the job with higher weight has higher priority. A flag
	 * of zero tells us to use badScore whereas a flag of 1 tells us to
	 * use goodScore.
	 */
	bool operator<(const Job& other) {

		// use bad score
		if( this->flag == 0 ) {
			// if scores are different, just compare scores
			if( this->badScore != other.badScore ) {
				return this->badScore < other.badScore;
			}
			// scores are equal. use weight to break tie
			return this->weight < other.weight;
		}

		// use good score
		if( this->flag == 1 ){
			// if scores are different, just compare scores
			if( this->goodScore != other.goodScore ) {
				return this->goodScore < other.goodScore;
			}
			// scores are equal. Use weight to break tie
			return this->weight < other.weight;
		}
	}	

};

// For printing a Job to an ostream. Useful for debugging 
ostream& operator<<(ostream&, const Job&) __attribute__((weak));
ostream& operator<<(ostream& stm, const Job& j) {
	stm << "[" ;
	stm << setw(10) << &j;
	stm << "; #:" << j.number;
	stm << "; w:" << j.weight;
	stm << "; l:" << j.length;
	stm << "; f:" << j.flag;
	stm << "; bs:" << j.badScore; 
	stm << "; gs:" << j.goodScore << "]";
	return stm;
}

#endif // JOB_HPP
