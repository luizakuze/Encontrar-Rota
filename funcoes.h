#ifndef PRG2_TREES_FUNCOES_H
#define PRG2_TREES_FUNCOES_H

#include <iostream>
#include <fstream>
#include <sstream>
#include <unordered_map>
#include <list>
#include <climits>

using namespace std;

// Struct para armazenar as cidades adjacentes a uma cidade
struct adjacente {
    int distancia;
    string cidade;
};

// Struct para utilizar na tabela dijkstra
struct nodo {
    int custo;
    string procedente;
};

// Função que lê um arquivo com relações de distâncias entre as cidades e retorna uma tabela hash com essas informações.
// Recebe como parâmetros: O nome do arquivo a ser processado e essa tabela hash que será um "mapa" dadas essas informações.
void le_arquivo (const string & nome_arquivo, unordered_map<string, list<adjacente>>& mapa);

// Função que faz a entrada da cidade de partida ou destino do usuário e a verifica se a cidade existe na base de dados.
// Se não encontrar a cidade, imprime uma mensagem novamente para a entrada de dados correta.
// Recebe como parâmetros: Uma string que mostrará na tela se o usuário deve colocar a partida ou o destino,
// e uma tabela hash contendo o nome das cidades.
string entrada_dados (const string & trajeto, const unordered_map <string, list<adjacente>>& tabela);

// Função que implementa a lógica do algoritmo de dijkstra e retorna uma tabela com os valores encontrados.
// Recebe como parâmetros: Uma tabela hash contendo as relações de distâncias entre as cidades
// e uma string contendo qual a cidade de destino do usuário.
unordered_map<string, nodo> dijkstra (unordered_map<string, list<adjacente>>& mapa, const string& destino);

// Função que procura em uma tabela dijkstra a melhor rota entre duas cidades.
// Recebe como parâmetros: Uma tabela com a lógica de dijkstra, a cidade de partida do trajeto e a cidade de destino do trajeto.
string melhor_rota (unordered_map<string, nodo>& tabela_dijkstra, const string & partida, const string & destino);

// Função que procura em uma tabela dijkstra a melhor distância entre duas cidades.
// Recebe como parâmetros: Uma tabela com a lógica de dijkstra e a cidade de partida do trajeto.
int melhor_distancia (unordered_map<string, nodo>& tabela_dijkstra, const string & partida);

#endif
