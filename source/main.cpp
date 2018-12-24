#include <iostream>
#include <fstream>
#include <string>
#include <stdlib.h>

using namespace std;

string *recover_content(string path)
{
    string *content = nullptr;
    ifstream file(path);
    if (file.is_open()) {
        string line = "";
        for (unsigned int i = 0; getline(file, line); i++) {
            cout << line << '\n';
            string *tmp = content;
            content = new string[i+1];
            for (unsigned int j = 0; j < i; j++)
                content[j] = tmp[j];
            content[i] = line;
        }
        file.close();
        return (content);
    } else {
        perror("Error: File can't be open\n");
        exit(-1);
    }
}

int main(int ac, char **av)
{
    if (ac != 2) {
        perror("Missing argument\n");
        exit(-1);
    }
    string *content = recover_content(av[1]);
    for (unsigned int i = 0; i < 4; i++)
        cout << content[i] << endl;
}