#define CATCH_CONFIG_RUNNER
#include "catch.hpp"
#include "DSString.h"
#include "Analyzer.h"

#include <iostream>
using namespace std;
void runCatch();
//int main (int argc, char**argv) {}
int main(int argc, char* argv[])
{
    Analyzer* a = new Analyzer();
    a->train(argv);
    a->optimizeTrainingMap();
    a->test(argv);
    a->evaluatePerformance(argv);

  //  a->test(argv);

 //
 //   runCatch();
    return 0;
}
void runCatch()
{
    Catch::Session().run();
}


