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
 int /*<<< orphan*/  SEEK_END ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (char const*,char*) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 size_t fread (char*,int,long,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fseek (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 long ftell (int /*<<< orphan*/ *) ; 
 char* malloc (long) ; 
 int /*<<< orphan*/  rewind (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stderr ; 

__attribute__((used)) static char *readFile(const char *zFilename){
  FILE *in;
  char *z;
  long n;
  size_t got;

  in = fopen(zFilename, "rb");
  if( in==0 ){
    fprintf(stderr, "unable to open '%s' for reading\n", zFilename);
    exit(1);
  }
  fseek(in, 0, SEEK_END);
  n = ftell(in);
  rewind(in);
  z = malloc( n+1 );
  if( z==0 ){
    fprintf(stderr, "cannot allocate %d bytes to store '%s'\n", 
            (int)(n+1), zFilename);
    exit(1);
  }
  got = fread(z, 1, n, in);
  fclose(in);
  if( got!=(size_t)n ){
    fprintf(stderr, "only read %d of %d bytes from '%s'\n",
           (int)got, (int)n, zFilename);
    exit(1);
  }
  z[n] = 0;
  return z;
}