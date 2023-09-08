//
// Created by msobral on 30/09/2022.
//

#ifndef PRG2_TREES_NODO_ARVORE_H
#define PRG2_TREES_NODO_ARVORE_H

#include <memory>
#include <experimental/optional>

namespace prglib {
    template<typename T, typename Compare>
    class nodo_arvore {
    public:
        nodo_arvore(Compare &func);

        //nodo_arvore(const nodo_arvore<T,Compare> & outra);
        nodo_arvore(const T &dado, Compare &func);

        virtual ~nodo_arvore();

        // adiciona um dado à árvore
        void adiciona(const T &algo);

        // obtém um dado da árvore
        const T &obtem(const T &algo) const;

        // obtém o valor da raiz da árvore
        const T &obtem() const;

        // Versão alternativa: enumera os dados in-order, pre-order, post-order e breadth-first
        // copiando-os para uma lista
        void listeInOrder(std::vector<T> &result);

        void listePreOrder(std::vector<T> &result);

        void listePostOrder(std::vector<T> &result);

        void listeEmLargura(std::vector<T> &result);

        // retorna a quantidade de dados na árvore
        unsigned int tamanho() const;

        // retorna a subárvore esquerda
        const nodo_arvore<T, Compare> *esquerda() const;

        // retorna a subárvore direita
        const nodo_arvore<T, Compare> *direita() const;

        // remove um dado
        T remove(const T &algo);

        // retorna o menor dado
        const T &obtemMenor() const;

        // retorna o maior dado
        const T &obtemMaior() const;

        // obtém o maior valor que é menor que "algo"
        std::experimental::optional<T> obtemMenorQue(const T & algo) const;

        // obtém o menor valor que é maior que "algo"
        std::experimental::optional<T> obtemMaiorQue(const T & algo) const;

        // copia na lista "result" os dados menores que "algo"
        void obtemMenoresQue(std::vector<T> &result, const T &algo);

        // copia na lista "result" os dados maiores que "algo"
        void obtemMaioresQue(std::vector<T> &result, const T &algo);

        // obtém todos valores entre "start" e "end" (inclusive)
        void obtemIntervalo(std::vector<T> &result, const T &start, const T &end);

        // retorna a altura da folha mais distante da raiz
        unsigned int altura();

        // retorna o fator de balanceamento
        int fatorB();

        // balanceia a árvore
        nodo_arvore<T,Compare>* balanceia();

        // balanceia a árvore repetidamente, até que a altura não mais se reduza
        nodo_arvore<T,Compare>* balanceia(bool otimo);

        bool folha() const { return !esq && !dir; }

    protected:
        T data;
        std::unique_ptr<nodo_arvore<T,Compare>> esq, dir;
        Compare &comp_func;

        nodo_arvore<T,Compare>* rotacionaL();

        nodo_arvore<T,Compare>* rotacionaR();

        std::pair<nodo_arvore<T,Compare>*,nodo_arvore<T,Compare>*> obtem_nodo(const T & algo) const;
    };
}
#include "nodo_arvore-impl.h"

#endif //PRG2_TREES_NODO_ARVORE_H
