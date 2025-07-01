#ifndef VENDAS_H
#define VENDAS_H
#include <string>
#include "compradores.h"

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

        int criar_codigoVenda();

        bool verificar_codigo(int codigo);

        Vendas inicializar_com_codigo(int codigoV);

        void consultar_venda(int codigoV);

        void alterar_venda(int codigoV);

        void alterar_itens_venda(int codigoV);

        void deletar_venda(int codigoV);

        void inserir_venda_manualmente();

        float calcular_frete(float valorT);

        void imprimir_nota_fiscal(Comprador compradorAtual,ItemVenda carrinho[],int contadorDeProdutos, float ValorTotal);

        void salvar_venda_usuario(int codigoVenda, string nomeComprador,ItemVenda carrinho[], int contadorDeProdutos, float ValorCompra);
};

#endif