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
            string tmp[array->x];
            for (unsigned int i = 0; i < array->x; i++)
                tmp[i] = array->array[0][i];
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

array_t *format_data(array_t *tmp)
{
    array_t *result = new array_t;

    result->x = 0;
    result->y = tmp->x;
    result->array = new string*[result->y];
    for (unsigned int y = 0; y < result->y; y++) {
        char const * str = tmp->array[0][y].c_str();
        unsigned int box = 0;
        string tmp_str = "";
        for (unsigned int i = 0; str[i] != '\0'; i++) {
            if (str[i] == '\t') {
                string *tmp_list = new string[box];
                for (unsigned int x = 0; x < box; x++)
                    tmp_list[x] = result->array[y][x]; 
                box++;
                delete[] result->array[y];
                result->array[y] = new string[box];
                for (unsigned int x = 0; x < box - 1; x++)
                    result->array[y][x] = tmp_list[x];
                result->array[y][box - 1] = tmp_str;
                tmp_str = "";
            } else {
                tmp_str += str[i];
            }
        }
        result->x = box;
    }
    delete[] tmp->array[0];
    delete[] tmp->array;
    delete[] tmp;
    return (result);
}

void display_debug(array_t *array)
{
    for (unsigned int x = 0; x < array->x; x++)
        printf("%s\n", array->array[0][x].c_str());
    printf("\nEND\n");
}

array_t *make_array(char * const path)
{
    array_t *tmp = recover_content(path);
    return (format_data(tmp));
}

void display(array_t *array)
{
    for (unsigned int y = 0; y < array->y; y++) {
        for (unsigned int x = 0; x < array->x; x++)
            printf("%s", array->array[y][x].c_str());
        printf("\n");
    }
}

int main(int ac, char **av)
{
    if (ac != 2) {
        perror("Error: Programm need more argument.\n");
        return (-1);
    }
    array_t *dataset = make_array(av[1]);
    display(dataset);
}