#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct pop_entry {
  int year;
  int population;
  char boro[15];
};

int main(int argc, char *argv[]) {
    char instruct[100];
    strcpy(instruct, argv[1]); // seg fault when empty

    printf("received instructions: %s\n", instruct);
    if (!strcmp(instruct, "-read_csv")) {
      read_csv();
    }
    if (!strcmp(instruct, "-read_data")) {
      read_data();
    }
    if (!strcmp(instruct, "-add_data")) {
      add_data();
    }
    if (!strcmp(instruct, "-updata_data")) {
      updata_data();
    }
    return 0;
}
// temporary return types
void read_csv() {
  printf("read_csv called\n");
}
void read_data() {
  printf("read_data called\n");  
}
void add_data() {
  printf("add_data called\n");  
}
void updata_data() {
  printf("updata_data called\n");
}