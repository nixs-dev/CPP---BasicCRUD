#ifndef ALUNO_HPP_INCLUDED
#define ALUNO_HPP_INCLUDED

#include <iostream>
#include <stdio.h>
#include <vector>
#include <conio.h>
#include <map>

class Aluno {
    public:
        std::string nome;
        int idade;
        std::string turma;
        std::map<std::string, int> notas;

        Aluno(std::string n, int i, std::string t, std::map<std::string, int> marks);
        void set_nota_por_materia(std::string materia, int nota);
        void setNotas(std::map<std::string, int> new_notas);
        std::string show_notas_string();
        bool checa_materia_existe(std::string materia);
        void aniversario();
};

#endif

