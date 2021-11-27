#include <cctype>
#include <fstream>
#include <iostream>
#include <iomanip>
#include <sstream>
#include <string>
#include <vector>
#include <stdlib.h>
#include <time.h>
using namespace std; 

int main()
{
    string s1 = "dididididi"; 
    string s2 = "alksjdlfkjsd"; 
    int x = s1.compare(s2); 
    if(x > 0)
    {
        cout << "S2 goes to the left" << endl; 
    }
    if(x < 0)
    {
        cout << "S2 goes to the right" << endl; 
    }
}