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

vector<Tocka> graham_scan(vector<Tocka>& tocki) {
    int n = tocki.size();
    if (n <= 2) return tocki;
    sort(tocki.begin(), tocki.end());
    vector<Tocka> hull;
    for (int i=0; i<n; i++) {
        while (hull.size() >= 2 && nasoka(hull[hull.size() - 2], hull.back(), tocki[i]) != KONTRACASOVNIK) {
            hull.pop_back();
        }
        hull.push_back(tocki[i]);
    }

    int dolna_golemina = hull.size();
    for (int i=n-2; i>=0; i--) {
        while (hull.size() > dolna_golemina && nasoka(hull[hull.size() - 2], hull.back(), tocki[i]) != KONTRACASOVNIK) {
            hull.pop_back();
        }
        hull.push_back(tocki[i]);
    }

    hull.pop_back();
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
    vector<Tocka> hull = graham_scan(tocki);
    auto end = chrono::high_resolution_clock::now();
    chrono::duration<double> duration = end-start;

    cout << "Vreme za 500k tocki: " << duration.count() << " sekundi" << endl;
    cout << "Tocki vo obvivkata: " << hull.size() << endl;

    return 0;
}