#include "prints.h"

void printUsage() {
    fprintf(stderr, 
            "lab4 [-u] [-locality] [-p <num-processes>] [-P <num-phases>]\n"
            "[-r <ref-min>] [-R <ref-max>] [-n <process-page-min] [-N <process-page-max]\n"
            "-u : show usage\n"
            "-l : enable locality of reference\n"
            "-p : number of processes\n"
            "-P : number of phases\n"
            "-r : minimum # of references per process\n"
            "-R : maximum # of references per process\n"
            "-n : minimum # of pages per process\n"
            "-N : maximum # of pages per process leaves\n");
}

void printNoArg(char opt) {
    fprintf(stderr,
            "-%c option given with no argument.\n\n", opt);
    printUsage();
}

void printNoOpt(char opt) {
    fprintf(stderr,
            "-%c option is not a valid option,\n\n", opt);
    printUsage();
}
