#include "../headers/Database.hpp"


std::string Database::host = "localhost";
unsigned int Database::port = 3306;
std::string Database::user = "root";
std::string Database::password = "santodeus123";
std::string Database::table = "alunos_dados";

Database::Database() {
}

void Database::database_connect() {
    Database::conn = mysql_init(NULL);

    if (mysql_real_connect(Database::conn, Database::host.c_str(), Database::user.c_str(), Database::password.c_str(), NULL, Database::port, NULL, 0))
    {
        Database::connected = true;
    }
    else{
        Database::database_error();
    }

    if(mysql_select_db(Database::conn, Database::table.c_str()) != 0) {
        Database::database_error();
    }
}

std::vector<Aluno> Database::get_all_alunos() {
    std::string query = "SELECT * FROM alunos";
    std::vector<Aluno> obtained_alunos;
    MYSQL_RES *result;

    if(mysql_real_query(Database::conn, query.c_str(), query.size()) != 0) {
        Database::database_error();
    }
    else {
        result = mysql_store_result(Database::conn);
    }

    if(result != NULL) {
        MYSQL_ROW row;

        while((row = mysql_fetch_row(result))!=0)
        {
            std::string nome = row[0];
            int idade = std::stoi(row[1]);
            std::string turma = row[2];
            Aluno aluno(nome, idade, turma, std::map<std::string, int>());
            obtained_alunos.push_back(aluno);
        }
    }

    mysql_free_result(result);
    return obtained_alunos;
}

std::map<std::string, int> Database::get_aluno_notas(std::string aluno_nome) {
    std::string query = "SELECT * FROM notas WHERE aluno_nome = '" + aluno_nome + "'";
    MYSQL_RES *result;
    std::map<std::string, int> notas;

    if(mysql_real_query(Database::conn, query.c_str(), query.size()) != 0) {
        Database::database_error();
    }
    else {
        result = mysql_store_result(Database::conn);
    }

    if(result != NULL) {
        MYSQL_ROW row;

        while((row = mysql_fetch_row(result)) != 0) {
            std::string materia = row[1];
            int nota;

            if(row[2] == NULL) {
                nota = NULL;
            }
            else {
                nota = std::stoi(row[2]);
            }

            notas.insert(std::pair<std::string, int>(materia, nota));
        }
    }

    mysql_free_result(result);
    return notas;
}

void Database::insert_aluno(Aluno aluno) {
    std::string query = "INSERT INTO alunos VALUES ('" + aluno.nome + "', " + std::to_string(aluno.idade) + ", '" + aluno.turma + "')";

    if(mysql_real_query(conn, query.c_str(), query.size()) != 0) {
        database_error();
    }

    std::map<std::string, int>::iterator notas_iterator;

    for(notas_iterator = aluno.notas.begin(); notas_iterator != aluno.notas.end(); notas_iterator++)
    {
        query = "INSERT INTO notas VALUES ('" + aluno.nome + "', '" + notas_iterator->first + "', " +  std::to_string(notas_iterator->second) + ")";

        if(mysql_real_query(conn, query.c_str(), query.size()) != 0) {
            database_error();
        }
    }
}



void Database::update_aluno_notas(Aluno* aluno) {
    std::string query;
    std::map<std::string, int>::iterator notas_iterator;

    for(notas_iterator = aluno->notas.begin(); notas_iterator != aluno->notas.end(); notas_iterator++)
    {
        std::string materia = notas_iterator->first;
        std::string nota_to_update;

        if(notas_iterator->second == NULL) {
            nota_to_update = "NULL";
        }
        else {
            nota_to_update = std::to_string(notas_iterator->second);
        }

        query = "UPDATE notas SET valor = " + nota_to_update + " WHERE aluno_nome = '" + aluno->nome + "' AND materia = '" + materia + "'";

        if(mysql_real_query(conn, query.c_str(), query.size()) != 0) {
            database_error();
        }
    }
}



void Database::delete_aluno(std::string nome_aluno) {
    std::string query = "DELETE FROM alunos WHERE nome = '" + nome_aluno + "'";

    if(mysql_real_query(conn, query.c_str(), query.size()) != 0) {
        database_error();
    }
}

bool Database::check_professor_exists(std::string professor_nome) {
    std::string query = "SELECT * FROM professores WHERE nome = '" + professor_nome + "'";

    if(mysql_real_query(conn, query.c_str(), query.size()) != 0) {
        database_error();
    }
    else {
        MYSQL_RES* result = mysql_store_result(conn);

        if(mysql_num_rows(result) == 0) {
            mysql_free_result(result);
            return false;
        }
        else {
            mysql_free_result(result);
            return true;
        }
    }
}

bool Database::check_professor_senha(std::string professor_nome, std::string senha) {
    std::string query = "SELECT * FROM professores WHERE nome = '" + professor_nome + "' AND senha = '" + senha + "'";

    if(mysql_real_query(conn, query.c_str(), query.size()) != 0) {
        database_error();
    }
    else {
        MYSQL_RES* result = mysql_store_result(conn);

        if(mysql_num_rows(result) == 0) {
            mysql_free_result(result);
            return false;
        }
        else {
            mysql_free_result(result);
            return true;
        }
    }
}



void Database::database_error() {
    std::cout << mysql_error(Database::conn);
    mysql_close(Database::conn);
    exit(1);
}
