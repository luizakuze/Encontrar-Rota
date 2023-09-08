#include "funcoes.h"

// Função que realiza a leitura dos dados de um arquivo
void le_arquivo (const string & nome_arquivo, unordered_map<string, list<adjacente>>& mapa) {

    // Abre um arquivo contendo a relação de cidades de distâncias
    ifstream arq(nome_arquivo);
    if (!arq.is_open()) {
        perror("Erro ");
        exit(errno);
    }

    string linha;
    string cidade1, cidade2;
    int distancia;
    while (getline(arq, linha)) {

        stringstream ss(linha);
        getline(ss, cidade1, ','); // Seleciona a string até o delimitador (,)
        getline(ss, cidade2, ',');
        ss >> distancia; // Único inteiro da linha do arquivo

        // Adiciona todas as cidades, cidades adjacentes a elas e
        // suas distâncias em uma tabela chamada "mapa"
        adjacente aux; // auxiliar
        aux = {distancia, cidade2};
        mapa[cidade1].push_back(aux);
    }

}

// Função que faz a entrada de dados e verifica se esses dados estão corretos
string entrada_dados(const string& trajeto, const unordered_map<string, list<adjacente>>& tabela) {
    string cidade;

    while (true) {
        cout << "Entre com a cidade de " << trajeto << ": " << endl;
        getline(cin, cidade);

        if (tabela.count(cidade) > 0) {
            return cidade; // Cidade válida, retorna
        } else {
            cout << "Cidade não encontrada na tabela. Por favor, digite novamente." << endl;
        }
    }
}

// Função que implementa a lógica do algoritmo de dijkstra em uma tabela hash chamada "tabela_dijkstra"
unordered_map<string, nodo> dijkstra (unordered_map<string, list<adjacente>>& mapa, const string& destino) {

    // Cria a tabela dijkstra
    unordered_map<string, nodo> tabela_dijkstra;

    // Cria uma lista para armazenar os nodos da tabela dijkstra
    list<string> nodos;

    // Lê as cidades/nodos para dentro da lista "nodos"
    for (auto & cidade: mapa) {
        nodos.push_back(cidade.first);
    }

    // Inicializa a tabela dijkstra
    for (auto & nodo : nodos) {
        tabela_dijkstra[nodo] = {INT_MAX, ""}; // Distância "infinita", sem procedente ainda
    }
    tabela_dijkstra[destino] = {0, destino}; // Distância zero para o nodo destino

    // Extrai da lista nodos o nodo com menor distância até o nodo destino
    while (!nodos.empty()) {
        string nodo_atual;
        int menor_distancia = INT_MAX;
        for (auto & nodo: nodos) {
            if (tabela_dijkstra[nodo].custo < menor_distancia) {
                menor_distancia = tabela_dijkstra[nodo].custo;
                nodo_atual = nodo;
            }
        }

        // Para cada nodo adjacente do nodo com menor distância:
        for (auto & adj : mapa[nodo_atual]) {
            // Calcula a distância do nodo adjacente
            int distancia = tabela_dijkstra[nodo_atual].custo + adj.distancia;

            // Se a distância encontrada for menor do que a distância atual do nodo:
            if (distancia < tabela_dijkstra[adj.cidade].custo) {
                tabela_dijkstra[adj.cidade] = {distancia, nodo_atual};
            }
        }

        // Remove o nodo atual da lista de nodos não visitados
        nodos.remove(nodo_atual);
    }

    return tabela_dijkstra;
}

// Função que procura em uma tabela dijkstra a melhor rota entre duas cidades
string melhor_rota (unordered_map<string, nodo>& tabela_dijkstra, const string & partida, const string & destino){

    // O trejeto começa na cidade de partida
    string trajeto = partida;

    // Armazena a melhor rota para o trajeto de uma cidade para outra
    string melhor_rota;

    // Acessa os dados da tabela dijkstra e analisa as cidades da melhor rota
    melhor_rota += partida + "   ";
    while (trajeto != destino) {
        trajeto = tabela_dijkstra[trajeto].procedente;
        melhor_rota += trajeto + "   ";
    }

    return melhor_rota;
}

// Função que procura em uma tabela dijkstra a melhor distância entre duas cidades
int melhor_distancia (unordered_map<string, nodo>& tabela_dijkstra, const string & partida){

    int distancia;

    // Procura na tabela dijkstra qual é a distância/custo do nodo destino
    distancia = tabela_dijkstra[partida].custo;

    return distancia;
}