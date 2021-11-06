#include <iostream>
#include <stdio.h>
#include <string.h>
#include <vector>
#include <conio.h>
#include <map>
#include "headers/utils.hpp"

void pausa_sistema() {
    std::cout << "\n\n" << "Aperte ENTER para prosseguir" << "\n";
    getch();
    system("cls");
}

std::vector<std::string> split_string(std::string str, char* delimiter)
{
    char data[1024];
    strcpy(data, str.c_str());

    char *token = strtok(data, delimiter);
    std::vector<std::string> splitted_string;

    while (token != NULL)
    {
        splitted_string.push_back(token);
        token = strtok(NULL, delimiter);
    }

    return splitted_string;
}
