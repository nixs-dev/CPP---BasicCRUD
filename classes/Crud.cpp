#include "../headers/Crud.hpp"

std::vector<Aluno> CRUD::alunos = std::vector<Aluno>();
Database CRUD::database = Database();
std::map<std::string, int> CRUD::default_marks = {
    {"Matematica", NULL},
    {"Portugues", NULL},
    {"Biologia", NULL},
    {"Quimica", NULL},
    {"Fisica", NULL},
    {"Historia", NULL},
    {"Geografia", NULL},
    {"Artes", NULL}
};


Aluno* CRUD::obter_aluno_por_nome(std::string nome) {
    std::vector<Aluno>::iterator alunos_interator;

    for(alunos_interator = alunos.begin(); alunos_interator != alunos.end(); alunos_interator++) {
        if(alunos_interator->nome == nome) {
            return &(*alunos_interator);
        }
    }
}

bool CRUD::checa_aluno_existe(std::string nome) {
    for(Aluno a: alunos) {
        if(a.nome == nome) {
            return true;
        }
    }

    return false;
}

void CRUD::adicionar_aluno() {
    std::string aluno_name;
    int aluno_idade;
    std::string aluno_turma;

    system("cls");

    std::cout << "Nome: ";
    std::cin >> aluno_name;
    std::cout << "Idade: ";
    std::cin >> aluno_idade;
    std::cout << "Turma: ";
    std::cin >> aluno_turma;

    Aluno aluno(aluno_name, aluno_idade, aluno_turma, CRUD::default_marks);
    database.insert_aluno(aluno);

    pausa_sistema();
    CRUD::reload_alunos();

    std::cout << "Aluno adicionado!" << std::endl;
}

void CRUD::atualizar_notas_aluno() {
    std::string nome_aluno;
    Aluno* aluno;

    system("cls");
    std::cout << "Nome: ";
    std::cin >> nome_aluno;

    if(!CRUD::checa_aluno_existe(nome_aluno)) {
        std::cout << "\n\nALUNO INEXISTENTE";

        pausa_sistema();
        return;
    }
    else {
         aluno = CRUD::obter_aluno_por_nome(nome_aluno);
    }

    while(true) {
        std::string materia_to_update;
        int nota_to_update;
        std::string continuar_resposta;

        std::cout << "Materia: ";
        std::cin >> materia_to_update;

        if(!aluno->checa_materia_existe(materia_to_update)) {
            std::cout << materia_to_update << " nao esta registrado!" << std::endl;
        }
        else {
            std::cout << "Nota: ";
            std::cin >> nota_to_update;

            aluno->set_nota_por_materia(materia_to_update, nota_to_update);
        }

        std::cout << "\n\n\nDeseja atualizar outra nota de " << aluno->nome << " ? [S/N]  ";
        std::cin >> continuar_resposta;

        std::cout << "\n\n\n";

        if(continuar_resposta != "S") {
            break;
        }

    }

    database.update_aluno_notas(aluno);
    std::cout << "NOTAS ATUALIZADAS\n";
    pausa_sistema();
};


void CRUD::remover_aluno()
{
    std::string nome_aluno;
    int index = 0;

    system("cls");
    std::cout << "Nome do aluno a ser removido: ";
    std::cin >> nome_aluno;

    if(!CRUD::checa_aluno_existe(nome_aluno)) {
        std::cout << "\n\nALUNO INEXISTENTE";

        pausa_sistema();
        return;
    }

    database.delete_aluno(nome_aluno);
    reload_alunos();

    std::cout << "Aluno removido" << std::endl;
    pausa_sistema();
}

void CRUD::mostrar_alunos() {

    system("cls");
    std::cout << "\n\n";

    if(alunos.size() == 0) {
        std::cout << "NENHUM ALUNO REGISTRADO";
    }
    else {
        for(Aluno a: alunos) {
            std::cout << a.nome << " - " << a.idade << " - " << a.turma << "\n";
        }
    }

    pausa_sistema();
}

void CRUD::mostrar_aluno_notas() {
    std::string nome_aluno;

    system("cls");

    std::cout << "Nome do aluno: ";
    std::cin >> nome_aluno;

    if(!CRUD::checa_aluno_existe(nome_aluno)) {
        std::cout << "\n\nALUNO INEXISTENTE";

        pausa_sistema();
        return;
    }

    for(Aluno a: alunos) {
        if(a.nome == nome_aluno) {
            std::cout << "Notas de " << a.nome << "\n\n" << a.show_notas_string();
        }
    }

    pausa_sistema();
}

void CRUD::reload_alunos() {
    alunos = database.get_all_alunos();
    std::vector<Aluno>::iterator it;

    for(it = alunos.begin(); it != alunos.end();it++) {
        std::map<std::string, int> notas = database.get_aluno_notas(it->nome);

        it->setNotas(notas);
    }
}

void CRUD::aluno_info() {
    system("cls");

    std::string aluno_nome;
    std::cout << "Nome do Aluno: "; std::cin >> aluno_nome;

    if(!CRUD::checa_aluno_existe(aluno_nome)) {
        std::cout << "\n\nALUNO INEXISTENTE";

        pausa_sistema();
        system("cls");
        return;
    }

    for(Aluno a: alunos) {
        if(a.nome == aluno_nome) {
            std::string info_completa = "\n\n\Nome: " + a.nome + "\n" +
                                        "Idade: " + std::to_string(a.idade) + "\n" +
                                        "Turma: " + a.turma + "\n" +
                                        "Notas: \n\n";

            info_completa += a.show_notas_string();

            std::cout << info_completa;
        }
    }

    pausa_sistema();
}
