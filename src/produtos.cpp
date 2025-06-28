#include "produtos.h"
#include <iostream>
#include <fstream>
#include <iomanip>
#include <sstream>

using namespace std;

Produtos::Produtos() : proximoCodigo(1001) {
    carregar_produtos();
}

void Produtos::atualizarProximoCodigo() {
    proximoCodigo = 1001;
    for (const auto& p : lista_produtos) {
        if (p.codigo >= proximoCodigo) proximoCodigo = p.codigo + 1;
    }
}

int Produtos::gerarCodigoAutomatico() {
    atualizarProximoCodigo();
    return proximoCodigo++;
}

bool Produtos::inserir_produto(const string& nome, int codigo, int quantidade, float preco) {
    for (const auto& p : lista_produtos) {
        if (p.codigo == codigo) return false;
    }
    Produto novo{codigo, nome, quantidade, preco};
    lista_produtos.push_back(novo);
    salvar_produtos();
    return true;
}

Produto* Produtos::consultar_produto(int codigo) {
    for (auto& p : lista_produtos) {
        if (p.codigo == codigo) return &p;
    }
    return nullptr;
}

bool Produtos::alterar_produto(int codigo, const string* novo_nome, int nova_quantidade, float novo_preco) {
    for (auto& p : lista_produtos) {
        if (p.codigo == codigo) {
            if (novo_nome) p.nome = *novo_nome;
            if (nova_quantidade != -1) p.quantidadeEstoque = nova_quantidade;
            if (novo_preco != -1) p.precoVenda = novo_preco;
            salvar_produtos();
            return true;
        }
    }
    return false;
}

bool Produtos::excluir_produto(int codigo) {
    for (auto it = lista_produtos.begin(); it != lista_produtos.end(); ++it) {
        if (it->codigo == codigo) {
            lista_produtos.erase(it);
            salvar_produtos();
            return true;
        }
    }
    return false;
}

void Produtos::listar_produtos() {
    if (lista_produtos.empty()) {
        cout << "\nNenhum produto cadastrado!" << endl;
        return;
    }
    cout << "\n=== LISTA DE PRODUTOS ===" << endl;
    cout << "Codigo    Nome do Produto                    Estoque    Preco (R$)" << endl;
    cout << "------    --------------------------------    -------    ----------" << endl;
    for (const auto& p : lista_produtos) {
        cout << setw(8) << left << p.codigo << "    "
             << setw(32) << left << p.nome << "    "
             << setw(8) << right << p.quantidadeEstoque << "    "
             << setw(10) << right << fixed << setprecision(2) << p.precoVenda << endl;
    }
}

void Produtos::salvar_produtos() {
    ofstream arquivo("data/estoque.txt");
    if (!arquivo.is_open()) {
        cout << "Erro ao abrir arquivo para escrita!" << endl;
        return;
    }
    
    for (const auto& p : lista_produtos) {
        arquivo << "Produto:" << endl;
        arquivo << "Codigo: " << p.codigo << endl;
        arquivo << "Nome: " << p.nome << endl;
        arquivo << "Estoque: " << p.quantidadeEstoque << endl;
        arquivo << "Preco: " << fixed << setprecision(2) << p.precoVenda << endl;
        arquivo << "---" << endl;
    }
    
    arquivo.close();
}

void Produtos::carregar_produtos() {
    lista_produtos.clear();
    ifstream arquivo("data/estoque.txt");
    if (!arquivo.is_open()) {
        cout << "ERRO: Nao foi possivel abrir o arquivo data/estoque.txt" << endl;
        return;
    }
    
    string linha;
    Produto produto_atual;
    bool lendo_produto = false;
    
    while (getline(arquivo, linha)) {
        if (linha.find("Produto:") != string::npos) {
            if (lendo_produto) {
                lista_produtos.push_back(produto_atual);
            }
            produto_atual = Produto();
            lendo_produto = true;
        }
        else if (linha.find("Codigo: ") != string::npos) {
            produto_atual.codigo = stoi(linha.substr(8));
        }
        else if (linha.find("Nome: ") != string::npos) {
            produto_atual.nome = linha.substr(6);
        }
        else if (linha.find("Estoque: ") != string::npos) {
            produto_atual.quantidadeEstoque = stoi(linha.substr(9));
        }
        else if (linha.find("Preco: ") != string::npos) {
            produto_atual.precoVenda = stof(linha.substr(7));
        }
        else if (linha.find("---") != string::npos) {
            if (lendo_produto) {
                lista_produtos.push_back(produto_atual);
                lendo_produto = false;
            }
        }
    }
    
    if (lendo_produto) {
        lista_produtos.push_back(produto_atual);
    }
    
    atualizarProximoCodigo();
    arquivo.close();
}

// Métodos de interface para o main.cpp
void Produtos::inserir_produto_manualmente() {
    Produto novoProduto;
    int opcao;

    cout << "\n=== CADASTRAR PRODUTO ===" << endl;

    cout << "1. Gerar codigo automaticamente" << endl;
    cout << "2. Inserir codigo manualmente" << endl;
    cout << "Escolha uma opcao: ";
    cin >> opcao;
    cin.ignore();

    if (opcao == 1) {
        novoProduto.codigo = gerarCodigoAutomatico();
        cout << "Codigo gerado automaticamente: " << novoProduto.codigo << endl;
    } else if (opcao == 2) {
        do {
            cout << "Digite o codigo do produto: ";
            cin >> novoProduto.codigo;
            cin.ignore();

            if (consultar_produto(novoProduto.codigo) != nullptr) {
                cout << "Erro: Ja existe um produto com este codigo!" << endl;
            }
        } while (consultar_produto(novoProduto.codigo) != nullptr);
    } else {
        cout << "Opcao invalida!" << endl;
        return;
    }

    cout << "Digite o nome do produto: ";
    getline(cin, novoProduto.nome);

    cout << "Digite a quantidade em estoque: ";
    cin >> novoProduto.quantidadeEstoque;
    cin.ignore();

    cout << "Digite o preco de venda: R$ ";
    cin >> novoProduto.precoVenda;
    cin.ignore();

    bool resultado = inserir_produto(novoProduto.nome, novoProduto.codigo,
                                   novoProduto.quantidadeEstoque, novoProduto.precoVenda);

    if (resultado) {
        cout << "\nProduto cadastrado com sucesso!" << endl;
        cout << "\n=== Dados do Produto ===" << endl;
        cout << "Codigo: " << novoProduto.codigo << endl;
        cout << "Nome: " << novoProduto.nome << endl;
        cout << "Quantidade em Estoque: " << novoProduto.quantidadeEstoque << endl;
        cout << "Preco de Venda: R$ " << fixed << setprecision(2) << novoProduto.precoVenda << endl;
        cout << "=========================" << endl;
    } else {
        cout << "\nErro: Codigo duplicado!" << endl;
    }
}

void Produtos::consultar_produto_interface() {
    int opcao;

    cout << "\n=== CONSULTAR PRODUTO ===" << endl;
    cout << "1. Consultar por codigo" << endl;
    cout << "2. Listar todos os produtos" << endl;
    cout << "Escolha uma opcao: ";
    cin >> opcao;
    cin.ignore();

    if (opcao == 1) {
        int codigo;
        cout << "Digite o codigo do produto: ";
        cin >> codigo;
        cin.ignore();

        Produto* produto = consultar_produto(codigo);
        if (produto != nullptr) {
            cout << "\n=== Dados do Produto ===" << endl;
            cout << "Codigo: " << produto->codigo << endl;
            cout << "Nome: " << produto->nome << endl;
            cout << "Quantidade em Estoque: " << produto->quantidadeEstoque << endl;
            cout << "Preco de Venda: R$ " << fixed << setprecision(2) << produto->precoVenda << endl;
            cout << "=========================" << endl;
        } else {
            cout << "Produto nao encontrado!" << endl;
        }
    } else if (opcao == 2) {
        listar_produtos();
    } else {
        cout << "Opcao invalida!" << endl;
    }
}

void Produtos::alterar_produto_interface() {
    int codigo;

    cout << "\n=== ALTERAR PRODUTO ===" << endl;
    cout << "Digite o codigo do produto: ";
    cin >> codigo;
    cin.ignore();

    Produto* produto = consultar_produto(codigo);
    if (produto == nullptr) {
        cout << "Produto nao encontrado!" << endl;
        return;
    }

    cout << "\nProduto encontrado:" << endl;
    cout << "\n=== Dados do Produto ===" << endl;
    cout << "Codigo: " << produto->codigo << endl;
    cout << "Nome: " << produto->nome << endl;
    cout << "Quantidade em Estoque: " << produto->quantidadeEstoque << endl;
    cout << "Preco de Venda: R$ " << fixed << setprecision(2) << produto->precoVenda << endl;
    cout << "=========================" << endl;

    string novo_nome;
    int nova_quantidade = -1;
    float novo_preco = -1;
    bool alterado = false;
    bool nome_alterado = false;

    int opcao;
    do {
        cout << "\nO que deseja alterar?" << endl;
        cout << "1. Nome" << endl;
        cout << "2. Quantidade em estoque" << endl;
        cout << "3. Preco de venda" << endl;
        cout << "0. Voltar" << endl;
        cout << "Escolha uma opcao: ";
        cin >> opcao;
        cin.ignore();

        switch (opcao) {
            case 1:
                cout << "Digite o novo nome: ";
                getline(cin, novo_nome);
                alterado = true;
                nome_alterado = true;
                cout << "Nome alterado!" << endl;
                break;
            case 2:
                cout << "Digite a nova quantidade em estoque: ";
                cin >> nova_quantidade;
                cin.ignore();
                alterado = true;
                cout << "Quantidade alterada!" << endl;
                break;
            case 3:
                cout << "Digite o novo preco de venda: R$ ";
                cin >> novo_preco;
                cin.ignore();
                alterado = true;
                cout << "Preco alterado!" << endl;
                break;
            case 0:
                break;
            default:
                cout << "Opcao invalida!" << endl;
        }
    } while (opcao != 0);

    if (!alterado) {
        cout << "Nenhuma alteracao foi feita!" << endl;
        return;
    }
    
    const string* ptr_nome = nome_alterado ? &novo_nome : nullptr;
    bool resultado = alterar_produto(codigo, ptr_nome, nova_quantidade, novo_preco);

    if (resultado) {
        cout << "Produto alterado com sucesso!" << endl;
    } else {
        cout << "Erro ao alterar produto!" << endl;
    }
}

void Produtos::excluir_produto_interface() {
    int codigo;

    cout << "\n=== EXCLUIR PRODUTO ===" << endl;
    cout << "Digite o codigo do produto: ";
    cin >> codigo;
    cin.ignore();

    Produto* produto = consultar_produto(codigo);
    if (produto == nullptr) {
        cout << "Produto nao encontrado!" << endl;
        return;
    }

    cout << "\nProduto encontrado:" << endl;
    cout << "\n=== Dados do Produto ===" << endl;
    cout << "Codigo: " << produto->codigo << endl;
    cout << "Nome: " << produto->nome << endl;
    cout << "Quantidade em Estoque: " << produto->quantidadeEstoque << endl;
    cout << "Preco de Venda: R$ " << fixed << setprecision(2) << produto->precoVenda << endl;
    cout << "=========================" << endl;

    char confirmacao;
    cout << "\nTem certeza que deseja excluir este produto? (s/n): ";
    cin >> confirmacao;
    cin.ignore();

    if (confirmacao == 's' || confirmacao == 'S') {
        bool resultado = excluir_produto(codigo);

        if (resultado) {
            cout << "Produto excluido com sucesso!" << endl;
        } else {
            cout << "Erro ao excluir produto!" << endl;
        }
    } else {
        cout << "Exclusao cancelada!" << endl;
    }
}

