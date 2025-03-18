#include "assets.h"
/** Global Constants **/
const string TRACE = "trace";
const string STATS = "stats";
const string ALGORITHMS[9] = {"", "FCFS", "RR-", "SPN", "SRT", "HRRN", "FB-1", "FB-2i", "AGING"};

bool Utilities:: sortByServiceTime(const tuple<string, int, int> &a, const tuple<string, int, int> &b)
{
    return (get<2>(a) < get<2>(b));
}
bool Utilities:: sortByArrivalTime(const tuple<string, int, int> &a, const tuple<string, int, int> &b)
{
    return (get<1>(a) < get<1>(b));
}

bool Utilities:: descendingly_by_response_ratio(tuple<string, double, int> a, tuple<string, double, int> b)
{
    return get<1>(a) > get<1>(b);
}

bool Utilities:: byPriorityLevel (const tuple<int,int,int>&a,const tuple<int,int,int>&b){
    if(get<0>(a)==get<0>(b))
        return get<2>(a)> get<2>(b);
    return get<0>(a) > get<0>(b);
}

void Utilities:: clear_timeline()
{
    for(int i=0; i<last_instant; i++)
        for(int j=0; j<process_count; j++)
            timeline[i][j] = ' ';
}

string Utilities:: getProcessName(tuple<string, int, int> &a)
{
    return get<0>(a);
}

int Utilities:: getArrivalTime(tuple<string, int, int> &a)
{
    return get<1>(a);
}

int Utilities:: getServiceTime(tuple<string, int, int> &a)
{
    return get<2>(a);
}

int Utilities:: getPriorityLevel(tuple<string, int, int> &a)
{
    return get<2>(a);
}

double Utilities:: calculate_response_ratio(int wait_time, int service_time)
{
    return (wait_time + service_time)*1.0 / service_time;
}

void Utilities:: filltime(){
    for (int i = 0; i < process_count; i++)
    {
        int arrivalTime = getArrivalTime(processes[i]);
        for (int k = arrivalTime; k < finishTime[i]; k++)
        {
            if (timeline[k][i] != '*')
                timeline[k][i] = '.';
        }
    }
}


void Printer:: printAlgorithm(int algorithm_index)
{
    int algorithm_id = policies[algorithm_index].first - '0';
    if(algorithm_id==2)
        cout << ALGORITHMS[algorithm_id] <<policies[algorithm_index].second <<endl;
    else
        cout << ALGORITHMS[algorithm_id] << endl;
}

void Printer::printProcesses()
{
    cout << "Process    ";
    for (int i = 0; i < process_count; i++)
        cout << "|  " << Utilities:: getProcessName(processes[i]) << "  ";
    cout << "|\n";
}
void Printer::printArrivalTime()
{
    cout << "Arrival    ";
    for (int i = 0; i < process_count; i++)
        printf("|%3d  ",Utilities:: getArrivalTime(processes[i]));
    cout<<"|\n";
}
void Printer:: printServiceTime()
{
    cout << "Service    |";
    for (int i = 0; i < process_count; i++)
        printf("%3d  |",Utilities:: getServiceTime(processes[i]));
    cout << " Mean|\n";
}
void Printer::printFinishTime()
{
    cout << "Finish     ";
    for (int i = 0; i < process_count; i++)
        printf("|%3d  ",finishTime[i]);
    cout << "|-----|\n";
}
void Printer::printTurnAroundTime()
{
    cout << "Turnaround |";
    int sum = 0;
    for (int i = 0; i < process_count; i++)
    {
        printf("%3d  |",turnAroundTime[i]);
        sum += turnAroundTime[i];
    }
    if((1.0 * sum / turnAroundTime.size())>=10)
		printf("%2.2f|\n",(1.0 * sum / turnAroundTime.size()));
    else
	 	printf(" %2.2f|\n",(1.0 * sum / turnAroundTime.size()));
}

void Printer::printNormTurn()
{
    cout << "NormTurn   |";
    float sum = 0;
    for (int i = 0; i < process_count; i++)
    {
        if( normTurn[i]>=10 )
            printf("%2.2f|",normTurn[i]);
        else
            printf(" %2.2f|",normTurn[i]);
        sum += normTurn[i];
    }

    if( (1.0 * sum / normTurn.size()) >=10 )
        printf("%2.2f|\n",(1.0 * sum / normTurn.size()));
	else
        printf(" %2.2f|\n",(1.0 * sum / normTurn.size()));
}
void Printer::printStats(int algorithm_index)
{
    printAlgorithm(algorithm_index);
    printProcesses();
    printArrivalTime();
    printServiceTime();
    printFinishTime();
    printTurnAroundTime();
    printNormTurn();
}

void Printer::printTimeline(int algorithm_index)
{
    for (int i = 0; i <= last_instant; i++)
        cout << i % 10<<" ";
    cout <<"\n";
    cout << "------------------------------------------------\n";
    for (int i = 0; i < process_count; i++)
    {
        cout << Utilities:: getProcessName(processes[i]) << "     |";
        for (int j = 0; j < last_instant; j++)
        {
            cout << timeline[j][i]<<"|";
        }
        cout << " \n";
    }
    cout << "------------------------------------------------\n";
}


void ProcessExecutor:: execute_algorithm(char algorithm_id, int quantum,string operation)
{
    switch (algorithm_id)
    {
    case '1':
        if(operation==TRACE)cout<<"FCFS  ";
        firstComeFirstServe();
        break;
    case '2':
        if(operation==TRACE)cout<<"RR-"<<quantum<<"  ";
            roundRobin(quantum);
        break;
    case '3':
        if(operation==TRACE)cout<<"SPN   ";
        shortestProcessNext();
        break;
    case '4':
        if(operation==TRACE)cout<<"SRT   ";
        shortestRemainingTime();
        break;
    case '5':
        if(operation==TRACE)cout<<"HRRN  ";
        highestResponseRatioNext();
        break;
    case '6':
        if(operation==TRACE)cout<<"FB-1  ";
        feedbackQ1();
        break;
    case '7':
        if(operation==TRACE)cout<<"FB-2i ";
        feedbackQ2i();
        break;
    case '8':
        if(operation==TRACE)cout<<"Aging ";
        aging(quantum);
        break;
    default:
        break;
    }
}

void ProcessExecutor:: firstComeFirstServe()
{
    int time = Utilities::getArrivalTime(processes[0]);
    for (int i = 0; i < process_count; i++)
    {
        int processIndex = i;
        int arrivalTime = Utilities::getArrivalTime(processes[i]);
        int serviceTime = Utilities::getServiceTime(processes[i]);

        finishTime[processIndex] = (time + serviceTime);
        turnAroundTime[processIndex] = (finishTime[processIndex] - arrivalTime);
        normTurn[processIndex] = (turnAroundTime[processIndex] * 1.0 / serviceTime);

        for (int j = time; j < finishTime[processIndex]; j++)
            timeline[j][processIndex] = '*';
        for (int j = arrivalTime; j < time; j++)
            timeline[j][processIndex] = '.';
        time += serviceTime;
    }
}
void ProcessExecutor::roundRobin(int originalQuantum) {
    queue<pair<int, int>> readyQueue;  // Renamed 'q' to 'readyQueue'
    int processIndex = 0;  // Renamed 'j' to 'processIndex'

    if (Utilities::getArrivalTime(processes[processIndex]) == 0) {
        readyQueue.push(make_pair(processIndex, Utilities::getServiceTime(processes[processIndex])));
        processIndex++;
    }

    int currentQuantum = originalQuantum;
    for (int currentTime = 0; currentTime < last_instant; currentTime++) {  // Renamed 'time' to 'currentTime'
        if (!readyQueue.empty()) {
            int currentProcessIndex = readyQueue.front().first;  // Renamed 'processIndex' to 'currentProcessIndex'
            readyQueue.front().second = readyQueue.front().second - 1;
            int remainingServiceTime = readyQueue.front().second;
            int processArrivalTime = Utilities::getArrivalTime(processes[currentProcessIndex]);  // Renamed 'arrivalTime' to 'processArrivalTime'
            int processServiceTime = Utilities::getServiceTime(processes[currentProcessIndex]);  // Renamed 'serviceTime' to 'processServiceTime'

            currentQuantum--;
            timeline[currentTime][currentProcessIndex] = '*';

            while (processIndex < process_count && Utilities::getArrivalTime(processes[processIndex]) == currentTime + 1) {
                readyQueue.push(make_pair(processIndex, Utilities::getServiceTime(processes[processIndex])));
                processIndex++;
            }

            if (currentQuantum == 0 && remainingServiceTime == 0) {
                finishTime[currentProcessIndex] = currentTime + 1;
                turnAroundTime[currentProcessIndex] = finishTime[currentProcessIndex] - processArrivalTime;
                normTurn[currentProcessIndex] = static_cast<double>(turnAroundTime[currentProcessIndex]) / processServiceTime;
                currentQuantum = originalQuantum;
                readyQueue.pop();
            } else if (currentQuantum == 0 && remainingServiceTime != 0) {
                readyQueue.pop();
                readyQueue.push(make_pair(currentProcessIndex, remainingServiceTime));
                currentQuantum = originalQuantum;
            } else if (currentQuantum != 0 && remainingServiceTime == 0) {
                finishTime[currentProcessIndex] = currentTime + 1;
                turnAroundTime[currentProcessIndex] = finishTime[currentProcessIndex] - processArrivalTime;
                normTurn[currentProcessIndex] = static_cast<double>(turnAroundTime[currentProcessIndex]) / processServiceTime;
                readyQueue.pop();
                currentQuantum = originalQuantum;
            }
        }

        while (processIndex < process_count && Utilities::getArrivalTime(processes[processIndex]) == currentTime + 1) {
            readyQueue.push(make_pair(processIndex, Utilities::getServiceTime(processes[processIndex])));
            processIndex++;
        }
    }
    Utilities::filltime();
}

void ProcessExecutor::shortestProcessNext()
{
    // Priority queue to hold (service time, process index) pairs, ordered by service time (ascending)
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> readyQueue;
    int processIndex = 0;

    for (int currentTime = 0; currentTime < last_instant; currentTime++) {
        // Add processes to the ready queue if their arrival time has arrived
        while (processIndex < process_count && Utilities::getArrivalTime(processes[processIndex]) <= currentTime) {
            readyQueue.push(make_pair(Utilities::getServiceTime(processes[processIndex]), processIndex));
            processIndex++;
        }

        if (!readyQueue.empty()) {
            int currentProcessIndex = readyQueue.top().second;
            int processArrivalTime = Utilities::getArrivalTime(processes[currentProcessIndex]);
            int processServiceTime = Utilities::getServiceTime(processes[currentProcessIndex]);
            readyQueue.pop();

            int tempTime = processArrivalTime;
            // Mark time intervals before the process starts as idle
            for (; tempTime < currentTime; tempTime++)
                timeline[tempTime][currentProcessIndex] = '.';

            tempTime = currentTime;
            // Mark the process execution time
            for (; tempTime < currentTime + processServiceTime; tempTime++)
                timeline[tempTime][currentProcessIndex] = '*';

            finishTime[currentProcessIndex] = (currentTime + processServiceTime);
            turnAroundTime[currentProcessIndex] = finishTime[currentProcessIndex] - processArrivalTime;
            normTurn[currentProcessIndex] = static_cast<double>(turnAroundTime[currentProcessIndex]) / processServiceTime;

            currentTime = tempTime - 1; // Adjust current time to reflect the process execution time
        }
    }
}

void ProcessExecutor::shortestRemainingTime()
{
    // Priority queue to hold (remaining service time, process index) pairs, ordered by remaining time (ascending)
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> readyQueue;
    int processIndex = 0;

    for (int currentTime = 0; currentTime < last_instant; currentTime++) {
        // Add processes to the ready queue if their arrival time has arrived
        while (processIndex < process_count && Utilities::getArrivalTime(processes[processIndex]) == currentTime) {
            readyQueue.push(make_pair(Utilities::getServiceTime(processes[processIndex]), processIndex));
            processIndex++;
        }

        if (!readyQueue.empty()) {
            int currentProcessIndex = readyQueue.top().second;
            int remainingServiceTime = readyQueue.top().first;
            readyQueue.pop();
            int processServiceTime = Utilities::getServiceTime(processes[currentProcessIndex]);
            int processArrivalTime = Utilities::getArrivalTime(processes[currentProcessIndex]);

            timeline[currentTime][currentProcessIndex] = '*';

            if (remainingServiceTime == 1) { // Process finished
                finishTime[currentProcessIndex] = currentTime + 1;
                turnAroundTime[currentProcessIndex] = finishTime[currentProcessIndex] - processArrivalTime;
                normTurn[currentProcessIndex] = static_cast<double>(turnAroundTime[currentProcessIndex]) / processServiceTime;
            } else {
                readyQueue.push(make_pair(remainingServiceTime - 1, currentProcessIndex));
            }
        }
    }
    Utilities::filltime();
}

void ProcessExecutor::highestResponseRatioNext()
{
    // Vector of tuple <process_name, process_response_ratio, time_in_service> for processes that are in the ready queue
    vector<tuple<string, double, int>> readyProcesses;
    int processIndex = 0;

    for (int currentTime = 0; currentTime < last_instant; currentTime++) {
        // Add processes to the ready queue if their arrival time has arrived
        while (processIndex < process_count && Utilities::getArrivalTime(processes[processIndex]) <= currentTime) {
            readyProcesses.push_back(make_tuple(Utilities::getProcessName(processes[processIndex]), 1.0, 0));
            processIndex++;
        }

        // Calculate response ratio for every process
        for (auto &proc : readyProcesses) {
            string processName = get<0>(proc);
            int processID = processToIndex[processName];
            int waitTime = currentTime - Utilities::getArrivalTime(processes[processID]);
            int processServiceTime = Utilities::getServiceTime(processes[processID]);
            get<1>(proc) = Utilities::calculate_response_ratio(waitTime, processServiceTime);
        }

        // Sort processes by response ratio, highest to lowest
        sort(readyProcesses.begin(), readyProcesses.end(), Utilities::descendingly_by_response_ratio);

        if (!readyProcesses.empty()) {
            int selectedProcessIndex = processToIndex[get<0>(readyProcesses[0])];
            while (currentTime < last_instant && get<2>(readyProcesses[0]) != Utilities::getServiceTime(processes[selectedProcessIndex])) {
                timeline[currentTime][selectedProcessIndex] = '*';
                currentTime++;
                get<2>(readyProcesses[0])++;
            }
            currentTime--;
            readyProcesses.erase(readyProcesses.begin()); // Process is now completed

            finishTime[selectedProcessIndex] = currentTime + 1;
            turnAroundTime[selectedProcessIndex] = finishTime[selectedProcessIndex] - Utilities::getArrivalTime(processes[selectedProcessIndex]);
            normTurn[selectedProcessIndex] = static_cast<double>(turnAroundTime[selectedProcessIndex]) / Utilities::getServiceTime(processes[selectedProcessIndex]);
        }
    }
    Utilities::filltime();
}

void ProcessExecutor::feedbackQ1()
{
    // Priority queue to hold (priority level, process index) pairs, ordered by priority level (ascending)
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> processQueue;
    unordered_map<int, int> remainingServiceTime; // Map from process index to the remaining service time
    int processIndex = 0;

    if (Utilities::getArrivalTime(processes[0]) == 0) {
        processQueue.push(make_pair(0, processIndex));
        remainingServiceTime[processIndex] = Utilities::getServiceTime(processes[processIndex]);
        processIndex++;
    }

    for (int currentTime = 0; currentTime < last_instant; currentTime++) {
        if (!processQueue.empty()) {
            int currentPriorityLevel = processQueue.top().first;
            int currentProcessIndex = processQueue.top().second;
            int arrivalTime = Utilities::getArrivalTime(processes[currentProcessIndex]);
            int serviceTime = Utilities::getServiceTime(processes[currentProcessIndex]);
            processQueue.pop();

            while (processIndex < process_count && Utilities::getArrivalTime(processes[processIndex]) == currentTime + 1) {
                processQueue.push(make_pair(0, processIndex));
                remainingServiceTime[processIndex] = Utilities::getServiceTime(processes[processIndex]);
                processIndex++;
            }

            remainingServiceTime[currentProcessIndex]--;
            timeline[currentTime][currentProcessIndex] = '*';

            if (remainingServiceTime[currentProcessIndex] == 0) {
                finishTime[currentProcessIndex] = currentTime + 1;
                turnAroundTime[currentProcessIndex] = (finishTime[currentProcessIndex] - arrivalTime);
                normTurn[currentProcessIndex] = (turnAroundTime[currentProcessIndex] * 1.0 / serviceTime);
            } else {
                if (processQueue.size() >= 1)
                    processQueue.push(make_pair(currentPriorityLevel + 1, currentProcessIndex));
                else
                    processQueue.push(make_pair(currentPriorityLevel, currentProcessIndex));
            }
        }

        while (processIndex < process_count && Utilities::getArrivalTime(processes[processIndex]) == currentTime + 1) {
            processQueue.push(make_pair(0, processIndex));
            remainingServiceTime[processIndex] = Utilities::getServiceTime(processes[processIndex]);
            processIndex++;
        }
    }
    Utilities::filltime();
}

void ProcessExecutor::feedbackQ2i()
{
    // Priority queue to hold (priority level, process index) pairs, ordered by priority level (ascending)
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> processQueue;
    unordered_map<int, int> remainingServiceTime; // Map from process index to the remaining service time
    int processIndex = 0;

    if (Utilities::getArrivalTime(processes[0]) == 0) {
        processQueue.push(make_pair(0, processIndex));
        remainingServiceTime[processIndex] = Utilities::getServiceTime(processes[processIndex]);
        processIndex++;
    }

    for (int currentTime = 0; currentTime < last_instant; currentTime++) {
        if (!processQueue.empty()) {
            int currentPriorityLevel = processQueue.top().first;
            int currentProcessIndex = processQueue.top().second;
            int arrivalTime = Utilities::getArrivalTime(processes[currentProcessIndex]);
            int serviceTime = Utilities::getServiceTime(processes[currentProcessIndex]);
            processQueue.pop();

            while (processIndex < process_count && Utilities::getArrivalTime(processes[processIndex]) <= currentTime + 1) {
                processQueue.push(make_pair(0, processIndex));
                remainingServiceTime[processIndex] = Utilities::getServiceTime(processes[processIndex]);
                processIndex++;
            }

            int currentQuantum = pow(2, currentPriorityLevel);
            int tempTime = currentTime;

            while (currentQuantum && remainingServiceTime[currentProcessIndex]) {
                currentQuantum--;
                remainingServiceTime[currentProcessIndex]--;
                timeline[tempTime++][currentProcessIndex] = '*';
            }

            if (remainingServiceTime[currentProcessIndex] == 0) {
                finishTime[currentProcessIndex] = tempTime;
                turnAroundTime[currentProcessIndex] = (finishTime[currentProcessIndex] - arrivalTime);
                normTurn[currentProcessIndex] = (turnAroundTime[currentProcessIndex] * 1.0 / serviceTime);
            } else {
                if (processQueue.size() >= 1)
                    processQueue.push(make_pair(currentPriorityLevel + 1, currentProcessIndex));
                else
                    processQueue.push(make_pair(currentPriorityLevel, currentProcessIndex));
            }

            currentTime = tempTime - 1;
        }

        while (processIndex < process_count && Utilities::getArrivalTime(processes[processIndex]) <= currentTime + 1) {
            processQueue.push(make_pair(0, processIndex));
            remainingServiceTime[processIndex] = Utilities::getServiceTime(processes[processIndex]);
            processIndex++;
        }
    }
    Utilities::filltime();
}

void ProcessExecutor::aging(int originalQuantum)
{
    // Vector to store (priority level, process index, waiting time) for ready processes
    vector<tuple<int, int, int>> readyQueue;
    int processIndex = 0, currentProcessIndex = -1;

    // Iterate through each time step
    for (int currentTime = 0; currentTime < last_instant; currentTime++) {
        // Add new arrivals to the ready queue
        while (processIndex < process_count && Utilities::getArrivalTime(processes[processIndex]) <= currentTime) {
            readyQueue.push_back(make_tuple(Utilities::getPriorityLevel(processes[processIndex]), processIndex, 0));
            processIndex++;
        }

        // Update priorities and waiting times
        for (int i = 0; i < readyQueue.size(); i++) {
            if (get<1>(readyQueue[i]) == currentProcessIndex) {
                // Reset waiting time and maintain priority for current process
                get<2>(readyQueue[i]) = 0;
                get<0>(readyQueue[i]) = Utilities::getPriorityLevel(processes[currentProcessIndex]);
            } else {
                // Increment priority and waiting time for other processes
                get<0>(readyQueue[i])++;
                get<2>(readyQueue[i])++;
            }
        }

        // Sort processes based on priority level (ascending)
        sort(readyQueue.begin(), readyQueue.end(), Utilities::byPriorityLevel);

        // Select process with highest priority (lowest priority level value)
        currentProcessIndex = get<1>(readyQueue[0]);
        int remainingQuantum = originalQuantum;

        // Process execution and idle states
        while (remainingQuantum-- && currentTime < last_instant) {
            for (int p = 0; p < process_count; p++) {
                if (p == currentProcessIndex) {
                    // Mark as executing
                    timeline[currentTime][p] = '*';
                } else if (Utilities::getArrivalTime(processes[p]) <= currentTime) {
                    // Mark as idle
                    timeline[currentTime][p] = '.';
                } else {
                    // Mark before arrival
                    timeline[currentTime][p] = ' ';
                }
            }
            currentTime++;
        }
        currentTime--; // Adjust for outer loop increment
    }

    // Fill wait time statistics
    Utilities::filltime();
}
