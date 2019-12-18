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
struct TYPE_3__ {int /*<<< orphan*/  zExpr; scalar_t__ bDesc; } ;
typedef  TYPE_1__ CidxColumn ;

/* Variables and functions */
 char* cidxMprintf (int*,char*,char*,char const*,int /*<<< orphan*/ ,...) ; 

__attribute__((used)) static char *cidxWhere(
  int *pRc, CidxColumn *aCol, char **azAfter, int iGt, int bLastIsNull
){
  char *zRet = 0;
  const char *zSep = "";
  int i;

  for(i=0; i<iGt; i++){
    zRet = cidxMprintf(pRc, "%z%s(%s) IS %s", zRet, 
        zSep, aCol[i].zExpr, (azAfter[i] ? azAfter[i] : "NULL")
    );
    zSep = " AND ";
  }

  if( bLastIsNull ){
    zRet = cidxMprintf(pRc, "%z%s(%s) IS NULL", zRet, zSep, aCol[iGt].zExpr);
  }
  else if( azAfter[iGt] ){
    zRet = cidxMprintf(pRc, "%z%s(%s) %s %s", zRet, 
        zSep, aCol[iGt].zExpr, (aCol[iGt].bDesc ? "<" : ">"), 
        azAfter[iGt]
    );
  }else{
    zRet = cidxMprintf(pRc, "%z%s(%s) IS NOT NULL", zRet, zSep,aCol[iGt].zExpr);
  }

  return zRet;
}