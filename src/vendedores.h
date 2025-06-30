#ifndef VENDEDORES_H
#define VENDEDORES_H

#include <iostream>
#include <fstream>
#include <iomanip>
#include <cstdlib>
#include <ctime>
#include <string>

class Vendedores {
private:
    int numero;
    std::string nome;
    float salarioFixo;
    float comissaoAcumulada;
    float salarioTotal;


    void calcularSalarioTotal();

public:
    Vendedores();
    bool verificarNumero(int num);
    void setNumero();
    void setNome();
    void setSalarioFixo();
    void salvarNoArquivo();
    void atualizarArquivo();
    void adicionarComissao(float valorVenda);
    void consultarVendedor(int numConsulta);
    void alterarVendedor(int numeroAlvo);
    void excluirVendedor(int numeroAlvo);
    void listarTodosVendedores();
};

#endif