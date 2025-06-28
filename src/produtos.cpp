#include "produtos.h"
#include <iostream>
#include <iomanip>

using namespace std;

vector<Produto> produtos;
int proximoCodigo = 1001;
const string ARQUIVO_PRODUTOS = "estoque.txt";

int gerarCodigoAutomatico() {
    return proximoCodigo++;
}

bool produtoExiste(const vector<Produto>& lista_produtos, int total_produtos, int codigo) {
    for (int i = 0; i < total_produtos; i++) {
        if (lista_produtos[i].codigo == codigo) {
            return true;
        }
    }
    return false;
}

Produto* encontrarProduto(int codigo) {
    for (auto& produto : produtos) {
        if (produto.codigo == codigo) {
            return &produto;
        }
    }
    return nullptr;
}

void exibirProduto(const Produto& produto) {
    cout << "\n=== Dados do Produto ===" << endl;
    cout << "Codigo: " << produto.codigo << endl;
    cout << "Nome: " << produto.nome << endl;
    cout << "Quantidade em Estoque: " << produto.quantidadeEstoque << endl;
    cout << "Preco de Venda: R$ " << fixed << setprecision(2) << produto.precoVenda << endl;
    cout << "=========================" << endl;
}

int cadastrar_produto(vector<Produto>& lista_produtos, int& total_produtos,
                     const string& nome, int codigo, int quantidade_estoque, double preco_venda) {
    if (produtoExiste(lista_produtos, total_produtos, codigo)) {
        return 0;
    }

    Produto novoProduto;
    novoProduto.nome = nome;
    novoProduto.codigo = codigo;
    novoProduto.quantidadeEstoque = quantidade_estoque;
    novoProduto.precoVenda = preco_venda;
    
    lista_produtos.push_back(novoProduto);
    total_produtos = lista_produtos.size();
    return 1;
}

Produto* consultar_produto(const vector<Produto>& lista_produtos, int total_produtos, int codigo) {
    for (int i = 0; i < total_produtos; i++) {
        if (lista_produtos[i].codigo == codigo) {
            return const_cast<Produto*>(&lista_produtos[i]);
        }
    }
    return nullptr;
}

int alterar_produto(vector<Produto>& lista_produtos, int total_produtos, int codigo,
                   const string* novo_nome, int nova_quantidade, double novo_preco) {
    for (int i = 0; i < total_produtos; i++) {
        if (lista_produtos[i].codigo == codigo) {
            bool alterado = false;

            if (novo_nome != nullptr) {
                lista_produtos[i].nome = *novo_nome;
                alterado = true;
            }

            if (nova_quantidade != -1) {
                lista_produtos[i].quantidadeEstoque = nova_quantidade;
                alterado = true;
            }

            if (novo_preco != -1) {
                lista_produtos[i].precoVenda = novo_preco;
                alterado = true;
            }

            return alterado ? 1 : 0;
        }
    }

    return 0;
}

int excluir_produto(vector<Produto>& lista_produtos, int& total_produtos, int codigo) {
    for (int i = 0; i < total_produtos; i++) {
        if (lista_produtos[i].codigo == codigo) {
            for (int j = i; j < total_produtos - 1; j++) {
                lista_produtos[j] = lista_produtos[j + 1];
            }

            total_produtos--;
            return 1;
        }
    }

    return 0;
}
void cadastrarProduto() {
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

            if (produtoExiste(produtos, produtos.size(), novoProduto.codigo)) {
                cout << "Erro: Ja existe um produto com este codigo!" << endl;
            }
        } while (produtoExiste(produtos, produtos.size(), novoProduto.codigo));
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

    int total_produtos = produtos.size();
    int resultado = cadastrar_produto(produtos, total_produtos, novoProduto.nome,
                                    novoProduto.codigo, novoProduto.quantidadeEstoque, novoProduto.precoVenda);

    if (resultado == 1) {
        cout << "\nProduto cadastrado com sucesso!" << endl;
        exibirProduto(novoProduto);
    } else {
        cout << "\nErro: Codigo duplicado!" << endl;
    }
}

void consultarProduto() {
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

        Produto* produto = consultar_produto(produtos, produtos.size(), codigo);
        if (produto != nullptr) {
            exibirProduto(*produto);
        } else {
            cout << "Produto nao encontrado!" << endl;
        }
    } else if (opcao == 2) {
        listarProdutos();
    } else {
        cout << "Opcao invalida!" << endl;
    }
}

void alterarProduto() {
    int codigo;

    cout << "\n=== ALTERAR PRODUTO ===" << endl;
    cout << "Digite o codigo do produto: ";
    cin >> codigo;
    cin.ignore();

    Produto* produto = consultar_produto(produtos, produtos.size(), codigo);
    if (produto == nullptr) {
        cout << "Produto nao encontrado!" << endl;
        return;
    }

    cout << "\nProduto encontrado:" << endl;
    exibirProduto(*produto);

    string novo_nome;
    int nova_quantidade = -1;
    double novo_preco = -1;
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
    int resultado = alterar_produto(produtos, produtos.size(), codigo, ptr_nome, nova_quantidade, novo_preco);

    if (resultado == 1) {
        cout << "Produto alterado com sucesso!" << endl;
    } else {
        cout << "Erro ao alterar produto!" << endl;
    }
}

void excluirProduto() {
    int codigo;

    cout << "\n=== EXCLUIR PRODUTO ===" << endl;
    cout << "Digite o codigo do produto: ";
    cin >> codigo;
    cin.ignore();

    Produto* produto = consultar_produto(produtos, produtos.size(), codigo);
    if (produto == nullptr) {
        cout << "Produto nao encontrado!" << endl;
        return;
    }

    cout << "\nProduto encontrado:" << endl;
    exibirProduto(*produto);

    char confirmacao;
    cout << "\nTem certeza que deseja excluir este produto? (s/n): ";
    cin >> confirmacao;
    cin.ignore();

    if (confirmacao == 's' || confirmacao == 'S') {
        int total_produtos = produtos.size();
        int resultado = excluir_produto(produtos, total_produtos, codigo);

        if (resultado == 1) {
            cout << "Produto excluido com sucesso!" << endl;
        } else {
            cout << "Erro ao excluir produto!" << endl;
        }
    } else {
        cout << "Exclusao cancelada!" << endl;
    }
}

void listarProdutos() {
    if (produtos.empty()) {
        cout << "\nNenhum produto cadastrado!" << endl;
        return;
    }

    cout << "\n=== LISTA DE PRODUTOS ===" << endl;
    cout << "Total de produtos: " << produtos.size() << endl;
    cout << "=========================" << endl;

    for (const auto& produto : produtos) {
        if (produto.codigo > 0) {
            exibirProduto(produto);
        }
    }
}

void salvarProdutos() {
    ofstream arquivo(ARQUIVO_PRODUTOS);
    if (!arquivo.is_open()) {
        cout << "Erro ao abrir arquivo para escrita!" << endl;
        return;
    }

    arquivo << "Produtos" << endl;
    arquivo << "Codigo    Nome do Produto                    Estoque    Preco (R$)" << endl;
    arquivo << "------    --------------------------------    -------    ----------" << endl;

    for (const auto& produto : produtos) {
        if (produto.codigo > 0) {
            arquivo << setw(8) << left << produto.codigo << "    "
                    << setw(32) << left << produto.nome << "    "
                    << setw(8) << right << produto.quantidadeEstoque << "    "
                    << setw(10) << right << fixed << setprecision(2) << produto.precoVenda << endl;
        }
    }

    arquivo.close();
}

void carregarProdutos() {
    produtos.clear();
    proximoCodigo = 1001;
    
    ifstream arquivo(ARQUIVO_PRODUTOS);
    if (!arquivo.is_open()) {
        cout << "Arquivo de produtos nao encontrado. Sera criado um novo arquivo." << endl;
        return;
    }
    
    string linha;
    
    for (int i = 0; i < 3; i++) {
        getline(arquivo, linha);
    }
    
    while (getline(arquivo, linha)) {
        if (linha.empty() || !isdigit(linha[0])) continue;
        
        Produto produto;
        
        size_t pos = 0;
        while (pos < linha.length() && linha[pos] == ' ') pos++;
        if (pos >= linha.length()) continue;
        
        size_t end = pos;
        while (end < linha.length() && isdigit(linha[end])) end++;
        produto.codigo = stoi(linha.substr(pos, end - pos));
        
        if (produto.codigo <= 0) continue;
        
        pos = end;
        while (pos < linha.length() && linha[pos] == ' ') pos++;
        
        string nome = "";
        while (pos < linha.length()) {
            if (isdigit(linha[pos])) break;
            nome += linha[pos];
            pos++;
        }
        
        while (!nome.empty() && nome.back() == ' ') nome.pop_back();
        produto.nome = nome;
        
        if (produto.nome.empty()) continue;
        
        while (pos < linha.length() && !isdigit(linha[pos])) pos++;
        if (pos >= linha.length()) continue;
        
        end = pos;
        while (end < linha.length() && isdigit(linha[end])) end++;
        produto.quantidadeEstoque = stoi(linha.substr(pos, end - pos));
        
        pos = end;
        while (pos < linha.length() && !isdigit(linha[pos])) pos++;
        if (pos >= linha.length()) continue;
        
        end = pos;
        while (end < linha.length() && (isdigit(linha[end]) || linha[end] == '.')) end++;
        produto.precoVenda = stod(linha.substr(pos, end - pos));
        
        produtos.push_back(produto);
        
        if (produto.codigo >= proximoCodigo) {
            proximoCodigo = produto.codigo + 1;
        }
    }
    
    arquivo.close();
    cout << "Produtos carregados com sucesso! Total: " << produtos.size() << endl;
}

