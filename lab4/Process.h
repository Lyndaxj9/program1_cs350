#include <string>

class Process {
    public:
        Process(std::string name, int ref, int pages, int phase, bool loc);
        ~Process();

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
        int getNumReferences();
        int getNumPages();
        std::string reference(int page);
        std::string generate();
    private:
};
