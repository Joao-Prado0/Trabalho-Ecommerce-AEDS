#include <iostream>
#include "produtos.h"
using namespace std;

void submenu_produtos() {
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

void submenu_vendedores() {
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

void submenu_compradores() {
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

void submenu_vendas() {
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
void submenu_realizar_venda() {
    int codigoProduto,codigoVendedor,cpfComprador,quantidadeProduto;
    bool usuario = false, vendedor = false;
    do {
        cout << "Informe seu CPF:" << endl;
        cin >> cpfComprador;
        if (validar_cpf(cpfComprador)) {
            usuario = true;
            //chamar função da classe vendas
        } else {
            cout << "Insira um cpf valido" << endl;
        }
    } while (!usuario);
    do {
        //imprimir todos os produtos disponíveis
        cout <<"Insira codigo do produto desejado (caso deseje finalizar a compra insira 0):"<<endl;
        cin >> codigoProduto;
        if (validar_produto(codigoProduto)) {
            cout <<"Insira quantas unidades desejadas:"<<endl;
            cin >> quantidadeProduto;
            // inicializar objeto na classe vendas
        } else {
            cout << "Insira um codigo valido" << endl;
        }
        system("cls");
    } while (codigoProduto!=0);
    do {
        // imprimir todos os vendedores (direto pelo arquivo)
        cout << "Insira o codigo do vendedor que te atendeu"
    } while (!vendedor)
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
        cout << "5. Realizar Compra" << endl;
        cout << "0. Sair" << endl;
        cout << "Escolha uma opcao: ";
        cin >> opcao;
        cin.ignore();
        switch(opcao) {
            case 1:
                submenu_produtos();
                break;
            case 2:
                submenu_vendedores();
                break;
            case 3:
                submenu_compradores();
                break;
            case 4:
                submenu_vendas();
                break;
            case 5:
                submenu_realizar_venda();
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