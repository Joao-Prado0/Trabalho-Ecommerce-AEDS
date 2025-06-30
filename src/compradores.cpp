#include "compradores.h"
#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;

void Endereco::exibir() const {
    cout << "  Rua: " << rua << endl;
    cout << "  Bairro: " << bairro << endl;
    cout << "  Cidade: " << cidade << endl;
    cout << "  Estado: " << estado << endl;
    cout << "  CEP: " << cep << endl;
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
    cout << "Nome: " << nome << endl;
    cout << "CPF: " << cpf << endl;
    cout << "Email: " << email << endl;
    endereco.exibir();
}

void Comprador::setNome(string nome) { this->nome = nome; }
void Comprador::setEmail(string email) { this->email = email; }
void Comprador::setEndereco(Endereco endereco) { this->endereco = endereco; }


bool Comprador::validarCPF(const string& cpf) {
    ifstream arq("data/compradores.txt");
    if (!arq.is_open()) {
        cerr << "Erro ao abrir arquivo para leitura!\n";
        return false;
    }

    string linha;
    while (getline(arq, linha)) {
        stringstream ss(linha);
        string nome, linhaCpf;

        getline(ss, nome, ';');      // nome
        getline(ss, linhaCpf, ';');  // cpf

        if (linhaCpf == cpf) {
            arq.close();
            return true;
        }
    }
    arq.close();
    return false;
}


void Comprador::inserirComprador(const Comprador& novo) {
    ofstream arq("data/compradores.txt", ios::app);
    if (!arq.is_open()) {
        cerr << "Erro ao abrir arquivo para escrita!\n";
        return;
    }
    arq << novo.toString() << endl;
    arq.close();
}


void Comprador::consultarCompradorInterface() {
    string cpf;
    cin.ignore();
    cout << "Digite o CPF do comprador: ";
    getline(cin, cpf);

    ifstream arq("data/compradores.txt");
    if (!arq.is_open()) {
        cerr << "Erro ao abrir arquivo para leitura!\n";
        return;
    }

    string linha;
    bool encontrado = false;
    while (getline(arq, linha)) {
        stringstream ss(linha);
        string nome, linhaCpf, email, rua, bairro, cidade, estado, cep;

        getline(ss, nome, ';');
        getline(ss, linhaCpf, ';');
        getline(ss, email, ';');
        getline(ss, rua, ';');
        getline(ss, bairro, ';');
        getline(ss, cidade, ';');
        getline(ss, estado, ';');
        getline(ss, cep, ';');

        if (linhaCpf == cpf) {
            Comprador c(nome, linhaCpf, email, Endereco{rua, bairro, cidade, estado, cep});
            c.exibir();
            encontrado = true;
            break;
        }
    }
    arq.close();

    if (!encontrado)
        cout << "Comprador não encontrado!\n";
}


bool Comprador::alterarComprador(const string& cpf, const Comprador& novo) {
    ifstream arq("data/compradores.txt");
    ofstream temp("data/temp.txt");

    if (!arq.is_open() || !temp.is_open()) {
        cerr << "Erro ao abrir arquivo para alteração!\n";
        return false;
    }

    string linha;
    bool encontrado = false;

    while (getline(arq, linha)) {
        stringstream ss(linha);
        string nome, linhaCpf, email, rua, bairro, cidade, estado, cep;

        getline(ss, nome, ';');
        getline(ss, linhaCpf, ';');
        getline(ss, email, ';');
        getline(ss, rua, ';');
        getline(ss, bairro, ';');
        getline(ss, cidade, ';');
        getline(ss, estado, ';');
        getline(ss, cep, ';');

        if (linhaCpf == cpf) {
            temp << novo.toString() << endl;
            encontrado = true;
        } else {
            temp << linha << endl;
        }
    }

    arq.close();
    temp.close();

    if (encontrado) {
        remove("data/compradores.txt");
        rename("data/temp.txt", "data/compradores.txt");
    } else {
        remove("data/temp.txt");
    }
    return encontrado;
}

// Excluir: copiar todas linhas menos a do CPF a excluir
bool Comprador::excluirComprador(const string& cpf) {
    ifstream arq("data/compradores.txt");
    ofstream temp("data/temp.txt");

    if (!arq.is_open() || !temp.is_open()) {
        cerr << "Erro ao abrir arquivo para exclusão!\n";
        return false;
    }

    string linha;
    bool encontrado = false;

    while (getline(arq, linha)) {
        stringstream ss(linha);
        string nome, linhaCpf;

        getline(ss, nome, ';');
        getline(ss, linhaCpf, ';');

        if (linhaCpf != cpf) {
            temp << linha << "\n";
        } else {
            encontrado = true;
        }
    }

    arq.close();
    temp.close();

    if (encontrado) {
        remove("data/compradores.txt");
        rename("data/temp.txt", "data/compradores.txt");
    } else {
        remove("data/temp.txt");
    }
    return encontrado;
}

// Interface para inserir comprador com dados do usuário
void Comprador::inserirCompradorInterface() {
    string nome, cpf, email;
    Endereco end;

    cin.ignore();
    cout << "CPF: ";
    getline(cin, cpf);

    if (validarCPF(cpf)) {
        cout << "CPF já cadastrado!\n";
        return;
    }

    cout << "Nome: ";
    getline(cin, nome);
    cout << "Email: ";
    getline(cin, email);
    cout << "Rua: ";
    getline(cin, end.rua);
    cout << "Bairro: ";
    getline(cin, end.bairro);
    cout << "Cidade: ";
    getline(cin, end.cidade);
    cout << "Estado: ";
    getline(cin, end.estado);
    cout << "CEP: ";
    getline(cin, end.cep);

    Comprador novo(nome, cpf, email, end);
    inserirComprador(novo);
    cout << "Comprador cadastrado com sucesso!\n";
}


void Comprador::alterarCompradorInterface() {
    string cpf;
    cin.ignore();
    cout << "Digite o CPF do comprador a alterar: ";
    getline(cin, cpf);

    if (!validarCPF(cpf)) {
        cout << "CPF não encontrado!\n";
        return;
    }

    string nome, email;
    Endereco end;

    cout << "Novo nome: ";
    getline(cin, nome);
    cout << "Novo email: ";
    getline(cin, email);
    cout << "Nova rua: ";
    getline(cin, end.rua);
    cout << "Novo bairro: ";
    getline(cin, end.bairro);
    cout << "Nova cidade: ";
    getline(cin, end.cidade);
    cout << "Novo estado: ";
    getline(cin, end.estado);
    cout << "Novo CEP: ";
    getline(cin, end.cep);

    Comprador atualizado(nome, cpf, email, end);
    if (alterarComprador(cpf, atualizado))
        cout << "Comprador alterado com sucesso!\n";
    else
        cout << "Erro ao alterar comprador.\n";
}


void Comprador::excluirCompradorInterface() {
    string cpf;
    cin.ignore();
    cout << "Digite o CPF do comprador a excluir: ";
    getline(cin, cpf);

    if (excluirComprador(cpf))
        cout << "Comprador excluído com sucesso!\n";
    else
        cout << "CPF não encontrado!\n";
}

