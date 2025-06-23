//
// Created by nogue on 22/06/2025.
//

#ifndef COMPRADORES_H
#define COMPRADORES_H
#include <string>


using namespace std;
class compradores {
private:
    int id;
    string nome;
    string email;
    string cpf;

public:

    compradores(int id, const string& nome, const string& email, const string& cpf)
        : id(id), nome(nome), email(email), cpf(cpf) {}


    int getId() const { return id; }
    string getNome() const { return nome; }
    string getEmail() const { return email; }
    string getCpf() const { return cpf; }


    void setNome(const string& novoNome) { nome = novoNome; }
    void setEmail(const string& novoEmail) { email = novoEmail; }
    void setCpf(const string& novoCpf) { cpf = novoCpf; }

    void exibir() const {
        cout << "ID: " << id << endl;
        cout << "Nome: " << nome << endl;
        cout << "Email: " << email << endl;
        cout << "CPF: " << cpf << endl;
    }

};



#endif //COMPRADORES_H
