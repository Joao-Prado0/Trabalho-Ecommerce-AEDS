#include "vendas.h"
#include "produtos.h"
#include "compradores.h"
#include "vendedores.h"
#include <iostream>
#include <fstream>
#include <ctime>
#include <cstdlib>  // Para rand() e srand()
using namespace std;
Vendas::Vendas(){}
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
    if (verificar_estoque(codigoItem,quant)) {
        produtoSolicitado.quantidadeVendida = quant;
        produtoSolicitado.precoTotal = item.preco * quant;
        produtoSolicitado.codigoProduto = codigoItem;
        produtoSolicitado.nomeProduto = item.nome;
        produtoSolicitado.precoUnitario = item.preco;
    } else {
        cout << "O produto: "<<item.nome<<". Esta esgotado"<<endl;
    }
}
bool Vendas::verificar_estoque(int codigoItem, int quant) {
    Produtos produtoSolicitado = getProduto(codigoItem);
    if (quant<=produtoSolicitado.estoque) {
        Produtos.diminuir_estoque(quant);
        return true;
    }
    return false;
}
void Vendas::calcular_preco(int quant, Produtos produtoSolicitado) {
    float precoU = produtoSolicitado.getPreco();
    precoUnidade = precoU;
    precoTotal = precoU*quant;
}
Vendas Vendas::consultar_venda(int codigoV) {
    // Vai retornar objeto da classe venda com todas as informações ou imprimir as informações na tela (decidir depois)
}
void Vendas::alterar_venda(int codigoV) {
    //Alteração de venda, buscar no arquivo pelo codigo
}
void Vendas::deletar_venda(int codigoV) {
    //Deletar venda, consultar no arquivo pelo codigo
}
void Vendas::inserir_venda_manualmente(int codigoV,int codigoVR, string nomeC, float valorT,vector<ItemVenda> produtos) {
    //Não sei qual o sentido dessa, vou perguntar
}
int main() {
    return 0;
}
