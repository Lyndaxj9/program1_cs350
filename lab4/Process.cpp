#include "Process.h"
#include <stdlib.h>
#include <time.h>
#include <sstream>

#define LOCALITY_RATE 1
#define LOCALITY_FREQ 0.25

Process::Process() {
    this->name = "Default Process";
    numReferences = 10000;
    numPages = 1000;
    numPhases = 10;
    currPhase = 0;
    currReference = 0;
    phases = NULL;
    phaseReferences = NULL;
    locality = NULL;
}

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
        int phaseLen = numPages/numPhases;
        phases[i] = phaseLen * (i+1);
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
    if (phaseReferences) delete [] phaseReferences;
    if (locality) delete [] locality;
}

int Process::randInt(int min, int max) {
    // inclusive
    return rand() % (max - min+1) + min;
}

int Process::getRandPage() {
    int ret;
    if (!currPhase) {
        ret = randInt(0, phases[0]-1);
    } else if (currPhase < numPhases-1) {
        ret = randInt(phases[currPhase-1], phases[currPhase]-1);
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

int Process::getCurrReference() {
    return currReference;
}

std::string Process::start() {
    std::stringstream ss;
    ss.clear();
    ss << numPages;
    return "START " + name + " " + ss.str() + "\n";
}

std::string Process::terminate() {
    return "TERMINATE " + name + "\n";
}

std::string Process::reference(int page) {
    std::stringstream ss;
    ss.clear();
    ss << page+1;
    std::string ret = "REFERENCE " + name + " " + ss.str() + "\n";
    return ret;
}

std::string Process::generate() {
    std::string ret = "";
    if (locality[currPhase]){
        int randomPage = getRandPage();
        ret += reference(randomPage);
        randomPage++;
        currReference++;
        phaseReferences[currPhase]--;
        if (!phaseReferences[currPhase]) {
            currPhase++;
            return ret;
        }

        int numLocality = getLocalityReferences() * LOCALITY_FREQ + 1;
        for (int i = 0; i < numLocality; i++) {
            randomPage++;
            if (randomPage >= numPages) {
                randomPage = phases[numPhases-2];
            }
            ret += reference(randomPage);
            currReference++;
            phaseReferences[currPhase]--;
            if (!phaseReferences[currPhase]) {
                currPhase++;
                return ret;
            }
        }
    } else {
        currReference++;
        phaseReferences[currPhase]--;
        if (!phaseReferences[currPhase]) {
            currPhase++;
            return ret;
        }
        ret += reference(randInt(0, numPages-1));
    }
    return ret;
}
