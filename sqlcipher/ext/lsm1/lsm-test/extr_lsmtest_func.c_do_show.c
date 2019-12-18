#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct Option   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  lsm_db ;
struct Option {char const* zName; int bConfig; int eOpt; } ;

/* Variables and functions */
 int LSM_CONFIG_BLOCK_SIZE ; 
 int LSM_CONFIG_PAGE_SIZE ; 
#define  LSM_INFO_ARRAY_PAGES 133 
#define  LSM_INFO_ARRAY_STRUCTURE 132 
#define  LSM_INFO_DB_STRUCTURE 131 
#define  LSM_INFO_FREELIST 130 
#define  LSM_INFO_PAGE_ASCII_DUMP 129 
#define  LSM_INFO_PAGE_HEX_DUMP 128 
 int LSM_OK ; 
 int /*<<< orphan*/  assert (int) ; 
 unsigned int atoi (char*) ; 
 int /*<<< orphan*/  fflush (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lsm_close (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lsm_config (int /*<<< orphan*/ *,int,int*) ; 
 int /*<<< orphan*/  lsm_free (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  lsm_get_env (int /*<<< orphan*/ *) ; 
 int lsm_info (int /*<<< orphan*/ *,int,...) ; 
 int lsm_new (int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 int lsm_open (int /*<<< orphan*/ *,char const*) ; 
 scalar_t__ memcmp (char*,char*,int) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int /*<<< orphan*/  stdout ; 
 int strlen (char*) ; 
 int /*<<< orphan*/  tdb_lsm_configure (int /*<<< orphan*/ *,char const*) ; 
 int testArgSelect (TYPE_1__*,char*,char*,int*) ; 
 int /*<<< orphan*/  testPrintError (char*,int) ; 
 int /*<<< orphan*/  testPrintUsage (char*) ; 

int do_show(int nArg, char **azArg){
  lsm_db *pDb;
  int rc;
  const char *zDb;

  int eOpt = LSM_INFO_DB_STRUCTURE;
  unsigned int iPg = 0;
  int bConfig = 0;
  const char *zConfig = "";

  struct Option {
    const char *zName;
    int bConfig;
    int eOpt;
  } aOpt [] = { 
    { "array",       0, LSM_INFO_ARRAY_STRUCTURE },
    { "array-pages", 0, LSM_INFO_ARRAY_PAGES },
    { "blocksize",   1, LSM_CONFIG_BLOCK_SIZE },
    { "pagesize",    1, LSM_CONFIG_PAGE_SIZE },
    { "freelist",    0, LSM_INFO_FREELIST },
    { "page-ascii",  0, LSM_INFO_PAGE_ASCII_DUMP },
    { "page-hex",    0, LSM_INFO_PAGE_HEX_DUMP },
    { 0, 0 } 
  };

  char *z = 0; 
  int iDb = 0;                    /* Index of DATABASE in azArg[] */

  /* Check if there is a "-config" option: */
  if( nArg>2 && strlen(azArg[0])>1 
   && memcmp(azArg[0], "-config", strlen(azArg[0]))==0
  ){
    zConfig = azArg[1];
    iDb = 2;
  }
  if( nArg<(iDb+1) ) goto usage;

  if( nArg>(iDb+1) ){
    rc = testArgSelect(aOpt, "option", azArg[iDb+1], &eOpt);
    if( rc!=0 ) return rc;
    bConfig = aOpt[eOpt].bConfig;
    eOpt = aOpt[eOpt].eOpt;
    if( (bConfig==0 && eOpt==LSM_INFO_FREELIST)
     || (bConfig==1 && eOpt==LSM_CONFIG_BLOCK_SIZE)
     || (bConfig==1 && eOpt==LSM_CONFIG_PAGE_SIZE)
    ){
      if( nArg!=(iDb+2) ) goto usage;
    }else{
      if( nArg!=(iDb+3) ) goto usage;
      iPg = atoi(azArg[iDb+2]);
    }
  }
  zDb = azArg[iDb];

  rc = lsm_new(0, &pDb);
  tdb_lsm_configure(pDb, zConfig);
  if( rc!=LSM_OK ){
    testPrintError("lsm_new(): rc=%d\n", rc);
  }else{
    rc = lsm_open(pDb, zDb);
    if( rc!=LSM_OK ){
      testPrintError("lsm_open(): rc=%d\n", rc);
    }
  }

  if( rc==LSM_OK ){
    if( bConfig==0 ){
      switch( eOpt ){
        case LSM_INFO_DB_STRUCTURE:
        case LSM_INFO_FREELIST:
          rc = lsm_info(pDb, eOpt, &z);
          break;
        case LSM_INFO_ARRAY_STRUCTURE:
        case LSM_INFO_ARRAY_PAGES:
        case LSM_INFO_PAGE_ASCII_DUMP:
        case LSM_INFO_PAGE_HEX_DUMP:
          rc = lsm_info(pDb, eOpt, iPg, &z);
          break;
        default:
          assert( !"no chance" );
      }

      if( rc==LSM_OK ){
        printf("%s\n", z ? z : "");
        fflush(stdout);
      }
      lsm_free(lsm_get_env(pDb), z);
    }else{
      int iRes = -1;
      lsm_config(pDb, eOpt, &iRes);
      printf("%d\n", iRes);
      fflush(stdout);
    }
  }

  lsm_close(pDb);
  return rc;

 usage:
  testPrintUsage("DATABASE ?array|page-ascii|page-hex PGNO?");
  return -1;
}