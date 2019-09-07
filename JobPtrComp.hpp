/* Filename: JobPtrComp.hpp
 * Description: Implements a 'function class' for use as the
 *              Compare class in a priority_queue<Job*>. For
 *		this to work, operator< must be defined to do
 *		the right thing on jobs.
 */

#ifndef JOBPTRCOMP_HPP
#define JOBPTRCOMP_HPP

#include <iostream>
#include "Job.hpp"

using namespace std;

/* A 'function class' for use as the Compare class in a 
 * priority_queue<Job*>. For this to work, operator< must
 * be defined to do the right thing on Jobs.
 */

class JobPtrComp {
public:
	bool operator()(Job*& lhs, Job*& rhs) const {
		return *lhs < *rhs;
	}
};

#endif // JOBPTRCOMP_HPP
