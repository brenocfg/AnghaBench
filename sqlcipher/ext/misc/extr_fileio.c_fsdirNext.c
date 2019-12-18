#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_6__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct dirent {char* d_name; } ;
typedef  int /*<<< orphan*/  sqlite3_vtab_cursor ;
typedef  int sqlite3_int64 ;
typedef  int /*<<< orphan*/  mode_t ;
struct TYPE_9__ {int /*<<< orphan*/  st_mode; } ;
struct TYPE_7__ {int iLvl; int nLvl; scalar_t__ zPath; TYPE_6__ sStat; TYPE_2__* aLvl; int /*<<< orphan*/  iRowid; } ;
typedef  TYPE_1__ fsdir_cursor ;
struct TYPE_8__ {scalar_t__ pDir; scalar_t__ zDir; } ;
typedef  TYPE_2__ FsdirLevel ;

/* Variables and functions */
 int SQLITE_ERROR ; 
 int SQLITE_NOMEM ; 
 int SQLITE_OK ; 
 scalar_t__ S_ISDIR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  closedir (scalar_t__) ; 
 scalar_t__ fileLinkStat (scalar_t__,TYPE_6__*) ; 
 int /*<<< orphan*/  fsdirSetErrmsg (TYPE_1__*,char*,scalar_t__) ; 
 int /*<<< orphan*/  memset (TYPE_2__*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ opendir (scalar_t__) ; 
 struct dirent* readdir (scalar_t__) ; 
 int /*<<< orphan*/  sqlite3_free (scalar_t__) ; 
 scalar_t__ sqlite3_mprintf (char*,scalar_t__,char*) ; 
 scalar_t__ sqlite3_realloc64 (TYPE_2__*,int) ; 

__attribute__((used)) static int fsdirNext(sqlite3_vtab_cursor *cur){
  fsdir_cursor *pCur = (fsdir_cursor*)cur;
  mode_t m = pCur->sStat.st_mode;

  pCur->iRowid++;
  if( S_ISDIR(m) ){
    /* Descend into this directory */
    int iNew = pCur->iLvl + 1;
    FsdirLevel *pLvl;
    if( iNew>=pCur->nLvl ){
      int nNew = iNew+1;
      sqlite3_int64 nByte = nNew*sizeof(FsdirLevel);
      FsdirLevel *aNew = (FsdirLevel*)sqlite3_realloc64(pCur->aLvl, nByte);
      if( aNew==0 ) return SQLITE_NOMEM;
      memset(&aNew[pCur->nLvl], 0, sizeof(FsdirLevel)*(nNew-pCur->nLvl));
      pCur->aLvl = aNew;
      pCur->nLvl = nNew;
    }
    pCur->iLvl = iNew;
    pLvl = &pCur->aLvl[iNew];
    
    pLvl->zDir = pCur->zPath;
    pCur->zPath = 0;
    pLvl->pDir = opendir(pLvl->zDir);
    if( pLvl->pDir==0 ){
      fsdirSetErrmsg(pCur, "cannot read directory: %s", pCur->zPath);
      return SQLITE_ERROR;
    }
  }

  while( pCur->iLvl>=0 ){
    FsdirLevel *pLvl = &pCur->aLvl[pCur->iLvl];
    struct dirent *pEntry = readdir(pLvl->pDir);
    if( pEntry ){
      if( pEntry->d_name[0]=='.' ){
       if( pEntry->d_name[1]=='.' && pEntry->d_name[2]=='\0' ) continue;
       if( pEntry->d_name[1]=='\0' ) continue;
      }
      sqlite3_free(pCur->zPath);
      pCur->zPath = sqlite3_mprintf("%s/%s", pLvl->zDir, pEntry->d_name);
      if( pCur->zPath==0 ) return SQLITE_NOMEM;
      if( fileLinkStat(pCur->zPath, &pCur->sStat) ){
        fsdirSetErrmsg(pCur, "cannot stat file: %s", pCur->zPath);
        return SQLITE_ERROR;
      }
      return SQLITE_OK;
    }
    closedir(pLvl->pDir);
    sqlite3_free(pLvl->zDir);
    pLvl->pDir = 0;
    pLvl->zDir = 0;
    pCur->iLvl--;
  }

  /* EOF */
  sqlite3_free(pCur->zPath);
  pCur->zPath = 0;
  return SQLITE_OK;
}