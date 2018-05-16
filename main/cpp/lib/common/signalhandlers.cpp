#include "logfile.h"

#include <csignal>
#include <cstdlib>
#include <iostream>

#define NUMSIG 256

using namespace std;

void writeUnexpectedTermination()
{
        string msg = "UNEXPECTED TERMINATION OF PROGRAM!";

        cerr << endl;
        cerr << msg << endl;
        cerr.flush();

        LogFile::writeToAllLogFiles(msg);
}

typedef void (*SignalHandler)(int);

SignalHandler oldSigHandlers[NUMSIG];

void terminationHandler(int sig)
{
        writeUnexpectedTermination();

        if (sig < NUMSIG && oldSigHandlers[sig])
                oldSigHandlers[sig](sig);

        exit(-1);
}

void installSignalHandlers()
{
        for (int i = 0; i < NUMSIG; i++)
                oldSigHandlers[i] = 0;

        int sigs[] = {SIGABRT, SIGQUIT, SIGSEGV, SIGTERM, -1};
        int pos    = 0;
        while (sigs[pos] >= 0) {
                int sigNum             = sigs[pos];
                oldSigHandlers[sigNum] = signal(sigNum, terminationHandler);
                pos++;
        }
}
