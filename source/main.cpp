#include <iostream>
#include <fstream>
#include <string>

using namespace std;

int main(int ac, char **av)
{
    if (ac != 2) {
        perror("Missing argument\n");
        exit(-1);
    }
    string content = "";
    ifstream file(av[1]);
    if (file.is_open()) {
        cout << content << '\0';
        while (getline(file, content))
            cout << content << '\n';
        file.close();
    }
}