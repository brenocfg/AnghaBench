#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int* abUnindexed; size_t nCol; char** azCol; } ;
typedef  TYPE_1__ Fts5Config ;

/* Variables and functions */
 char* FTS5_RANK_NAME ; 
 char* FTS5_ROWID_NAME ; 
 int SQLITE_ERROR ; 
 int SQLITE_OK ; 
 char* sqlite3_mprintf (char*,char*) ; 
 scalar_t__ sqlite3_stricmp (char*,char*) ; 

__attribute__((used)) static int fts5ConfigParseColumn(
  Fts5Config *p, 
  char *zCol, 
  char *zArg, 
  char **pzErr
){
  int rc = SQLITE_OK;
  if( 0==sqlite3_stricmp(zCol, FTS5_RANK_NAME) 
   || 0==sqlite3_stricmp(zCol, FTS5_ROWID_NAME) 
  ){
    *pzErr = sqlite3_mprintf("reserved fts5 column name: %s", zCol);
    rc = SQLITE_ERROR;
  }else if( zArg ){
    if( 0==sqlite3_stricmp(zArg, "unindexed") ){
      p->abUnindexed[p->nCol] = 1;
    }else{
      *pzErr = sqlite3_mprintf("unrecognized column option: %s", zArg);
      rc = SQLITE_ERROR;
    }
  }

  p->azCol[p->nCol++] = zCol;
  return rc;
}