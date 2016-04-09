// Lab 4
// Ra, Nuri
// Ademola, Lynda
// Fischman, Daelin

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <iostream>

#include "prints.h"
#include "Process.h"
#include <time.h>

int main (int argc, char ** argv) {
    // Process p("12345", 1000, 200, 10, true); 
    // while (p.currReference < p.numReferences) {
    //     std::cout << p.generate();
    // }

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
}
