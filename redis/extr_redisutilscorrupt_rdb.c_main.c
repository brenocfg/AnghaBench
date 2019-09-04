#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct stat {int st_size; } ;

/* Variables and functions */
 int /*<<< orphan*/  O_RDWR ; 
 int /*<<< orphan*/  SEEK_SET ; 
 int atoi (char*) ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  fstat (int,struct stat*) ; 
 int /*<<< orphan*/  lseek (int,unsigned long,int /*<<< orphan*/ ) ; 
 int open (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  perror (char*) ; 
 int /*<<< orphan*/  printf (char*,int,unsigned long) ; 
 int rand () ; 
 int /*<<< orphan*/  srand (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  time (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  write (int,unsigned char*,int) ; 

int main(int argc, char **argv) {
    struct stat stat;
    int fd, cycles;

    if (argc != 3) {
        fprintf(stderr,"Usage: <filename> <cycles>\n");
        exit(1);
    }

    srand(time(NULL));
    char *filename = argv[1];
    cycles = atoi(argv[2]);
    fd = open(filename,O_RDWR);
    if (fd == -1) {
        perror("open");
        exit(1);
    }
    fstat(fd,&stat);

    while(cycles--) {
        unsigned char buf[32];
        unsigned long offset = rand()%stat.st_size;
        int writelen = 1+rand()%31;
        int j;

        for (j = 0; j < writelen; j++) buf[j] = (char)rand();
        lseek(fd,offset,SEEK_SET);
        printf("Writing %d bytes at offset %lu\n", writelen, offset);
        write(fd,buf,writelen);
    }
    return 0;
}