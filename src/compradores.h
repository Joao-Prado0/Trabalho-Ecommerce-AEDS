#ifndef COMPRADORES_H
#define COMPRADORES_H

#include <string>
using namespace std;

struct Endereco {
    string rua;
    string bairro;
    string cidade;
    string estado;
    string cep;

    void exibir() const;

    string toString() const {
        return rua + ";" + bairro + ";" + cidade + ";" + estado + ";" + cep;
    }
};

class Comprador {
private:
    string nome;
    string cpf;
    string email;
    Endereco endereco;

public:
    Comprador();
    Comprador(string nome, string cpf, string email, Endereco endereco);

    string getCpf() const;
    string toString() const;
    string toStringFormatado() const;
    void exibir() const;

    static bool validarCPF(const string& cpf);
    static void inserirComprador(const Comprador& novo);
    static bool alterarComprador(const string& cpf, const Comprador& novo);
    static bool excluirComprador(const string& cpf);


    static void inserirCompradorInterface();
    static void consultarCompradorInterface();
    static void alterarCompradorInterface();
    static void excluirCompradorInterface();
};

#endif



