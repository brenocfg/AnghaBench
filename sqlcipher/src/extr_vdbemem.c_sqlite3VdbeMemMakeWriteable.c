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
struct TYPE_8__ {int flags; scalar_t__ szMalloc; scalar_t__ z; scalar_t__ zMalloc; scalar_t__ pScopyFrom; TYPE_1__* db; } ;
struct TYPE_7__ {int /*<<< orphan*/  mutex; } ;
typedef  TYPE_2__ Mem ;

/* Variables and functions */
 scalar_t__ ExpandBlob (TYPE_2__*) ; 
 int MEM_Blob ; 
 int MEM_Ephem ; 
 int MEM_Str ; 
 int SQLITE_NOMEM ; 
 int SQLITE_OK ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  sqlite3VdbeMemIsRowSet (TYPE_2__*) ; 
 scalar_t__ sqlite3_mutex_held (int /*<<< orphan*/ ) ; 
 int vdbeMemAddTerminator (TYPE_2__*) ; 

int sqlite3VdbeMemMakeWriteable(Mem *pMem){
  assert( pMem->db==0 || sqlite3_mutex_held(pMem->db->mutex) );
  assert( !sqlite3VdbeMemIsRowSet(pMem) );
  if( (pMem->flags & (MEM_Str|MEM_Blob))!=0 ){
    if( ExpandBlob(pMem) ) return SQLITE_NOMEM;
    if( pMem->szMalloc==0 || pMem->z!=pMem->zMalloc ){
      int rc = vdbeMemAddTerminator(pMem);
      if( rc ) return rc;
    }
  }
  pMem->flags &= ~MEM_Ephem;
#ifdef SQLITE_DEBUG
  pMem->pScopyFrom = 0;
#endif

  return SQLITE_OK;
}