#include "Process.h"
#include <stdlib.h>
#include <time.h>
#include <sstream>
#include <iostream>

#define LOCALITY_RATE 0.5
#define LOCALITY_FREQ 0.25

Process::Process(std::string name, int ref, int pages, int phase, bool loc) {
    this->name = name;
    numReferences = ref;
    numPages = pages;
    numPhases = phase;
    currPhase = 0;
    currReference = 0;
    phases = new int[numPhases];
    phaseReferences = new int[numPhases];
    locality = new bool[numPhases];

    // Initialize end of phase ranges
    for (int i = 0; i < numPhases-1; i++) {
        phases[i] = (numPages/numPhases) * (i+1);
    } 
    phases[numPhases-1] = numPages;

    // Initialize number of references per phase, distribute evenly
    int total = 0;
    for (int i = 0; i < numPhases-1; i++) {
        phaseReferences[i] = numReferences/numPhases;
        total += phaseReferences[i];
    }
    phaseReferences[numPhases-1] = numReferences - total;

    for (int i = 0; i < numPhases; i++) {
        locality[i] = 0;
    }
    srand(time(NULL));
    // randomly distribute locality
    if (loc) {
        int numRand = numPhases * LOCALITY_RATE;
        for (int i = 0; i < numRand; i++) {
            locality[rand() % numPhases] = true;
        }
    }
}

Process::~Process() {
    if (phases) delete [] phases;
    if (locality) delete [] locality;
    if (phaseReferences) delete [] phaseReferences;
}

int Process::randInt(int min, int max) {
    // inclusive
    return rand() % (max - min + 1) + min;
}

int Process::getRandPage() {
    int ret;
    if (!currPhase) {
        ret = randInt(0, phases[0]);
    } else if (currPhase < numPhases-1) {
        ret = randInt(phases[currPhase-1], phases[currPhase]);
    } else {
        ret = randInt(phases[currPhase-1], numPages-1);
    }
    return ret;
}

int Process::getLocalityReferences() {
    int ret;
    if (!currPhase) {
        ret = phases[0];
    } else if (currPhase < numPhases-1) {
        ret = phases[currPhase] - phases[currPhase-1];
    } else {
        ret = phases[numPhases-1] - phases[numPhases-2];
    }
    return ret;
}

int Process::getNumReferences() {
    return numReferences;
}

int Process::getNumPages() {
    return numPages;
}

std::string Process::reference(int page) {
    std::string ret = "REFERENCE " + name + " ";
    std::stringstream ss;
    ss << page;
    std::string pageStr;
    ss >> pageStr;
    return ret + pageStr + "\n";
}

std::string Process::generate() {
    std::string ret = "";
    if (locality[currPhase]){
        // std::cout << "LOCALITY REFERENCE:" << std::endl;
        int randomPage = getRandPage();
        ret += reference(randomPage);
        randomPage++;
        currReference++;
        phaseReferences[currPhase]--;
        if (!phaseReferences[currPhase]) {
            //std::cout << "NEW PHASE:" << std::endl;
            currPhase++;
            return ret;
        }

        int numLocality = getLocalityReferences() * LOCALITY_FREQ + 1;
        for (int i = 0; i < numLocality; i++) {
            // roll back locality references if max is reached
            randomPage++;
            if (randomPage >= numPages) {
                randomPage = phases[numPhases-2];
            }
            ret += reference(randomPage);
            currReference++;
            if (!phaseReferences[currPhase]) {
                //std::cout << "NEW PHASE:" << std::endl;
                currPhase++;
                return ret;
            }
            phaseReferences[currPhase]--;
        }
    } else {
        // std::cout << "REGULAR REFERENCE:" << std::endl;
        currReference++;
        if (!phaseReferences[currPhase]) {
            //std::cout << "NEW PHASE:" << std::endl;
            currPhase++;
            return ret;
        }
        phaseReferences[currPhase]--;
        ret += reference(randInt(0, numPages-1));
    }
    return ret;
}
