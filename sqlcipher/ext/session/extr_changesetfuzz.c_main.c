#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
typedef  int sqlite3_int64 ;
struct TYPE_5__ {int nGroup; int /*<<< orphan*/ * apGroup; } ;
typedef  TYPE_1__ FuzzChangeset ;

/* Variables and functions */
 int SQLITE_NOMEM ; 
 int SQLITE_OK ; 
 int atoi (char*) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,int) ; 
 int fuzzDoOneFuzz (char*,int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  fuzzFree (int /*<<< orphan*/ *) ; 
 scalar_t__ fuzzMalloc (int) ; 
 int fuzzParseChangeset (void*,int,TYPE_1__*) ; 
 int /*<<< orphan*/  fuzzPrintGroup (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fuzzRandomSeed (unsigned int) ; 
 int /*<<< orphan*/  fuzzReadFile (char const*,int*,void**) ; 
 int /*<<< orphan*/  sqlite3_free (char*) ; 
 char* sqlite3_mprintf (char*,char const*,int) ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  usage (char*) ; 

int main(int argc, char **argv){
  int nRepeat = 0;                /* Number of output files */
  int iSeed = 0;                  /* Value of PRNG seed */
  const char *zInput;             /* Name of input file */
  void *pChangeset = 0;           /* Input changeset */
  int nChangeset = 0;             /* Size of input changeset in bytes */
  int i;                          /* Current output file */
  FuzzChangeset changeset;        /* Partially parsed changeset */
  int rc;
  u8 *pBuf = 0;

  if( argc!=4 && argc!=2 ) usage(argv[0]);
  zInput = argv[1];

  fuzzReadFile(zInput, &nChangeset, &pChangeset);
  rc = fuzzParseChangeset(pChangeset, nChangeset, &changeset);

  if( rc==SQLITE_OK ){
    if( argc==2 ){
      for(i=0; i<changeset.nGroup; i++){
        fuzzPrintGroup(&changeset, changeset.apGroup[i]);
      }
    }else{
      pBuf = (u8*)fuzzMalloc((sqlite3_int64)nChangeset*2 + 1024);
      if( pBuf==0 ){
        rc = SQLITE_NOMEM;
      }else{
        iSeed = atoi(argv[2]);
        nRepeat = atoi(argv[3]);
        fuzzRandomSeed((unsigned int)iSeed);
        for(i=0; rc==SQLITE_OK && i<nRepeat; i++){
          char *zOut = sqlite3_mprintf("%s-%d", zInput, i);
          rc = fuzzDoOneFuzz(zOut, pBuf, &changeset);
          sqlite3_free(zOut);
        }
        fuzzFree(pBuf);
      }
    }
  }

  if( rc!=SQLITE_OK ){
    fprintf(stderr, "error while processing changeset: %d\n", rc);
  }

  return rc;
}