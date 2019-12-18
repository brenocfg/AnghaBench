#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  sqlite3_vtab_cursor ;
typedef  int /*<<< orphan*/  sqlite3_value ;
struct TYPE_4__ {char const* zBase; int nBase; scalar_t__ zPath; int /*<<< orphan*/  sStat; } ;
typedef  TYPE_1__ fsdir_cursor ;

/* Variables and functions */
 int SQLITE_ERROR ; 
 int SQLITE_NOMEM ; 
 int SQLITE_OK ; 
 int /*<<< orphan*/  assert (int) ; 
 scalar_t__ fileLinkStat (scalar_t__,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fsdirResetCursor (TYPE_1__*) ; 
 int /*<<< orphan*/  fsdirSetErrmsg (TYPE_1__*,char*,...) ; 
 void* sqlite3_mprintf (char*,char const*,...) ; 
 scalar_t__ sqlite3_value_text (int /*<<< orphan*/ *) ; 
 scalar_t__ strlen (char const*) ; 

__attribute__((used)) static int fsdirFilter(
  sqlite3_vtab_cursor *cur, 
  int idxNum, const char *idxStr,
  int argc, sqlite3_value **argv
){
  const char *zDir = 0;
  fsdir_cursor *pCur = (fsdir_cursor*)cur;
  (void)idxStr;
  fsdirResetCursor(pCur);

  if( idxNum==0 ){
    fsdirSetErrmsg(pCur, "table function fsdir requires an argument");
    return SQLITE_ERROR;
  }

  assert( argc==idxNum && (argc==1 || argc==2) );
  zDir = (const char*)sqlite3_value_text(argv[0]);
  if( zDir==0 ){
    fsdirSetErrmsg(pCur, "table function fsdir requires a non-NULL argument");
    return SQLITE_ERROR;
  }
  if( argc==2 ){
    pCur->zBase = (const char*)sqlite3_value_text(argv[1]);
  }
  if( pCur->zBase ){
    pCur->nBase = (int)strlen(pCur->zBase)+1;
    pCur->zPath = sqlite3_mprintf("%s/%s", pCur->zBase, zDir);
  }else{
    pCur->zPath = sqlite3_mprintf("%s", zDir);
  }

  if( pCur->zPath==0 ){
    return SQLITE_NOMEM;
  }
  if( fileLinkStat(pCur->zPath, &pCur->sStat) ){
    fsdirSetErrmsg(pCur, "cannot stat file: %s", pCur->zPath);
    return SQLITE_ERROR;
  }

  return SQLITE_OK;
}