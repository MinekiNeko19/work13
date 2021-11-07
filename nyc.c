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

  strcpy(instruct, argv[1]);
  printf("received instructions: %s\n", instruct);

    if (argv[1]) {
      if (!strcmp(instruct, "-read_csv")) {
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
    }
    return 0;
}

// temporary return types
int read_csv() {
  printf("read_csv called\n");

 // preparing to scan the file 

  int file = open("nyc_pop.csv", O_RDONLY, 0);
  struct stat sb;
  stat("nyc_pop.csv", &sb);
  printf("size of data: %lu\n", sb.st_size);

  char ogdata[sb.st_size];
  read(file, ogdata, sb.st_size);
  // printf("%s",ogdata);
  char line[100];
  int i = 0;
  int j = 0;
  int x = 0;
  // printf("line: %s\n", line);

  if (errno) {
    printf("error %d: %s\n", errno, strerror(errno));
  } else {
    int ogcopy = open("nyc_pop.data", O_WRONLY | O_CREAT, 0644);

    // converting data into lines
    while (i != sb.st_size+1) {
      if (ogdata[i] != '\n' && i != sb.st_size) {
        if (j) {
          line[x] = ogdata[i];
          x++;
        }
      } else {
        // printf("line: %s\n", line);
        int y;
        int m;
        int bn;
        int q;
        int bx;
        int si;
        sscanf(line, "%d,%d,%d,%d,%d,%d", &y,&m,&bn,&q,&bx,&si);
        // printf("year: %d,m: %d,bn: %d,q: %d,bx: %d, si: %d\n", year,m,bn,q,bx,si);
        int c;
        struct pop_entry d;
        d.year = y;

        for (c = 0; c < 5; c++) {
          if (c = 0) {
            d.population = m;
            strncpy(d.boro, "Manhattan",15);
          }
          if (c = 1) {
            d.population = bn;
            strncpy(d.boro, "Brooklyn",15);
          }
          if (c = 2) {
            d.population = q;
            strncpy(d.boro, "Queens",15);
          }
          if (c = 3) {
            d.population = bx;
            strncpy(d.boro, "Bronx",15);
          }
          if (c = 4) {
            d.population = si;
            strncpy(d.boro, "Staten Island",15);
          }
          // printf("pop_entry: y: %d, pop: %d, boro: %s\n", d.year, d.population, d.boro);
          write(ogcopy, &d, sizeof(struct pop_entry));
        }
        j++;
        x = 0;
      }
      i++;
    }
    
    
    // printf("line: %s\n", line);
    // printf("i: %d sb.st_size: %lu\n", i, sb.st_size);
    
    close(ogcopy);
  }

  close(file);
  return errno;
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