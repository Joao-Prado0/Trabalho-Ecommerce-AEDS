#ifndef VENDAS_H
#define VENDAS_H
#include <string>
#include <vector>
using namespace std;

struct ItemVenda{
    int codigoProduto;
    string nomeProduto;
    int quantidadeVendida;
    float precoUnitario;
    float precoTotal;
};

class Vendas {
    private:
        int codigoVenda;
        int codigoVendedor;
        string nomeComprador;
        float valorTotal;
        float frete;
        vector<ItemVenda> itens;

    public:
        Vendas(int codigoP, int quant);
        void setCodigoVenda();

        void aicionar_item(int codigoItem, int quant);

        void calcular_preco(int quant,Produtos produtoSolicitado);

        Vendas consultar_venda(int codigoV);

        void alterar_venda(int codigoV);

        void deletar_venda(int codigoV);

        void inserir_venda_manualmente();

        bool verificar_estoque(int codigo, int quant);
};

#endif