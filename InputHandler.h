#ifndef INPUT_HANDLER_H_INCLUDED
#define INPUT_HANDLER_H_INCLUDED

#include <bits/stdc++.h>
#include <sstream>
#include <iostream>
using namespace std;



/*
    header file for handling file operation (input/output)
*/
class InputHandler {
public:
    // Constructor
    InputHandler();

    // Methods to handle parsing
    void parse();
    void parse_algorithms(const string& algorithm_chunk);
    void parse_processes();

private:
    // Helper function to split strings by delimiter
    vector<string> split(const string& str, char delimiter);
};

// Member variables 
    extern string operation;
    extern int last_instant, process_count;
    extern vector<pair<char, int>> policies;
    extern vector<tuple<string, int, int>> processes;
    extern vector<vector<char>> timeline;
    extern unordered_map<string, int> processToIndex;
    extern vector<int> finishTime;
    extern vector<int> turnAroundTime;
    extern vector<float> normTurn;
#endif // INPUT_HANDLER_H_INCLUDED
