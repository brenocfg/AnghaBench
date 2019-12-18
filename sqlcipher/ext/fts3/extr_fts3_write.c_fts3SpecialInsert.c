#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  sqlite3_value ;
struct TYPE_8__ {void* bNoIncrDoclist; void* nMaxPendingData; void* nNodeSize; } ;
typedef  TYPE_1__ Fts3Table ;

/* Variables and functions */
 int SQLITE_ERROR ; 
 int SQLITE_NOMEM ; 
 int SQLITE_OK ; 
 void* atoi (char const*) ; 
 int fts3DoAutoincrmerge (TYPE_1__*,char const*) ; 
 int fts3DoIncrmerge (TYPE_1__*,char const*) ; 
 int fts3DoIntegrityCheck (TYPE_1__*) ; 
 int fts3DoOptimize (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int fts3DoRebuild (TYPE_1__*) ; 
 scalar_t__ sqlite3_strnicmp (char const*,char*,int) ; 
 int sqlite3_value_bytes (int /*<<< orphan*/ *) ; 
 scalar_t__ sqlite3_value_text (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int fts3SpecialInsert(Fts3Table *p, sqlite3_value *pVal){
  int rc;                         /* Return Code */
  const char *zVal = (const char *)sqlite3_value_text(pVal);
  int nVal = sqlite3_value_bytes(pVal);

  if( !zVal ){
    return SQLITE_NOMEM;
  }else if( nVal==8 && 0==sqlite3_strnicmp(zVal, "optimize", 8) ){
    rc = fts3DoOptimize(p, 0);
  }else if( nVal==7 && 0==sqlite3_strnicmp(zVal, "rebuild", 7) ){
    rc = fts3DoRebuild(p);
  }else if( nVal==15 && 0==sqlite3_strnicmp(zVal, "integrity-check", 15) ){
    rc = fts3DoIntegrityCheck(p);
  }else if( nVal>6 && 0==sqlite3_strnicmp(zVal, "merge=", 6) ){
    rc = fts3DoIncrmerge(p, &zVal[6]);
  }else if( nVal>10 && 0==sqlite3_strnicmp(zVal, "automerge=", 10) ){
    rc = fts3DoAutoincrmerge(p, &zVal[10]);
#ifdef SQLITE_TEST
  }else if( nVal>9 && 0==sqlite3_strnicmp(zVal, "nodesize=", 9) ){
    p->nNodeSize = atoi(&zVal[9]);
    rc = SQLITE_OK;
  }else if( nVal>11 && 0==sqlite3_strnicmp(zVal, "maxpending=", 9) ){
    p->nMaxPendingData = atoi(&zVal[11]);
    rc = SQLITE_OK;
  }else if( nVal>21 && 0==sqlite3_strnicmp(zVal, "test-no-incr-doclist=", 21) ){
    p->bNoIncrDoclist = atoi(&zVal[21]);
    rc = SQLITE_OK;
#endif
  }else{
    rc = SQLITE_ERROR;
  }

  return rc;
}