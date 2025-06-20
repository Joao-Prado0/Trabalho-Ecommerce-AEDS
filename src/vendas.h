#ifndef VENDAS_H
#define VENDAS_H

class Vendas {
private:
    int codigoVenda;
    int codigoProduto;
    int quantidade;
    float precoUnidade;
    float precoTotal;
    float precoComFrete;

public:
    Vendas(int codigoP, int quant);
    void setCodigoVenda();
    void realizar_compra(int codigo, int quant);
};

#endif