# Distâncias entre cidades

Aplicações baseadas em mapas têm sido comuns, ainda mais com a integração com GPS. Um mapa é representado essencialmente por um conjunto de localidades conectadas em uma malha, o que indica quais pares de localidades possuem uma ligação direta entre si (ex: uma estrada). Com isso se pode tanto procurar localidades, quanto descobrir caminhos e calcular distâncias entre elas. Exemplos conhecidos são [Google Maps](http://maps.google.com) e [Waze](https://www.waze.com).  

A identificação de caminhos e cálculo de distâncias é feita diretamente sobre as informações que representam um mapa. Por exemplo, a figura a seguir mostra um mapa simplificado que contém algumas cidades, e as distâncias entre elas. Como se pode observar, o mapa informa diretamente a distância entre Porto Alegre e Brasília (1614 km), mas para saber a distância entre Porto Alegre e Belo Horizonte é necessário primeiro procurar um caminho e então calcular a distância respectiva. Como pode haver mais de um caminho entre essas cidades, algum critério deve ser usado para escolher aquele mais adequado. No caso, pode-se escolher o caminho com menor distância total, ou aquele que passa por menos cidades intermediárias.
 
![Exemplo de mapa de distâncias entre cidades](http://tele.sj.ifsc.edu.br/~msobral/prg2/imagens/cidades.png)

O objetivo deste exercício é **escrever um programa que calcule e apresente o caminho com menor distância total entre duas cidades identificadas em um mapa**. Para isso é necessário:
* Obter uma representação apropriada de um mapa
* Usar um algoritmo de busca para procurar o caminho mais curto

## O mapa de cidades

O conjunto de cidades conhecidas, e as distâncias entre elas, está armazenado em um arquivo de texto. No entanto, para facilitar o desenvolvimento do projeto, é fornecida uma pequena biblioteca de programação capaz de ler esse arquivo e acessar seus dados. Basicamente, essa biblioteca disponibiliza a classe Mapa mostrada a seguir:

```c++
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
};
```

Um exemplo de uso dessa classe Mapa pode ser visto neste pequeno trecho de código:

```c++
    Mapa mapa("../data/cidades.txt");

    queue<string> cidades = mapa.cidades();
    cout << "As cidades conhecidas são: ";
    while (! cidades.empty()) {
        cout << cidades.front() << ',';
        cidades.pop();
    }
```

## Algoritmos de busca

A busca por um caminho mais curto entre duas cidades pode ser feita de duas formas:

* **Usando um algoritmo de busca em largura**: verificam-se cidades em ordem de distância em relação à cidade que é o ponto de partida. A distância é definida pela soma das distâncias entre as cidades vizinhas que formam cada caminho. Quer dizer, primeiro verificam-se todas as cidades vizinhas da cidade inicial. Se a cidade de destino não foi encontrada nessa primeira busca, então, para cada cidade vizinha da cidade inicial, verificam-se suas cidades vizinhas. Se ainda assim a cidade de destino não foi encontrada, então repete-se o procedimento para todas as cidades identificadas na segunda busca, e assim por diante (ver figura a seguir). Esse tipo de algoritmo precisa de uma fila para ser implementado.

    ![Algoritmo de busca em largura (BFS)](http://tele.sj.ifsc.edu.br/~msobral/prg2/imagens/bfs.gif)
    
* **Usando um algoritmo de busca em profundidade**: verificam-se as cidades partindo da cidade inicial e seguindo-se cada cidade vizinha, seguindo-se a cada vez uma sequência de cidades até aquela mais distante (ver figura a seguir). Esse tipo de algoritmo precisa de uma pilha para ser implementado.

    ![Algoritmo de busca em profundidade (DFS)](http://tele.sj.ifsc.edu.br/~msobral/prg2/imagens/dfs.gif)

### Algoritmos de busca

O algoritmo de busca em largura pode ser implementado usando uma fila, onde se armazenam as próximas cidades a serem visitadas.

```
algoritmo busca_bfs():
  cria uma fila
  enfileira nó inicial
  enquanto fila não vazia
    desenfileira um nó
    se for o nó procurado então retorna o valor do nó
    para cada nó adjacente ao nó desenfileirado
      enfileira o nó adjacente
```

O algoritmo de busca em profundidade, por sua vez, pode ser implementado usando uma pilha, onde se armazenam os próximos links a visitar. Ele fica muito parecido com a busca em largura, como se pode perceber neste pseudo-código:

```
algoritmo busca_dfs():
  cria uma pilha
  empilha o nó inicial
  enquanto pilha não vazia
    desempilha um nó
    se for o nó procurado, então retorna o valor do nó
    para cada nó adjacente ao nó desempilhado
      empilha nó adjacente
```
