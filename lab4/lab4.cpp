// Lab 4
// Ra, Nuri
// Ademola, Lynda
// Fischman, Daelin

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <iostream>
#include <sstream>

#include "prints.h"
#include "Process.h"
#include <time.h>

#define ACTIVE_PROCS 10

int randInt(int min, int max) {
    //inclusive
    return rand() % (max - min+1) + min;
}

int main (int argc, char ** argv) {
    int l_opt;
    l_opt = 0;

    int process_num = 1000;
    int phase_num = 5;
    int reference_min = 1000;
    int reference_max = 2500;
    int page_min = 500;
    int page_max = 1000;

    int opt;
    opterr = 0;
    while ((opt = getopt(argc, argv, ":ulp:P:r:R:n:N:")) != -1) {
        switch (opt) {
            case 'u':
                printUsage();
                return 1;
            case 'l':
                l_opt = 1;
                break;
            case 'p':
                process_num = atoi(optarg);
                if (process_num < 1) {
                    printf("Invalid # of processes.\n");
                }
                break;
            case 'P':
                phase_num = atoi(optarg);
                if (phase_num < 1) {
                    printf("Invalid # of phases.\n");
                }
                break;
            case 'r':
                reference_min = atoi(optarg);
                if (reference_min < 1) {
                    printf("Invalid min # of references.\n");
                }
                break;
            case 'R':
                reference_max = atoi(optarg);
                if (reference_max == 0 || reference_max < reference_min) {
                    printf("Invalid max # of references.\n");
                }
                break;
            case 'n':
                page_min = atoi(optarg);
                if (page_min < 1) {
                    printf("Invalid min # of pages per process.\n");
                }
                break;
            case 'N':
                page_max = atoi(optarg);
                if (page_max < 1 || page_max < page_min) {
                    printf("Invalid max # of pages per process.\n");
                }
                break;
            case ':':
                printNoArg(optopt);
                return 1;
            case '?':
                printNoOpt(optopt);
                return 1;
        }
    }
    
    srand(time(NULL));
    Process * processes = new Process[process_num];
    int * validProcesses = new int[ACTIVE_PROCS];
    for (int i = 0; i < ACTIVE_PROCS; i++) {
        validProcesses[i] = -1;
    }

    if (process_num < ACTIVE_PROCS) {
        for (int i = 0; i < process_num; i++) {
            validProcesses[i] = i;
        }
    } else {
        for (int i = 0; i < ACTIVE_PROCS; i++) {
            validProcesses[i] = i;
        }
    }

    std::stringstream ss;
    for (int i = 0; i < process_num; i++) {
        ss.str(std::string());
        ss << i;
        processes[i] = Process(ss.str(), randInt(reference_min, reference_max),
                randInt(page_min, page_max), phase_num, l_opt);
    }

    int currProcess = 10;
    int terminated = 0;
    while (terminated < process_num) {
        int randProc = randInt(0, ACTIVE_PROCS-1);
        while (validProcesses[randProc] == -1) {
            randProc = randInt(0, ACTIVE_PROCS-1);
        }
        // std::cout << "Random Process: " << randProc << std::endl;
        std::cout << processes[validProcesses[randProc]].generate();
        if (processes[validProcesses[randProc]].numReferences == 
                processes[validProcesses[randProc]].currReference) {
            std::cout << "TERMINATE " << processes[validProcesses[randProc]].name << std::endl;
            if (currProcess < process_num) {
                validProcesses[randProc] = currProcess;
            } else {
                validProcesses[randProc] = -1;
            }
            currProcess++;
            terminated++;
        }
    }
    
    //std::cout << processes[2].generate();
    
    // std::cout << "ACTIVE PROCESSES:" << std::endl;
    // for (int i = 0; i < ACTIVE_PROCS; i++) {
    //     std::cout << validProcesses[i] << std::endl;
    // }

    //std::cout << processes[1].generate();

    if (processes) delete [] processes;
    if (validProcesses) delete [] validProcesses;

    // Process p("12345", randInt(reference_min, reference_max),
    //         randInt(page_min, page_max), phase_num, l_opt); 
    // while (p.currReference < p.numReferences) {
    //     std::cout << p.generate();
    // }

}
