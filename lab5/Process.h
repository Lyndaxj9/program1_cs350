#ifndef PROCESS_H
#define PROCESS_H

class Process {
    private:
        int processNumber;
        int addressSpaceSize;
        int * pages;
        int pagesInMemory;

    public:
        Process();
        Process(int pNum, int size);
        ~Process();

        Process & operator=(const Process &rhs);

        int getProcessNumber();
        int getProcessSize();
        int * getPages();

        int getPageLocation(int pageNum);
        int getRandomPage();
        void setPageLocation(int pageNum, int loc);
		int getSize();
};

#endif
