#include "InputHandler.h"

string operation;
int last_instant, process_count;
vector<pair<char, int>> policies;
vector<tuple<string, int, int>> processes;
vector<vector<char>> timeline;
unordered_map<string, int> processToIndex;
vector<int> finishTime;
vector<int> turnAroundTime;
vector<float> normTurn;

// Constructor definition
InputHandler::InputHandler() {
    // Initialize any variables if needed
}

// Method to parse the entire input
void InputHandler::parse() {
    string algorithm_chunk;
    cin >> operation >> algorithm_chunk >> last_instant >> process_count;
    parse_algorithms(algorithm_chunk);
    parse_processes();
    finishTime.resize(process_count);
    turnAroundTime.resize(process_count);
    normTurn.resize(process_count);
    timeline.resize(last_instant);
    for (int i = 0; i < last_instant; i++) {
        for (int j = 0; j < process_count; j++) {
            timeline[i].push_back(' ');
        }
    }
}

// Method to parse the algorithms
void InputHandler::parse_algorithms(const string& algorithm_chunk) {
    stringstream stream(algorithm_chunk);
    while (stream.good()) {
        string temp_str;
        getline(stream, temp_str, ',');
        stringstream ss(temp_str);
        getline(ss, temp_str, '-');
        char algorithm_id = temp_str[0];
        getline(ss, temp_str, '-');
        int quantum = temp_str.size() >= 1 ? stoi(temp_str) : -1;
        policies.push_back(make_pair(algorithm_id, quantum));
    }
}

// Method to parse the processes
void InputHandler::parse_processes() {
    string process_chunk, process_name;
    int process_arrival_time, process_service_time;
    for (int i = 0; i < process_count; i++) {
        cin >> process_chunk;

        stringstream stream(process_chunk);
        string temp_str;
        getline(stream, temp_str, ',');
        process_name = temp_str;
        getline(stream, temp_str, ',');
        process_arrival_time = stoi(temp_str);
        getline(stream, temp_str, ',');
        process_service_time = stoi(temp_str);

        processes.push_back(make_tuple(process_name, process_arrival_time, process_service_time));
        processToIndex[process_name] = i;
    }
}
