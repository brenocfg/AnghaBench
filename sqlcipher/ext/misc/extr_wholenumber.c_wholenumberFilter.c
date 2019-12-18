#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int iValue; int mxValue; } ;
typedef  TYPE_1__ wholenumber_cursor ;
typedef  int /*<<< orphan*/  sqlite3_vtab_cursor ;
typedef  int /*<<< orphan*/  sqlite3_value ;
typedef  void* sqlite3_int64 ;

/* Variables and functions */
 int SQLITE_OK ; 
 int sqlite3_value_int64 (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int wholenumberFilter(
  sqlite3_vtab_cursor *pVtabCursor, 
  int idxNum, const char *idxStr,
  int argc, sqlite3_value **argv
){
  wholenumber_cursor *pCur = (wholenumber_cursor *)pVtabCursor;
  sqlite3_int64 v;
  int i = 0;
  pCur->iValue = 1;
  pCur->mxValue = 0xffffffff;  /* 4294967295 */
  if( idxNum & 3 ){
    v = sqlite3_value_int64(argv[0]) + (idxNum&1);
    if( v>pCur->iValue && v<=pCur->mxValue ) pCur->iValue = v;
    i++;
  }
  if( idxNum & 12 ){
    v = sqlite3_value_int64(argv[i]) - ((idxNum>>2)&1);
    if( v>=pCur->iValue && v<pCur->mxValue ) pCur->mxValue = v;
  }
  return SQLITE_OK;
}