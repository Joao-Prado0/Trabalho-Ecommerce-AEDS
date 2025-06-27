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
    verificar_estoque();
}
void Vendas::setCodigoVenda() {
    unsigned seed = time(0);
    srand(seed);
    // Criar verificação (depende da formatação do txt)
    codigoVenda = rand() % 1000;
}
Vendas Vendas::inicializar_com_codigo(int codigoV) {
    return Vendas();
}
// void Vendas::aicionar_item(int codigoItem,int quant) {
//     Produtos item = Produtos::buscar_codigo_produto(codigoItem);
//     ItemVenda produtoSolicitado;
//     if (verificar_estoque(codigoItem,quant)) {
//         produtoSolicitado.quantidadeVendida = quant;
//         produtoSolicitado.precoTotal = item.preco * quant;
//         produtoSolicitado.codigoProduto = codigoItem;
//         produtoSolicitado.nomeProduto = item.nome;
//         produtoSolicitado.precoUnitario = item.preco;
//     } else {
//         cout << "O produto: "<<item.nome<<". Esta esgotado"<<endl;
//     }
// }
bool Vendas::verificar_estoque() {
    return true;
}
void Vendas::calcular_preco(int quant) {

}

void Vendas::consultar_venda(int codigoV) {
    ifstream arquivo("../data/vendas.txt");
    string linha;
    bool encontrou = false;
    bool imprimir = false;

    if (!arquivo.is_open()) {
        cout << "Erro ao abrir o arquivo" << endl;
    }

    while (getline(arquivo,linha)) {
        if (linha.find("Codigo: " + to_string(codigoV)) != string::npos) {
            encontrou = true;
            imprimir = true;
            cout << "\n=== Detalhes da Venda ===" << endl;
        }

        if (imprimir) {
            cout << linha << endl;
        }

        if (linha.find("---") != string::npos) {
            if (encontrou) break;
            imprimir = false;
        }
    }

    if (!encontrou) {
        cout << "Venda com codigo " << codigoV << " nao encontrada." << endl;
    }
    arquivo.close();
}
void Vendas::alterar_venda(int codigoV) {
    Vendas alterarVenda = inicializar_com_codigo(codigoV);
    int opcao;
    do {
        cout << "Insira Opcao Desejada: " << endl;
        cout << "1. Alterar codigo da venda:" << endl;
        cout << "2. ALterar codigo do vendedor:" << endl;
        cout << "3. Alterar nome do comprador:" << endl;
        cout << "4. Alterar valor total da compra:" << endl;
        cout << "5. ALterar valor final:" << endl;
        cout << "6. Alterar itens da venda:" << endl;
        cout << "0. Sair" << endl;
        cin >> opcao;
        cin.ignore();
    }while (opcao!=0);
    switch (opcao) {
        case 1:
            cout<<"Insira o novo codigo de venda: "<<endl;
            cin >> alterarVenda.codigoVenda;
        case 2:
            cout<<"Insira o novo codigo de vendedor: "<<endl;
            cin >> alterarVenda.codigoVendedor;
        case 3:
            cout<<"Insira o novo nome do comprador: "<<endl;
            cin >> alterarVenda.nomeComprador;
        case 4:
            cout<<"Insira o novo valor da venda: "<<endl;
            cin >> alterarVenda.valorTotal;
        case 5:
            cout<<"Insira o novo valor do frete: "<<endl;
            cin >> alterarVenda.frete;
        case 6:
            alterar_itens_venda(codigoV);
    }
}
void Vendas::alterar_itens_venda(int codigoV) {

}
void Vendas::deletar_venda(int codigoV) {
    //Deletar venda, consultar no arquivo pelo codigo
}
void Vendas::inserir_venda_manualmente(int codigoV,int codigoVR, string nomeC, float valorT,ItemVenda *produtos) {

}

