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
    std::cout << "Número gerado: " << numero << std::endl;
}

void Vendedores::setNome() {
    std::cout << "Nome: ";
    std::cin.ignore();
    getline(std::cin, nome);
}

void Vendedores::setSalarioFixo() {
    std::cout << "Salário fixo: R$ ";
    std::cin >> salarioFixo;
    calcularSalarioTotal();
}

bool Vendedores::verificarNumero(int num) {
    std::ifstream arquivo("../data/vendedores.txt");
    if (!arquivo) return false;

    std::string linha;
    while (getline(arquivo, linha)) {
        if (linha.find("Número: " + std::to_string(num)) != std::string::npos) {
            return true;
        }
    }
    return false;
}

void Vendedores::salvarNoArquivo() {
    std::ofstream arquivo("../data/vendedores.txt", std::ios::app);
    if (!arquivo) {
        std::cerr << "Erro ao abrir arquivo!" << std::endl;
        return;
    }

    arquivo << "Vendedor\n"
            << "Número: " << numero << "\n"
            << "Nome: " << nome << "\n"
            << std::fixed << std::setprecision(2)
            << "Salário fixo: " << salarioFixo << "\n"
            << "Comissão acumulada: " << comissaoAcumulada << "\n"
            << "Salário total (fixo + comissão): " << salarioTotal << "\n"
            << "------------------------------\n";

    std::cout << "Vendedor cadastrado com sucesso!" << std::endl;
}

void Vendedores::atualizarArquivo() {
    std::ifstream entrada("../data/vendedores.txt");
    std::ofstream temp("../data/temp.txt");

    std::string linha;
    bool encontrado = false;

    while (getline(entrada, linha)) {
        if (linha == "Vendedor") {
            std::string bloco[6];
            bloco[0] = linha;
            for (int i = 1; i < 6; ++i) {
                getline(entrada, bloco[i]);
            }

            int num = std::stoi(bloco[1].substr(8));
            if (num == numero) {
                encontrado = true;
                temp << "Vendedor\n"
                     << "Número: " << numero << "\n"
                     << "Nome: " << nome << "\n"
                     << std::fixed << std::setprecision(2)
                     << "Salário fixo: " << salarioFixo << "\n"
                     << "Comissão acumulada: " << comissaoAcumulada << "\n"
                     << "Salário total (fixo + comissão): " << salarioTotal << "\n";
            } else {
                for (const auto& l : bloco) {
                    temp << l << "\n";
                }
            }
            getline(entrada, linha); // Pular a linha de separação
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

    std::cout << "\nComissão de R$ " << comissao << " adicionada!\n";
    std::cout << "Total acumulado: R$ " << comissaoAcumulada << std::endl;

    atualizarArquivo();
}

void Vendedores::consultarVendedor(int numConsulta) {
    std::ifstream arquivo("../data/vendedores.txt");
    if (!arquivo) {
        std::cerr << "Erro ao abrir arquivo!" << std::endl;
        return;
    }

    std::string linha;
    bool encontrado = false;

    while (getline(arquivo, linha)) {
        if (linha == "Vendedor") {
            std::string bloco[6];
            bloco[0] = linha;
            for (int i = 1; i < 6; ++i) {
                getline(arquivo, bloco[i]);
            }

            int num = std::stoi(bloco[1].substr(8));
            if (num == numConsulta) {
                encontrado = true;
                std::cout << "\n=== DADOS DO VENDEDOR ===\n";
                for (const auto& l : bloco) {
                    std::cout << l << "\n";
                }
                break;
            }
            getline(arquivo, linha); // Pular separador
        }
    }

    if (!encontrado) {
        std::cout << "Vendedor não encontrado!" << std::endl;
    }
}

void Vendedores::alterarVendedor(int numeroAlvo) {
    std::ifstream entrada("../data/vendedores.txt");
    std::ofstream temp("../data/temp.txt");

    std::string linha;
    bool encontrado = false;
    std::string novoNome;
    float novoSalario;

    while (getline(entrada, linha)) {
        if (linha == "Vendedor") {
            std::string bloco[6];
            bloco[0] = linha;
            for (int i = 1; i < 6; ++i) {
                getline(entrada, bloco[i]);
            }

            int num = std::stoi(bloco[1].substr(8));
            if (num == numeroAlvo) {
                encontrado = true;
                std::cout << "\n=== ALTERAR VENDEDOR ===\n";
                std::cout << "Nome atual: " << bloco[2].substr(6) << "\n";
                std::cout << "Novo nome (ou enter para manter): ";
                std::cin.ignore();
                getline(std::cin, novoNome);
                if (novoNome.empty()) {
                    novoNome = bloco[2].substr(6);
                }

                std::cout << "Salário atual: " << bloco[3].substr(13) << "\n";
                std::cout << "Novo salário (ou 0 para manter): ";
                std::string input;
                getline(std::cin, input);
                novoSalario = input.empty() ? std::stof(bloco[3].substr(13)) : std::stof(input);

                temp << "Vendedor\n"
                     << "Número: " << numeroAlvo << "\n"
                     << "Nome: " << novoNome << "\n"
                     << std::fixed << std::setprecision(2)
                     << "Salário fixo: " << novoSalario << "\n"
                     << bloco[4] << "\n"  // Mantém comissão
                     << "Salário total (fixo + comissão): "
                     << novoSalario + std::stof(bloco[4].substr(19)) << "\n";
            } else {
                for (const auto& l : bloco) {
                    temp << l << "\n";
                }
            }
            getline(entrada, linha); // Pular separador
            temp << "------------------------------\n";
        }
    }

    entrada.close();
    temp.close();

    remove("../data/vendedores.txt");
    rename("../data/temp.txt", "../data/vendedores.txt");

    if (encontrado) {
        std::cout << "Vendedor alterado com sucesso!\n";
    } else {
        std::cout << "Vendedor não encontrado!\n";
    }
}

void Vendedores::excluirVendedor(int numeroAlvo) {
    std::ifstream entrada("../data/vendedores.txt");
    std::ofstream temp("../data/temp.txt");

    std::string linha;
    bool encontrado = false;
    char confirmacao;

    while (getline(entrada, linha)) {
        if (linha == "Vendedor") {
            std::string bloco[6];
            bloco[0] = linha;
            for (int i = 1; i < 6; ++i) {
                getline(entrada, bloco[i]);
            }

            int num = std::stoi(bloco[1].substr(8));
            if (num == numeroAlvo) {
                encontrado = true;
                std::cout << "\n=== CONFIRMAR EXCLUSÃO ===\n";
                for (const auto& l : bloco) {
                    std::cout << l << "\n";
                }
                std::cout << "Confirmar exclusão? (s/n): ";
                std::cin >> confirmacao;
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
        std::cout << "Vendedor excluído com sucesso!\n";
    } else if (!encontrado) {
        std::cout << "Vendedor não encontrado!\n";
    }
}
