//
// Created by msobral on 22/08/2019.
//

#ifndef BACON_MAPA_H
#define BACON_MAPA_H

#include <string>
#include <map>
#include <set>
#include <queue>

using std::string;
using std::map;
using std::set;
using std::queue;

// Um objeto Mapa contém as distâncias entre cidades conhecidas
// o conjunto de cidades e suas distâncias são lidos de um arquivo
class Mapa {
public:
    // construtor: cria um objeto Mapa que acessa o conteúdo do arquivo cujo nome é
    // informado no parâmetro path
    Mapa(const string & path);

    // Obtem a lista de cidades conhecidas
    queue<string> cidades() const;

    // Obtem a lista de cidades com distâncias conhecidas desde uma determinada cidade
    queue<string> cidades_vizinhas(const string & cidade);

    // Obtem a distância entre duas cidades. Retorna -1 se distância for desconhecida
    int distancia(const string & origem, const string & destino);

    // esquece todas as cidades já visitadas
    void limpa();
private:
    map<string,map<string,int>> m_cidades;
    set<string> s_cidades;
};


#endif //BACON_MAPA_H
