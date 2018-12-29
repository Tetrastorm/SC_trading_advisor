#include <iostream>
#include <fstream>
#include <string>
#include <stdlib.h>

using namespace std;

typedef struct ressource_s {
    string name;
    double profitable;
    double cost;
    string sell_location;
    string buy_location;
} ressource_t;

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
        result->array[y] = new string[1];
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
                delete[] tmp_list;
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

array_t *make_array(char * const path)
{
    array_t *tmp = recover_content(path);
    return (format_data(tmp));
}

void display(array_t *array)
{
    for (unsigned int y = 0; y < array->y; y++) {
        for (unsigned int x = 0; x < array->x; x++)
            printf("%s ", array->array[y][x].c_str());
        printf("\n");
    }
}

unsigned int find_location(array_t *array, string location, bool is_buy)
{
    unsigned int range = 0;

    while (range < array->x && location != array->array[4][range])
        range++;
    if (range > array->x) {
        perror("Error: Location not found.\n");
        exit(-1);
    } else if (!is_buy)
        range++;
    return (range);
}

ressource_t *find_most_profitable(array_t *array, string buy, string sell)
{
    unsigned int location_a = find_location(array, buy, true);
    unsigned int location_b = find_location(array, sell, false);

    ressource_t *ressource = new ressource_t[1];

    ressource->name = "";
    ressource->profitable = 0.0;
    ressource->sell_location = sell;
    ressource->buy_location = buy;
    ressource->cost = 0.0f;
    for (unsigned int i = 7; i < array->y; i++) {
        if (!array->array[i][location_a].empty() && !array->array[i][location_b].empty()) {
            double profitable = atof(array->array[i][location_b].c_str()) / atof(array->array[i][location_a].c_str());
            printf("Ressource = %s, %s: %s, %s: %s, Profitable = %f\n", array->array[i][1].c_str(), buy.c_str(), array->array[i][location_a].c_str(), sell.c_str(), array->array[i][location_b].c_str(), profitable);
            if (profitable > 1.0 && ressource->profitable < profitable) {
                ressource->cost = atof(array->array[i][location_a].c_str());
                ressource->name = array->array[i][1];
                ressource->profitable = profitable;
            }
        }
    }
    return (ressource);
}

int main(int ac, char **av)
{
    if (ac != 4) {
        perror("Error: Programm need more argument.\n");
        return (-1);
    }
    array_t *dataset = make_array(av[1]);
    ressource_t *result = find_most_profitable(dataset, av[2], av[3]);
    if (result->name.empty())
        printf("\nNo ressource profitable found.\n\n");
    else
        printf("\nRessource: %s\nCost: %g UEC\nProfitable: %f\nBuy Location: %s\nSell Location: %s\n\n", result->name.c_str(), result->cost, result->profitable, result->buy_location.c_str(), result->sell_location.c_str());

    for (unsigned int i = 0; i < dataset->y; i++)
        delete[] dataset->array[i];
    delete[] dataset->array;
    delete[] dataset;
}