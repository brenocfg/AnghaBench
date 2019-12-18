#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  hook ;
typedef  int /*<<< orphan*/  TestDb ;
struct TYPE_7__ {int member_1; int member_2; int member_3; int member_4; int /*<<< orphan*/  member_0; } ;
struct TYPE_6__ {int /*<<< orphan*/  pOut; } ;
typedef  TYPE_1__ InsertWriteHook ;
typedef  TYPE_2__ DatasourceDefn ;
typedef  int /*<<< orphan*/  Datasource ;

/* Variables and functions */
 int /*<<< orphan*/  TEST_DATASOURCE_RANDOM ; 
 int /*<<< orphan*/  do_insert_work_hook ; 
 int /*<<< orphan*/  do_insert_write_hook ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  flushHook (TYPE_1__*) ; 
 int /*<<< orphan*/  fopen (char*,char*) ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  tdb_close (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tdb_lsm_config_work_hook (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tdb_lsm_env () ; 
 int tdb_lsm_open (char const*,char*,int,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  tdb_lsm_write_hook (int /*<<< orphan*/ *,int /*<<< orphan*/ ,void*) ; 
 int tdb_open (char const*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  tdb_write (int /*<<< orphan*/ *,void*,int,void*,int) ; 
 int /*<<< orphan*/  testDatasourceEntry (int /*<<< orphan*/ *,int,void**,int*,void**,int*) ; 
 int /*<<< orphan*/  testDatasourceFree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * testDatasourceNew (TYPE_2__*) ; 
 int /*<<< orphan*/  testMallocInstall (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  testMallocUninstall (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  testPrintError (char*,...) ; 

__attribute__((used)) static int do_insert(int nArg, char **azArg){
  const char *zDb = "lsm";
  TestDb *pDb = 0;
  int i;
  int rc;
  const int nRow = 1 * 1000 * 1000;

  DatasourceDefn defn = { TEST_DATASOURCE_RANDOM, 8, 15, 80, 150 };
  Datasource *pData = 0;

  if( nArg>1 ){
    testPrintError("Usage: insert ?DATABASE?\n");
    return 1;
  }
  if( nArg==1 ){ zDb = azArg[0]; }

  testMallocUninstall(tdb_lsm_env());
  for(i=0; zDb[i] && zDb[i]!='='; i++);
  if( zDb[i] ){
    rc = tdb_lsm_open(zDb, "testdb.lsm", 1, &pDb);
  }else{
    rc = tdb_open(zDb, 0, 1, &pDb);
  }

  if( rc!=0 ){
    testPrintError("Error opening db \"%s\": %d\n", zDb, rc);
  }else{
    InsertWriteHook hook;
    memset(&hook, 0, sizeof(hook));
    hook.pOut = fopen("writelog.txt", "w");

    pData = testDatasourceNew(&defn);
    tdb_lsm_config_work_hook(pDb, do_insert_work_hook, 0);
    tdb_lsm_write_hook(pDb, do_insert_write_hook, (void *)&hook);

    if( rc==0 ){
      for(i=0; i<nRow; i++){
        void *pKey; int nKey;     /* Database key to insert */
        void *pVal; int nVal;     /* Database value to insert */
        testDatasourceEntry(pData, i, &pKey, &nKey, &pVal, &nVal);
        tdb_write(pDb, pKey, nKey, pVal, nVal);
      }
    }

    testDatasourceFree(pData);
    tdb_close(pDb);
    flushHook(&hook);
    fclose(hook.pOut);
  }
  testMallocInstall(tdb_lsm_env());

  return rc;
}