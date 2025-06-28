#include <iostream>
#include "src/produtos.h"
using namespace std;

int main() {
    Produtos produtos;
    int opcao;
    do {
        cout << "\n--- Gerenciar Produtos (TESTE) ---" << endl;
        cout << "1. Listar Produtos" << endl;
        cout << "2. Cadastrar Produto" << endl;
        cout << "3. Consultar Produto" << endl;
        cout << "4. Alterar Produto" << endl;
        cout << "5. Excluir Produto" << endl;
        cout << "0. Sair" << endl;
        cout << "Escolha uma opcao: ";
        cin >> opcao;
        cin.ignore();
        switch(opcao) {
            case 1:
                produtos.listar_produtos();
                break;
            case 2:
                produtos.inserir_produto_manualmente();
                break;
            case 3:
                produtos.consultar_produto_interface();
                break;
            case 4:
                produtos.alterar_produto_interface();
                break;
            case 5:
                produtos.excluir_produto_interface();
                break;
            case 0:
                cout << "Saindo..." << endl;
                break;
            default:
                cout << "Opcao invalida!" << endl;
        }
    } while(opcao != 0);
    return 0;
} 