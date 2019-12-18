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
struct TYPE_6__ {scalar_t__ rc; } ;
typedef  TYPE_1__ sqlite3rbu ;
struct TYPE_7__ {int nTblCol; char** azTblCol; scalar_t__ eType; scalar_t__* abIndexed; } ;
typedef  TYPE_2__ RbuObjIter ;

/* Variables and functions */
 scalar_t__ RBU_PK_EXTERNAL ; 
 scalar_t__ RBU_PK_NONE ; 
 scalar_t__ SQLITE_NOMEM ; 
 scalar_t__ SQLITE_OK ; 
 char* rbuMPrintf (TYPE_1__*,char*,char*,char const*) ; 
 char* sqlite3_mprintf (char*,char*,char const*,...) ; 

__attribute__((used)) static char *rbuObjIterGetOldlist(
  sqlite3rbu *p, 
  RbuObjIter *pIter,
  const char *zObj
){
  char *zList = 0;
  if( p->rc==SQLITE_OK && pIter->abIndexed ){
    const char *zS = "";
    int i;
    for(i=0; i<pIter->nTblCol; i++){
      if( pIter->abIndexed[i] ){
        const char *zCol = pIter->azTblCol[i];
        zList = sqlite3_mprintf("%z%s%s.\"%w\"", zList, zS, zObj, zCol);
      }else{
        zList = sqlite3_mprintf("%z%sNULL", zList, zS);
      }
      zS = ", ";
      if( zList==0 ){
        p->rc = SQLITE_NOMEM;
        break;
      }
    }

    /* For a table with implicit rowids, append "old._rowid_" to the list. */
    if( pIter->eType==RBU_PK_EXTERNAL || pIter->eType==RBU_PK_NONE ){
      zList = rbuMPrintf(p, "%z, %s._rowid_", zList, zObj);
    }
  }
  return zList;
}