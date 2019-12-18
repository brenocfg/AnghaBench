#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  sqlite3rbu ;
typedef  int sqlite3_int64 ;

/* Variables and functions */
 scalar_t__ rbuMalloc (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static char *rbuObjIterGetBindlist(sqlite3rbu *p, int nBind){
  char *zRet = 0;
  sqlite3_int64 nByte = 2*(sqlite3_int64)nBind + 1;

  zRet = (char*)rbuMalloc(p, nByte);
  if( zRet ){
    int i;
    for(i=0; i<nBind; i++){
      zRet[i*2] = '?';
      zRet[i*2+1] = (i+1==nBind) ? '\0' : ',';
    }
  }
  return zRet;
}