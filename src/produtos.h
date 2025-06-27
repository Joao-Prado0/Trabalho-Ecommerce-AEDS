#ifndef PRODUTOS_H
#define PRODUTOS_H

#include <string>
#include <vector>
#include <fstream>

struct Produto {
    std::string nome;
    int codigo;
    int quantidadeEstoque;
    double precoVenda;
};

// Funções principais 
int cadastrar_produto(std::vector<Produto>& lista_produtos, int& total_produtos, 
                     const std::string& nome, int codigo, int quantidade_estoque, double preco_venda);

Produto* consultar_produto(const std::vector<Produto>& lista_produtos, int total_produtos, int codigo);

int alterar_produto(std::vector<Produto>& lista_produtos, int total_produtos, int codigo,
                   const std::string* novo_nome, int nova_quantidade, double novo_preco);

int excluir_produto(std::vector<Produto>& lista_produtos, int& total_produtos, int codigo);

// Funções auxiliares
bool produtoExiste(const std::vector<Produto>& lista_produtos, int total_produtos, int codigo);
int gerarCodigoAutomatico();
void salvarProdutos();
void carregarProdutos();
void exibirProduto(const Produto& produto);
void listarProdutos();

// Funções de interface para o menu
void cadastrarProduto();
void consultarProduto();
void alterarProduto();
void excluirProduto();

// Variáveis globais
extern std::vector<Produto> produtos;
extern int proximoCodigo;

#endif 
