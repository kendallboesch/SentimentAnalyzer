//
// Created by Kendalll Boesch on 1/31/22.
//

#ifndef PA01_SENTIMENT_ANALYZER_H
#define PA01_SENTIMENT_ANALYZER_H

#include "DSString.h"
#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
#include <map>

using namespace std;
class Analyzer{
public:
    Analyzer();
    void applyStopWords();    // add stop words to dictionary - default, constant sentiment values of 0;
    void train(char*[]);        // builds dictionary, read in word, if not stop check tweet sentiment, add to dictionary if not there & increment by necessary semtiment value
    void test(char*[]);
    void wordParse4(vector<DSString>&, DSString);
    void updateSentiment(vector<DSString>&, int);
    char tweetAnalysis(vector<DSString>&);
    void optimizeTrainingMap();
    void evaluatePerformance(char*[]);

private:
    std::map<DSString, double> dictionary;
    std::map<DSString, int> stopWords;
    std::vector<DSString> analysis;
    DSString validChars;




};


#endif //PA01_SENTIMENT_ANALYZER_H
