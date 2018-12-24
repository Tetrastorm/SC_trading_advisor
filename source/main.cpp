#include <iostream>
#include <fstream>
#include <string>
#include <stdlib.h>

using namespace std;

string *add_to_list(string *list, string str, unsigned int size)
{
    string *tmp = list;
    list = new string[size + 1];
    for (unsigned int i = 0; i < size; i++)
        list[i] = tmp[i];
    list[size] = str;
    return (list);
}

string *recover_content(string path)
{
    string *content = nullptr;
    ifstream file(path);
    if (file.is_open()) {
        string line = "";
        for (unsigned int i = 0; getline(file, line); i++)
            content = add_to_list(content, line, i);
        file.close();
        return (content);
    } else {
        perror("Error: File can't be open\n");
        exit(-1);
    }
    return (content);
}

void display_list(string * const list)
{
    for (unsigned int i = 0; list[i] != "\0"; i++)
        cout << list[i] << endl;
}

int main(int ac, char **av)
{
    if (ac != 2) {
        perror("Missing argument\n");
        exit(-1);
    }
    string *content = recover_content(av[1]);
    display_list(content);
}