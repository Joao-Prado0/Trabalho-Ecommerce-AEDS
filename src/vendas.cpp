#include "vendas.h"
#include "produtos.h"
#include "compradores.h"
#include "vendedores.h"
#include <iostream>
#include <fstream>
#include <ctime>
#include <cstdlib>  // Para rand() e srand()
using namespace std;

Vendas::Vendas(int codigoP, int quant) {
    verificar_estoque(codigoP,quant);
}
void Vendas::setCodigoVenda() {
    unsigned seed = time(0);
    srand(seed);
    // Criar verificação (depende da formatação do txt)
    codigoVenda = rand() % 1001;
}

void Vendas::aicionar_item(int codigoItem,int quant) {
    Produtos item = Produtos::buscar_codigo_produto(codigoItem);
    ItemVenda produtoSolicitado;
    produtoSolicitado.codigoProduto = codigoItem;
    produtoSolicitado.nomeProduto = item.nome;
    produtoSolicitado.precoUnitario = item.preco;
    if (verificar_estoque(codigoItem,quant)) {
        produtoSolicitado.quantidadeVendida = quant;
        produtoSolicitado.precoTotal = item.preco * quant;
    }


}
bool Vendas::verificar_estoque(int codigoP, int quant) {
    Produtos produtoSolicitado = getProduto(codigoP);
    if (quant<=produtoSolicitado.estoque) {
        produtoSolicitado-quant;
        quantidade = quant;
        calcular_preco(quant,produtoSolicitado);
    }

}
void Vendas::calcular_preco(int quant, Produtos produtoSolicitado) {
    float precoU = produtoSolicitado.getPreco();
    precoUnidade = precoU;
    precoTotal = precoU*quant;
}

int main() {
    return 0;
}
