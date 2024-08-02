typedef struct {
    int id;
    char *name;
    int age;
    char *department;
    float salary;
} Employee;

FILE* openFile(char *fileName); // PROBLEMAS AQUI AINDA
Employee* readFile(FILE *file, int *numEmployees);
void listEmployees(Employee *employees, int numEmployees);
void closeFile(FILE *file);
Employee* countingSort(Employee array[], int size);
void saveToFile(Employee array[], int size, char *fileName);
char* convertEmployeesToString(Employee array[], int size);
