#include <iostream>
#include <fstream>
#include <string>
using namespace std;

int main()
{
    char ch;
    fstream fin("./tests.txt", fstream::in);
    while (fin >> noskipws >> ch) {
        cout << ch;
    }
}