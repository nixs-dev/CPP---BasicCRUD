create database if not exists alunos_dados;

use alunos_dados;

create table professores (
	nome varchar(50) not null,
    senha varchar(30) not null,
    
    constraint professores_pk primary key(nome) 
);

create table alunos (
	nome varchar(50) not null,
    idade int not null,
    turma varchar(20) not null,
    
    constraint alunos_pk primary key(nome) 
);

create table notas (
	aluno_nome varchar(50) not null,
    materia varchar(30) not null,
    valor int null,
    
    constraint notas_fk foreign key(aluno_nome) references alunos(nome) on delete cascade
);
