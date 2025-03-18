#include <iostream>
#include "InputHandler.h"
#include "assets.h"

using namespace std;

int main() {
    // Instantiate InputHandler to parse inputs
    InputHandler handler;
    handler.parse();
    for (int index = 0; index < (int)policies.size(); index++)
    {
        Utilities:: clear_timeline();
        ProcessExecutor:: execute_algorithm(policies[index].first, policies[index].second,operation);
        if (operation == TRACE)
            Printer:: printTimeline(index);
        else if (operation == STATS)
            Printer:: printStats(index);
        cout << "\n";
    }
    return 0;
}
