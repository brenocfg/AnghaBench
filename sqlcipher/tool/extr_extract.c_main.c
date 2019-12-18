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
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  SEEK_SET ; 
 int atoi (char*) ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (char*,char*) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 size_t fread (char*,int,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fseek (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fwrite (char*,int,int,int /*<<< orphan*/ ) ; 
 char* malloc (int) ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  stdout ; 

int main(int argc, char **argv){
  FILE *f;
  char *zBuf;
  int ofst;
  int n;
  size_t got;

  if( argc!=4 ){
    fprintf(stderr, "Usage: %s FILENAME OFFSET AMOUNT\n", *argv);
    return 1;
  }
  f = fopen(argv[1], "rb");
  if( f==0 ){
    fprintf(stderr, "cannot open \"%s\"\n", argv[1]);
    return 1;
  }
  ofst = atoi(argv[2]);
  n = atoi(argv[3]);
  zBuf = malloc( n );
  if( zBuf==0 ){
    fprintf(stderr, "out of memory\n");
    return 1;
  }
  fseek(f, ofst, SEEK_SET);
  got = fread(zBuf, 1, n, f);
  fclose(f);
  if( got<n ){
    fprintf(stderr, "got only %d of %d bytes\n", got, n);
    return 1;
  }else{
    fwrite(zBuf, 1, n, stdout);
  }
  return 0;
}