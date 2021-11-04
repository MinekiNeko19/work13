#include <stdio.h>
#include <stdlib.h>

struct pop_entry {
  int year;
  int population;
  char boro[15];
};

int main() {
    char instruct[100];
    fgets(instruct, sizeof(instruct), stdin);
    printf("%s\n", instruct);
    return 0;
}