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
struct Option {char const* zName; } ;

/* Variables and functions */
 int /*<<< orphan*/  LSM_CONFIG_AUTOCHECKPOINT ; 
 int /*<<< orphan*/  LSM_CONFIG_BLOCK_SIZE ; 
 int LSM_OK ; 
 int atoi (char*) ; 
 int lsm_checkpoint (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lsm_close (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lsm_config (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int*) ; 
 int lsm_new (int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 int lsm_open (int /*<<< orphan*/ *,char const*) ; 
 int lsm_work (int /*<<< orphan*/ *,int,int,int /*<<< orphan*/ ) ; 
 int testArgSelect (TYPE_1__*,char*,char*,int*) ; 
 int /*<<< orphan*/  testPrintError (char*,int) ; 
 int /*<<< orphan*/  testPrintUsage (char*) ; 

int do_work(int nArg, char **azArg){
  struct Option {
    const char *zName;
  } aOpt [] = {
    { "-nmerge" },
    { "-nkb" },
    { 0 }
  };

  lsm_db *pDb;
  int rc;
  int i;
  const char *zDb;
  int nMerge = 1;
  int nKB = (1<<30);

  if( nArg==0 ) goto usage;
  zDb = azArg[nArg-1];
  for(i=0; i<(nArg-1); i++){
    int iSel;
    rc = testArgSelect(aOpt, "option", azArg[i], &iSel);
    if( rc ) return rc;
    switch( iSel ){
      case 0:
        i++;
        if( i==(nArg-1) ) goto usage;
        nMerge = atoi(azArg[i]);
        break;
      case 1:
        i++;
        if( i==(nArg-1) ) goto usage;
        nKB = atoi(azArg[i]);
        break;
    }
  }

  rc = lsm_new(0, &pDb);
  if( rc!=LSM_OK ){
    testPrintError("lsm_open(): rc=%d\n", rc);
  }else{
    rc = lsm_open(pDb, zDb);
    if( rc!=LSM_OK ){
      testPrintError("lsm_open(): rc=%d\n", rc);
    }else{
      int n = -1;
      lsm_config(pDb, LSM_CONFIG_BLOCK_SIZE, &n);
      n = n*2;
      lsm_config(pDb, LSM_CONFIG_AUTOCHECKPOINT, &n);

      rc = lsm_work(pDb, nMerge, nKB, 0);
      if( rc!=LSM_OK ){
        testPrintError("lsm_work(): rc=%d\n", rc);
      }
    }
  }
  if( rc==LSM_OK ){
    rc = lsm_checkpoint(pDb, 0);
  }

  lsm_close(pDb);
  return rc;

 usage:
  testPrintUsage("?-optimize? ?-n N? DATABASE");
  return -1;
}