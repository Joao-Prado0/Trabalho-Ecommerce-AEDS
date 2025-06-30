#include "vendedores.h"
#include <iostream>
#include <fstream>
#include <iomanip>
#include <cstdlib>
#include <ctime>
#include <string>
using namespace std;

Vendedores::Vendedores() {
    numero = 0;
    nome = "";
    salarioTotal = 0.0;
    comissaoAcumulada = 0;
}

void Vendedores::calcularSalarioTotal() {
    salarioTotal = salarioFixo + comissaoAcumulada;
}

void Vendedores::setNumero() {
    static bool seeded = false;
    if (!seeded) {
        srand(time(nullptr));
        seeded = true;
    }

    int novoNumero;
    do {
        novoNumero = rand() % 900 + 100;
    } while (verificarNumero(novoNumero));

    numero = novoNumero;
    cout << "Numero gerado: " << numero << endl;
}

void Vendedores::setNome() {
    cout << "Nome: ";
    cin.ignore();
    getline(cin, nome);
}

void Vendedores::setSalarioFixo() {
    cout << "Salario fixo: R$ ";
    cin >> salarioFixo;
    calcularSalarioTotal();
}

bool Vendedores::verificarNumero(int num) {
    ifstream arquivo("../data/vendedores.txt");
    if (!arquivo) return false;

    string linha;
    while (getline(arquivo, linha)) {
        if (linha.find("Numero: " + to_string(num)) != string::npos) {
            return true;
        }
    }
    return false;
}

void Vendedores::salvarNoArquivo() {
    ofstream arquivo("../data/vendedores.txt", ios::app);
    if (!arquivo) {
        cerr << "Erro ao abrir arquivo!" << endl;
        return;
    }

    arquivo << "Vendedor\n"
            << "Numero: " << numero << "\n"
            << "Nome: " << nome << "\n"
            << fixed << setprecision(2)
            << "Salario fixo: " << salarioFixo << "\n"
            << "Comissao acumulada: " << comissaoAcumulada << "\n"
            << "Salario total (fixo + comissao): " << salarioTotal << "\n"
            << "------------------------------\n";

    cout << "Vendedor cadastrado com sucesso!" << endl;
}

void Vendedores::atualizarArquivo() {
    ifstream entrada("../data/vendedores.txt");
    ofstream temp("../data/temp.txt");

    string linha;
    bool encontrado = false;

    while (getline(entrada, linha)) {
        if (linha == "Vendedor") {
            string bloco[6];
            bloco[0] = linha;
            for (int i = 1; i < 6; ++i) {
                getline(entrada, bloco[i]);
            }

            int num = stoi(bloco[1].substr(8));
            if (num == numero) {
                encontrado = true;
                temp << "Vendedor\n"
                     << "Numero: " << numero << "\n"
                     << "Nome: " << nome << "\n"
                     << fixed << setprecision(2)
                     << "Salario fixo: " << salarioFixo << "\n"
                     << "Comissao acumulada: " << comissaoAcumulada << "\n"
                     << "Salario total (fixo + comissao): " << salarioTotal << "\n";
            } else {
                for (const auto& l : bloco) {
                    temp << l << "\n";
                }
            }
            getline(entrada, linha);
            temp << "------------------------------\n";
        }
    }

    entrada.close();
    temp.close();

    remove("../data/vendedores.txt");
    rename("../data/temp.txt", "../data/vendedores.txt");
}

void Vendedores::adicionarComissao(float valorVenda) {
    float comissao = valorVenda * 0.03f;
    comissaoAcumulada += comissao;
    calcularSalarioTotal();

    cout << "\nComissao de R$ " << comissao << " adicionada!\n";
    cout << "Total acumulado: R$ " << comissaoAcumulada << endl;

    atualizarArquivo();
}

void Vendedores::consultarVendedor(int numConsulta) {
    ifstream arquivo("../data/vendedores.txt");
    if (!arquivo) {
        cerr << "Erro ao abrir arquivo!" << endl;
        return;
    }

    string linha;
    bool encontrado = false;

    while (getline(arquivo, linha)) {
        if (linha == "Vendedor") {
            string bloco[6];
            bloco[0] = linha;
            for (int i = 1; i < 6; ++i) {
                getline(arquivo, bloco[i]);
            }

            int num = stoi(bloco[1].substr(8));
            if (num == numConsulta) {
                encontrado = true;
                cout << "\n=== DADOS DO VENDEDOR ===\n";
                for (const auto& l : bloco) {
                    cout << l << "\n";
                }
                break;
            }
            getline(arquivo, linha);
        }
    }

    if (!encontrado) {
        cout << "Vendedor nao encontrado!" << endl;
    }
}

void Vendedores::alterarVendedor(int numeroAlvo) {
    ifstream entrada("../data/vendedores.txt");
    ofstream temp("../data/temp.txt");

    string linha;
    bool encontrado = false;
    string novoNome;
    float novoSalario;

    while (getline(entrada, linha)) {
        if (linha == "Vendedor") {
            string bloco[6];
            bloco[0] = linha;
            for (int i = 1; i < 6; ++i) {
                getline(entrada, bloco[i]);
            }

            int num = stoi(bloco[1].substr(8));
            if (num == numeroAlvo) {
                encontrado = true;
                cout << "\n=== ALTERAR VENDEDOR ===\n";
                cout << "Nome atual: " << bloco[2].substr(6) << "\n";
                cout << "Novo nome (ou enter para manter): ";
                cin.ignore();
                getline(cin, novoNome);
                if (novoNome.empty()) {
                    novoNome = bloco[2].substr(6);
                }

                cout << "Salario atual: " << bloco[3].substr(13) << "\n";
                cout << "Novo salario (ou 0 para manter): ";
                string input;
                getline(cin, input);
                novoSalario = input.empty() ? stof(bloco[3].substr(13)) : stof(input);

                temp << "Vendedor\n"
                     << "Numero: " << numeroAlvo << "\n"
                     << "Nome: " << novoNome << "\n"
                     << fixed << setprecision(2)
                     << "Salario fixo: " << novoSalario << "\n"
                     << bloco[4] << "\n"
                     << "Salario total (fixo + comissao): "
                     << novoSalario + stof(bloco[4].substr(19)) << "\n";
            } else {
                for (const auto& l : bloco) {
                    temp << l << "\n";
                }
            }
            getline(entrada, linha);
            temp << "------------------------------\n";
        }
    }

    entrada.close();
    temp.close();

    remove("../data/vendedores.txt");
    rename("../data/temp.txt", "../data/vendedores.txt");

    if (encontrado) {
        cout << "Vendedor alterado com sucesso!\n";
    } else {
        cout << "Vendedor nao encontrado!\n";
    }
}

void Vendedores::excluirVendedor(int numeroAlvo) {
    ifstream entrada("../data/vendedores.txt");
    ofstream temp("../data/temp.txt");

    string linha;
    bool encontrado = false;
    char confirmacao;

    while (getline(entrada, linha)) {
        if (linha == "Vendedor") {
            string bloco[6];
            bloco[0] = linha;
            for (int i = 1; i < 6; ++i) {
                getline(entrada, bloco[i]);
            }

            int num = stoi(bloco[1].substr(8));
            if (num == numeroAlvo) {
                encontrado = true;
                cout << "\n=== CONFIRMAR EXCLUSAO ===\n";
                for (const auto& l : bloco) {
                    cout << l << "\n";
                }
                cout << "Confirmar exclusao? (s/n): ";
                cin >> confirmacao;
                if (tolower(confirmacao) != 's') {
                    for (const auto& l : bloco) {
                        temp << l << "\n";
                    }
                    temp << "------------------------------\n";
                }
            } else {
                for (const auto& l : bloco) {
                    temp << l << "\n";
                }
                temp << "------------------------------\n";
            }
        }
    }

    entrada.close();
    temp.close();

    remove("../data/vendedores.txt");
    rename("../data/temp.txt", "../data/vendedores.txt");

    if (encontrado && tolower(confirmacao) == 's') {
        cout << "Vendedor excluido com sucesso!\n";
    } else if (!encontrado) {
        cout << "Vendedor nao encontrado!\n";
    }
}

void Vendedores::listarTodosVendedores() {
    ifstream arquivo("../data/vendedores.txt");
    if (!arquivo.is_open()) {
        cout << "Nenhum vendedor cadastrado ainda!" << endl;
        return;
    }

    cout << "\n=== LISTA COMPLETA DE VENDEDORES ===" << endl;
    cout << left << setw(10) << "CODIGO" << "NOME" << endl;
    cout << "----------------------------------" << endl;

    string linha;
    bool encontrouVendedor = false;

    while (getline(arquivo, linha)) {
        if (linha == "Vendedor") {
            encontrouVendedor = true;

            // Ler número
            getline(arquivo, linha);
            string codigo = linha.substr(8);

            // Ler nome
            getline(arquivo, linha);
            string nome = linha.substr(6);

            cout << left << setw(10) << codigo << nome << endl;

            // Pular as linhas restantes do registro (4 linhas: salário, comissão, total, separador)
            for (int i = 0; i < 4; i++) {
                if (!getline(arquivo, linha)) break;
            }
        }
    }

    arquivo.close();

    if (!encontrouVendedor) {
        cout << "Nenhum vendedor encontrado no arquivo!" << endl;
    }
}