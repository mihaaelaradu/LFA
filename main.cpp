#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#define MARIME 1000
using namespace std;

ifstream f("fisier.in");
ofstream g("fisier.out");
vector <pair<int, string> > dfa[MARIME];

void input(int &n, int &m) {
    f >> n >> m;
    for (int i = 0; i < m; ++i) {
        int x, y;
        string cuv;
        f >> x >> y >> cuv;
        dfa[x].push_back({y, cuv});
    }
}



void verificare(string test, int init, int nf, int fin[]) {
    int q = init;                     // q - numarul starii curente
    vector <int> states;               // vectorul starilor
    states.push_back(q);

    for (int i = 0; i < test.size(); ++i)
    for (int j = 0; j < dfa[q].size(); ++j)
        if (dfa[q][j].second[0] == test[i]) {
            q = dfa[q][j].first;
            states.push_back(q);
            break;
        }

                            // Verficam daca ultima stare e finala
    int k = 0, aux = states[states.size() - 1];
    for (int i = 1; i <= nf && k == 0; ++i)
        if (fin[i] == aux) k = 1;

                           // Afisare
    if (k == 0)
        g << "NU\n";
    else {
        g << "DA\nTraseu: ";
        for (int i = 0; i < states.size(); ++i)
            g << states[i] << " ";
        g << "\n";
    }

    states.clear();
}

int main() {
    int n, m;
                           // Citim DFA
    input(n,m);

    int init, nf;         // Starea initiala, numar stari finale
    f >> init >> nf;

    int fin[nf];          // Stari finale
    for (int i = 1; i <= nf; ++i)
        f >>fin[i];

    int nr_teste;
    f >> nr_teste;

    string test;
    for (int i = 0; i < nr_teste; ++i) {
        f >>test;
                       // Verificam daca cuvantul este acceptat
        verificare(test, init, nf, fin);
    }

    f.close();
    g.close();
    return 0;
}


