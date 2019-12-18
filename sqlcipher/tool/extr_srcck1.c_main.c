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
 unsigned int findAllSideEffects (char*) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  free (char*) ; 
 char* readFile (char*) ; 
 int /*<<< orphan*/  stderr ; 

int main(int argc, char **argv){
  char *z;
  unsigned int nErr = 0;
  if( argc!=2 ){
    fprintf(stderr, "Usage: %s FILENAME\n", argv[0]);
    return 1;
  }
  z = readFile(argv[1]);
  nErr = findAllSideEffects(z);
  free(z);
  if( nErr ){
    fprintf(stderr, "Found %u undesirable side-effects\n", nErr);
    return 1;
  }
  return 0; 
}