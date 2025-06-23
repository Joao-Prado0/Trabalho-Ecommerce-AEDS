//
// Created by nogue on 22/06/2025.
//
#include <iostream>
#include "compradores.h"

int main() {
    int id;
    string nome, email, cpf;

    cout << "Digite o ID do comprador: ";
    cin >> id;
    cin.ignore();

    cout << "Digite o nome do comprador: ";
    getline(cin, nome);

    cout << "Digite o email do comprador: ";
    getline(cin, email);

    cout << "Digite o CPF do comprador: ";
    getline(cin, cpf);


    compradores comprador(id, nome, email, cpf);


    cout << "\nDados" << endl;
    comprador.exibir();

    return 0;
}
