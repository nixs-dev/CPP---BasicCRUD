#include <iostream>
#include <string.h>
#include "headers/Titles.hpp"
#include "headers/Professor.hpp"
#include "headers/Crud.hpp"



void notas_center() {
    std::vector<std::string> options = {"Voltar", "Setar notas de um aluno", "Notas de um aluno"};
    std::vector<void (*)(void)> calls = {NULL, CRUD::atualizar_notas_aluno, CRUD::mostrar_aluno_notas};
    int answer;

    while(true) {
        int option_index = 1;

        std::cout << main_title << "\n\n\n";

        for(std::string option: options) {
            std::cout << option_index << " - " << option << "\n";
            option_index += 1;
        }

        std::cout << "\n\nEscolha: ";
        std::cin >> answer;

        if(answer-1 == 0) {
            system("cls");
            break;
        }
        else {
            calls[answer-1]();
        }
    }
}

void main_menu() {
    std::vector<std::string> options = {"Adicionar aluno", "Informacoes do Aluno", "Ver alunos", "Remover aluno", "Central de notas"};
    std::vector<void (*)(void)> calls = {CRUD::adicionar_aluno, CRUD::aluno_info, CRUD::mostrar_alunos, CRUD::remover_aluno, notas_center};
    int answer;

    CRUD::reload_alunos();

    while(true) {
        int option_index = 1;

        std::cout << main_title << "\n\n\n";

        for(std::string option: options) {
            std::cout << option_index << " - " << option << "\n";
            option_index += 1;
        }

        std::cout << "\n\nEscolha: ";
        std::cin >> answer;

        calls[answer-1]();
    }
}

int main() {
    std::string professor_nome;
    std::string professor_senha;
    std::string login_response = "";
    CRUD::database.database_connect();

    while(true) {
        std::cout << login_title;

        std::cout << "\n\n" << login_response << "\n\n";

        std::cout << "Nome do Professor: ";
        std::cin >> professor_nome;

        std::cout << "Senha: ";
        std::cin >> professor_senha;

        if(CRUD::database.check_professor_exists(professor_nome)) {
            if(CRUD::database.check_professor_senha(professor_nome, professor_senha)) {
                break;
            }
            else {
                login_response = "Senha incorreta!";
            }
        }
        else {
            login_response = "Professor nao cadastrado!";
        }

        system("cls");
    }

    system("cls");
    main_menu();
}
