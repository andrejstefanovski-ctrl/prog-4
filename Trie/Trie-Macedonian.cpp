#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <windows.h>
using namespace std;

struct Trie {
    bool end = false;
    map<string, Trie*> next;
};

/* Logikata pozadi bitmask: 
Vo UTF-8 postoi slednovo: 
1B karakteri(ASCII) se zapisuvaat kako: 0xxxxxxx 
2B karakteri: 110xxxxx 
3B karakteri: 1110xxxx 
4B karakteri: 11110xxx 
koristejki na logicko AND nie mozeme so pomos na bitmask da gi pretvorime vo edno od slednive vrednosti: 
Maska: 0xE0(11100000); Ocekuvan Rezultat(1B): 0xC0(11000000) 
Maska: 0xD0(11110000); Ocekuvan Rezultat(2B): 0xE0(11100000) 
Maska: 0xF8(11111000); Ocekuvan Rezultat(4B): 0xF0(11110000) 
andrej stefanovski
da vizuelizirame so primer: 
c:      110xxxxx 
AND:    11100000 
--------------------- 
        11000000 == Ocekuvan Rezultat(1B) = TRUE, znaci c e 1B itn itn. */

string nextRune(const string& s, int& i) { //UTF Rune e vsusnost integer value za nekoj UTF-8 character
    unsigned char c = s[i]; //zemi go prviot bajt od UTF-8 karakterot
    int bytes = 1; //default e 1B(ASCII)
    if ((c & 0xE0) == 0xC0) bytes = 2;  //proverkata shto ja zborev
    else if ((c & 0xF0) == 0xE0) bytes = 3; //andrej stefanovski
    else if ((c & 0xF8) == 0xF0) bytes = 4;

    string r = s.substr(i, bytes); //zemi go celosniot UTF-8 rune
    i += bytes; //odnesi go inkeksot napred za tolku bajti kolku sto e rune-to
    return r; //vrati go detektiraniot UTF-8 karakter
}

void insertTrie(Trie* root, const string& word) { //stefanovski
    Trie* cur = root;
    for (int i=0; i<word.size();) { //ova ne e klasicna iteracija tuku UTF-8 iteracija
        string r = nextRune(word, i);
        if (!cur->next.count(r)) //ako ne postoi patekata, kreiraj nov jazol andrejstefanovski
            cur->next[r] = new Trie();
        cur = cur->next[r];
    }
    cur->end = true; //kraj na zborot
}

void printTrie(Trie* t, string prefix = "") { //klasicno za printanje
    if (t->end) cout << prefix << "\n"; //ako postoi krajot prijntaj go zborot andst
    for (auto& kv : t->next)
        printTrie(kv.second, prefix + kv.first);
}

int main() {
    SetConsoleOutputCP(CP_UTF8); //moralo za windows
    SetConsoleCP(CP_UTF8);

    Trie* root = new Trie();

    ifstream fin("MK-dict.txt");
    if (!fin.is_open()) {
        cerr << "NE MOZE DA SE OTVORI TXT FAJLOT!!\n";
        return 1;
    }

    string line;
    while (getline(fin, line)) {
        if (!line.empty() && line.back() == '\r')
            line.pop_back();
        insertTrie(root, line);
    }
    fin.close();

    printTrie(root);
    return 0;
}