//
// Created by mark on 6/2/2021.
//
//ADD FILE HEADER


#include "DSString.h"

using namespace std;

/**********
 *                                  DEFAULT CONSTRUCTOR
 **********/
DSString::DSString()
{
    cstr = nullptr;
}
/**********
 *                                  SIZE CONSTRUCTOR
 * @param n
 **********/
DSString::DSString(int n)
{
    cstr = new char[n + 1];
//    cstr[strlen(cstr)] = '\0';
    cstr[n + 1] = '\0';
}
/**********
*                                   ARGUMENT CONSTRUCTOR
**********/
DSString::DSString(const char* cIn)
{
    cstr = new char[strlen(cIn)+ 1];
    strcpy(cstr, cIn);
    cstr[strlen(cIn)] = '\0';
}
/**********
*                                   COPY CONSTRUCTOR
**********/
DSString::DSString(const DSString& sIn)
{
    cstr = new char[strlen(sIn.cstr) + 1];
    strcpy(cstr, sIn.cstr);
    cstr[strlen(sIn.cstr)] = '\0';
}
/**********
*                                  DECONSTRUCTOR
**********/
DSString::~DSString()
{
//    if(cstr != nullptr && cstr != "" && cstr != NULL)
//    {
    delete [] cstr;
//    }
}
/**********
 *                                  GET LENGTH
 * @return int
 **********/
int DSString::getLength()
{
    return strlen(cstr);
}
/**********
 *                                  OVERLOADED GREATER THAN OPERATOR >
 * @param arg
 * @return
 **********/
bool DSString::operator> (const char* arg) const
{
    return strcmp(cstr, arg) > 0;
}
/*********
 *
 * @param arg
 * @return
 */
bool DSString::operator<(const char* arg) const
{
    return strcmp(cstr, arg) < 0;
}
/******************
 *
 * @param arg
 * @return
 */
bool DSString::operator>(const DSString& arg) const
{
    return strcmp(cstr,arg.cstr) > 0;
}
bool DSString::operator<(const DSString& arg) const
{
    return strcmp(cstr, arg.cstr) < 0;
}
/**********
 *                                  OVERLOADED COMPARISON OPERATOR W CHAR* PARAM
 * @param arg
 * @return
 */
bool DSString::operator== (const char* arg) const
{

    return strcmp(this->cstr, arg) == 0;
}
/**********
 *                              OVERLOADED COMPARISON OPERATOR W DSSTRING PARAM
 * @param arg
 * @return
 *********/
bool DSString::operator== (const DSString& arg) const
{
    return strcmp(this->cstr, arg.cstr) == 0;
}
/**********
 *                          OVERLOADED ASSIGNMENT OPERATOR W CHAR* PARAM
 * @param arg
 * @return
 */
DSString& DSString::operator= (const char* arg)
{
    if (cstr != nullptr && cstr != "" && cstr != NULL)
    {
        delete [] cstr;
    }
    cstr = new char[strlen(arg) + 1];
    strcpy(cstr, arg);
    cstr[strlen(arg)] = '\0';
    return *this;
}
/**********
 *                         OVERLOADED ASSIGNMENT OPERATOR W DSSTRING& PARAM
 * @param arg
 * @return
 */
DSString& DSString::operator= (const DSString& arg)
{
    if (cstr != nullptr && cstr != "" && cstr != NULL)
    {
        delete [] cstr;
    }
    cstr = new char[strlen(arg.cstr) +1];
    strcpy(cstr, arg.cstr);
    cstr[strlen(arg.cstr)] = '\0';
    return *this;
}
/**********
 *                      OVERLOADED INDEXING OPERATOR
 * @param n
 * @return
 **********/
char& DSString::operator[] (const int n) const
{
    return this->cstr[n];
}
/**********
 *                      OVERLOADED CONCATENATION OPERATOR
 * @param arg
 * @return
 */
DSString DSString::operator+ (const DSString& arg)
{
    int length = strlen(this->cstr) + strlen(arg.cstr);
    char* temp = new char[length + 1];
    strcpy(temp, this->cstr);
    strcat(temp, arg.cstr);
    DSString dest = DSString(temp);
    delete [] temp;
    return dest;
}
/**********
 *                              SUBSTRING
 * @param start
 * @param numChars
 * @return
 */
DSString DSString::substring(int start, int numChars)
{
    // start is the index that the substring will start on
    // numChars is the total number of chars INCLUDING start that will be copied
    //into a new substring
    if(cstr == nullptr)
    {
        return nullptr;
    }
    char* temp = new char[numChars + 1];
    int i = 0;
    // edit: have to make sure that you do not overwrite the original string here
    while(i < numChars && i+start < strlen(cstr))
    {
        temp[i] = cstr[i + start];
        i++;
    }
    temp[i] = '\0';
    DSString s(temp);

    delete [] temp;

    return s;
}
/**********
 *                              SUBSTRING FROM N TO END
 * @param s
 * @return
 */
DSString DSString::substring(int s)
{
    int newLen = strlen(cstr) - s;
    char* temp = new char[newLen + 1];

    for(int i = 0; i < newLen; i++)
    {
        temp[i] = cstr[s + i];
    }
    temp[newLen] = '\0';
    DSString sub(temp);
    delete [] temp;
    return sub;
}
/**********
 *                      C_STR
 * @return
 */
char* DSString::c_str()
{
    return cstr;
}
/**********
 *                          OVERLOADED STREAM INSERTION OPERATOR
 * @param out
 * @param c
 * @return
 */
ostream& operator<< (ostream &out, const DSString& c)
{
    out << c.cstr;
    return out;
}
/**********
 *                          INDEX OF
 * @param c
 * @return
 */
int DSString::indexOf(char c)
{
    if(cstr != nullptr)
    {
        for(int i = 0; i < strlen(cstr); i++)
        {
            if(cstr[i] == c)
            {
                return i;
            }
        }
        return -1;
    }
    return -1;
}
bool DSString::contains(char* key)
{
    DSString tmp(cstr);
    int length = 0;
    char c = key[0];
    int keySize = strlen(key);
    int index = 1000;
    //char* testCstr = new char[keySize + 1];
    DSString test(keySize + 1);
    bool searching = true;
    while(searching)
    {
        length = strlen(tmp.cstr);
        index = tmp.indexOf(c);

        if(index == -1 || keySize > length)
        {
          //  std::cout << "String not found: " << key << std::endl;
            return false;
        }
        else
        {
            tmp = tmp.substring(index);
            if (test.cstr != nullptr && test.cstr != "" && test.cstr != NULL)
            {
                test.cstr = nullptr;
            }
            test = tmp.substring(0, keySize);
            test[keySize + 1] = '\0';

            if(test == key)
            {
                std::cout << "FOUND: " << key << std::endl;
                searching = false;
            }
        }
    }
    return true;
}
char DSString::begin()
{
    return cstr[0];
}
char DSString::end()
{
    return cstr[strlen(cstr) - 1];
}
DSString DSString::operator+ (const char c)
{
    int length = strlen(cstr) + 2;
    char* temp = new char[length];
    strcpy(temp, cstr);
    temp[length - 1] = c;
    temp[length] = '\0';

    DSString dest(temp);
    delete [] temp;
    return dest;
}

void DSString::makeLower()
{
   // vector<char> upper;

    for(int i = 0; i < strlen(cstr); i++)
    {
       cstr[i] = tolower(cstr[i]);
    }
}
