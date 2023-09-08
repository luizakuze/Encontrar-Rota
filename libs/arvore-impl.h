/* 
 * File:   arvore-impl.h
 * Author: sobral
 *
 * Created on 8 de Outubro de 2016, 19:37
 */

#ifndef ARVORE_IMPL_H
#define	ARVORE_IMPL_H

#include <sstream>
#include <ostream>
#include <stdexcept>
#include <utility>
#include "arvore.h"


using std::ostream;
using std::ostringstream;
using std::endl;

#define TRY_PROC(p) if (!p) throw std::runtime_error("árvore vazia"); \
                 else

namespace prglib {

    template <typename T, typename Compare> arvore_basica<T,Compare>::arvore_basica(Compare compare):comp_func(compare),_owner(true),raiz(nullptr) {
    }

    template <typename T, typename Compare> arvore_basica<T,Compare>::~arvore_basica() {
        if (_owner && raiz != nullptr) {
            delete raiz;
        }
    }

    template <typename T, typename Compare> arvore_basica<T,Compare>::arvore_basica(const arvore_basica<T,Compare>& outra): comp_func(outra.comp_func),_owner(true) {
        if (!outra.vazia()) {
            auto it = outra.preorder_begin();
            this->comp_func = outra.comp_func;
            this->raiz = new nodo_arvore<T,Compare>(*it,this->comp_func);
            for (; it != outra.preorder_end(); it++) {
                this->raiz->adiciona(*it);
            }
        } else {
            this->raiz = nullptr;
        }
    }

    template <typename T, typename Compare> arvore_basica<T,Compare>::arvore_basica(arvore_basica<T,Compare>&& outra): comp_func(outra.comp_func),_owner(true) {
        this->raiz = outra.raiz;
        outra.raiz = nullptr;
    }

    template <typename T, typename Compare> arvore_basica<T,Compare>::arvore_basica(nodo_arvore<T,Compare> * ptr, Compare compare): comp_func(compare),_owner(false),raiz(ptr) {
    }

    template <typename T, typename Compare> arvore_basica<T,Compare>::arvore_basica(istream &inp,Compare compare): comp_func(compare),_owner(true) {
        T data;

        inp >> data;
        if (inp.fail()) throw std::runtime_error("não pode ler da stream");
        raiz = new nodo_arvore<T,Compare>(data,this->comp_func);

        while (inp >> data) raiz->adiciona(data);
    }

    template <typename T, typename Compare> template <typename Container> arvore_basica<T,Compare>::arvore_basica(Container &dados,Compare compare): comp_func(compare),_owner(true) {
        auto it = dados.begin();
        if (it != dados.end()) {
            raiz = new nodo_arvore<T,Compare>(*it,this->comp_func);
            for (it++; it != dados.end(); it++) raiz->adiciona(*it);
        }
    }

    template<typename T, typename Compare>
    arvore_basica<T, Compare>::arvore_basica(Compare compare, const std::initializer_list<T> &dados) {
        auto it = dados.begin();
        if (it != dados.end()) {
            auto it = dados.begin();
            raiz = new nodo_arvore<T,Compare>(*it,this->comp_func);
            for (it++; it != dados.end(); it++) raiz->adiciona(*it);
        }
    }

    template <typename T, typename Compare> bool arvore_basica<T,Compare>::existe(const T & dado) const {
        bool status = false;
        if (! vazia()) {
            try {
                raiz->obtem(dado);
                status=true;
            } catch (...) {            
            }
        }
        return status;
    }

    template <typename T, typename Compare> bool arvore_basica<T,Compare>::vazia() const {
        return raiz == nullptr;
    }

    template <typename T, typename Compare> const T& arvore_basica<T,Compare>::obtem() const {
        TRY_PROC(raiz) {
            return raiz->obtem();
        }
    }

    template <typename T, typename Compare> const T& arvore_basica<T,Compare>::obtem(const T &dado) const {
        TRY_PROC(raiz) {
            return raiz->obtem(dado);
        }
    }

    template <typename T, typename Compare> const arvore_basica<T,Compare> arvore_basica<T,Compare>::direita() const {
        if (raiz) {
            auto nodo = const_cast<nodo_arvore<T,Compare>*>(raiz->direita());
            return arvore_basica(nodo, comp_func);
        } else {
            return arvore_basica(comp_func);
        }
    }

    template <typename T, typename Compare> const arvore_basica<T,Compare> arvore_basica<T,Compare>::esquerda() const {
        if (raiz) {
            auto nodo = const_cast<nodo_arvore<T,Compare>*>(raiz->esquerda());
            return arvore_basica(nodo, comp_func);
        } else {
            return arvore_basica(comp_func);
        }
    }

    template <typename T, typename Compare> unsigned int arvore_basica<T,Compare>::altura() const {
        TRY_PROC(raiz) {
            return raiz->altura();
        }
    }

    template <typename T, typename Compare> unsigned int arvore_basica<T,Compare>::tamanho() const {
        if (raiz) {
            return raiz->tamanho();
        } else {
            return 0;
        }
    }

    template <typename T, typename Compare> int arvore_basica<T,Compare>::fatorB() const {
        TRY_PROC(raiz) {
            return raiz->fatorB();
        }
    }

    template <typename T, typename Compare> const T& arvore_basica<T,Compare>::obtemMaior() const {
        TRY_PROC(raiz) {
            return raiz->obtemMaior();
        }
    }

    template <typename T, typename Compare> const T& arvore_basica<T,Compare>::obtemMenor() const {
        TRY_PROC(raiz) {
            return raiz->obtemMenor();
        }
    }

    template <typename T, typename Compare> std::vector<T> arvore_basica<T,Compare>::listeInOrder() {
        std::vector<T> result;

        if (raiz) {
            raiz->listeInOrder(result);
        }
        return result;
    }

    template <typename T, typename Compare> std::vector<T> arvore_basica<T,Compare>::listePreOrder() {
        std::vector<T> result;

        if (raiz) {
            raiz->listePreOrder(result);
        }
        return result;
    }
    template <typename T, typename Compare> std::vector<T> arvore_basica<T,Compare>::listePostOrder() {
        std::vector<T> result;

        if (raiz) {
            raiz->listePostOrder(result);
        }
        return result;
    }
    template <typename T, typename Compare> std::vector<T> arvore_basica<T,Compare>::listeEmLargura() {
        std::vector<T> result;

        if (raiz) {
            raiz->listeEmLargura(result);
        }
        return result;
    }

    template <typename T, typename Compare> std::vector<T> arvore_basica<T,Compare>::obtemMaioresQue(const T &algo) const {
        std::vector<T> result;

        if (raiz) {
            raiz->obtemMaioresQue(result, algo);
        }
        return result;
    }

    template <typename T, typename Compare> std::vector<T> arvore_basica<T,Compare>::obtemMenoresQue(const T &algo) const {
        std::vector<T> result;
        if (raiz) {
            raiz->obtemMenoresQue(result, algo);
        }

        return result;
    }

    template <typename T, typename Compare> std::vector<T> arvore_basica<T,Compare>::obtemIntervalo(const T &start, const T &end) const {
        std::vector<T> result;

        if (raiz) {
            raiz->obtemIntervalo(result, start, end);
        }

        return result;
    }

    template<typename T, typename Compare>
    std::experimental::optional<T> arvore_basica<T, Compare>::obtemMenorQue(const T &algo) const {
        if (this->raiz) {
            return this->raiz->obtemMenorQue(algo);
        }
        return std::experimental::nullopt;
    }

    template<typename T, typename Compare>
    std::experimental::optional<T> arvore_basica<T, Compare>::obtemMaiorQue(const T &algo) const {
        if (this->raiz) {
            return this->raiz->obtemMaiorQue(algo);
        }
        return std::experimental::nullopt;
    }


    template <typename T, typename Compare> arvore<T,Compare>::arvore(Compare compare): arvore_basica<T,Compare>(compare) {
    }

    template <typename T, typename Compare> arvore<T,Compare>::arvore(const arvore<T,Compare>& outra): arvore_basica<T,Compare>(outra) {
    }

    template<typename T, typename Compare>
    arvore<T, Compare>::arvore(const std::initializer_list<T> &dados, Compare compare):arvore_basica<T,Compare>(dados, compare) {
    }

//    template<typename T, typename Compare>
//    void arvore<T, Compare>::adiciona(T &&dado) {
//
//    }

    template <typename T, typename Compare> arvore<T,Compare>::arvore(arvore<T,Compare>&& outra): arvore_basica<T,Compare>(std::forward<arvore<T,Compare>>(outra)) {
    }

    template <typename T, typename Compare> template <typename Container> arvore<T,Compare>::arvore(Container &dados, Compare compare): arvore_basica<T,Compare>(dados, compare) {}

    template <typename T, typename Compare> arvore<T,Compare>::arvore(istream &inp, Compare compare): arvore_basica<T,Compare>(inp, compare) {}
    template <typename T, typename Compare> arvore<T,Compare>::arvore(std::ifstream &inp, Compare compare): arvore_basica<T,Compare>(dynamic_cast<istream&>(inp), compare) {}

    template <typename T, typename Compare> arvore<T,Compare>::~arvore() {
    }

    template <typename T, typename Compare> arvore<T,Compare>& arvore<T,Compare>::operator=(const arvore<T,Compare> & outra) {
        if (this->_owner && this->raiz != nullptr) {
            delete this->raiz;
        }
        if (!outra.vazia()) {
            auto it = outra.preorder_begin();
            this->comp_func = outra.comp_func;
            this->raiz = new nodo_arvore<T,Compare>(it->obtem(),this->comp_func);
            for (; it != outra.preorder_end(); it++) {
                this->raiz->adiciona(it->obtem());
            }
        } else {
            this->raiz = nullptr;
        }
        this->_owner = true;
        return *this;
    }

    template <typename T, typename Compare> arvore<T,Compare>& arvore<T,Compare>::operator=(arvore<T,Compare> && outra) {
        if (this->_owner && this->raiz != nullptr) {
            delete this->raiz;
        }
        this->raiz = outra.raiz;
        outra.raiz = nullptr;
        this->_owner = true;
        return *this;
    }

    template <typename T, typename Compare> void arvore<T,Compare>::adiciona(const T &dado) {
        if (this->raiz) {
            this->raiz->adiciona(dado);
        } else {
            this->raiz = new nodo_arvore<T,Compare>(dado,this->comp_func);
        }
    }

    template <typename T, typename Compare>
    template <typename Container>
    void arvore<T,Compare>::adiciona(const Container &dados) {
        for (auto & dado: dados) {
            adiciona(dado);
        }
    }

    template <typename T, typename Compare> T arvore<T,Compare>::remove(const T &dado) {
        TRY_PROC(this->raiz) {
            if (this->raiz->folha()) {
                auto algo = this->raiz->obtem();
                delete this->raiz;
                this->raiz = nullptr;
                return algo;
            }
            return this->raiz->remove(dado);
        }
    }

    template <typename T, typename Compare> void arvore<T,Compare>::balanceia() {
        TRY_PROC(this->raiz) {
            this->raiz = this->raiz->balanceia();
        }
    }

    template <typename T, typename Compare> void arvore<T,Compare>::balanceia(bool otimo) {
        TRY_PROC(this->raiz) {
            this->raiz = this->raiz->balanceia(otimo);
        }
    }


    template <typename T,typename Compare> void desenha_nodos(const arvore_basica<T,Compare> & arv, ostream & out) {
        auto raiz = arv.obtem();
        auto esq = arv.esquerda();
        auto dir = arv.direita();

        if (esq.vazia() and dir.vazia()) out << raiz << endl;
        else {
            if (!esq.vazia()) {
                out << '"' << raiz << "\" -- \"" << esq.obtem() << '"' << endl;
                if (esq.altura()) desenha_nodos(esq, out);
            }
            if (!dir.vazia()) {
                out << '"' << raiz << "\" -- \"" << dir.obtem() << '"' << endl;
                if (dir.altura()) desenha_nodos(dir, out);
            }
        }

    }

    template <typename T, typename Compare> string desenha_arvore(const arvore_basica<T,Compare> & arv) {
        ostringstream out;

        out << "strict graph {" << endl;
        desenha_nodos(arv, out);
        out << "}" << endl;

        return out.str();
    }

    template<typename T, typename Compare> typename arvore_basica<T,Compare>::preorder_iterator arvore_basica<T,Compare>::preorder_begin() const{
        return preorder_iterator(this->raiz);
    }

    template<typename T, typename Compare> typename arvore_basica<T,Compare>::preorder_iterator arvore_basica<T,Compare>::preorder_end() const {
        return preorder_iterator();
    }

    template<typename T, typename Compare> typename arvore_basica<T,Compare>::inorder_iterator arvore_basica<T,Compare>::inorder_begin() const{
        return inorder_iterator(this->raiz);
    }

    template<typename T, typename Compare> typename arvore_basica<T,Compare>::inorder_iterator arvore_basica<T,Compare>::inorder_end() const {
        return inorder_iterator();
    }

    template<typename T, typename Compare> typename arvore_basica<T,Compare>::preorder_riterator arvore_basica<T,Compare>::preorder_rbegin() const {
        return preorder_riterator(this->raiz);
    }

    template<typename T, typename Compare> typename arvore_basica<T,Compare>::preorder_riterator arvore_basica<T,Compare>::preorder_rend() const {
        return preorder_riterator();
    }

    template<typename T, typename Compare> typename arvore_basica<T,Compare>::inorder_riterator arvore_basica<T,Compare>::inorder_rbegin() const{
        return inorder_riterator(this->raiz);
    }

    template<typename T, typename Compare> typename arvore_basica<T,Compare>::inorder_riterator arvore_basica<T,Compare>::inorder_rend() const {
        return inorder_riterator();
    }

    template<typename T, typename Compare>
    arvore_basica<T,Compare>::preorder_iterator::preorder_iterator() {

    }

    template<typename T, typename Compare>
    arvore_basica<T,Compare>::preorder_iterator::preorder_iterator(const arvore_basica::preorder_iterator &it) {
        p = it.p;
    }

    template<typename T, typename Compare>
    arvore_basica<T,Compare>::preorder_iterator::preorder_iterator(const nodo_arvore<T,Compare> * raiz) {
        p.push(raiz);
    }

    template<typename T, typename Compare>
    bool arvore_basica<T,Compare>::preorder_iterator::operator==(const arvore_basica::preorder_iterator &it) const {
        return p == it.p;
    }

    template<typename T, typename Compare>
    bool arvore_basica<T,Compare>::preorder_iterator::operator!=(const arvore_basica::preorder_iterator &it) const {
        return p != it.p;
    }

    template<typename T, typename Compare>
    const T &arvore_basica<T,Compare>::preorder_iterator::operator*() const {
        if (p.empty()) throw std::runtime_error("fim da iteração"); // a meu critério ???
        auto ptr = p.top();
        return ptr->obtem();
    }

    template <typename T, typename Compare> const T* arvore_basica<T,Compare>::preorder_iterator::operator->() const {
        if (p.empty()) throw std::runtime_error("fim da iteração");
        auto const ptr = p.top();
        return &ptr->obtem();
    }

    template<typename T, typename Compare>
    typename arvore_basica<T,Compare>::preorder_iterator &arvore_basica<T,Compare>::preorder_iterator::operator++() {
        if (! p.empty()) {
            auto ptr = p.top();
            p.pop();
            if (ptr->direita() != nullptr) p.push(ptr->direita());
            if (ptr->esquerda() != nullptr) p.push(ptr->esquerda());
        }
        return *this;
    }

    template<typename T, typename Compare>
    typename arvore_basica<T,Compare>::preorder_iterator &arvore_basica<T,Compare>::preorder_iterator::operator++(int) {
        return ++(*this);
    }

    template<typename T, typename Compare>
    arvore_basica<T,Compare>::preorder_riterator::preorder_riterator() {

    }

    template<typename T, typename Compare>
    arvore_basica<T,Compare>::preorder_riterator::preorder_riterator(const arvore_basica::preorder_riterator &it):preorder_iterator(it) {
    }

    template<typename T, typename Compare>
    arvore_basica<T,Compare>::preorder_riterator::preorder_riterator(const nodo_arvore<T,Compare> * raiz): preorder_iterator(raiz) {
    }

    template<typename T, typename Compare>
    typename arvore_basica<T,Compare>::preorder_riterator &arvore_basica<T,Compare>::preorder_riterator::operator++() {
        auto & p = this->p;

        if (! p.empty()) {
            auto ptr = p.top();
            p.pop();
            if (ptr->esquerda() != nullptr) p.push(ptr->esquerda());
            if (ptr->direita() != nullptr) p.push(ptr->direita());
        }
        return *this;
    }

    template<typename T, typename Compare>
    typename arvore_basica<T,Compare>::preorder_riterator &arvore_basica<T,Compare>::preorder_riterator::operator++(int) {
        return ++(*this);
    }

    template<typename T, typename Compare>
    arvore_basica<T,Compare>::inorder_iterator::inorder_iterator(): arvore_basica<T,Compare>::preorder_iterator() {

    }

    template<typename T, typename Compare>
    arvore_basica<T,Compare>::inorder_iterator::inorder_iterator(const arvore_basica::inorder_iterator &it): arvore_basica<T,Compare>::preorder_iterator(it) {
    }

    template<typename T, typename Compare>
    arvore_basica<T,Compare>::inorder_iterator::inorder_iterator(const nodo_arvore<T,Compare> * raiz) {
        for (auto ptr = raiz; ptr != nullptr; ptr=ptr->esquerda()) {
            this->p.push(ptr);
        }
    }

    template<typename T, typename Compare>
    typename arvore_basica<T,Compare>::inorder_iterator &arvore_basica<T,Compare>::inorder_iterator::operator++() {
        if (! this->p.empty()) {
            const nodo_arvore<T,Compare> * ptr = this->p.top();
            this->p.pop();
            for (ptr = ptr->direita(); ptr != nullptr; ptr=ptr->esquerda()) {
                this->p.push(ptr);
            }
        }
        return *this;
    }

    template<typename T, typename Compare>
    typename arvore_basica<T,Compare>::inorder_iterator &arvore_basica<T,Compare>::inorder_iterator::operator++(int) {
        return ++(*this);
    }

    template<typename T, typename Compare>
    arvore_basica<T,Compare>::inorder_riterator::inorder_riterator(): arvore_basica<T,Compare>::preorder_iterator() {

    }

    template<typename T, typename Compare>
    arvore_basica<T,Compare>::inorder_riterator::inorder_riterator(const arvore_basica::inorder_riterator &it): arvore_basica<T,Compare>::preorder_iterator(it) {
    }

    template<typename T, typename Compare>
    arvore_basica<T,Compare>::inorder_riterator::inorder_riterator(const nodo_arvore<T,Compare> * raiz) {
        for (auto ptr = raiz; ptr != nullptr; ptr=ptr->direita()) {
            this->p.push(ptr);
        }
    }

    template<typename T, typename Compare>
    typename arvore_basica<T,Compare>::inorder_riterator &arvore_basica<T,Compare>::inorder_riterator::operator++() {
        if (! this->p.empty()) {
            auto ptr = this->p.top();
            this->p.pop();
            for (ptr = ptr->esquerda(); ptr != nullptr; ptr=ptr->direita()) {
                this->p.push(ptr);
            }
        }
        return *this;
    }

    template<typename T, typename Compare>
    typename arvore_basica<T,Compare>::inorder_riterator &arvore_basica<T,Compare>::inorder_riterator::operator++(int) {
        return ++(*this);
    }

};

#endif	/* ARVORE_IMPL_H */

