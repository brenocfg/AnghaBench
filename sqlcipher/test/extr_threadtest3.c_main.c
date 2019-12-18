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
typedef  int /*<<< orphan*/  aTest ;

/* Variables and functions */
 int /*<<< orphan*/  SQLITE_CONFIG_MULTITHREAD ; 
 int SQLITE_OK ; 
 int /*<<< orphan*/  cgt_pager_1 ; 
 int /*<<< orphan*/  checkpoint_starvation_1 ; 
 int /*<<< orphan*/  checkpoint_starvation_2 ; 
 int /*<<< orphan*/  create_drop_index_1 ; 
 int /*<<< orphan*/  dynamic_triggers ; 
 int /*<<< orphan*/  fflush (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  lookaside1 ; 
 int nGlobalErr ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int /*<<< orphan*/  sqlite3_config (int /*<<< orphan*/ ) ; 
 int sqlite3_multiplex_initialize (int /*<<< orphan*/ ,int) ; 
 scalar_t__ sqlite3_strglob (char const*,char const*) ; 
 scalar_t__ sqlite3_stricmp (char const*,char*) ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  stdout ; 
 int /*<<< orphan*/  stress1 ; 
 int /*<<< orphan*/  stress2 ; 
 void stub1 (int) ; 
 int /*<<< orphan*/  vacuum1 ; 
 int /*<<< orphan*/  walthread1 ; 
 int /*<<< orphan*/  walthread2 ; 
 int /*<<< orphan*/  walthread3 ; 
 int /*<<< orphan*/  walthread4 ; 
 int /*<<< orphan*/  walthread5 ; 

int main(int argc, char **argv){
  struct ThreadTest {
    void (*xTest)(int);   /* Routine for running this test */
    const char *zTest;    /* Name of this test */
    int nMs;              /* How long to run this test, in milliseconds */
  } aTest[] = {
    { walthread1, "walthread1", 20000 },
    { walthread2, "walthread2", 20000 },
    { walthread3, "walthread3", 20000 },
    { walthread4, "walthread4", 20000 },
    { walthread5, "walthread5",  1000 },
    
    { cgt_pager_1,      "cgt_pager_1", 0 },
    { dynamic_triggers, "dynamic_triggers", 20000 },

    { checkpoint_starvation_1, "checkpoint_starvation_1", 10000 },
    { checkpoint_starvation_2, "checkpoint_starvation_2", 10000 },

    { create_drop_index_1, "create_drop_index_1", 10000 },
    { lookaside1,          "lookaside1", 10000 },
    { vacuum1,             "vacuum1", 10000 },
    { stress1,             "stress1", 10000 },
    { stress2,             "stress2", 60000 },
  };
  static char *substArgv[] = { 0, "*", 0 };
  int i, iArg;
  int nTestfound = 0;

  sqlite3_config(SQLITE_CONFIG_MULTITHREAD);
  if( argc<2 ){
    argc = 2;
    argv = substArgv;
  }

  /* Loop through the command-line arguments to ensure that each argument
  ** selects at least one test. If not, assume there is a typo on the 
  ** command-line and bail out with the usage message.  */
  for(iArg=1; iArg<argc; iArg++){
    const char *zArg = argv[iArg];
    if( zArg[0]=='-' ){
      if( sqlite3_stricmp(zArg, "-multiplexor")==0 ){
        /* Install the multiplexor VFS as the default */
        int rc = sqlite3_multiplex_initialize(0, 1);
        if( rc!=SQLITE_OK ){
          fprintf(stderr, "Failed to install multiplexor VFS (%d)\n", rc);
          return 253;
        }
      }
      else {
        goto usage;
      }

      continue;
    }

    for(i=0; i<sizeof(aTest)/sizeof(aTest[0]); i++){
      if( sqlite3_strglob(zArg, aTest[i].zTest)==0 ) break;
    }
    if( i>=sizeof(aTest)/sizeof(aTest[0]) ) goto usage;   
  }

  for(iArg=1; iArg<argc; iArg++){
    if( argv[iArg][0]=='-' ) continue;
    for(i=0; i<sizeof(aTest)/sizeof(aTest[0]); i++){
      char const *z = aTest[i].zTest;
      if( sqlite3_strglob(argv[iArg],z)==0 ){
        printf("Running %s for %d seconds...\n", z, aTest[i].nMs/1000);
        fflush(stdout);
        aTest[i].xTest(aTest[i].nMs);
        nTestfound++;
      }
    }
  }
  if( nTestfound==0 ) goto usage;

  printf("%d errors out of %d tests\n", nGlobalErr, nTestfound);
  return (nGlobalErr>0 ? 255 : 0);

 usage:
  printf("Usage: %s [-multiplexor] [testname|testprefix*]...\n", argv[0]);
  printf("Available tests are:\n");
  for(i=0; i<sizeof(aTest)/sizeof(aTest[0]); i++){
    printf("   %s\n", aTest[i].zTest);
  }

  return 254;
}