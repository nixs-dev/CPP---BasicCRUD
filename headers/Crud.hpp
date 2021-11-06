#ifndef CRUD_HPP_INCLUDED
#define CRUD_HPP_INCLUDED

#include <vector>
#include <iostream>
#include <string>
#include <map>
#include "utils.hpp"
#include "Aluno.hpp"
#include "Database.hpp"

class CRUD {
    public:
        static std::vector<Aluno> alunos;
        static Database database;
        static std::map<std::string, int> default_marks;

        static Aluno* obter_aluno_por_nome(std::string nome);
        static bool checa_aluno_existe(std::string nome_aluno);
        static void adicionar_aluno();
        static void atualizar_notas_aluno();
        static void remover_aluno();
        static void mostrar_alunos();
        static void mostrar_aluno_notas();
        static void reload_alunos();
        static void aluno_info();
};


#endif
