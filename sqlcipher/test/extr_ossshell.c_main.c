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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 unsigned int FUZZ_SHOW_ERRORS ; 
 unsigned int FUZZ_SHOW_MAX_DELAY ; 
 unsigned int FUZZ_SQL_TRACE ; 
 int /*<<< orphan*/  LLVMFuzzerTestOneInput (int /*<<< orphan*/ *,size_t) ; 
 int /*<<< orphan*/  SEEK_END ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fflush (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * fopen (char const*,char*) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 int fread (int /*<<< orphan*/ *,size_t,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fseek (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 size_t ftell (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ossfuzz_set_debug_flags (unsigned int) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int /*<<< orphan*/ * realloc (int /*<<< orphan*/ *,size_t) ; 
 int /*<<< orphan*/  rewind (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  stdout ; 
 scalar_t__ strcmp (char const*,char*) ; 

int main(int argc, char **argv){
  FILE *in;
  int i;
  int nErr = 0;
  uint8_t *zBuf = 0;
  size_t sz;
  unsigned mDebug = 0;

  for(i=1; i<argc; i++){
    const char *zFilename = argv[i];
    if( zFilename[0]=='-' ){
      if( zFilename[1]=='-' ) zFilename++;
      if( strcmp(zFilename, "-show-errors")==0 ){
        mDebug |= FUZZ_SHOW_ERRORS;
        ossfuzz_set_debug_flags(mDebug);
      }else
      if( strcmp(zFilename, "-show-max-delay")==0 ){
        mDebug |= FUZZ_SHOW_MAX_DELAY;
        ossfuzz_set_debug_flags(mDebug);
      }else
      if( strcmp(zFilename, "-sql-trace")==0 ){
        mDebug |= FUZZ_SQL_TRACE;
        ossfuzz_set_debug_flags(mDebug);
      }else
      {
        printf("unknown option \"%s\"\n", argv[i]);
        printf("should be one of: --show-errors --show-max-delay"
               " --sql-trace\n");
        exit(1);
      }
      continue;
    }
    in = fopen(zFilename, "rb");
    if( in==0 ){
      fprintf(stderr, "cannot open \"%s\"\n", zFilename);
      nErr++;
      continue;
    }
    fseek(in, 0, SEEK_END);
    sz = ftell(in);
    rewind(in);
    zBuf = realloc(zBuf, sz);
    if( zBuf==0 ){
      fprintf(stderr, "cannot malloc() for %d bytes\n", (int)sz);
      exit(1);
    }
    if( fread(zBuf, sz, 1, in)!=1 ){
      fprintf(stderr, "cannot read %d bytes from \"%s\"\n",
                       (int)sz, zFilename);
      nErr++;
    }else{
      printf("%s... ", zFilename);
      if( mDebug ) printf("\n");
      fflush(stdout);
      (void)LLVMFuzzerTestOneInput(zBuf, sz);
      if( mDebug ) printf("%s: ", zFilename);
      printf("ok\n");
    }
    fclose(in);
  }
  free(zBuf);
  return nErr;
}