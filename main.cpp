#include "funcoes.h"

using namespace std;

int main(int argc, char *argv[]) {

    // Cria tabela que armazena uma cidade como chave
    // e as cidades adjacentes bem como as distâncias a essa cidade como dado
    unordered_map <string, list<adjacente>> mapa;

    // Realiza a leitura de dados do arquivo csv para dentro da tabela "mapa"
    le_arquivo(argv[1],mapa);

    // Armazenam as cidades de partida e destino
    string partida, destino;

    // Realiza a leitura das cidades de partida e destino dadas pelo usuário
    // e verifica a existência delas no mapa que contém todas as cidades
    partida = entrada_dados("partida", mapa);
    destino = entrada_dados("destino", mapa);

    // Cria uma tabela com a lógica de dijkstra para esses dados
    unordered_map<string, nodo> tabela_dijkstra = dijkstra(mapa, destino);

    // Imprime a melhor rota entre 2 cidades e a distância do trajeto
    cout << endl << "-> A melhor rota é: " << endl << melhor_rota(tabela_dijkstra, partida, destino) << endl << endl;
    cout << "-> A melhor distância é: " << endl << melhor_distancia(tabela_dijkstra, partida) << " km" << endl;

    return 0;
}