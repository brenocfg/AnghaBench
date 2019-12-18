#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  sqlite3_vtab ;
struct TYPE_6__ {int nSrc; scalar_t__ db; struct TYPE_6__* aSrc; struct TYPE_6__* zSourceStr; int /*<<< orphan*/  pOpenClose; int /*<<< orphan*/  pNotFound; struct TYPE_6__* zContext; struct TYPE_6__* zFile; struct TYPE_6__* zTab; struct TYPE_6__* zDb; } ;
typedef  TYPE_1__ UnionTab ;
typedef  TYPE_1__ UnionSrc ;

/* Variables and functions */
 int SQLITE_OK ; 
 int /*<<< orphan*/  sqlite3_close (scalar_t__) ; 
 int /*<<< orphan*/  sqlite3_finalize (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sqlite3_free (TYPE_1__*) ; 
 int /*<<< orphan*/  unionInvokeOpenClose (TYPE_1__*,TYPE_1__*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int unionDisconnect(sqlite3_vtab *pVtab){
  if( pVtab ){
    UnionTab *pTab = (UnionTab*)pVtab;
    int i;
    for(i=0; i<pTab->nSrc; i++){
      UnionSrc *pSrc = &pTab->aSrc[i];
      int bHaveSrcDb = (pSrc->db!=0);
      sqlite3_close(pSrc->db);
      if( bHaveSrcDb ){
        unionInvokeOpenClose(pTab, pSrc, 1, 0);
      }
      sqlite3_free(pSrc->zDb);
      sqlite3_free(pSrc->zTab);
      sqlite3_free(pSrc->zFile);
      sqlite3_free(pSrc->zContext);
    }
    sqlite3_finalize(pTab->pNotFound);
    sqlite3_finalize(pTab->pOpenClose);
    sqlite3_free(pTab->zSourceStr);
    sqlite3_free(pTab->aSrc);
    sqlite3_free(pTab);
  }
  return SQLITE_OK;
}