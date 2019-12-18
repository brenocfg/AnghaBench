#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int sqlite3_uint64 ;
struct TYPE_5__ {int colUsed; } ;
typedef  TYPE_1__ sqlite3_index_info ;
struct TYPE_6__ {int nCol; int /*<<< orphan*/ * aCol; } ;
typedef  TYPE_2__ echo_vtab ;

/* Variables and functions */
 int sqlite3_libversion_number () ; 
 char* sqlite3_mprintf (char*,...) ; 

__attribute__((used)) static char *echoSelectList(echo_vtab *pTab, sqlite3_index_info *pIdxInfo){
  char *zRet = 0;
  if( sqlite3_libversion_number()<3010000 ){
    zRet = sqlite3_mprintf(", *");
  }else{
    int i;
    for(i=0; i<pTab->nCol; i++){
      if( pIdxInfo->colUsed & ((sqlite3_uint64)1 << (i>=63 ? 63 : i)) ){
        zRet = sqlite3_mprintf("%z, %s", zRet, pTab->aCol[i]);
      }else{
        zRet = sqlite3_mprintf("%z, NULL", zRet);
      }
      if( !zRet ) break;
    }
  }
  return zRet;
}