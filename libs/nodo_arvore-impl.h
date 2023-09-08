//
// Created by msobral on 30/09/2022.
//

#ifndef PRG2_TREES_NODO_ARVORE_IMPL_H
#define PRG2_TREES_NODO_ARVORE_IMPL_H

#include <queue>
#include <algorithm>
#include "nodo_arvore.h"


namespace prglib {
    template <typename T,typename Compare> nodo_arvore<T,Compare>::~nodo_arvore() {
    }

    template <typename T,typename Compare> nodo_arvore<T,Compare>::nodo_arvore(Compare &func): comp_func(func)  {
    }

    template <typename T,typename Compare> nodo_arvore<T,Compare>::nodo_arvore(const T & dado, Compare &func) : data(dado),comp_func(func) {
    }

    template <typename T,typename Compare> void nodo_arvore<T,Compare>::adiciona(const T & algo) {
        auto p_nodo = this;

        while (true) {
            auto comp = comp_func(algo, p_nodo->data);
            if (comp == 0) {
                p_nodo->data = algo;
                break;
            }
            if (comp < 0) {
                if (!p_nodo->esq) {
                    p_nodo->esq = std::make_unique<nodo_arvore<T,Compare>>(algo, comp_func);
                    break;
                } else {
                    p_nodo = p_nodo->esq.get();
                }
            } else {
                if (!p_nodo->dir) {
                    p_nodo->dir = std::make_unique<nodo_arvore<T,Compare>>(algo, comp_func);
                    break;
                } else {
                    p_nodo = p_nodo->dir.get();
                }
            }
        }
    }

    template <typename T,typename Compare> const T& nodo_arvore<T,Compare>::obtem(const T & algo) const {
        auto p_nodo = this;

        while (p_nodo) {
            auto comp = comp_func(algo, p_nodo->data);
            if (comp == 0) {
                return p_nodo->data;
                break;
            }
            if (comp < 0) {
                p_nodo = p_nodo->esq.get();
            } else {
                p_nodo = p_nodo->dir.get();
            }
        }
        throw std::invalid_argument("valor não existe");
    }

    template <typename T,typename Compare> const T& nodo_arvore<T,Compare>::obtem() const {
        return this->data;
    }

    template <typename T,typename Compare> const nodo_arvore<T,Compare> * nodo_arvore<T,Compare>::esquerda() const {
        return static_cast<const nodo_arvore<T,Compare>*>(this->esq.get());
    }

    template <typename T,typename Compare> const nodo_arvore<T,Compare> * nodo_arvore<T,Compare>::direita() const {
        return static_cast<const nodo_arvore<T,Compare>*>(this->dir.get());
    }

    template <typename T,typename Compare> void nodo_arvore<T,Compare>::listeEmLargura(std::vector<T> & result) {
        std::queue<nodo_arvore<T,Compare>*> q;

        q.push(this);
        while (! q.empty()) {
            auto p_nodo = q.front();
            q.pop();
            result.push_back(p_nodo->data);
            if (p_nodo->esq) {
                q.push(p_nodo->esq.get());
            }
            if (p_nodo->dir) {
                q.push(p_nodo->dir.get());
            }
        }
    }

    template <typename T,typename Compare> void nodo_arvore<T,Compare>::listeInOrder(std::vector<T> & result) {
        if (esq) esq->listeInOrder(result);
        result.push_back(this->data);
        if (dir) dir->listeInOrder(result);
    }

    template <typename T,typename Compare>  void nodo_arvore<T,Compare>::listePreOrder(std::vector<T> & result) {
        result.push_back(this->data);
        if (esq) esq->listePreOrder(result);
        if (dir) dir->listePreOrder(result);
    }

    template <typename T,typename Compare>  void nodo_arvore<T,Compare>::listePostOrder(std::vector<T> & result) {
        if (esq) esq->listePostOrder(result);
        if (dir) dir->listePostOrder(result);
        result.push_back(this->data);
    }

    template <typename T,typename Compare> unsigned int nodo_arvore<T,Compare>::tamanho() const {
        int n=0;

        if (esq) n += esq->tamanho();
        if (dir) n += dir->tamanho();
        return 1 + n;
    }

    template <typename T,typename Compare> int nodo_arvore<T,Compare>::fatorB()  {
        int he=0, hd=0;

        if (esq) he = 1 + esq->altura();
        if (dir) hd = 1 + dir->altura();

        return he - hd;
    }

    template <typename T,typename Compare> unsigned int nodo_arvore<T,Compare>::altura()  {
        int he=0, hd=0;

        if (esq) he = 1 + esq->altura();
        if (dir) hd = 1 + dir->altura();

        return std::max(he, hd);
    }

    template <typename T,typename Compare> nodo_arvore<T,Compare>* nodo_arvore<T,Compare>::balanceia() {
        if (not (esq or dir)) return this;
        if (esq) {
            auto p_esq = esq.release();
            esq.reset(p_esq->balanceia());
        }
        if (dir) {
            auto p_dir = dir.release();
            dir.reset(p_dir->balanceia());
        }

        int fb = fatorB();
        auto ptr = this;
        // tá maior do lado direito
        while (fb < -1) {
            if (ptr->dir->fatorB() > 0) {
                auto p_dir = ptr->dir.release();
                ptr->dir.reset(p_dir->rotacionaL());
            }
            ptr = ptr->rotacionaR();
            fb = ptr->fatorB();
        }
        // tá maior do lado esquerdo
        while (fb > 1) {
            if (ptr->esq->fatorB() < 0) {
                auto p_esq = ptr->esq.release();
                ptr->esq.reset(p_esq->rotacionaR());
            }
            ptr = ptr->rotacionaL();
            fb = ptr->fatorB();
        }
//        ptr->h = -1;
        return ptr;
    }

    template <typename T,typename Compare> nodo_arvore<T,Compare>* nodo_arvore<T,Compare>::balanceia(bool otimo) {
        int h;
        auto ptr = this;

        do {
            h = ptr->altura();
            ptr = ptr->balanceia();
        } while (h > ptr->altura() && otimo);
        return ptr;
    }

    template <typename T,typename Compare> const T& nodo_arvore<T,Compare>::obtemMenor() const{
        auto p_nodo = this;

        while (p_nodo->esq) p_nodo = p_nodo->esq.get();
        return p_nodo->data;
    }

    template <typename T,typename Compare>
    std::pair<nodo_arvore<T,Compare>*,nodo_arvore<T,Compare>*> nodo_arvore<T,Compare>::obtem_nodo(const T & algo) const {
        auto ptr = const_cast<nodo_arvore<T,Compare>*>(this);
        nodo_arvore<T,Compare>* pai = nullptr;

        while (ptr != nullptr) {
            if (ptr->data == algo) break;
            pai = ptr;
            if (algo < ptr->data) ptr = ptr->esq.get();
            else ptr = ptr->dir.get();
        }
        return std::make_pair(ptr, pai);
    }

    template <typename T,typename Compare> T nodo_arvore<T,Compare>::remove(const T & algo) {
        auto par = obtem_nodo(algo);
        auto pai = par.second;
        auto  ptr = par.first;

        if (not ptr) throw std::invalid_argument("valor inexistente");

        auto result = ptr->data;

        if (ptr->esq or ptr->dir) {
            int fb = ptr->fatorB();
            if (fb > 0) { // maior do lado esquerdo
                auto maior = ptr->esq->obtemMaior();
                ptr->remove(maior);
                ptr->data = maior;
            } else { // maior do lado direito
                auto menor = ptr->dir->obtemMenor();
                ptr->remove(menor);
                ptr->data = menor;
            }
        } else { // nodo é uma folha
            if (pai) {
                if (pai->esq.get() == ptr) pai->esq.reset();
                else pai->dir.reset();
            }
        }

        return result;
    }

    template <typename T,typename Compare> const T& nodo_arvore<T,Compare>::obtemMaior() const{
        auto p_nodo = this;

        while (p_nodo->dir) p_nodo = p_nodo->dir.get();
        return p_nodo->data;
    }

    template <typename T,typename Compare> void nodo_arvore<T,Compare>::obtemMenoresQue(std::vector<T> & result, const T & algo) {
        if (data <= algo) {
            result.push_back(data);
            if (esq) esq->listePreOrder(result);
            if (dir) dir->obtemMenoresQue(result, algo);
        } else {
            if (esq) esq->obtemMenoresQue(result, algo);
        }
    }

    template <typename T,typename Compare> void nodo_arvore<T,Compare>::obtemMaioresQue(std::vector<T> & result, const T & algo) {
        if (data >= algo) {
            result.push_back(data);
            if (dir) dir->listePreOrder(result);
            if (esq) esq->obtemMaioresQue(result, algo);
        } else {
            if (dir) dir->obtemMaioresQue(result, algo);
        }
    }

    template <typename T,typename Compare> void nodo_arvore<T,Compare>::obtemIntervalo(std::vector<T>& result, const T& start, const T& end) {
        if (data < start) {
            if (dir) dir->obtemIntervalo(result, start, end);
        } else if (data > end) {
            if (esq) esq->obtemIntervalo(result, start, end);
        } else {
            result.push_back(data);
            if (dir) dir->obtemIntervalo(result, start, end);
            if (esq) esq->obtemIntervalo(result, start, end);
        }
    }

    template <typename T,typename Compare> nodo_arvore<T,Compare>* nodo_arvore<T,Compare>::rotacionaL() {
        auto p3 = this;
//        auto & p2 = p3->esq;
//        auto & c = p2->dir;
        auto p2 = p3->esq.release();
        auto c = p2->dir.release();

        p3->esq.reset(c);
        p2->dir.reset(p3);

        return p2;
    }

    template <typename T,typename Compare> nodo_arvore<T,Compare>* nodo_arvore<T,Compare>::rotacionaR() {
        auto p1 = this;
        auto p2 = p1->dir.release();
        auto b = p2->esq.release();

        p1->dir.reset(b);
        //if (b) b->pai = p1;
        p2->esq.reset(p1);
        //p1->pai = p2;
        //p2->pai = nullptr; // nova raiz
        return p2;
    }

    template<typename T, typename Compare>
    std::experimental::optional<T> nodo_arvore<T, Compare>::obtemMenorQue(const T &algo) const {
        auto ptr = const_cast<nodo_arvore<T, Compare>*>(this);
        T * last = nullptr;
        while (ptr != nullptr) {
            if (ptr->data == algo) {
                if (ptr->esq != nullptr) {
                    return std::experimental::make_optional(ptr->esq->obtemMaior());
                }
                break;
            } else if (algo < ptr->data) {
                ptr = ptr->esq.get();
            } else {
                last = &ptr->data;
                ptr = ptr->dir.get();
            }

        }
        if (last != nullptr) {
            return std::experimental::make_optional(*last);
        }
        return std::experimental::nullopt;
    }

    template<typename T, typename Compare>
    std::experimental::optional<T> nodo_arvore<T, Compare>::obtemMaiorQue(const T &algo) const {
        auto ptr = const_cast<nodo_arvore<T, Compare>*>(this);
        T * last = nullptr;
        while (ptr != nullptr) {
            if (ptr->data == algo) {
                if (ptr->dir != nullptr) {
                    return std::experimental::make_optional(ptr->dir->obtemMenor());
                }
                break;
            } else if (algo < ptr->data) {
                last = &ptr->data;
                ptr = ptr->esq.get();
            } else {
                ptr = ptr->dir.get();
            }
        }
        if (last != nullptr) {
            return std::experimental::make_optional(*last);
        }
        return std::experimental::nullopt;
    }
}
#endif //PRG2_TREES_NODO_ARVORE_IMPL_H
