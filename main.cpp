#include <iostream>
#include "Mapa.h"

using namespace std;

int main(int argc, char * argv[]) {
    if (argc < 2) {
        cerr << "Uso: " << argv[0] << "CIDADE" << endl;
        return 0;
    }
    Mapa mapa("../data/cidades.txt");
    string procurado = argv[1];

    queue<string> cidades = mapa.cidades();
    cout << "As cidades conhecidas são: ";
    while (! cidades.empty()) {
        cout << cidades.front() << ',';
        cidades.pop();
    }
    cout << endl << endl << "Procurando: " << procurado << endl;

    queue<string> q = mapa.cidades_vizinhas(procurado);
    while (! q.empty()) {
        string dest = q.front();
        cout << "--> " << dest << ": ";
        cout << mapa.distancia(procurado, dest) << " km" << endl;
        q.pop();
    }

    return 0;
}