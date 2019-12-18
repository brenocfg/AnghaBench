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
typedef  int /*<<< orphan*/  sqlite3rbu ;
struct TYPE_3__ {int nTblCol; char** azTblCol; } ;
typedef  TYPE_1__ RbuObjIter ;

/* Variables and functions */
 char* rbuMPrintf (int /*<<< orphan*/ *,char*,char*,char const*,char const*) ; 

__attribute__((used)) static char *rbuObjIterGetCollist(
  sqlite3rbu *p,                  /* RBU object */
  RbuObjIter *pIter               /* Object iterator for column names */
){
  char *zList = 0;
  const char *zSep = "";
  int i;
  for(i=0; i<pIter->nTblCol; i++){
    const char *z = pIter->azTblCol[i];
    zList = rbuMPrintf(p, "%z%s\"%w\"", zList, zSep, z);
    zSep = ", ";
  }
  return zList;
}