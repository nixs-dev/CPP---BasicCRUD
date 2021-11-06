#include <iostream>
#include <stdio.h>
#include <string.h>
#include <vector>
#include <conio.h>
#include <map>
#include "../headers/Aluno.hpp"

Aluno::Aluno(std::string n, int i, std::string t, std::map<std::string, int> marks){
    nome = n;
    idade = i;
    turma = t;
    notas = marks;
}

void Aluno::set_nota_por_materia(std::string materia, int nota) {
    std::map<std::string, int>::iterator notas_interator;

    for(notas_interator = notas.begin(); notas_interator != notas.end(); notas_interator++) {
        if(notas_interator->first == materia) {
            notas_interator->second = nota;
        }
    }
}

void Aluno::setNotas(std::map<std::string, int> new_notas) {
    notas = new_notas;
}

std::string Aluno::show_notas_string() {
    std::map<std::string, int>::iterator notas_interator;
    std::string notas_string;

    for(notas_interator = notas.begin(); notas_interator != notas.end(); notas_interator++) {

        std::string nota;

        if(notas_interator->second == NULL) {
            nota = "N/A";
        }
        else {
            nota = std::to_string(notas_interator->second);
        }

        notas_string += "\t" + notas_interator->first + " - " + nota + "\n";
    }

    return notas_string;
}

bool Aluno::checa_materia_existe(std::string materia) {
    std::map<std::string, int>::iterator notas_interator;

    for(notas_interator = notas.begin(); notas_interator != notas.end(); notas_interator++) {
        if(notas_interator->first == materia) {
            return true;
        }
    }

    return false;
}

void Aluno::aniversario() {
    idade += 1;
}
