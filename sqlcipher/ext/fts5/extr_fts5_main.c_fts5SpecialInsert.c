#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  sqlite3_value ;
struct TYPE_9__ {scalar_t__ eContent; void* bPrefixIndex; } ;
struct TYPE_7__ {TYPE_3__* pConfig; int /*<<< orphan*/  pIndex; } ;
struct TYPE_8__ {int /*<<< orphan*/  pStorage; TYPE_1__ p; } ;
typedef  TYPE_2__ Fts5FullTable ;
typedef  TYPE_3__ Fts5Config ;

/* Variables and functions */
 scalar_t__ FTS5_CONTENT_NONE ; 
 scalar_t__ FTS5_CONTENT_NORMAL ; 
 int SQLITE_ERROR ; 
 int SQLITE_OK ; 
 int /*<<< orphan*/  fts5SetVtabError (TYPE_2__*,char*) ; 
 int sqlite3Fts5ConfigSetValue (TYPE_3__*,char const*,int /*<<< orphan*/ *,int*) ; 
 int sqlite3Fts5IndexLoadConfig (int /*<<< orphan*/ ) ; 
 int sqlite3Fts5StorageConfigValue (int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int sqlite3Fts5StorageDeleteAll (int /*<<< orphan*/ ) ; 
 int sqlite3Fts5StorageIntegrity (int /*<<< orphan*/ ) ; 
 int sqlite3Fts5StorageMerge (int /*<<< orphan*/ ,int) ; 
 int sqlite3Fts5StorageOptimize (int /*<<< orphan*/ ) ; 
 int sqlite3Fts5StorageRebuild (int /*<<< orphan*/ ) ; 
 scalar_t__ sqlite3_stricmp (char*,char const*) ; 
 void* sqlite3_value_int (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int fts5SpecialInsert(
  Fts5FullTable *pTab,            /* Fts5 table object */
  const char *zCmd,               /* Text inserted into table-name column */
  sqlite3_value *pVal             /* Value inserted into rank column */
){
  Fts5Config *pConfig = pTab->p.pConfig;
  int rc = SQLITE_OK;
  int bError = 0;

  if( 0==sqlite3_stricmp("delete-all", zCmd) ){
    if( pConfig->eContent==FTS5_CONTENT_NORMAL ){
      fts5SetVtabError(pTab, 
          "'delete-all' may only be used with a "
          "contentless or external content fts5 table"
      );
      rc = SQLITE_ERROR;
    }else{
      rc = sqlite3Fts5StorageDeleteAll(pTab->pStorage);
    }
  }else if( 0==sqlite3_stricmp("rebuild", zCmd) ){
    if( pConfig->eContent==FTS5_CONTENT_NONE ){
      fts5SetVtabError(pTab, 
          "'rebuild' may not be used with a contentless fts5 table"
      );
      rc = SQLITE_ERROR;
    }else{
      rc = sqlite3Fts5StorageRebuild(pTab->pStorage);
    }
  }else if( 0==sqlite3_stricmp("optimize", zCmd) ){
    rc = sqlite3Fts5StorageOptimize(pTab->pStorage);
  }else if( 0==sqlite3_stricmp("merge", zCmd) ){
    int nMerge = sqlite3_value_int(pVal);
    rc = sqlite3Fts5StorageMerge(pTab->pStorage, nMerge);
  }else if( 0==sqlite3_stricmp("integrity-check", zCmd) ){
    rc = sqlite3Fts5StorageIntegrity(pTab->pStorage);
#ifdef SQLITE_DEBUG
  }else if( 0==sqlite3_stricmp("prefix-index", zCmd) ){
    pConfig->bPrefixIndex = sqlite3_value_int(pVal);
#endif
  }else{
    rc = sqlite3Fts5IndexLoadConfig(pTab->p.pIndex);
    if( rc==SQLITE_OK ){
      rc = sqlite3Fts5ConfigSetValue(pTab->p.pConfig, zCmd, pVal, &bError);
    }
    if( rc==SQLITE_OK ){
      if( bError ){
        rc = SQLITE_ERROR;
      }else{
        rc = sqlite3Fts5StorageConfigValue(pTab->pStorage, zCmd, pVal, 0);
      }
    }
  }
  return rc;
}