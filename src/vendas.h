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

        void imprimir_no_documento(int codigoV, int codigoVR, string nome, float valorT, ItemVenda *itens, int quant);

        Vendas(int codigoP);

        int criar_codigoVenda();

        bool verificar_codigo(int codigo);

        Vendas inicializar_com_codigo(int codigoV);

        void aicionar_item(int codigoItem, int quant);

        void consultar_venda(int codigoV);

        void alterar_venda(int codigoV);

        void alterar_itens_venda(int codigoV);

        void deletar_venda(int codigoV);

        void inserir_venda_manualmente();

        bool verificar_estoque();

        float calcular_frete(float valorT);
};

#endif