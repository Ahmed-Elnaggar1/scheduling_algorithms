# Scheduling Algorithm Visualization

## Overview
This repository is an academic project that implements and visualizes **eight CPU scheduling algorithms**. The project provides an interactive way to observe how different scheduling techniques allocate CPU time to processes. Each algorithm is accompanied by a corresponding visualization image to aid in understanding their execution flow.

Additionally, the project includes a **Dockerfile** for easy setup and execution, along with a structured set of test cases and an automated testing script.

## Implemented Scheduling Algorithms
The following scheduling algorithms are implemented:

1. **First-Come, First-Served (FCFS)**
2. **Round Robin (RR)**
3. **Shortest Process Next (SPN)**
4. **Shortest Remaining Time (SRT)**
5. **Highest Response Ratio Next (HRRN)**
6. **Feedback Queue (FB-1)** (Single-level feedback queue)
7. **Feedback Queue (FB-2i)** (Multilevel feedback queue with increasing time quantum)
8. **Aging Algorithm** (Priority-based scheduling with aging to prevent starvation)

Each scheduling method is visualized using a graphical representation, showcasing the execution timeline and process transitions.

## Project Structure
```
📂 scheduling-algorithms
│-- 📂 test_cases        # Predefined test cases for validation
│-- 📝 Dockerfile        # Docker setup for execution
│-- 📝 README.md         # Project documentation
│-- 📝 tester.sh         # Shell script for automatic testing
```

## Features
- **Algorithm Visualization**: Each scheduling method is represented with a timeline image.
- **Automated Testing**: A `tester.sh` script is included for running test cases automatically.
- **Predefined Test Cases**: A collection of test cases to validate scheduling behavior.
- **Docker Support**: The project includes a `Dockerfile` for seamless execution in a containerized environment.

## Prerequisites
Before running the project, ensure you have the following installed:
- **GCC** (for compiling the scheduling algorithms)
- **Make** (for build automation)
- **Docker** (optional, for containerized execution)

## Installation & Usage
### Running the Project Manually
1. Clone the repository:
   ```bash
   git clone https://github.com/yourusername/scheduling-algorithms.git
   cd scheduling-algorithms
   ```
2. Compile the project:
   ```bash
   make
   ```
3. Run the scheduling program with test cases:
   ```bash
   ./scheduler test_cases/test1.txt
   ```

### Running with Docker
1. Build the Docker image:
   ```bash
   docker build -t scheduling-algorithms .
   ```
2. Run the container:
   ```bash
   docker run --rm scheduling-algorithms
   ```

### Running the Automatic Tester
To execute all test cases and verify output correctness:
```bash
./tester.sh
```
### FCFS Scheduling Output  
![FCFS Scheduling](https://res.cloudinary.com/dgqimvydy/image/upload/v1742304329/yhsk2eo35cawppnfvkuk.png)

### Round Robin Scheduling Output  
![RR Scheduling](https://res.cloudinary.com/dgqimvydy/image/upload/v1742304329/ldxqgbivdgavsr4a1k2g.png)

### Aging Scheduling Output  
![Aging Scheduling](https://res.cloudinary.com/dgqimvydy/image/upload/v1742304329/l0viobdfpa10jaausrdb.png)
