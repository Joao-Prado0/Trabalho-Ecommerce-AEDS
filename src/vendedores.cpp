#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cstdio>
#include <fstream>
#include <iomanip>
using namespace std;

class Vendedores {
private:
    int numero;
    string nome;
    float salario;
    int comissao;

public:
    Vendedores() {
        numero = 0;
        nome = "";
        salario = 0.0;
        comissao = 0;
    }

    Vendedores(int num, string n, float s, int c) {
        this->numero = num;
        this->nome = n;
        this->salario = s;
        this->comissao = c;
    }

    void setNumero() {
        static bool inicializado = false;
        if (!inicializado) {
            srand(time(nullptr));
            inicializado = true;
        }

        int numGerado;
        do {
            numGerado = (rand() % 900) + 100;
        } while (verificarNumero(numGerado));

        numero = numGerado;
        cout << "Número do vendedor gerado: " << numero << endl;
    }

    void setNome() {
        cout << "Nome do vendedor: ";
        cin.ignore();
        getline(cin, nome);
    }

    void setSalario() {
        cout << "Salário fixo: ";
        cin >> salario;
    }

    void setComissao() {
        comissao = 0;
    }

    bool verificarNumero(int num) {
        ifstream arquivo("../data/vendedores.txt");
        if (!arquivo.is_open()) {
            return false;
        }

        string linha;
        while (getline(arquivo, linha)) {
            if (linha.find("Numero: " + to_string(num)) != string::npos) {
                return true;
            }
        }
        return false;
    }

    void salvarNoArquivo() {
        ofstream arquivo("../data/vendedores.txt", ios::app);
        if (!arquivo.is_open()) {
            cout << "Erro ao abrir o arquivo para salvar vendedor." << endl;
            return;
        }

        arquivo << "Vendedor" << endl;
        arquivo << "Número: " << numero << endl;
        arquivo << "Nome: " << nome << endl;
        arquivo << fixed;
        arquivo.precision(2);
        arquivo << "Salário: " << salario << endl;
        arquivo << "Comissão: " << comissao << endl;
        arquivo << "-----" << endl;

        cout << "Vendedor salvo com sucesso!" << endl;
    }

    void adicionarComissao(float valorVenda) {
        float valorComissao = valorVenda * 0.03;
        salario += valorComissao;
        cout << "Comissão de R$ " << valorComissao << " adicionada ao salário." << endl;
        cout << "Novo salário: R$ " << salario << endl;
        atualizarSalarioNoArquivo();
    }

    void atualizarSalarioNoArquivo() {
        ifstream arquivoIn("../data/vendedores.txt");
        ofstream arquivoOut("../data/temp.txt");

        if (!arquivoIn.is_open() || !arquivoOut.is_open()) {
            cout << "Erro ao abrir os arquivos para atualização." << endl;
            return;
        }

        string linha;
        bool achou = false;

        while (getline(arquivoIn, linha)) {
            if (linha == "Vendedor") {
                arquivoOut << linha << endl;

                getline(arquivoIn, linha);
                int num = stoi(linha.substr(8));
                arquivoOut << linha << endl;

                getline(arquivoIn, linha);
                string nomeLinha = linha;
                arquivoOut << nomeLinha << endl;

                getline(arquivoIn, linha);
                if (num == numero) {
                    achou = true;
                    arquivoOut << "Salário: " << fixed << setprecision(2) << salario << endl;
                } else {
                    arquivoOut << linha << endl;
                }

                getline(arquivoIn, linha); // Comissão
                arquivoOut << linha << endl;

                getline(arquivoIn, linha); // Separador
                arquivoOut << linha << endl;
            } else {
                arquivoOut << linha << endl;
            }
        }

        arquivoIn.close();
        arquivoOut.close();

        remove("../data/vendedores.txt");
        rename("../data/temp.txt", "../data/vendedores.txt");

        if (achou)
            cout << "Salário atualizado com sucesso no arquivo!" << endl;
        else
            cout << "Vendedor não encontrado para atualização." << endl;
    }
};

