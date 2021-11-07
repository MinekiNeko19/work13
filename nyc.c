#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>

struct pop_entry {
  int year;
  int population;
  char boro[15];
};

int main(int argc, char *argv[]) {
    char instruct[100];
    char line[100];
    if (argv[1]) {

      // preparing to scan the file 
      strcpy(instruct, argv[1]);
      printf("received instructions: %s\n", instruct);

      int file = open("nyc_pop.csv", O_RDONLY, 0);
      struct stat sb;
      stat("nyc_pop.csv", &sb);
      printf("size of data: %lu\n", sb.st_size);

      char ogdata[sb.st_size];
      read(file, ogdata, sb.st_size);
      // printf("%s",ogdata);
      int i = 0;
      printf("%d\n",i);
      while(ogdata[i] != '\n') {
        i++;
      }
      printf("%d\n",i);
  
      if (errno) {
        printf("error %d: %s\n", errno, strerror(errno));
      }
      else if (!strcmp(instruct, "-read_csv")) {
        read_csv();
      // }
      // else if (!strcmp(instruct, "-read_data")) {
      //   read_data();
      // }
      // else if (!strcmp(instruct, "-add_data")) {
      //   add_data();
      // }
      // else if (!strcmp(instruct, "-updata_data")) {
      //   updata_data();
      } else {
        printf("%s is an invalid action call\n", argv[1]);
      }

      close(ogdata);
    }
    return 0;
}

// temporary return types
void read_csv() {
  printf("read_csv called\n");
}
// void read_data() {
//   printf("read_data called\n");  
// }
// void add_data() {
//   printf("add_data called\n");  
// }
// void updata_data() {
//   printf("updata_data called\n");
// }