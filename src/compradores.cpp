#include "compradores.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

using namespace std;


void Endereco::exibir() const {
    cout << "Rua: " << rua << ", Bairro: " << bairro << ", Cidade: " << cidade
         << ", Estado: " << estado << ", CEP: " << cep << endl;
}


Comprador::Comprador() {}

Comprador::Comprador(string nome, string cpf, string email, Endereco endereco)
    : nome(nome), cpf(cpf), email(email), endereco(endereco) {}

string Comprador::getCpf() const {
    return cpf;
}

string Comprador::toString() const {
    return nome + ";" + cpf + ";" + email + ";" + endereco.toString();
}

void Comprador::exibir() const {
    cout << "Nome: " << nome << "\nCPF: " << cpf << "\nEmail: " << email << endl;
    endereco.exibir();
}



bool Comprador::validarCPF(const string& cpf) {
    ifstream arquivo("../data/compradores.txt");
    if (!arquivo.is_open()) {
        cout << "Erro ao abrir arquivo para leitura!" << endl;
        return false;
    }

    string linha;
    while (getline(arquivo, linha)) {
        stringstream ss(linha);
        string nomeArq, cpfArq;
        getline(ss, nomeArq, ';');
        getline(ss, cpfArq, ';');

        if (cpfArq == cpf) {
            return true;
        }
    }

    return false;
}

void Comprador::inserirComprador(const Comprador& novo) {
    ofstream arquivo("../data/compradores.txt", ios::app);
    if (!arquivo.is_open()) {
        cout << "Erro ao abrir arquivo para escrita!" << endl;
        return;
    }

    arquivo << novo.toString() << endl;
    arquivo.close();
}

bool Comprador::alterarComprador(const string& cpf, const Comprador& novo) {
    ifstream arquivoLeitura("../data/compradores.txt");
    if (!arquivoLeitura.is_open()) return false;

    string linha;
    string resultadoFinal = "";
    bool encontrado = false;

    while (getline(arquivoLeitura, linha)) {
        stringstream ss(linha);
        string nomeArq, cpfArq;
        getline(ss, nomeArq, ';');
        getline(ss, cpfArq, ';');

        if (cpfArq == cpf) {
            resultadoFinal += novo.toString() + "\n";
            encontrado = true;
        } else {
            resultadoFinal += linha + "\n";
        }
    }

    arquivoLeitura.close();

    if (encontrado) {
        ofstream arquivoEscrita("../data/compradores.txt", ios::trunc);
        if (!arquivoEscrita.is_open()) return false;

        arquivoEscrita << resultadoFinal;
        arquivoEscrita.close();
    }

    return encontrado;
}

bool Comprador::excluirComprador(const string& cpf) {
    ifstream arquivoLeitura("../data/compradores.txt");
    if (!arquivoLeitura.is_open()) return false;

    string linha;
    string resultadoFinal = "";
    bool encontrado = false;

    while (getline(arquivoLeitura, linha)) {
        stringstream ss(linha);
        string nomeArq, cpfArq;
        getline(ss, nomeArq, ';');
        getline(ss, cpfArq, ';');

        if (cpfArq == cpf) {
            encontrado = true;
            continue;
        }
        resultadoFinal += linha + "\n";
    }

    arquivoLeitura.close();

    if (encontrado) {
        ofstream arquivoEscrita("../data/compradores.txt", ios::trunc);
        if (!arquivoEscrita.is_open()) return false;

        arquivoEscrita << resultadoFinal;
        arquivoEscrita.close();
    }

    return encontrado;
}

// ====== Interfaces para main.cpp ======

void Comprador::inserirCompradorInterface() {
    string nome, cpf, email;
    Endereco endereco;

    cout << "Digite o nome: ";
    getline(cin, nome);

    cout << "Digite o CPF: ";
    getline(cin, cpf);

    if (validarCPF(cpf)) {
        cout << "CPF ja cadastrado!" << endl;
        return;
    }

    cout << "Digite o email: ";
    getline(cin, email);

    cout << "Rua: ";
    getline(cin, endereco.rua);
    cout << "Bairro: ";
    getline(cin, endereco.bairro);
    cout << "Cidade: ";
    getline(cin, endereco.cidade);
    cout << "Estado: ";
    getline(cin, endereco.estado);
    cout << "CEP: ";
    getline(cin, endereco.cep);

    Comprador novo(nome, cpf, email, endereco);
    inserirComprador(novo);
    cout << "\nComprador cadastrado com sucesso!" << endl;
}

void Comprador::consultarCompradorInterface() {
    string cpf;
    cout << "Digite o CPF do comprador: ";
    getline(cin, cpf);

    ifstream arquivo("../data/compradores.txt");
    if (!arquivo.is_open()) {
        cout << "Erro ao abrir arquivo para leitura!" << endl;
        return;
    }

    string linha;
    bool encontrado = false;

    while (getline(arquivo, linha)) {
        stringstream ss(linha);
        string nome, cpfArq, email, rua, bairro, cidade, estado, cep;

        getline(ss, nome, ';');
        getline(ss, cpfArq, ';');
        getline(ss, email, ';');
        getline(ss, rua, ';');
        getline(ss, bairro, ';');
        getline(ss, cidade, ';');
        getline(ss, estado, ';');
        getline(ss, cep, ';');

        if (cpfArq == cpf) {
            Endereco end{rua, bairro, cidade, estado, cep};
            Comprador encontradoComprador(nome, cpfArq, email, end);
            encontradoComprador.exibir();
            encontrado = true;
            break;
        }
    }

    if (!encontrado) {
        cout << "Comprador nao encontrado!" << endl;
    }
}

void Comprador::alterarCompradorInterface() {
    string cpf;
    cout << "Digite o CPF do comprador a ser alterado: ";
    getline(cin, cpf);

    if (!validarCPF(cpf)) {
        cout << "CPF nao encontrado!" << endl;
        return;
    }

    string novoNome, novoEmail;
    Endereco novoEndereco;

    cout << "Digite o novo nome: ";
    getline(cin, novoNome);

    cout << "Digite o novo email: ";
    getline(cin, novoEmail);

    cout << "Nova rua: ";
    getline(cin, novoEndereco.rua);
    cout << "Novo bairro: ";
    getline(cin, novoEndereco.bairro);
    cout << "Nova cidade: ";
    getline(cin, novoEndereco.cidade);
    cout << "Novo estado: ";
    getline(cin, novoEndereco.estado);
    cout << "Novo CEP: ";
    getline(cin, novoEndereco.cep);

    Comprador novo(novoNome, cpf, novoEmail, novoEndereco);

    if (alterarComprador(cpf, novo)) {
        cout << "Dados alterados com sucesso!" << endl;
    } else {
        cout << "Erro ao alterar dados!" << endl;
    }
}

void Comprador::excluirCompradorInterface() {
    string cpf;
    cout << "Digite o CPF do comprador a ser excluido: ";
    getline(cin, cpf);

    if (!validarCPF(cpf)) {
        cout << "CPF nao encontrado!" << endl;
        return;
    }

    char confirmacao;
    cout << "Tem certeza que deseja excluir esse comprador? (s/n): ";
    cin >> confirmacao;
    cin.ignore();

    if (confirmacao == 's' || confirmacao == 'S') {
        if (excluirComprador(cpf)) {
            cout << "Comprador excluido com sucesso!" << endl;
        } else {
            cout << "Erro ao excluir comprador!" << endl;
        }
    } else {
        cout << "Operacao cancelada." << endl;
    }
}


