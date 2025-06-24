#include <iostream>
#include "produtos.h"
using namespace std;

void submenuProdutos() {
    int opcao;
    do {
        cout << "\n--- Gerenciar Produtos ---" << endl;
        cout << "1. Cadastrar Produto" << endl;
        cout << "2. Consultar Produto" << endl;
        cout << "3. Alterar Produto" << endl;
        cout << "4. Excluir Produto" << endl;
        cout << "0. Voltar" << endl;
        cout << "Escolha uma opcao: ";
        cin >> opcao;
        cin.ignore();
        switch(opcao) {
            case 1:
                cadastrarProduto();
                break;
            case 2:
                consultarProduto();
                break;
            case 3:
                alterarProduto();
                break;
            case 4:
                excluirProduto();
                break;
            case 0:
                break;
            default:
                cout << "Opcao invalida!" << endl;
        }
    } while(opcao != 0);
}

void submenuVendedores() {
    int opcao;
    do {
        cout << "\n--- Gerenciar Vendedores ---" << endl;
        cout << "1. Cadastrar Vendedor" << endl;
        cout << "2. Consultar Vendedor" << endl;
        cout << "3. Alterar Vendedor" << endl;
        cout << "4. Excluir Vendedor" << endl;
        cout << "0. Voltar" << endl;
        cout << "Escolha uma opcao: ";
        cin >> opcao;
        cin.ignore();
        switch(opcao) {
            case 1:
                cout << "Cadastrar Vendedor (implementar)" << endl;
                break;
            case 2:
                cout << "Consultar Vendedor (implementar)" << endl;
                break;
            case 3:
                cout << "Alterar Vendedor (implementar)" << endl;
                break;
            case 4:
                cout << "Excluir Vendedor (implementar)" << endl;
                break;
            case 0:
                break;
            default:
                cout << "Opcao invalida!" << endl;
        }
    } while(opcao != 0);
}

void submenuCompradores() {
    int opcao;
    do {
        cout << "\n--- Gerenciar Compradores ---" << endl;
        cout << "1. Cadastrar Comprador" << endl;
        cout << "2. Consultar Comprador" << endl;
        cout << "3. Alterar Comprador" << endl;
        cout << "4. Excluir Comprador" << endl;
        cout << "0. Voltar" << endl;
        cout << "Escolha uma opcao: ";
        cin >> opcao;
        cin.ignore();
        switch(opcao) {
            case 1:
                cout << "Cadastrar Comprador (implementar)" << endl;
                break;
            case 2:
                cout << "Consultar Comprador (implementar)" << endl;
                break;
            case 3:
                cout << "Alterar Comprador (implementar)" << endl;
                break;
            case 4:
                cout << "Excluir Comprador (implementar)" << endl;
                break;
            case 0:
                break;
            default:
                cout << "Opcao invalida!" << endl;
        }
    } while(opcao != 0);
}

void submenuVendas() {
    int opcao;
    do {
        cout << "\n--- Gerenciar Vendas ---" << endl;
        cout << "1. Realizar Venda" << endl;
        cout << "2. Consultar Venda" << endl;
        cout << "0. Voltar" << endl;
        cout << "Escolha uma opcao: ";
        cin >> opcao;
        cin.ignore();
        switch(opcao) {
            case 1:
                cout << "Realizar Venda (implementar)" << endl;
                break;
            case 2:
                cout << "Consultar Venda (implementar)" << endl;
                break;
            case 0:
                break;
            default:
                cout << "Opcao invalida!" << endl;
        }
    } while(opcao != 0);
}

int main() {
    // Carregar dados dos produtos ao iniciar o programa
    carregarProdutos();
    
    int opcao;
    do {
        cout << "\n===== MENU PRINCIPAL =====" << endl;
        cout << "1. Gerenciar Produtos" << endl;
        cout << "2. Gerenciar Vendedores" << endl;
        cout << "3. Gerenciar Compradores" << endl;
        cout << "4. Gerenciar Vendas" << endl;
        cout << "5. Emitir Nota Fiscal" << endl;
        cout << "0. Sair" << endl;
        cout << "Escolha uma opcao: ";
        cin >> opcao;
        cin.ignore();
        switch(opcao) {
            case 1:
                submenuProdutos();
                break;
            case 2:
                submenuVendedores();
                break;
            case 3:
                submenuCompradores();
                break;
            case 4:
                submenuVendas();
                break;
            case 5:
                cout << "Emitir Nota Fiscal (implementar)" << endl;
                break;
            case 0:
                cout << "Saindo..." << endl;
                break;
            default:
                cout << "Opcao invalida! Tente novamente." << endl;
        }
    } while(opcao != 0);
    return 0;
}