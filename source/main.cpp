#include <iostream>
#include <fstream>
#include <string>
#include <stdlib.h>

using namespace std;

typedef struct array_s {
    unsigned int x;
    unsigned int y;
    string **array;
} array_t;

array_t *recover_content(char * const path)
{
    string line;
    array_t *array = new array_t;
    ifstream file;

    file.open(path);
    array->x = 0;
    array->y = 0;
    array->array = new string*;
    if (file.is_open()) {
        while (getline(file, line)) {
            string *tmp = array->array[0];
            array->x++;
            delete[] array->array[0];
            array->array[0] = new string[array->x];
            for (unsigned int i = 0; i < array->x - 1; i++)
                array->array[0][i] = tmp[i];
            array->array[0][array->x - 1] = line;
        }
        file.close();
    } else {
        perror("Error: File can't be open.\n");
        exit(-1);
    }
    return (array);
}

void display(array_t *array)
{
    for (unsigned int i = 0; i < array->x; i++)
        printf("%s\n", array->array[0][i].c_str());
}

int main(int ac, char **av)
{
    if (ac != 2) {
        perror("Error: Programm need more argument.\n");
        return (-1);
    }
    array_t *dataset = recover_content(av[1]);
    display(dataset);

    delete[] dataset->array[0];
    delete[] dataset->array;
    delete[] dataset;
}