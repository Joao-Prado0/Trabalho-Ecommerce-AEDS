#include "vendas.h"
#include "produtos.h"
#include "compradores.h"
#include "vendedores.h"
#include <iostream>
#include <fstream>
#include <ctime>
#include <cstdlib>  // Para rand() e srand()
#include <utility>
using namespace std;
Vendas::Vendas(){}
Vendas::Vendas(int codigoV,int codigoVR, string nome, float valorT, ItemVenda *itens, int quant) {
    codigoVenda = codigoV;
    codigoVendedor = codigoVR;
    nomeComprador = std::move(nome);
    auto *produtosInseridos = new ItemVenda[quant];
    for (int i=0; i<quant; i++) {
        produtosInseridos[i] = itens[i];
    }
    frete = calcular_frete(valorT);
    valorTotal = valorT + frete;
}
int Vendas::criar_codigoVenda() {
    static bool inicializado = false;
    if (!inicializado) {
        srand(time(nullptr));
        inicializado = true;
    }
    int codigo;
    do {
        codigo = (rand() % 900) + 100;
    } while (verificar_codigo(codigo));
    return codigo;
}

bool Vendas::verificar_codigo(int codigo) {
    ifstream arquivo("../data/vendas.txt");
    string linha;
    while (getline(arquivo, linha)) {
        if (linha.find("Codigo: " + to_string(codigo)) != string::npos) {
            return true;
        }
    }
    return false;
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
float Vendas::calcular_frete(float valorT) {
    if (valorT<=100.00) {
        return 30.00;
    }
    if (valorT>100.00 && valorT<=300.00) {
        return 20.00;
    }
    return 0.00;
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
void Vendas::inserir_venda_manualmente() {
    int diferentesProdutos,codigoVR;
    float valorT = 0.0f;
    string nome;
    int codigoV = criar_codigoVenda();
    cout << "Quantos produtos diferentes foram comprados" << endl;
    cin >> diferentesProdutos;
    if (diferentesProdutos <= 0) {
        cout << "Quantidade inválida!" << endl;
        return;
    }
    ItemVenda* produtos = new ItemVenda[diferentesProdutos];
    for (int i = 0; i < diferentesProdutos; i++) {
        cout << "\nProduto " << i+1 << ":\n";

        cout << "Código: ";
        cin >> produtos[i].codigoProduto;

        cout << "Nome: ";
        cin.ignore();
        getline(cin, produtos[i].nomeProduto);

        cout << "Quantidade: ";
        cin >> produtos[i].quantidadeVendida;

        cout << "Preço Unitário: ";
        cin >> produtos[i].precoUnitario;

        produtos[i].precoTotal = produtos[i].quantidadeVendida * produtos[i].precoUnitario;
        valorT += produtos[i].precoTotal;
    }
    cout<<"Insira o nome do comprador: "<<endl;
    cin.ignore();
    cin >> nome;
    cout<<"Insira o codigo do vendedor: "<<endl;
    cin >> codigoVR;

    Vendas(codigoV,codigoVR,nome,valorT,produtos,diferentesProdutos);
    delete[] produtos;
}

