#ifndef ASSETS_H_INCLUDED
#define ASSETS_H_INCLUDED

#include <iostream>
#include <vector>
#include <tuple>
#include <string>


#include "InputHandler.h"
using namespace std;

// Printer Class: Handles all the printing
class Printer {
public:
    static void printAlgorithm(int algorithm_index);
    static void printProcesses();
    static void printArrivalTime();
    static void printServiceTime();
    static void printFinishTime();
    static void printTurnAroundTime();
    static void printNormTurn();
    static void printStats(int algorithm_index);
    static void printTimeline(int algorithm_index);
};

// ProcessExecutor Class: Responsible for scheduling algorithm execution
class ProcessExecutor {
public:
    static void execute_algorithm(char algorithm_id, int quantum,string operation);
    static void firstComeFirstServe();
    static void roundRobin(int quantum);
    static void shortestProcessNext();
    static void shortestRemainingTime();
    static void highestResponseRatioNext();
    static void feedbackQ1();
    static void feedbackQ2i();
    static void aging(int quantum);
};

// Utilities Class: Common utility functions
class Utilities {
public:
    static bool sortByServiceTime(const tuple<string, int, int> &a, const tuple<string, int, int> &b);
    static bool sortByArrivalTime(const tuple<string, int, int> &a, const tuple<string, int, int> &b);
    static bool descendingly_by_response_ratio(tuple<string, double, int> a, tuple<string, double, int> b);
    static bool byPriorityLevel (const tuple<int,int,int>&a,const tuple<int,int,int>&b);
    static void clear_timeline();
    static string getProcessName(tuple<string, int, int> &a);
    static int getArrivalTime(tuple<string, int, int> &a);
    static int getServiceTime(tuple<string, int, int> &a);
    static int getPriorityLevel(tuple<string, int, int> &a);
    static double calculate_response_ratio(int wait_time, int service_time);
    static void filltime();

};

extern const string TRACE;
extern const string STATS;
extern const string ALGORITHMS[];

#endif // ASSETS_H_INCLUDED
