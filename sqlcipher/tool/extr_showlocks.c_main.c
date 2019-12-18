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

/* Variables and functions */
 int /*<<< orphan*/  MX_LCK ; 
 int /*<<< orphan*/  O_RDWR ; 
 int /*<<< orphan*/  close (int) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char*,...) ; 
 int open (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf (char*) ; 
 int showLocksInRange (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stderr ; 

int main(int argc, char **argv){
  int fd;
  int cnt;

  if( argc!=2 ){
    fprintf(stderr, "Usage: %s FILENAME\n", argv[0]);
    return 1;
  }
  fd = open(argv[1], O_RDWR, 0);
  if( fd<0 ){
    fprintf(stderr, "%s: cannot open %s\n", argv[0], argv[1]);
    return 1;
  }
  cnt = showLocksInRange(fd, 0, MX_LCK);
  if( cnt==0 ) printf("no locks\n");  
  close(fd);
  return 0;
}