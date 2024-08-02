#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "projeto-arvores.h"

FILE* openFile(char *fileName) {
    FILE *file = fopen(fileName, "r");
    if (file == NULL) {
        printf("Erro de abertura no arquivo!\n");
        system("pause");
        exit(1);
    }
    return file;
}

Employee* readFile(FILE *file, int *numEmployees) {
    size_t capacity = 13;
    *numEmployees = 0;
    Employee *employees = malloc(capacity * sizeof(Employee));
    if (!employees) {
        perror("Erro de alocacao de memoria\n");
        exit(1);
    }

    char buffer[1024];
    while (fgets(buffer, sizeof(buffer), file) != NULL) {
        if (*numEmployees >= capacity) {
            capacity *= 2;
            employees = realloc(employees, capacity * sizeof(Employee));
            if (!employees) {
                perror("Erro de alocacao de memoria\n");
                exit(1);
            }
        }

        Employee employee;
        /* Tentativa 1 de conseguir pegar o salário
        employee.id = atoi(strtok(buffer, ","));
        employee.name = strdup(strtok(NULL, ","));
        employee.age = atoi(strtok(NULL, ","));
        employee.department = strdup(strtok(NULL, ","));
        employee.salary = atof(strtok(NULL, "\n"));*/

        // Tentativa 2 de conseguir pegar o salário
        char *token;

        // ID
        token = strtok(buffer, ",");
        if (token != NULL) {
            employee.id = atoi(token);
        }

        // Name
        token = strtok(NULL, ",");
        if (token != NULL) {
            employee.name = strdup(token);
        }

        // Age
        token = strtok(NULL, ",");
        if (token != NULL) {
            employee.age = atoi(token);
        }

        // Department
        token = strtok(NULL, ",");
        if (token != NULL) {
            employee.department = strdup(token);
        }

        // Salary
        token = strtok(NULL, "\n"); // Read till end of line
        if (token != NULL) {
            employee.salary = atof(token);
        }

        employees[*numEmployees] = employee;
        (*numEmployees)++;
    }

    return employees;
}

// Test function to verify if the employees are being read correctly
void listEmployees(Employee *employees, int numEmployees) {
    for (int i = 0; i < numEmployees; i++) {
        printf("ID: %d, Name: %s, Age: %d, Department: %s, Salary: %.2f\n",
               employees[i].id, employees[i].name, employees[i].age,
               employees[i].department, employees[i].salary);
    }
}

void closeFile(FILE *file) {
    fclose(file);
}

// Counting sort function
Employee* countingSort(Employee array[], int size) {
    if (size <= 0) return NULL;

    int maxVal = array[0].id;
    for (int i = 1; i < size; i++) {
        if (array[i].id > maxVal) {
            maxVal = array[i].id;
        }
    }

    int *count = (int *)calloc(maxVal + 1, sizeof(int));
    Employee *output = (Employee *)malloc(size * sizeof(Employee));

    for (int i = 0; i < size; i++) {
        count[array[i].id]++;
    }

    for (int i = 1; i <= maxVal; i++) {
        count[i] += count[i - 1];
    }

    for (int i = size - 1; i >= 0; i--) {
        output[count[array[i].id] - 1] = array[i];
        count[array[i].id]--;
    }

    free(count);
    return output;
}

void saveToFile(Employee array[], int size, char *fileName) {
    FILE *file = fopen(fileName, "w");
    if (file == NULL) {
        printf("Error opening file!\n");
        system("pause");
        exit(1);
    }

    char *data = convertEmployeesToString(array, size);
    fputs(data, file);

    fclose(file);
    free(data); // Libera a memória alocada para a string
}

char* convertEmployeesToString(Employee array[], int size) {
    char* line = malloc(1024 * size);
    if (line == NULL) {
        perror("Memory allocation failed");
        exit(EXIT_FAILURE);
    }
    line[0] = '\0';

    char temp[300];
    for (int i = 0; i < size; i++) {
        sprintf(temp, "%d", array[i].id);
        strcat(line, temp);
        strcat(line, ",");

        strcat(line, array[i].name);
        strcat(line, ",");

        sprintf(temp, "%d", array[i].age);
        strcat(line, temp);
        strcat(line, ",");

        strcat(line, array[i].department);
        strcat(line, ",");

        sprintf(temp, "%.2f", array[i].salary);
        strcat(line, temp);
        strcat(line, "\n");
    }

    return line;
}
