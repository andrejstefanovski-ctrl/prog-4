//
// Created by Andrej on 12/7/2025.
//

#include <iostream>
#include <vector>
#include <string>
#include <cctype>
#include <fstream>

using namespace std;

struct Trie {
    Trie* children[26] = {NULL};
    bool is_end_word = false;
    string label=""; //za patricia edge
};

void add_to_trie(Trie* root, const string& str) {
    Trie* curr = root;
    for (char ch : str) { //izmini gi site charovi vo stringot
        char c = tolower(ch); //napravi gi so mali bukvi
        if (c < 'a' || c > 'z') continue; //izbegni gi ne-malite bukvi (special characters)
        //CREATED BY ANDREJ STEFANOVSKI
        int ind = c - 'a'; //napravi ja sekoja bukva vo odreden indeks (a-0, b-1, c-2, ..., z-25)

        if (!curr->children[ind])
            curr->children[ind] = new Trie(); //napravi dete ako nema za taa bukva

        curr = curr->children[ind]; //odi na novoto dete
    }
    curr->is_end_word = true; //oznaci kraj na zborot posle postapkite andrej stefaovski
}

void convert_patricia(Trie* node) {
    if (!node) return;

    for (int i=0; i<26; i++) {
        if (node->children[i])
            convert_patricia(node->children[i]); //post-order i so ova rekurzivno ke gi kompresirame site deca prvo
    }

    int brojac = 0, ind = -1; //ova e vsusnost  kolku deca ima nekoj clen i index na nekoe negobo dete
    for (int i=0; i<26; i++) {
        if (node->children[i]) {
            brojac++;
            ind = i;
        }
    }
    if (brojac != 1) return; //ako clenot nema tocno edno dete togas nemoze da se kompresira
    Trie* child = node->children[ind];
    //CREATED BY ANDREJ STEFANOVSKI
    node->label.push_back('a' + ind);
    node->label += child->label; //spoj gi podatocite od deteto na roditelot created by andst
    for (int i=0; i<26; i++)
        node->children[i] = child->children[i]; //decata na deteto se sega deca na roditelot
    node->is_end_word = child->is_end_word; //sega ima nov kraj
    delete child; //ubi go staroto dete, sega ima novo dete
}

void print_trie(Trie* node, string &current) { //rekurzivna postapka za da gi isprinta site zborovi vo Trieto
    if (!node) return;

    if (node->is_end_word) //ako stignavme do krajot pecati go zborot
        cout << current << "\n";

    for (int i=0; i<26; i++) {
        if (node->children[i]) { //ako postoi dete
            current.push_back('a' + i); //stavi ja momentalnata bukva vo current created by andrej st
            print_trie(node->children[i], current); //sega rekurzivno povikaj se za noviot current
            current.pop_back(); //backtracking za tocno da gradime novi zborovi
        }
    }
}

void print_patricia(Trie* node, string &current) { //print funkcija za patricia
    if (!node) return;
    current += node->label; //dodai go label-ot vo current
    if (node->is_end_word) //andrej stefanovski
        cout << current << "\n"; //stignavme do kraj, pecati

    for (int i=0; i<26; i++) {
        if (node->children[i])
            print_patricia(node->children[i], current); //istata rekurzija kako kaj obicniot print
    }
    current.erase(current.size() - node->label.size()); //backtracking
}

bool search_trie(Trie* root, const string& str) { //prebaraj go zborot vo Trie-to
    Trie* curr = root;
    for (char ch : str) { //pomini gi site bukvi vo stringot
        char c = tolower(ch); //pretvori ja bukvata vo mala bukva
        if (c < 'a' || c > 'z') return false;

        int ind = c - 'a'; //zemi go indeksot
        if (!curr->children[ind]) //ako nema deca vrati netocno
            return false; //CREATED BY ANDREJ STEFANOVSKI
        curr = curr->children[ind]; //premesti se na deteto
    }
    return curr->is_end_word; //vrati deka e kraj na zborot
}

bool search_patricia(Trie* node, const string& word, int pos = 0) { //prebaraj za patricia
    if (!node) return false;

    int len = node->label.size();

    // ako preostanatiot zbor e pomal od label-ot, ne moze da postoi
    if (word.size()-pos < len) return false;

    for (int i=0; i<len; i++) {
        if (tolower(word[pos + i]) != node->label[i]) //ako ne se sovpagjaat
            return false;
    }
    //andrej stefanovski
    pos += len; // premesti ja pozicijata po labelot
    if (pos == word.size()) // dojde do kraj
        return node->is_end_word;

    // inaku idi do narednoto dete
    char next_char = tolower(word[pos]);
    if (next_char < 'a' || next_char > 'z') return false;

    int ind = next_char - 'a';
    return search_patricia(node->children[ind], word, pos);
}

int main() {
    Trie* root = new Trie();
    //string path = "C:/Users/Andrej/GITHUB REPOSITORY/prog-4/string-matching/wiki-100k.txt";
    string path = "./wiki-100k.txt";
    ifstream txt(path);

    vector<string> words;
    string line;

    while (getline(txt, line)) {
        if (line.empty())
            continue;
        if (line[0] == '#')
            continue;

        words.push_back(line);
    }
    for (int i=0; i<words.size(); i++) {
        add_to_trie(root, words[i]);
    }
    string temp;
    print_trie(root, temp);

    convert_patricia(root);
    print_patricia(root, temp);

    return 0;
}
