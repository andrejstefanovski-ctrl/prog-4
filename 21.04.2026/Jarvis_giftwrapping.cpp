#include <bits/stdc++.h>

using namespace std;
typedef pair<long long, long long> Tocka;

enum NASOKA { KOLINEARNI, CASOVNIK, KONTRACASOVNIK };

NASOKA nasoka(Tocka a, Tocka b, Tocka c) {
    long long det = a.first * (b.second - c.second) + b.first * (c.second - a.second) + c.first * (a.second - b.second);
    if (det < 0) return CASOVNIK;
    if (det > 0) return KONTRACASOVNIK;
    return KOLINEARNI;
}

vector<Tocka> jarvis_giftwrapping(vector<Tocka>& tocki) {
    int n = tocki.size();
    if (n < 3) return tocki;

    vector<Tocka> hull;
    int p=0;
    for (int i=1; i<n; i++) {
        if (tocki[i].first < tocki[p].first) {
            p = i;
        }
    }

    int start_tocka = p;
    int q;

    do {
        hull.push_back(tocki[p]);
        q = (p+1)%n;
        for (int i=0; i<n; i++) {
            if (nasoka(tocki[p], tocki[i], tocki[q]) == KONTRACASOVNIK) {
                q=i;
            }
        }
        p=q;
    } while (p != start_tocka);

    return hull;
}

int main() {
    int n = 500000;
    vector<Tocka> tocki(n);
    srand(time(0));
    for (int i=0; i<n; i++) {
        tocki[i] = {rand() % 1000000, rand() % 1000000};
    }

    auto start = chrono::high_resolution_clock::now();
    vector<Tocka> hull = jarvis_giftwrapping(tocki);
    auto end = chrono::high_resolution_clock::now();
    chrono::duration<double> duration = end-start;

    cout << "Vreme za 500k tocki: " << duration.count() << " sekundi" << endl;
    cout << "Tocki vo obvivkata: " << hull.size() << endl;

    return 0;
}