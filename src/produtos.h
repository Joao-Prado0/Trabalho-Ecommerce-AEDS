#ifndef PRODUTOS_H
#define PRODUTOS_H
#include <string>
#include <vector>
using namespace std;

struct Produto {
    int codigo;
    std::string nome;
    int quantidadeEstoque;
    float precoVenda;
    Produto() = default;
    bool encontrado = true;
};

class Produtos {
private:
    vector<Produto> lista_produtos;
    int proximoCodigo;
    void atualizarProximoCodigo();
public:
    Produtos();
    int gerarCodigoAutomatico();
    bool inserir_produto(const string& nome, int codigo, int quantidade, float preco);
    Produto consultar_produto(int codigo);
    bool alterar_produto(int codigo, const string* novo_nome, int nova_quantidade, float novo_preco);
    bool excluir_produto(int codigo);
    void listar_produtos();
    void salvar_produtos();
    void carregar_produtos();
    
    // Métodos de interface para o main.cpp
    void inserir_produto_manualmente();
    void consultar_produto_interface();
    void alterar_produto_interface();
    void excluir_produto_interface();

// Funções para controle de estoque em vendas
    bool verificar_quantidade(int codigo, int quantidade_desejada);
    bool confirmar_venda(int codigo, int quantidade_vendida);
};

#endif 