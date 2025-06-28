#include "vendas.h"
#include "produtos.h"
#include "compradores.h"
#include "vendedores.h"
#include <iostream>
#include <fstream>
#include <ctime>
#include <iomanip>
#include <cmath>
using namespace std;
Vendas::Vendas(){}

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
        return;
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
    ifstream arquivoEntrada("../data/vendas.txt");
    if (!arquivoEntrada.is_open()) {
        cout << "Erro ao abrir o arquivo" << endl;
        return;
    }
    vector<string> linhas;
    string linha;
    while (getline(arquivoEntrada, linha)) {
        linhas.push_back(linha);
    }
    arquivoEntrada.close();

    bool encontrou = false;
    int inicio = -1, fim = -1;

    for (size_t i = 0; i < linhas.size(); ++i) {
        if (linhas[i] == "Codigo: " + to_string(codigoV)) {
            encontrou = true;
            inicio = i;
        }
        if (encontrou && linhas[i] == "---") {
            fim = i;
            break;
        }
    }
    if (!encontrou) {
        cout << "Venda com codigo " << codigoV << " nao encontrada." << endl;
        return;
    }
    int opcao;
    do {
        cout << "O que deseja alterar?"<<endl;
        cout << "1. Codigo da venda."<<endl;
        cout << "2. Nome do comprador." << endl;
        cout << "3. Valor total." << endl;
        cout << "4. Frete."<<endl;
        cout << "5. Itens da venda."<<endl;
        cout << "0. Sair e salvar."<<endl;
        cin >> opcao;
        cin.ignore();
        switch (opcao) {
            case 1: {
                int novoCodigo;
                cout << "Novo codigo: ";
                cin >> novoCodigo;
                linhas[inicio] = "Codigo: " + to_string(novoCodigo);
                break;
            }
            case 2: {
                string novoNome;
                cout << "Novo nome do comprador: ";
                getline(cin, novoNome);
                linhas[inicio + 1] = "Comprador: " + novoNome;
                break;
            }
            case 3: {
                float novoTotal;
                cout << "Novo valor total: ";
                cin >> novoTotal;
                linhas[fim - 1] = "Valor Total: " + to_string(novoTotal);
                break;
            }
            case 4: {
                float novoFrete;
                cout << "Novo valor do frete: ";
                cin >> novoFrete;
                linhas[fim - 2] = "Frete: " + to_string(novoFrete);
                break;
            }
            case 5:
                alterar_itens_venda(codigoV);
                break;
            case 0:
                cout << "Saindo da edição." << endl;
                break;
            default:
                cout << "Opção inválida!" << endl;
        }
    } while (opcao != 0);

    ofstream arquivoSaida("../data/vendas.txt");
    if (!arquivoSaida.is_open()) {
        cout << "Erro ao regravar o arquivo." << endl;
        return;
    }
    for (size_t i = 0; i < linhas.size(); ++i) {
        arquivoSaida << linhas[i] << endl;
    }
    arquivoSaida.close();
    cout << "Venda atualizada com sucesso!" << endl;
}
void Vendas::alterar_itens_venda(int codigoV) {
    ifstream arquivoEntrada("../data/vendas.txt");
    if (!arquivoEntrada.is_open()) {
        cout << "Erro ao abrir o arquivo" << endl;
        return;
    }
    vector<string> linhas;
    string linha;
    while (getline(arquivoEntrada, linha)) {
        linhas.push_back(linha);
    }
    arquivoEntrada.close();
    int inicio = -1, fim = -1;
    for (size_t i = 0; i < linhas.size(); ++i) {
        if (linhas[i] == "Codigo: " + to_string(codigoV)) {
            inicio = i;
        }
        if (inicio != -1 && linhas[i] == "---") {
            fim = i;
            break;
        }
    }
    if (inicio == -1 || fim == -1) {
        cout << "Venda não encontrada." << endl;
        return;
    }

    int idxItens = -1;
    for (int i = inicio; i < fim; ++i) {
        if (linhas[i] == "Itens:") {
            idxItens = i;
            break;
        }
    }
    if (idxItens == -1) {
        cout << "Erro: seção de itens não encontrada." << endl;
        return;
    }

    int idxFrete = -1;
    for (int i = idxItens + 1; i < fim; ++i) {
        if (linhas[i].find("Frete:") != string::npos) {
            idxFrete = i;
            break;
        }
    }
    if (idxFrete == -1) {
        cout << "Erro: linha de frete não encontrada." << endl;
        return;
    }

    linhas.erase(linhas.begin() + idxItens + 1, linhas.begin() + idxFrete);

    int n;
    cout << "Quantos produtos deseja inserir? ";
    cin >> n;
    vector<string> novosItens;
    float novoTotal = 0.0f;

    for (int i = 0; i < n; ++i) {
        int cod, qtd;
        float preco;
        string nome;

        cout << "Produto " << (i+1) << endl;
        cout << "Código: "; cin >> cod;
        cout << "Nome: "; cin.ignore(); getline(cin, nome);
        cout << "Quantidade: "; cin >> qtd;
        cout << "Preço unitário: "; cin >> preco;

        preco = round(preco * 100) / 100;
        float total = round((preco * qtd) * 100) / 100;
        novoTotal += total;

        string itemLinha = " - Codigo: " + to_string(cod)
        + " | Nome: " + nome
        + " | Qtd: " + to_string(qtd)
        + " | Unitario: " + to_string(preco)
        + " | Total: " + to_string(total);
        novosItens.push_back(itemLinha);
    }
    linhas.insert(linhas.begin() + idxFrete, novosItens.begin(), novosItens.end());
    float novoFrete = calcular_frete(novoTotal);
    linhas[idxFrete] = "Frete: " + to_string(novoFrete);
    linhas[idxFrete + 1] = "Valor Total: " + to_string(novoTotal + novoFrete);

    ofstream arquivoaSaida("../data/vendas.txt");
    if (!arquivoaSaida.is_open()) {
        cout << "Erro ao reescrever o arquivo" << endl;
        return;
    }
    for (size_t i = 0; i < linhas.size(); ++i) {
        arquivoaSaida << linhas[i] << endl;
    }
    arquivoaSaida.close();
    cout << "Itens alterados com sucesso!" << endl;
}
void Vendas::deletar_venda(int codigoV) {
    ifstream entrada("../data/vendas.txt");
    if (!entrada.is_open()) {
        cout << "Erro ao abrir o arquivo" << endl;
        return;
    }

    vector<string> linhas;
    string linha;
    while (getline(entrada, linha)) {
        linhas.push_back(linha);
    }
    entrada.close();

    int inicio = -1, fim = -1;
    for (size_t i = 0; i < linhas.size(); ++i) {
        if (linhas[i] == "Codigo: " + to_string(codigoV)) {
            // "Venda:" está sempre uma linha antes
            if (i > 0 && linhas[i - 1] == "Venda:") {
                inicio = i - 1;
            } else {
                inicio = i;
            }
        }
        if (inicio != -1 && linhas[i] == "---") {
            fim = i;
            break;
        }
    }
    if (inicio == -1 || fim == -1) {
        cout << "Venda com código " << codigoV << " não encontrada." << endl;
        return;
    }

    linhas.erase(linhas.begin() + inicio, linhas.begin() + fim + 1);

    ofstream arquivosSaida("../data/vendas.txt");
    if (!arquivosSaida.is_open()) {
        cout << "Erro ao reescrever o arquivo" << endl;
        return;
    }
    for (const string& l : linhas) {
        arquivosSaida << l << endl;
    }
    arquivosSaida.close();
    cout << "Venda removida com sucesso!" << endl;
}
void Vendas::inserir_venda_manualmente() {
    int diferentesProdutos, codigoVR;
    float valorT = 0.0f;
    string nome;
    int codigoV = criar_codigoVenda();
    cin.clear();
    while (true) {
        cout << "Insira o numero de produtos comprados: " << endl;
        if (cin >> diferentesProdutos) {
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            if (diferentesProdutos > 0) {
                break;
            }
            cout << "Quantidade deve ser maior que zero!" << endl;
        } else {
            cout << "Entrada invalida! Digite um numero valido." << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
    }

    ItemVenda* produtos = new ItemVenda[diferentesProdutos];

    for (int i = 0; i < diferentesProdutos; i++) {
        cout << "\nProduto " << i+1 << ":\n";
        while (true) {
            cout << "Codigo: ";
            if (cin >> produtos[i].codigoProduto) {
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                break;
            }
            cout << "Codigo invalido! Digite um numero." << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
        cout << "Nome: ";
        getline(cin, produtos[i].nomeProduto);

        while (true) {
            cout << "Quantidade: ";
            if (cin >> produtos[i].quantidadeVendida) {
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                if (produtos[i].quantidadeVendida > 0) {
                    break;
                }
                cout << "Quantidade deve ser maior que zero!" << endl;
            } else {
                cout << "Quantidade invalida! Digite um numero." << endl;
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
            }
        }

        while (true) {
            cout << "Preco Unitario: ";
            if (cin >> produtos[i].precoUnitario) {
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                if (produtos[i].precoUnitario > 0) {
                    break;
                }
                cout << "Preco deve ser maior que zero!" << endl;
            } else {
                cout << "Preco invalido! Digite um numero." << endl;
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
            }
        }

        produtos[i].precoTotal = produtos[i].quantidadeVendida * produtos[i].precoUnitario;
        valorT += produtos[i].precoTotal;
    }

    cout << "Insira o nome do comprador: " << endl;
    getline(cin, nome);

    while (true) {
        cout << "Insira o codigo do vendedor: " << endl;
        if (cin >> codigoVR) {
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            break;
        } else {
            cout << "Codigo invalido! Digite um numero." << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
    }

    imprimir_no_documento(codigoV, codigoVR, nome, valorT, produtos, diferentesProdutos);
    delete[] produtos;
}
void Vendas::imprimir_no_documento(int codigoV,int codigoVR, string nome, float valorT, ItemVenda *itens, int quant) {
    ofstream arquivo("../data/vendas.txt", ios::app);
    if (!arquivo.is_open()) {
        cerr<<"Erro ao abrir o arquivo" << endl;
        return;
    }
    arquivo << "Venda:\n";
    arquivo << "Codigo: " << codigoV << "\n";
    arquivo << "Comprador: " << nome << "\n";
    arquivo << "Itens:\n";
    for (int i = 0;i<quant; i++) {
        arquivo << " - Codigo: " << itens[i].codigoProduto
               << " | Nome: " << itens[i].nomeProduto
               << " | Qtd: " << itens[i].quantidadeVendida
               << " | Unitario: " << fixed << setprecision(2) << itens[i].precoUnitario
               << " | Total: " << itens[i].precoTotal << "\n";
    }
    arquivo << "Frete: " << calcular_frete(valorT)<<"\n";
    arquivo << "Valor Total: " << valorT+calcular_frete(valorT)<<"\n";
    arquivo << "---\n";
    // talvez colocar função que seta a comissão do vendedor automaticamente.
    arquivo.close();
    cout << "Venda registrada com sucesso! Codigo gerado: "<< codigoV<< endl;
}
