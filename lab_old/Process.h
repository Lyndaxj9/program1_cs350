#ifndef PROCESS_H
#define PROCESS_H

class Process{
    private:
        int pNum;
        int size;
        int* pages;
        int* location;

    public:
        Process();
        Process(int pid, int sizeN);
        ~Process();
        Process (const Process &rhs);
        Process& operator=(const Process &rhs);
        int getPnum();
        int* getAddrsp();
        void setValid(int pgN);
        void setInvalid(int pgN);        
        int getPgStat(int pgN);
        void setLocation(int pgN, int loc);
};

#endif
