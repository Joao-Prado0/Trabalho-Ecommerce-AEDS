// ======= vendedores.h =======
#ifndef VENDEDORES_H
#define VENDEDORES_H

#include <string>

class Vendedores {
private:
    int numero;
    std::string nome;
    float salario;
    int comissao;

public:
    Vendedores();
    Vendedores(int num, std::string n, float s, int c);

    void setNumero();
    void setNome();
    void setSalario();
    void setComissao();

    bool verificarNumero(int num);
    void salvarNoArquivo();

    void adicionarComissao(float valorVenda);
    void atualizarSalarioNoArquivo();
    void consultarVendedor(int numConsulta);
    void alterarVendedor(int numeroAlvo);
    void excluirVendedor(int numeroAlvo);
};

#endif