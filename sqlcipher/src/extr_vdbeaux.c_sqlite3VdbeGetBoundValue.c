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
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  sqlite3_value ;
struct TYPE_7__ {TYPE_6__* db; TYPE_2__* aVar; } ;
typedef  TYPE_1__ Vdbe ;
struct TYPE_9__ {int flags; } ;
struct TYPE_8__ {int flags; } ;
typedef  TYPE_2__ Mem ;

/* Variables and functions */
 int MEM_Null ; 
 int SQLITE_EnableQPSG ; 
 int /*<<< orphan*/  SQLITE_UTF8 ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  sqlite3ValueApplyAffinity (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * sqlite3ValueNew (TYPE_6__*) ; 
 int /*<<< orphan*/  sqlite3VdbeMemCopy (TYPE_2__*,TYPE_2__*) ; 

sqlite3_value *sqlite3VdbeGetBoundValue(Vdbe *v, int iVar, u8 aff){
  assert( iVar>0 );
  if( v ){
    Mem *pMem = &v->aVar[iVar-1];
    assert( (v->db->flags & SQLITE_EnableQPSG)==0 );
    if( 0==(pMem->flags & MEM_Null) ){
      sqlite3_value *pRet = sqlite3ValueNew(v->db);
      if( pRet ){
        sqlite3VdbeMemCopy((Mem *)pRet, pMem);
        sqlite3ValueApplyAffinity(pRet, aff, SQLITE_UTF8);
      }
      return pRet;
    }
  }
  return 0;
}