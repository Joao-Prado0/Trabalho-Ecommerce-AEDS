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

    ItemVenda(){};
};

class Vendas {
    private:
        int codigoVenda;
        int codigoVendedor;
        string nomeComprador;
        float valorTotal;
        float frete;
        ItemVenda *itens = new ItemVenda;

    public:
        Vendas();

        Vendas(int codigoP, int quant);
        void setCodigoVenda();

        Vendas inicializar_com_codigo(int codigoV);

        void aicionar_item(int codigoItem, int quant);

        void calcular_preco(int quant);

        void consultar_venda(int codigoV);

        void alterar_venda(int codigoV);

        void alterar_itens_venda(int codigoV);

        void deletar_venda(int codigoV);

        void inserir_venda_manualmente(int codigoV,int codigoVR, string nomeC, float valorT,ItemVenda *produtos);

        bool verificar_estoque();
};

#endif