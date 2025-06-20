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
        FILE *arqVendedores;
    public:
    Vendedores(){}
    void setNumero() {
        unsigned seed = time(0);
        srand(seed);
        arqVendedores = fopen("vendedores.txt","r+");
        while (feof(arqVendedores)) {

        }
        numero = rand()%1001;
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
