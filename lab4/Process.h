#include <string>

class Process {
    public:
        Process();
        Process(std::string name, int ref, int pages, int phase, bool loc);
        ~Process();

        int getNumReferences();
        int getCurrReference();

        std::string reference(int page);
        std::string start();
        std::string terminate();
        std::string generate();
    private:
        std::string name;
        int numReferences;
        int numPages;
        int numPhases;
        int currPhase;
        int currReference;
        int * phases;
        int * phaseReferences;
        bool * locality;

        int randInt(int min, int max);
        int getRandPage();
        int getLocalityReferences();
};
