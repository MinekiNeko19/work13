#include "nyc.h"

int main(int argc, char *argv[]) {
    char instruct[100];
    char line[100];

  strcpy(instruct, argv[1]);
  // printf("received instructions: %s\n", instruct);

    if (argv[1]) {
      if (!strcmp(instruct, "-read_csv")) {
        read_csv();
      }
      else if (!strcmp(instruct, "-read_data")) {
        read_data();
      }
      else if (!strcmp(instruct, "-add_data")) {
        add_data();
      }
      else if (!strcmp(instruct, "-update_data")) {
        update_data();
      } else {
        printf("%s is an invalid action call\n", argv[1]);
      }
    }
    return 0;
}

int read_csv() {
  printf("\nread_csv called\n");

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
  // printf("%s\n",ogdata);

  if (errno) {
    printf("error %d: %s\n", errno, strerror(errno));
  } else {
    int ogcopy = open("nyc_pop.data", O_WRONLY | O_CREAT, 0644);

    // converting data into lines
    while (i != sb.st_size+1) {
      // printf("i: %d\n",i);
      if (ogdata[i] != '\n' && i != sb.st_size) {
        if (j) {
          line[x] = ogdata[i];
          x++;
        }
      } else {
        // printf("line: %s\n", line);
        if (j) {
          int y;
          int m;
          int bn;
          int q;
          int bx;
          int si;
          sscanf(line, "%d,%d,%d,%d,%d,%d", &y,&m,&bn,&q,&bx,&si);
          // printf("j: %d\tyear: %d\tm: %d\tbn: %d\tq: %d\tbx: %d\tsi: %d\n", j,y,m,bn,q,bx,si);
          int c;

          for (c = 0; c < 5; c++) {
            struct pop_entry d;
            d.year = y;
            if (c == 0) {
              d.population = m;
              strncpy(d.boro, "Manhattan",15);
            }
            if (c == 1) {
              d.population = bn;
              strncpy(d.boro, "Brooklyn",15);
            }
            if (c == 2) {
              d.population = q;
              strncpy(d.boro, "Queens",15);
            }
            if (c == 3) {
              d.population = bx;
              strncpy(d.boro, "Bronx",15);
            }
            if (c == 4) {
              d.population = si;
              strncpy(d.boro, "Staten Island",15);
            }
            // printf("pop_entry: y: %d, pop: %d, boro: %s\n", d.year, d.population, d.boro);
            write(ogcopy, &d, sizeof(struct pop_entry));
          }
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

void read_data() {
  printf("\nread_data called\n");
  struct stat sb;
  stat("nyc_pop.data", &sb);

  struct pop_entry d[sb.st_size/sizeof(struct pop_entry)];
  printf("number of entries: %lu\n", sb.st_size/sizeof(struct pop_entry));
  int ogcopy = open("nyc_pop.data", O_RDONLY, 0);
  read(ogcopy,d,sb.st_size);
  // printf("year: %d, pop: %d, boro: %s\n", d[0].year, d[0].population, d[0].boro);
  int i = 0;
  while (i < sb.st_size/sizeof(struct pop_entry)) {
    printf("%d:\tyear: %d\t pop: %d\t boro: %s\n", i, d[i].year, d[i].population, d[i].boro);
    i++;
  }
  close(ogcopy);
}

void add_data() {
  printf("\nadd_data called\n");

  int file = open("nyc_pop.data", O_WRONLY | O_APPEND, 0);

  struct pop_entry d;

  char input[100];
  printf("Enter the year boro pop: ");
  fgets(input, sizeof(input), stdin);
  sscanf(input,"%d %s %d",&d.year,d.boro,&d.population);

  // printf("year: %d\tpopulation: %d\tboro: %s\n",d.year,d.population,d.boro);
  write(file,&d,sizeof(struct pop_entry));

  close(file);
}

void update_data() {
  printf("update_data called\n");

  struct stat sb;
  stat("nyc_pop.data", &sb);

  struct pop_entry d[sb.st_size/sizeof(struct pop_entry)];
  printf("number of entries: %lu\n", sb.st_size/sizeof(struct pop_entry));
  int ogcopy = open("nyc_pop.data", O_RDONLY, 0);
  read(ogcopy,d,sb.st_size);
  // printf("year: %d, pop: %d, boro: %s\n", d[0].year, d[0].population, d[0].boro);
  int i = 0;
  while (i < sb.st_size/sizeof(struct pop_entry)) {
    printf("%d:\tyear: %d\t pop: %d\t boro: %s\n", i, d[i].year, d[i].population, d[i].boro);
    i++;
  }
  close(ogcopy);

  ogcopy = open("nyc_pop.data", O_WRONLY, 0);
  char buffer[100];
  int entry;
  printf("entry to update: ");
  fgets(buffer, sizeof(buffer), stdin);
  sscanf(buffer,"%d",&entry);

  struct pop_entry fixit;
  printf("Enter year boro pop: ");
  fgets(buffer, sizeof(buffer), stdin);
  sscanf(buffer, "%d %s %d", &fixit.year, fixit.boro, &fixit.population);
  
  printf("%d:\tyear: %d\t pop: %d\t boro: %s\n", entry, d[entry].year, d[entry].population, d[entry].boro);
  d[entry].year = fixit.year;
  d[entry].population = fixit.population;
  strncpy(d[entry].boro,fixit.boro,15);
  printf("%d:\tyear: %d\t pop: %d\t boro: %s\n", entry, d[entry].year, d[entry].population, d[entry].boro);

  int j = 0;
  while(j < sb.st_size/sizeof(struct pop_entry)) {
    write(ogcopy,&d[j],sizeof(struct pop_entry));
    j++;
  }

  close(ogcopy);
}