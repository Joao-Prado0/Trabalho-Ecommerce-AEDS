#include "produtos.h"
#include <iostream>
#include <iomanip>

using namespace std;

vector<Produto> produtos;
int proximoCodigo = 1001;
const string ARQUIVO_PRODUTOS = "estoque.txt";

int gerarCodigoAutomatico() {
    return proximoCodigo++;
}

bool produtoExiste(const vector<Produto>& lista_produtos, int total_produtos, int codigo) {
    for (int i = 0; i < total_produtos; i++) {
        if (lista_produtos[i].codigo == codigo) {
            return true;
        }
    }
    return false;
}

Produto* encontrarProduto(int codigo) {
    for (auto& produto : produtos) {
        if (produto.codigo == codigo) {
            return &produto;
        }
    }
    return nullptr;
}

void exibirProduto(const Produto& produto) {
    cout << "\n=== Dados do Produto ===" << endl;
    cout << "Codigo: " << produto.codigo << endl;
    cout << "Nome: " << produto.nome << endl;
    cout << "Quantidade em Estoque: " << produto.quantidadeEstoque << endl;
    cout << "Preco de Venda: R$ " << fixed << setprecision(2) << produto.precoVenda << endl;
    cout << "=========================" << endl;
}

int cadastrar_produto(vector<Produto>& lista_produtos, int& total_produtos,
                     const string& nome, int codigo, int quantidade_estoque, double preco_venda) {
    if (produtoExiste(lista_produtos, total_produtos, codigo)) {
        return 0;
    }

    Produto novoProduto;
    novoProduto.nome = nome;
    novoProduto.codigo = codigo;
    novoProduto.quantidadeEstoque = quantidade_estoque;
    novoProduto.precoVenda = preco_venda;
    
    lista_produtos.push_back(novoProduto);
    total_produtos = lista_produtos.size();
    return 1;
}

Produto* consultar_produto(const vector<Produto>& lista_produtos, int total_produtos, int codigo) {
    for (int i = 0; i < total_produtos; i++) {
        if (lista_produtos[i].codigo == codigo) {
            return const_cast<Produto*>(&lista_produtos[i]);
        }
    }
    return nullptr;
}

int alterar_produto(vector<Produto>& lista_produtos, int total_produtos, int codigo,
                   const string* novo_nome, int nova_quantidade, double novo_preco) {
    for (int i = 0; i < total_produtos; i++) {
        if (lista_produtos[i].codigo == codigo) {
            bool alterado = false;

            if (novo_nome != nullptr) {
                lista_produtos[i].nome = *novo_nome;
                alterado = true;
            }

            if (nova_quantidade != -1) {
                lista_produtos[i].quantidadeEstoque = nova_quantidade;
                alterado = true;
            }

            if (novo_preco != -1) {
                lista_produtos[i].precoVenda = novo_preco;
                alterado = true;
            }

            return alterado ? 1 : 0;
        }
    }

    return 0;
}

int excluir_produto(vector<Produto>& lista_produtos, int& total_produtos, int codigo) {
    for (int i = 0; i < total_produtos; i++) {
        if (lista_produtos[i].codigo == codigo) {
            for (int j = i; j < total_produtos - 1; j++) {
                lista_produtos[j] = lista_produtos[j + 1];
            }

            total_produtos--;
            return 1;
        }
    }

    return 0;
}

