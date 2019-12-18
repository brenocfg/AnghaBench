#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {scalar_t__ rc; } ;
typedef  TYPE_1__ sqlite3rbu ;
struct TYPE_8__ {int nTblCol; size_t* aiSrcOrder; int /*<<< orphan*/ * azTblCol; } ;
typedef  TYPE_2__ RbuObjIter ;

/* Variables and functions */
 scalar_t__ SQLITE_OK ; 
 int /*<<< orphan*/  rbuBadControlError (TYPE_1__*) ; 
 char* rbuMPrintf (TYPE_1__*,char*,char*,char const*,int /*<<< orphan*/ ,int,...) ; 
 scalar_t__ strlen (char const*) ; 

__attribute__((used)) static char *rbuObjIterGetSetlist(
  sqlite3rbu *p,
  RbuObjIter *pIter,
  const char *zMask
){
  char *zList = 0;
  if( p->rc==SQLITE_OK ){
    int i;

    if( (int)strlen(zMask)!=pIter->nTblCol ){
      rbuBadControlError(p);
    }else{
      const char *zSep = "";
      for(i=0; i<pIter->nTblCol; i++){
        char c = zMask[pIter->aiSrcOrder[i]];
        if( c=='x' ){
          zList = rbuMPrintf(p, "%z%s\"%w\"=?%d", 
              zList, zSep, pIter->azTblCol[i], i+1
          );
          zSep = ", ";
        }
        else if( c=='d' ){
          zList = rbuMPrintf(p, "%z%s\"%w\"=rbu_delta(\"%w\", ?%d)", 
              zList, zSep, pIter->azTblCol[i], pIter->azTblCol[i], i+1
          );
          zSep = ", ";
        }
        else if( c=='f' ){
          zList = rbuMPrintf(p, "%z%s\"%w\"=rbu_fossil_delta(\"%w\", ?%d)", 
              zList, zSep, pIter->azTblCol[i], pIter->azTblCol[i], i+1
          );
          zSep = ", ";
        }
      }
    }
  }
  return zList;
}