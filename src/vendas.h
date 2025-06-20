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
    float precoTotal;};

class Vendas {
    private:
        int codigoVenda;
        string nomeComprador;
        float valorTotal;
        float frete;
        vector<ItemVenda> itens;

    public:
        Vendas(int codigoP, int quant);
        void setCodigoVenda();

        void aicionar_item(int codigoItem, int quant);

        void calcular_preco(int quant,Produtos produtoSolicitado);

        bool verificar_estoque(int codigo, int quant);
};

#endif