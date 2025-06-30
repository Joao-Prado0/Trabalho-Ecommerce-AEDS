#ifndef VENDEDORES_H
#define VENDEDORES_H

#include <iostream>
#include <fstream>
#include <iomanip>
#include <cstdlib>
#include <ctime>
#include <string>
using namespace std;

class Vendedores {
private:
    int numero;
    string nome;
    float salario;
    int comissao;

public:
    Vendedores() {
        numero = 0;
        nome = "";
        salario = 0.0;
        comissao = 0;
    }

    void setNumero() {
        static bool inicializado = false;
        if (!inicializado) {
            srand(time(nullptr));
            inicializado = true;
        }

        int numGerado;
        do {
            numGerado = (rand() % 900) + 100;
        } while (verificarNumero(numGerado));

        numero = numGerado;
        cout << "Número do vendedor gerado: " << numero << endl;
    }

    void setNome() {
        cout << "Nome do vendedor: ";
        cin.ignore();
        getline(cin, nome);
    }

    void setSalario() {
        cout << "Salário fixo: ";
        cin >> salario;
    }

    void setComissao() {
        comissao = 0;
    }

    bool verificarNumero(int num) {
        ifstream arquivo("../data/vendedores.txt");
        if (!arquivo.is_open()) return false;

        string linha;
        while (getline(arquivo, linha)) {
            if (linha.find("Número: " + to_string(num)) != string::npos)
                return true;
        }
        return false;
    }

    void salvarNoArquivo() {
        ofstream arquivo("../data/vendedores.txt", ios::app);
        if (!arquivo.is_open()) {
            cout << "Erro ao abrir o arquivo para salvar vendedor." << endl;
            return;
        }

        arquivo << "Vendedor" << endl;
        arquivo << "Número: " << numero << endl;
        arquivo << "Nome: " << nome << endl;
        arquivo << fixed << setprecision(2);
        arquivo << "Salário: " << salario << endl;
        arquivo << "Comissão: " << comissao << endl;
        arquivo << "------------------------------" << endl;

        cout << "Vendedor salvo com sucesso!" << endl;
    }

    void adicionarComissao(float valorVenda) {
        float valorComissao = valorVenda * 0.03;
        salario += valorComissao;
        cout << "Comissão de R$ " << valorComissao << " adicionada ao salário." << endl;
        cout << "Novo salário: R$ " << salario << endl;
        atualizarSalarioNoArquivo();
    }

    void atualizarSalarioNoArquivo() {
        ifstream arquivoIn("../data/vendedores.txt");
        ofstream arquivoOut("../data/temp.txt");

        if (!arquivoIn.is_open() || !arquivoOut.is_open()) {
            cout << "Erro ao abrir os arquivos para atualização." << endl;
            return;
        }

        string linha;
        bool achou = false;

        while (getline(arquivoIn, linha)) {
            if (linha == "Vendedor") {
                arquivoOut << linha << endl;
                getline(arquivoIn, linha);
                int num = stoi(linha.substr(8));
                arquivoOut << linha << endl;

                getline(arquivoIn, linha);
                arquivoOut << linha << endl;

                getline(arquivoIn, linha);
                if (num == numero) {
                    achou = true;
                    arquivoOut << "Salário: " << fixed << setprecision(2) << salario << endl;
                } else {
                    arquivoOut << linha << endl;
                }

                getline(arquivoIn, linha);
                arquivoOut << linha << endl;

                getline(arquivoIn, linha);
                arquivoOut << linha << endl;
            } else {
                arquivoOut << linha << endl;
            }
        }

        arquivoIn.close();
        arquivoOut.close();

        remove("../data/vendedores.txt");
        rename("../data/temp.txt", "../data/vendedores.txt");

        if (achou)
            cout << "Salário atualizado com sucesso no arquivo!" << endl;
        else
            cout << "Vendedor não encontrado para atualização." << endl;
    }

    void consultarVendedor(int numConsulta) {
        ifstream arquivo("../data/vendedores.txt");
        if (!arquivo.is_open()) {
            cout << "Erro ao abrir o arquivo para leitura." << endl;
            return;
        }

        string linha;
        bool achou = false;

        while (getline(arquivo, linha)) {
            if (linha == "Vendedor") {
                string bloco[5];
                bloco[0] = linha;
                for (int i = 1; i < 5; i++) {
                    getline(arquivo, bloco[i]);
                }

                int numeroArquivo = stoi(bloco[1].substr(8));
                if (numeroArquivo == numConsulta) {
                    achou = true;
                    cout << "\n--- Vendedor Encontrado ---" << endl;
                    for (int i = 0; i < 5; i++) {
                        cout << bloco[i] << endl;
                    }
                    break;
                }
            }
        }

        if (!achou) {
            cout << "\nNenhum vendedor com número " << numConsulta << " foi encontrado." << endl;
        }

        arquivo.close();
    }

    void alterarVendedor(int numeroAlvo) {
        ifstream arquivoIn("../data/vendedores.txt");
        ofstream arquivoOut("../data/temp.txt");

        if (!arquivoIn.is_open() || !arquivoOut.is_open()) {
            cout << "Erro ao abrir os arquivos para alteração." << endl;
            return;
        }

        string linha;
        bool achou = false;

        while (getline(arquivoIn, linha)) {
            if (linha == "Vendedor") {
                string bloco[5];
                bloco[0] = linha;
                for (int i = 1; i < 5; i++) {
                    getline(arquivoIn, bloco[i]);
                }

                int numeroArquivo = stoi(bloco[1].substr(8));
                string nomeAntigo = bloco[2].substr(6);
                float salarioAntigo = stof(bloco[3].substr(9));

                if (numeroArquivo == numeroAlvo) {
                    achou = true;

                    cout << "\n--- Vendedor encontrado ---" << endl;
                    cout << "Nome atual: " << nomeAntigo << endl;
                    cout << "Salário atual: R$ " << salarioAntigo << endl;

                    string novoNome = nomeAntigo;
                    float novoSalario = salarioAntigo;

                    char resp;
                    cout << "Deseja alterar o nome? (s/n): ";
                    cin >> resp;
                    cin.ignore();
                    if (resp == 's' || resp == 'S') {
                        cout << "Novo nome: ";
                        getline(cin, novoNome);
                    }

                    cout << "Deseja alterar o salário? (s/n): ";
                    cin >> resp;
                    if (resp == 's' || resp == 'S') {
                        cout << "Novo salário: ";
                        cin >> novoSalario;
                    }

                    arquivoOut << "Vendedor" << endl;
                    arquivoOut << "Número: " << numeroArquivo << endl;
                    arquivoOut << "Nome: " << novoNome << endl;
                    arquivoOut << fixed << setprecision(2);
                    arquivoOut << "Salário: " << novoSalario << endl;
                    arquivoOut << bloco[4] << endl;
                    arquivoOut << "------------------------------" << endl;
                } else {
                    for (int i = 0; i < 5; i++) {
                        arquivoOut << bloco[i] << endl;
                    }
                    arquivoOut << "------------------------------" << endl;
                }
            } else {
                arquivoOut << linha << endl;
            }
        }

        arquivoIn.close();
        arquivoOut.close();

        remove("../data/vendedores.txt");
        rename("../data/temp.txt", "../data/vendedores.txt");

        if (achou)
            cout << "\n✅ Vendedor alterado com sucesso!" << endl;
        else
            cout << "\n❌ Vendedor com número " << numeroAlvo << " não foi encontrado." << endl;
    }

    void excluirVendedor(int numeroAlvo) {
        ifstream arquivoIn("../data/vendedores.txt");
        ofstream arquivoOut("../data/temp.txt");

        if (!arquivoIn.is_open() || !arquivoOut.is_open()) {
            cout << "Erro ao abrir os arquivos para exclusão." << endl;
            return;
        }

        string linha;
        bool achou = false;

        while (getline(arquivoIn, linha)) {
            if (linha == "Vendedor") {
                string bloco[6];
                bloco[0] = linha;
                for (int i = 1; i < 6; i++) {
                    getline(arquivoIn, bloco[i]);
                }

                int numeroArquivo = stoi(bloco[1].substr(8));

                if (numeroArquivo == numeroAlvo) {
                    achou = true;
                    cout << "\n--- Vendedor encontrado ---" << endl;
                    cout << bloco[1] << endl;
                    cout << bloco[2] << endl;
                    cout << bloco[3] << endl;
                    cout << bloco[4] << endl;

                    char resp;
                    cout << "Tem certeza que deseja excluir este vendedor? (s/n): ";
                    cin >> resp;

                    if (resp == 's' || resp == 'S') {
                        cout << "✅ Vendedor excluído com sucesso!" << endl;
                        continue;
                    } else {
                        cout << "❎ Exclusão cancelada. Vendedor mantido." << endl;
                    }
                }

                for (int i = 0; i < 6; i++) {
                    arquivoOut << bloco[i] << endl;
                }
            } else {
                arquivoOut << linha << endl;
            }
        }

        arquivoIn.close();
        arquivoOut.close();

        remove("../data/vendedores.txt");
        rename("../data/temp.txt", "../data/vendedores.txt");

        if (!achou) {
            cout << "\n❌ Vendedor com número " << numeroAlvo << " não foi encontrado." << endl;
        }
    }
};

#endif