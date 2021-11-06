#ifndef DATABASE_HPP_INCLUDED
#define DATABASE_HPP_INCLUDED

#include <iostream>
#include <string>
#include <mysql.h>
#include <vector>
#include <map>
#include "Aluno.hpp"


class Database {
    public:
        static std::string host;
        static unsigned int port;
        static std::string user;
        static std::string password;
        static std::string table;
        MYSQL *conn;
        bool connected = false;

        Database();
        void database_connect();
        void database_error();

        //ALUNO CONTROLL

        std::vector<Aluno> get_all_alunos();
        std::map<std::string, int> get_aluno_notas(std::string aluno_nome);
        void insert_aluno(Aluno aluno);
        void update_aluno_notas(Aluno* aluno);
        void delete_aluno(std::string aluno_nome);

        //PROFESSOR CONTROLL

        bool check_professor_exists(std::string professor_nome);
        bool check_professor_senha(std::string professor_nome, std::string senha);
};


#endif // DATABASE_H_INCLUDED
