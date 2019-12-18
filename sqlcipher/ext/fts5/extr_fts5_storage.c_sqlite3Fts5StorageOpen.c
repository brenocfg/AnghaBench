#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int sqlite3_int64 ;
typedef  int /*<<< orphan*/  i64 ;
struct TYPE_10__ {int nCol; scalar_t__ eContent; scalar_t__ bColumnsize; } ;
struct TYPE_9__ {int /*<<< orphan*/ * pIndex; TYPE_2__* pConfig; int /*<<< orphan*/ * aTotalSize; } ;
typedef  TYPE_1__ Fts5Storage ;
typedef  int /*<<< orphan*/  Fts5Index ;
typedef  TYPE_2__ Fts5Config ;

/* Variables and functions */
 scalar_t__ FTS5_CONTENT_NORMAL ; 
 int /*<<< orphan*/  FTS5_CURRENT_VERSION ; 
 int SQLITE_NOMEM ; 
 int SQLITE_OK ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,size_t) ; 
 int sqlite3Fts5CreateTable (TYPE_2__*,char*,char*,int,char**) ; 
 int /*<<< orphan*/  sqlite3Fts5StorageClose (TYPE_1__*) ; 
 int sqlite3Fts5StorageConfigValue (TYPE_1__*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sqlite3_free (char*) ; 
 char* sqlite3_malloc64 (int) ; 
 int /*<<< orphan*/  sqlite3_snprintf (int,char*,char*,...) ; 
 scalar_t__ strlen (char*) ; 

int sqlite3Fts5StorageOpen(
  Fts5Config *pConfig, 
  Fts5Index *pIndex, 
  int bCreate, 
  Fts5Storage **pp,
  char **pzErr                    /* OUT: Error message */
){
  int rc = SQLITE_OK;
  Fts5Storage *p;                 /* New object */
  sqlite3_int64 nByte;            /* Bytes of space to allocate */

  nByte = sizeof(Fts5Storage)               /* Fts5Storage object */
        + pConfig->nCol * sizeof(i64);      /* Fts5Storage.aTotalSize[] */
  *pp = p = (Fts5Storage*)sqlite3_malloc64(nByte);
  if( !p ) return SQLITE_NOMEM;

  memset(p, 0, (size_t)nByte);
  p->aTotalSize = (i64*)&p[1];
  p->pConfig = pConfig;
  p->pIndex = pIndex;

  if( bCreate ){
    if( pConfig->eContent==FTS5_CONTENT_NORMAL ){
      int nDefn = 32 + pConfig->nCol*10;
      char *zDefn = sqlite3_malloc64(32 + (sqlite3_int64)pConfig->nCol * 10);
      if( zDefn==0 ){
        rc = SQLITE_NOMEM;
      }else{
        int i;
        int iOff;
        sqlite3_snprintf(nDefn, zDefn, "id INTEGER PRIMARY KEY");
        iOff = (int)strlen(zDefn);
        for(i=0; i<pConfig->nCol; i++){
          sqlite3_snprintf(nDefn-iOff, &zDefn[iOff], ", c%d", i);
          iOff += (int)strlen(&zDefn[iOff]);
        }
        rc = sqlite3Fts5CreateTable(pConfig, "content", zDefn, 0, pzErr);
      }
      sqlite3_free(zDefn);
    }

    if( rc==SQLITE_OK && pConfig->bColumnsize ){
      rc = sqlite3Fts5CreateTable(
          pConfig, "docsize", "id INTEGER PRIMARY KEY, sz BLOB", 0, pzErr
      );
    }
    if( rc==SQLITE_OK ){
      rc = sqlite3Fts5CreateTable(
          pConfig, "config", "k PRIMARY KEY, v", 1, pzErr
      );
    }
    if( rc==SQLITE_OK ){
      rc = sqlite3Fts5StorageConfigValue(p, "version", 0, FTS5_CURRENT_VERSION);
    }
  }

  if( rc ){
    sqlite3Fts5StorageClose(p);
    *pp = 0;
  }
  return rc;
}