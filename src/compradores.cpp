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

string Comprador::toString() const {
    return nome + ";" + cpf + ";" + email + ";" + endereco.toString();
}

// NOVO: para salvar formatado
string Comprador::toStringFormatado() const {
    stringstream ss;
    ss << "Comprador:\n";
    ss << "Nome: " << nome << "\n";
    ss << "CPF: " << cpf << "\n";
    ss << "Email: " << email << "\n";
    ss << "Rua: " << endereco.rua << "\n";
    ss << "Bairro: " << endereco.bairro << "\n";
    ss << "Cidade: " << endereco.cidade << "\n";
    ss << "Estado: " << endereco.estado << "\n";
    ss << "CEP: " << endereco.cep << "\n";
    ss << "---\n";
    return ss.str();
}

Comprador::Comprador() {}

Comprador::Comprador(string nome, string cpf, string email, Endereco endereco)
    : nome(nome), cpf(cpf), email(email), endereco(endereco) {}

string Comprador::getCpf() const {
    return cpf;
}

void Comprador::exibir() const {
    cout << "Nome: " << nome << "\nCPF: " << cpf << "\nEmail: " << email << endl;
    endereco.exibir();
}

bool Comprador::validarCPF(const string& cpfBusca) {
    ifstream arquivo("../data/compradores.txt");
    if (!arquivo.is_open()) {
        cout << "Erro ao abrir arquivo para leitura!" << endl;
        return false;
    }

    string linha, cpf;
    while (getline(arquivo, linha)) {
        if (linha.find("CPF: ") == 0) {
            cpf = linha.substr(5);
            if (cpf == cpfBusca) return true;
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
    arquivo << novo.toStringFormatado();
    arquivo.close();
}

bool Comprador::alterarComprador(const string& cpfBusca, const Comprador& novo) {
    ifstream arquivoLeitura("../data/compradores.txt");
    if (!arquivoLeitura.is_open()) return false;

    string linha, bloco, cpf;
    string resultadoFinal = "";
    bool encontrado = false;

    while (getline(arquivoLeitura, linha)) {
        if (linha == "Comprador:") {
            bloco = linha + "\n";
            cpf = "";
        } else if (linha.find("CPF: ") == 0) {
            cpf = linha.substr(5);
            bloco += linha + "\n";
        } else if (linha == "---") {
            bloco += linha + "\n";
            if (cpf == cpfBusca) {
                resultadoFinal += novo.toStringFormatado();
                encontrado = true;
            } else {
                resultadoFinal += bloco;
            }
            bloco = "";
        } else {
            bloco += linha + "\n";
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

bool Comprador::excluirComprador(const string& cpfBusca) {
    ifstream arquivoLeitura("../data/compradores.txt");
    if (!arquivoLeitura.is_open()) return false;

    string linha, bloco, cpf;
    string resultadoFinal = "";
    bool encontrado = false;

    while (getline(arquivoLeitura, linha)) {
        if (linha == "Comprador:") {
            bloco = linha + "\n";
            cpf = "";
        } else if (linha.find("CPF: ") == 0) {
            cpf = linha.substr(5);
            bloco += linha + "\n";
        } else if (linha == "---") {
            bloco += linha + "\n";
            if (cpf == cpfBusca) {
                encontrado = true;
            } else {
                resultadoFinal += bloco;
            }
            bloco = "";
        } else {
            bloco += linha + "\n";
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
    string cpfBusca;
    cout << "Digite o CPF do comprador: ";
    getline(cin, cpfBusca);

    ifstream arquivo("../data/compradores.txt");
    if (!arquivo.is_open()) {
        cout << "Erro ao abrir arquivo para leitura!" << endl;
        return;
    }

    string linha;
    string nome, cpf, email, rua, bairro, cidade, estado, cep;
    bool encontrado = false;

    while (getline(arquivo, linha)) {
        if (linha.find("Comprador:") != string::npos) {
            nome = cpf = email = rua = bairro = cidade = estado = cep = "";
        } else if (linha.find("Nome: ") == 0) {
            nome = linha.substr(6);
        } else if (linha.find("CPF: ") == 0) {
            cpf = linha.substr(5);
        } else if (linha.find("Email: ") == 0) {
            email = linha.substr(7);
        } else if (linha.find("Rua: ") == 0) {
            rua = linha.substr(5);
        } else if (linha.find("Bairro: ") == 0) {
            bairro = linha.substr(8);
        } else if (linha.find("Cidade: ") == 0) {
            cidade = linha.substr(8);
        } else if (linha.find("Estado: ") == 0) {
            estado = linha.substr(8);
        } else if (linha.find("CEP: ") == 0) {
            cep = linha.substr(5);
        } else if (linha.find("---") != string::npos) {
            if (cpf == cpfBusca) {
                Endereco endereco{rua, bairro, cidade, estado, cep};
                Comprador compradorEncontrado(nome, cpf, email, endereco);
                compradorEncontrado.exibir();
                encontrado = true;
                break;
            }
        }
    }

    if (!encontrado) {
        cout << "Comprador nao encontrado!" << endl;
    }

    arquivo.close();
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

Comprador Comprador::buscarCompradorPorCPF(const string& cpfBusca) {
    ifstream arquivo("../data/compradores.txt");
    if (!arquivo.is_open()) {
        cout << "Erro ao abrir arquivo para leitura!" << endl;
        return Comprador();
    }

    string linha;
    string nome, cpf, email, rua, bairro, cidade, estado, cep;

    while (getline(arquivo, linha)) {
        if (linha.find("Comprador:") == 0) {
            nome = cpf = email = rua = bairro = cidade = estado = cep = "";
        } else if (linha.find("Nome: ")   == 0) nome   = linha.substr(6);
        else if (linha.find("CPF: ")      == 0) cpf    = linha.substr(5);
        else if (linha.find("Email: ")    == 0) email  = linha.substr(7);
        else if (linha.find("Rua: ")      == 0) rua    = linha.substr(5);
        else if (linha.find("Bairro: ")   == 0) bairro = linha.substr(8);
        else if (linha.find("Cidade: ")   == 0) cidade = linha.substr(8);
        else if (linha.find("Estado: ")   == 0) estado = linha.substr(8);
        else if (linha.find("CEP: ")      == 0) cep    = linha.substr(5);
        else if (linha == "---") {
            if (cpf == cpfBusca) {
                Endereco e{rua, bairro, cidade, estado, cep};
                return Comprador(nome, cpf, email, e);
            }
        }
    }
    return Comprador();
}


