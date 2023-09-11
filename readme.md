# Melhor Caminho 🚗
> Autora: Luiza Kuze <br>
> Projeto de [PRG2](https://github.com/luizakuze/PRG2)

## Descrição 📌

O programa exibe a melhor rota possível entre duas cidades. A rota é apresentada como uma sequência de cidades desde a origem até o destino, juntamente com a distância total da viagem. As cidades devem ser inseridas através do teclado, e o resultado é exibido na tela. 

Existe um "mapa" que é um arquivo csv que fornece informações sobre cada par de locais e a distância entre eles. 

<div align="center">
  
| Cidade 1  | Cidade 2	| Distância (km) |
|------------------------| --- |----------------|
| Florianópolis          | São José	| 19             | 
| Florianópolis	         | Biguaçu	| 24             |
| São José	              | Biguaçu	| 20 |               
| São José	              | Palhoça	| 6 |                
| São José	              | São Pedro de Alcântara |	22 |
| Biguaçu                |	Antônio Carlos             |	17 |
| São Pedro de Alcântara	 | Antônio Carlos	| 10             |

_parte do mapa com algumas cidades próximas a Florianópolis_

</div>
  
## Objetivos 🎯

- [x] Implementar um "mapa" da região analisada no programa. 
- [x] Encontrar a menor rota entre duas cidades desse mapa. 
- [x] Encontrar a distância da menor rota das cidades.
- [x] Tratamento de erros ao informar cidades inválidas.
- [x] Aprender sobre grafos e o algoritmo Dijkstra.
- [x] Adaptar o algoritmo de Dijkstra para a resolução do problema.

## Funcionamento 💻

```Bash
# Clonar o repositório do projeto 
git clone https://github.com/luizakuze/Melhor-Caminho

# Acessar o diretório 
cd Melhor-Caminho

# Compilar o projeto
g++ main.cpp funcoes.cpp -o projeto

# Executar o projeto (no linux)
./projeto distancias.csv
```
> Após essa sequência de comandos, o usuário deve realizar a entrada de dados e verificar os resutlados do programa.

## Implementação 📚

### [Algoritmo Dijkstra](https://pt.wikipedia.org/wiki/Algoritmo_de_Dijkstra) 📕

É um algoritmo de busca de menor caminho usado em grafos ponderados direcionados. Sua principal aplicação é encontrar a rota mais curta entre dois nodos em um grafo, levando em consideração os pesos associados às arestas. 

A ideia para construção do mapa foi que cada nodo é uma cidade e as arestas são as distâncias entre as cidades. O passo foi o seguitne:

1) #### Inicialização

Inicialmente, todas as distâncias para os nodos são definidas como infinito, exceto a distância para o nodo de origem, que é definida como zero.
Um conjunto (geralmente uma fila de prioridade) é mantido para acompanhar os nodos não visitados.

2) #### Seleção do Nodo Atual:

Em cada etapa, o algoritmo seleciona o nodo não visitado com a menor distância conhecida a partir da origem.
Isso é feito de forma eficiente usando a estrutura linear "fila", que permite facilmente recuperar o nodo com a menor distância.

3) #### Atualização das Distâncias:

O algoritmo visita os nodos adjacentes ao nodo atual e calcula as distâncias até esses nodos através do nodo atual.
Se a nova distância calculada for menor do que a distância conhecida anteriormente, a distância é atualizada.

4) #### Marcação de Nodos Visitados:

O nodo atual é marcado como visitado e removido do conjunto de nodos não visitados.

5) #### Repetição:

Os passos 2~4 são repetidos até que todos os nodos tenham sido visitados ou até que o nodo de destino tenha sido visitado (se estivermos procurando a menor rota para um nodo específico).

6) #### Resultado:

Após a conclusão do algoritmo, temos uma tabela que contém as menores distâncias conhecidas de origem para todos os nodos no grafo, bem como os predecessores que formam a menor rota para cada nodo. 🎈✨🎉

### Tabela hash 📘

Dada a descrição sobre o algoritmo de Dijkstra acima, é visível a extrema importância da estrutura da tabela hash no projeto. Frisando os benefícios que o projeto ganhou ao utilizar ela:

- Facilita a seleção eficiente do próximo nodo a ser explorado pelo algoritmo de Dijkstra, permitindo encontrar o nodo com a menor distância conhecida de forma rápida.
- Permite a atualização rápida das distâncias mínimas dos nodos à medida que o algoritmo avança, garantindo que as informações estejam sempre atualizadas.
- Após a conclusão do algoritmo, as tabelas hash são cruciais para construir a menor rota entre a cidade de partida e a cidade de destino.

## Licença 📜

Este projeto é licenciado sob a [MIT License](https://github.com/luizakuze/Melhor-Caminho/blob/main/license)
