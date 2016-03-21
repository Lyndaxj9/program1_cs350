#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

#include "prints.h"
#include <time.h>

void startProcess(int process, int pages) {
    printf("START %d %d\n", process, pages);
}

void referencePage(int process, int page) {
    printf("REFERENCE %d %d\n", process, page);
}

void terminateProcess(int process) {
    printf("TERMINATE %d\n", process);
}

int main (int argc, char ** argv) {
    int u_opt, l_opt, p_opt, r_opt, R_opt, n_opt, N_opt;
    u_opt = l_opt = p_opt = r_opt = R_opt = n_opt = N_opt = 0;

    int process_num = 100;
    int reference_min = 100;
    int reference_max = 250;
    int page_min = 50;
    int page_max = 100;

    int opt;
    opterr = 0;
    while ((opt = getopt(argc, argv, ":ulp:r:R:n:N:")) != -1) {
        switch (opt) {
            case 'u':
                printUsage();
                return 1;
            case 'l':
                l_opt = 1;
                break;
            case 'p':
                p_opt = 1;
                process_num = atoi(optarg);
                if (process_num < 1) {
                    printf("Invalid # of processes.\n");
                }
                break;
            case 'r':
                r_opt = 1;
                reference_min = atoi(optarg);
                if (reference_min < 1) {
                    printf("Invalid min # of references.\n");
                }
                break;
            case 'R':
                R_opt = 1;
                reference_max = atoi(optarg);
                if (reference_max == 0 || reference_max < reference_min) {
                    printf("Invalid max # of references.\n");
                }
                break;
            case 'n':
                n_opt = 1;
                page_min = atoi(optarg);
                if (page_min < 1) {
                    printf("Invalid min # of pages per process.\n");
                }
                break;
            case 'N':
                N_opt = 1;
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

    // if (l_opt) {
    //     printf("Locality enabled.\n");
    // } else {
    //     printf("Locality disabled.\n");
    // }
    // printf("# of processes: %d\n", process_num);
    // printf("References: %d - %d\n", reference_min, reference_max);
    // printf("Pages per process: %d - %d\n", page_min, page_max);

    int processArray[process_num];
    int referenceArray[process_num];
    int pageNumArray[process_num];
    int i;

    for (i = 0; i < process_num; i++) {
        processArray[i] = 0;
        referenceArray[i] = rand() % (reference_max - reference_min) + reference_min;
        pageNumArray[i] = rand() % (page_max - page_min) + page_min;
    }

    int procsRemaining = process_num;

    int active = 10;
    int current = 0;
    int activeProcesses[active];
    // printf("ACTIVE PROCESSES\n");
    for (i = 0; i < active; i++) {
        activeProcesses[i] = i;
        processArray[i] = 1;
        startProcess(i, pageNumArray[i]);
        current++;
    }

    int localityCounter = 0;
    int randomIndex;
    srand(time(NULL));
    while (procsRemaining > 0) {
        if (l_opt) {
            if (localityCounter % 10 == 0) {
                randomIndex = rand() % active;
            }
        } else {
            randomIndex = rand() % active;
        }
        int randomProcess = activeProcesses[randomIndex];

        if (randomProcess != -1) {
            referencePage(randomProcess, rand() % pageNumArray[randomProcess]);
            referenceArray[randomProcess]--;
            // printf("References: %d", referenceArray[randomProcess]);
            if (referenceArray[randomProcess] == 0) {
                terminateProcess(randomProcess);
                processArray[randomProcess] = 2;

                if (procsRemaining > 10) {
                    activeProcesses[randomIndex] = current;
                    startProcess(current, pageNumArray[current]);
                    current++;
                }
                procsRemaining--;
            }
        }
        localityCounter++;
    }
}
