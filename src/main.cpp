#include <iostream>
#include "produtos.h"
#include "compradores.h"
#include "vendas.h"
#include "vendedores.h"
using namespace std;

void submenu_produtos(Produtos& produtos) {
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
                produtos.inserir_produto_manualmente();
                break;
            case 2:
                produtos.consultar_produto_interface();
                break;
            case 3:
                produtos.alterar_produto_interface();
                break;
            case 4:
                produtos.excluir_produto_interface();
                break;
            case 0:
                break;
            default:
                cout << "Opcao invalida!" << endl;
        }
    } while(opcao != 0);
}

void submenu_vendedores(Vendedores vendedores) {
    int opcao, numero;
    float valor;

    do {
        cout << "\n=== GERENCIAMENTO DE VENDEDORES ===" << endl;
        cout << "1. Cadastrar Vendedor" << endl;
        cout << "2. Consultar Vendedor" << endl;
        cout << "3. Alterar Vendedor" << endl;
        cout << "4. Excluir Vendedor" << endl;
        cout << "5. Adicionar Comissao" << endl;
        cout << "6. Listar Todos Vendedores" << endl;
        cout << "0. Voltar" << endl;
        cout << "Opcao: ";
        cin >> opcao;

        switch(opcao) {
            case 1:
                vendedores.setNumero();
                vendedores.setNome();
                vendedores.setSalarioFixo();
                vendedores.salvarNoArquivo();
                break;
            case 2:
                cout << "Numero do vendedor: ";
                cin >> numero;
                vendedores.consultarVendedor(numero);
                break;
            case 3:
                cout << "Numero do vendedor: ";
                cin >> numero;
                vendedores.alterarVendedor(numero);
                break;
            case 4:
                cout << "Numero do vendedor: ";
                cin >> numero;
                vendedores.excluirVendedor(numero);
                break;
            case 5:
                cout << "Numero do vendedor: ";
                cin >> numero;
                cout << "Valor da venda: R$ ";
                cin >> valor;
                vendedores.adicionarComissaoPorNumero(numero,valor);
                break;
            case 6:
                vendedores.listarTodosVendedores();
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
                Comprador::inserirCompradorInterface();
                break;
            case 2:
                Comprador::consultarCompradorInterface();
                break;
            case 3:
                Comprador::alterarCompradorInterface();
                break;
            case 4:
                Comprador::excluirCompradorInterface();
                break;
            case 0:
                break;
            default:
                cout << "Opcao invalida!" << endl;
        }
    } while(opcao != 0);
}

void submenu_vendas(Vendas venda) {
    int opcao,codigoVenda;
    do {
        cout << "\n--- Gerenciar Vendas ---" << endl;
        cout << "1. Cadastrar Venda" << endl;
        cout << "2. Consultar Venda" << endl;
        cout << "3. Alterar Venda" << endl;
        cout << "4. Excluir Venda" << endl;
        cout << "0. Voltar" << endl;
        cout << "Escolha uma opcao: ";
        cin >> opcao;
        cin.ignore();
        switch(opcao) {
            case 1:
                venda.inserir_venda_manualmente();
                break;
            case 2:
                cout << "Insira o codigo da venda (ou 0 para voltar)" << endl;
                cin >> codigoVenda;
                venda.consultar_venda(codigoVenda);
                break;
            case 3:
                cout << "Insira o codigo da venda" << endl;
                cin >> codigoVenda;
                venda.alterar_venda(codigoVenda);
                break;
            case 4:
                cout << "Insira o codigo da venda" << endl;
                cin >> codigoVenda;
                venda.deletar_venda(codigoVenda);
                break;
            case 0:
                break;
            default:
                cout << "Opcao invalida!" << endl;
        }
    } while(opcao != 0);
}
void submenu_realizar_venda(Vendas venda,Vendedores vendedores, Produtos& produto, Comprador compradorAtual) {
    string cpfComprador, nomeComprador;
    bool usuarioValido = false;
    do {
        cout << "Informe seu CPF: ";
        cin >> cpfComprador;
        compradorAtual = Comprador::buscarCompradorPorCPF(cpfComprador);
        if (!compradorAtual.getCpf().empty()) {
            usuarioValido = true;
        } else {
            cout << "CPF não encontrado. Tente novamente.\n";
        }
        cin.ignore();
        system("cls");
    } while (!usuarioValido);
    //-------------------------------------------------------------------------------------
    auto carrinhoCompra = new ItemVenda;
    int  codigoProduto;
    int  quantidadeProd;
    int  contadorDeProdutos = 0;
    float valorTotal = 0.00f;
     while (codigoProduto!=0){
        produto.listar_produtos();
        cout <<"Insira codigo do produto desejado (caso deseje finalizar a compra insira 0):"<<endl;
        cin >> codigoProduto;
         if (codigoProduto==0) break;

        Produto prod = produto.consultar_produto(codigoProduto);
        if (!prod.encontrado) {
            cout << "Código inválido!\n";
            continue;
        }

         cout << "Quantidade Desejada";
         cin >> quantidadeProd;

         ItemVenda item;
         item.codigoProduto     = prod.codigo;
         item.nomeProduto       = prod.nome;
         item.quantidadeVendida = quantidadeProd;
         item.precoUnitario     = prod.precoVenda;
         item.precoTotal        = quantidadeProd * prod.precoVenda;
         carrinhoCompra[contadorDeProdutos] = item;
         system("cls");
         contadorDeProdutos++;
         valorTotal += item.precoTotal;
    }
    // ---------------------------------------------------------
    bool vendedorValido = false;
    int codigoVendedor;
    do {
        vendedores.listarTodosVendedores();
        cout << "Insira o codigo do vendedor que te atendeu" << endl;
        cin >> codigoVendedor;
        if (vendedores.verificarNumero(codigoVendedor)) {
            vendedorValido = true;
            vendedores.adicionarComissaoPorNumero(codigoVendedor,valorTotal);
        } else {
            cout << "Insira um codigo valido" << endl;
        }
    } while (!vendedorValido);
//----------------------------------------------------------------------
    // função inicializar objeto venda com todos os parametros gerados
    char notaFiscal;
    cout<<"Deseja gerar nota fiscal? (digite s (sim) ou n (nao))"<<endl;
    cin >> notaFiscal;
    if (notaFiscal=='s' || notaFiscal=='S') {
        // gerar arquivo de nota fiscal
        cout << "Obrigado pela compra!" << endl;
    } else if (notaFiscal=='n' || notaFiscal=='N') {
        cout << "Obrigado pela compra!" << endl;
    }
}
int main() {
    cout << "=== PROGRAMA INICIADO - VERSAO ATUALIZADA ===" << endl;
    Vendas venda;
    Produtos produtos;
    Vendedores vendedores;
    Comprador comprador;

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
                submenu_produtos(produtos);
                break;
            case 2:
                submenu_vendedores(vendedores);
                break;
            case 3:
                submenu_compradores();
                break;
            case 4:
                submenu_vendas(venda);
                break;
            case 5:
                submenu_realizar_venda(venda,vendedores,produtos,comprador);
                break;
            case 0:
                cout << "Saindo..." << endl;
                break;
            default:
                cout << "Opcao invalida! Tente novamente." << endl;

        }
    }while(opcao != 0);
    return 0;
}