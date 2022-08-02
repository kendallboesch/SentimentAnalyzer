#include "Analyzer.h"

using namespace std;

                //Sentiment values
const int POS = 4;
const int NEG = 0;
const double pVal = .01;
const double nVal = -.01;

/**************
 *
 *          ANALYZER CONSTRUCTOR
 */
Analyzer::Analyzer()
{
    applyStopWords();
    validChars = "ABCDEFGHIJKLMN;:-~OPQRSTUVWXYZabcdefgh'ijklmn opqrstu\"v123456\'7890wxyz!@#$%^&*()-+=[]{}|/?,.<>";
}
/**********
 *          APPLY STOP WORDS
 *
 *       READS IN STOP WORDS INTO THE ANALYZER STOPWORD
 *       VECTOR
 **********/
void Analyzer::applyStopWords()
{

   vector<DSString> stopWrds = {"i", "me", "my", "myself", "we", "our", "ours", "ourselves", "you", "your", "yours", "yourself",
                 "yourselves", "he", "him", "his", "himself", "she", "her", "hers", "herself", "it", "its", "itself", "got",
                 "they", "them", "their", "theirs", "themselves", "what", "which", "who", "whom", "this", "that", "these",
                 "those", "am", "is", "are", "was", "were", "be", "been", "being", "have", "has", "had", "having", "do", "does",
                 "did", "doing", "a", "an", "the", "and", "but", "if", "or", "because", "as", "until", "while", "of", "at",
                 "by", "for", "with", "about", "against", "between", "into", "through", "during", "before", "after", "above",
                 "below", "to", "from", "up", "down", "in", "out", "on", "off", "over", "under", "again", "further", "then",
                 "once", "here", "there", "when", "where", "why", "how", "all", "any", "both", "each", "few", "more", "most",
                 "other", "some", "such", "no", "nor", "not", "only", "own", "same", "so", "than", "too", "very", "s", "t",
                 "can", "will", "just", "don", "should", "now", "when's", "I", "when", "whens", "��", "�","♫", "♥", "☆", "...",
                 "yu", "ur", "ll", "d", "re", "ve", "yo", "yet", "ya", "ed", "yall", "y", "AM", "PM", "k","th", "st", "ml",
                 "mg", "ish", "g", "d","c", "get", "km", "oz", "pm", "yr", "yrs", "…", "⌘", "-", "x�","y�", "a", "b","c",
                 "d", "e", "f", "g", "h", "i", "j", "k", "l", "m", "n", "o", "p", "q", "r", "u", "v", "w", "x", "y", "z", " ",
                 "while", "awhile", "here", "on", "off", "up", "down", "want", "wanna", "who", "£", "¡"} ;
   for(int i = 0; i < stopWrds.size(); i++)
   {
       DSString add = stopWrds[i];
       stopWords[add] = 1000;
   }
   cout << "       ----------- STOP WORDS LOADED ----------- " << endl;
}
/*******************
 *
 *              TRAIN
 *
 *     OPENS TRAINING DATA FILE, READS IN TWEETS AND SENTIMENT VALUES
 *     & CALLS PARSING METHOD, & SENTIMENT UPDATE METHOD
 *
 * @param argv
 ****************/
void Analyzer::train(char* argv[])
{
    ifstream fileIn;
    fileIn.open(argv[1]);       //OPEN TRAINING FILE
    if(fileIn.is_open())                // CHECK IF FILE IS OPEN
    {
        cout << " -------------FILE OPENED_______" << endl;
    }
    else
    {
        cout<< "Failed to open file" << endl;
    }
    char temp[100]; // line < 350
    fileIn.getline(temp, 50);   // FIRST LINE IN FILE IS HEADER - DISREGARD

    int i = 0;      // ITERATOR FOR FILE, INCREMENTS EVERY TIME A NEW TWEET IS READ

    char value [5];     // READ IN AS CHAR SENTIMENT VALUE
    int valueIn;    // SENTIMENT VALUE
    char id[15];
    char date[50];
    char nq[10];    // IGNORE
    char user[25];
    char data [300];        // STORING THE TWEET

    while(i < 20000)
    {
        fileIn.getline(value, 5, ',');
        fileIn.getline(id, 15, ',');
        fileIn.getline(date, 50, ',');
        fileIn.getline(nq, 10, ',');
        fileIn.getline(user, 25, ',');
        fileIn.getline(data, 300);

        valueIn = atoi(value);      // CHANGE VALUE FROM CHAR TO INT
        DSString tweet(data);
        tweet.makeLower();


        vector<DSString> parsedWords;
        wordParse4(parsedWords, tweet); // PARSE WORDS FROM TWEET
        updateSentiment(parsedWords, valueIn);  // ASSIGN WORDS VALUES IN DICTIONARY MAP

        i++;
    }
    fileIn.close();
    cout << "------------TRAINING COMPLETE--------" << endl;
}
/*************
 *          UPDATE SENTIMENT
 *
 *       INTAKES VECTOR OF PARSED WORDS & THEIR ASSOCIATED SENTIMENT
 *       TRAVERSES DICTIONARY MAP FOR THE WORDS, IF THEY EXIST,
 *       UPDATE THEIR SENTIMENT ACCORDING TO THE VALUE PASSED IN
 *       IF THEY DO NOT EXIST, CREATE A NEW PAIR ON THE MAP &
 *       INITIALIZE ITS SENTIMENT ACCORDING TO VALUE PASSED
 *
 * @param parsedData
 * @param val
 */
void Analyzer::updateSentiment(vector<DSString>& parsedData, int val)
{

    long numWords = parsedData.size();      // NUMBER OF WORDS PASSED
    double increment; // VALUE ADDED TO THE STANDING SENTIMENT VALUE

    if (val == POS)     // IF TWEET PASSED WAS POSITIVE
    {
        increment = .01;
    }
    else if (val == NEG)        // IF TWEET PASSED WAS NEGATIVE
    {
        increment = -.01;
    }
    else
    {
        cout << "INVALID SENTIMENT VALUE" << endl;
        return;
    }

    for(int i = 0; i < numWords; i++)       // ITERATE THROUGH VECTOR
    {
        DSString popped = parsedData.at(numWords - (i+1));  //GET LAST ELEMENT IN VECTOR
      //  popped = popped.makeLower();

            if(dictionary.find(popped) == dictionary.end())     //CHECK IF EXISTS IN DICTIONARY
            {
                // not in dictionary yet
                dictionary.insert(pair<DSString, double> (popped, increment)); // ADD TO DICTIONARY
            }
            else
            {
                // ALREADY EXISTS IN DICTIONARY
                dictionary[popped] = dictionary[popped] + increment;    // UPDATE SENTIMENT VALUE ACCORDINGLY
            }


        parsedData.pop_back(); // GET THE NEXT WORD
    }
}
/************
 *
 *          WORD PARSE 4
 *
 *      TAKES IN REFERENCE TO VECTOR OF WORDS & THE DATA FROM
 *      THE TWEET UN PARSED. TRAVERSES THE DSSTRING OF DATA
 *      PARSING INTO WORDS & ADDING TO THE VECTOR THOSE
 *      THAT ARE LONGER THAN 3 CHARS & DO NOT EXIST IN THE STOP
 *      WORD VECTOR
 *
 * @param words
 * @param data
 */
void Analyzer::wordParse4(vector<DSString>& words, DSString data)
{
   // vector<char> allowed

    char* temp = new char[data.getLength()];        // UNPARSED DATA
  //  cout << data.getLength() << endl;
    int l = 0;      // L TRACKS INDEX IN THE WORD BEING CREATED
    for(int i = 0; i < data.getLength(); i++)   // I TRACKS INDEX IN THE ORIGINAL DATA STRING
    {
        if(validChars.indexOf(data[i]) != -1)
        {


            if (data[i] == ' ' || data[i] == ',' || data[i] == '.' || data[i] == '!'
                || data[i] == '?' || data[i] == '"' || data[i] == '-' || data[i] == ':'
                || data[i] == '/' || data[i] == '(' || data[i] == ')' || data[i] == ';'
                || data[i] == '@' || data[i] == '&' || data[i] == '=' || data[i] == '*'
                || data[i] == '#' || data[i] == '~' || data[i] == '%' || data[i] == '^')       // CHARACTERS THAT INDICATE THE END OF A WORD
            {
                if (l > 1)  // IF THE WORD IS LONGER THAN 3 CHARS,
                {
                    temp[l] = '\0';
                    DSString word(temp);
//                    if(word.contains("ing"))
//                    {
//                        word = word.substring(0, word.getLength() - 3);
//                    }
                     //word.makeLower();
                    if (stopWords.find(word) == stopWords.end()) // IF THE NEW WORD DOES NOT EXIST IN STOPWORDS
                    {
                        words.push_back(word);  // ADD THE NEW WORD TO THE VECTOR
                        // cout << word << endl;
                    }
                }
                l = 0;      // NEW WORD STARTING, INDEX 0

            }
            else        // IF THE DATA[I] DOES NOT == END OF WORD INDICATOR
            {
                temp[l] = data[i];  // ADD THE CURRENT CHAR TO THE NEXT INDEX OF THE NEW WORD
                l++;    // INCREMENT NEW WORD LENGTH
            }
        }
        else
        {
            l = 0;
           // cout << "----- INVALID CHAR:  " << data[i] << endl;
        }
    }
}

void Analyzer::test(char* argv[])
{
    ifstream inFile;
    inFile.open(argv[2]);

    if (inFile.is_open())
    {
        cout << "TEST FILE OPENED" << endl;
    }
    else
    {
        cout << "TEST FILE FAILED TO OPEN" << endl;
    }
    char temp[100];
    inFile.getline(temp, 100);
    int i = 0;

    char id[15];
    char date[50];
    char nq[10];
    char user[25];
    char data[300];


    while(i < 20000)
    {
        inFile.getline(id, 15, ',');
        inFile.getline(date, 50, ',');
        inFile.getline(nq, 10, ',');
        inFile.getline(user, 25, ',');
        inFile.getline(data, 300);

        DSString tweet(data);
        vector<DSString> parsed;
        DSString analyzed;
        DSString dest;

        wordParse4(parsed, tweet);
        char sentimentScore = tweetAnalysis(parsed);
        char concat[5];
        concat[0] = sentimentScore;
        concat[1] = ',';
        analyzed = concat;

        dest = analyzed + id;



        analysis.push_back(dest);
    //    cout << dest << endl;

        i++;
    }
    inFile.close();
}


char Analyzer::tweetAnalysis(vector<DSString>& words)
{
    DSString word;
    double pointValue = 0;

    for(int i = 0; i < words.size(); i++)
    {
        word = words.at(i);
        for(auto itr = dictionary.begin(); itr != dictionary.end(); itr++)
        {
            if(itr->first == word)
            {
                pointValue = pointValue + itr->second;
            }
        }

    }
    //cout << pointValue << endl;

    if(pointValue < 0.0)
    {
        return '0';
    }
    else if(pointValue > 0.0)
    {
        return '4';
    }
    else
    {
        return 'X';
    }
}

void Analyzer::optimizeTrainingMap()
{

    auto itr = dictionary.begin();
    while (itr != dictionary.end())
    {
        double currentSentValue = itr->second;
        double absSentval = abs(currentSentValue);
        if(absSentval < 1.15)
        {
               // dictionary.erase(itr++);
                itr = dictionary.erase(itr);
        }
        else
        {
            if(itr++ != dictionary.end())
            {
                itr++;
            }
            break;
        }
    }
    cout << "--------EXIT TRAINING MAP OPTIMIZATION -------" << endl;
}

void Analyzer::evaluatePerformance(char* argv[])
{
    vector<DSString> incorrect;
    double nCorrect = 0;
    double nTotal = 0;
    ifstream inFs;
    inFs.open(argv[3]);
    char temp[50];
    inFs.getline(temp, 50);     // CONTAINS FILE HEADER

    char inActual[1];
    int actual;
    char inCalculated[5];
    int calculated;

    char id[15];
    DSString ID;
    DSString analyzedResult;

    for(int o = analysis.size() - 1; o > 0; o--)
    {
        inFs.getline(inActual, 1, ',');
        inFs.getline(id, 15);

        actual = atoi(inActual);
        analyzedResult = analysis.at(o);

        inCalculated[0] = analyzedResult[0];
        inCalculated[1] = '\0';
        calculated = atoi(inCalculated);
        ID = id;

        if(actual == calculated)
        {
            nCorrect++;
        }
        else
        {
            incorrect.push_back(analyzedResult.substring(2));
        }

        nTotal++;
    }
    cout << nCorrect /nTotal << endl;
    ofstream out;
    out.open("output.txt");
    if(out.is_open())
    {
        cout << "---------- OUTPUT FILE OPENED--------" << endl;
    }
    else
    {
        cout << "---------FAILED TO OPEN OUTPUT FILE ------ " << endl;
    }
    DSString popped;
    double accuracy = nCorrect / nTotal;
    //TODO: SET PRECISION

    out << setprecision(3) << accuracy  << endl;
    for(int num = 0; num < incorrect.size(); num++)
    {
        popped = incorrect.at(num);
        out << popped << endl;

    }

}