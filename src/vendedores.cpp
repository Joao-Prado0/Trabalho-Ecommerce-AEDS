#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cstdio>
using namespace std;
class Vendedores {
    private:
        int numero;
        string nome;
        float salario;
        int comissao;
    public:
    Vendedores(){}
    void setNumero() {

    }
    void setNome(){

    }
    void setSalario() {

    }
    void setComissao() {

    }
};
int main() {
    FILE *arqVendedores = fopen("vendedores.txt","w ");
    fprintf(arqVendedores,"Opa tudo bom");
    return 0;
}
