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
    codigoProduto = codigoP;
    quantidade = quant;
    setCodigoVenda();
}
void Vendas::setCodigoVenda() {
    unsigned seed = time(0);
    srand(seed);
    // Criar verificação (depende da formatação do txt)
    codigoVenda = rand() % 1001;
}
void Vendas::realizar_compra(int codigo, int quant) {
    // Implementação do
    // Produtos
    // int estoque =
}

int main() {
    return 0;
}
