#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {int nZero; } ;
struct TYPE_11__ {int flags; int n; TYPE_2__ u; int /*<<< orphan*/ * z; TYPE_1__* db; } ;
struct TYPE_9__ {int /*<<< orphan*/  mutex; } ;
typedef  TYPE_3__ Mem ;

/* Variables and functions */
 int MEM_Blob ; 
 int MEM_Term ; 
 int MEM_Zero ; 
 scalar_t__ MemNullNochng (TYPE_3__*) ; 
 int SQLITE_NOMEM_BKPT ; 
 int SQLITE_OK ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 scalar_t__ sqlite3VdbeMemGrow (TYPE_3__*,int,int) ; 
 int /*<<< orphan*/  sqlite3VdbeMemIsRowSet (TYPE_3__*) ; 
 scalar_t__ sqlite3_mutex_held (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sqlite3_value_nochange (TYPE_3__*) ; 
 int /*<<< orphan*/  testcase (int /*<<< orphan*/ ) ; 

int sqlite3VdbeMemExpandBlob(Mem *pMem){
  int nByte;
  assert( pMem->flags & MEM_Zero );
  assert( (pMem->flags&MEM_Blob)!=0 || MemNullNochng(pMem) );
  testcase( sqlite3_value_nochange(pMem) );
  assert( !sqlite3VdbeMemIsRowSet(pMem) );
  assert( pMem->db==0 || sqlite3_mutex_held(pMem->db->mutex) );

  /* Set nByte to the number of bytes required to store the expanded blob. */
  nByte = pMem->n + pMem->u.nZero;
  if( nByte<=0 ){
    if( (pMem->flags & MEM_Blob)==0 ) return SQLITE_OK;
    nByte = 1;
  }
  if( sqlite3VdbeMemGrow(pMem, nByte, 1) ){
    return SQLITE_NOMEM_BKPT;
  }

  memset(&pMem->z[pMem->n], 0, pMem->u.nZero);
  pMem->n += pMem->u.nZero;
  pMem->flags &= ~(MEM_Zero|MEM_Term);
  return SQLITE_OK;
}