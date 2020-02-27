//
// Created by msobral on 22/08/2019.
//

#include "Mapa.h"
#include <fstream>
#include <iostream>
#include <vector>

using std::ifstream;
using std::exception;
using std::cout;
using std::endl;
using std::vector;

string maiuscula(const string & s) {
    string r;

    for (auto & c: s) r += toupper(c);
    return r;
}

void strip(string &s) {
    int pos = 0;
    while (pos < s.size()) {
        if (!isspace(s[pos])) {
            if (pos > 0) s.erase(0, pos);
            break;
        }
        pos++;
    }
    if (pos == s.size()) {
        s.clear();
        return;
    }

    pos = s.size()-1;
    while (pos >= 0) {
        if (!isspace(s[pos])) {
            if (pos < s.size()-1) s.erase(pos+1);
            break;
        }
        pos--;
    }
}

vector<string> split(const string & s, const string & delim) {
    vector<string> v;
    if (s.empty()) return v;

    //cout << ">>" << s << "===";
    //cout.flush();

    int pos = 0;
    while (pos != string::npos) {
        int pos1 = s.find_first_not_of(delim, pos);
        if (pos1 == string::npos) break;
        pos = s.find_first_of(delim, pos1);
        if (pos == string::npos) {
            v.push_back(s.substr(pos1));
            break;
        } else {
            v.push_back(s.substr(pos1, pos-pos1));
        }
    }
    //cout << "ok" << endl;
    return v;
}

Mapa::Mapa(const string &path) {
    ifstream arq(path);

    if (! arq.is_open()) throw -1;
    string w;
    while (getline(arq, w)) {
        auto v = split(w, ",");
        if (v.size() == 3) {
            m_cidades[v[0]][v[1]] = stoi(v[2]);
        }
    }
}

queue<string> Mapa::cidades_vizinhas(const string &city) {
    queue<string> res;

    // evitar loop
    auto cidade = maiuscula(city);
    if (s_cidades.count(cidade)) return res;
    s_cidades.insert(cidade);

    auto it = m_cidades.find(cidade);
    if (it == m_cidades.end()) return res;
    for (auto &s: it->second) res.push(s.first);
    return res;
}

queue<string> Mapa::cidades() const {
    queue<string> tudo;

//    auto prim = m_cidades.begin();
    for (auto &par: m_cidades) tudo.push(par.first);
    return tudo;
}

void Mapa::limpa() {
    s_cidades.clear();
}

int Mapa::distancia(const string &src, const string &dst) {
    auto origem = maiuscula(src);
    auto destino = maiuscula(dst);
    try {
        return m_cidades.at(origem).at(destino);
    } catch(...){
        try {
            return m_cidades.at(destino).at(origem);
        } catch(...) {
            return -1;
        }
    }
}
