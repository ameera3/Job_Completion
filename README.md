# Job_Completion

## Usage
To compile, type "make". To run the program, type "./Job_Completion jobs.txt".

## Introduction
The command line program, Job_Completion.cpp, takes in one parameter, an input file name. 
The input file specified by the input file name should contain a list of jobs with 
positive integral weights and lengths. The program runs two greedy algorithms to determine 
the sum of the weighted completion times. The first greedy algorithm is non-optimal
and uses the score weight - length. The second greedy algorithm is optimal and uses the 
score weight/length.
