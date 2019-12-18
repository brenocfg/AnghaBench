#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {int flags; } ;
typedef  TYPE_1__ Mem ;

/* Variables and functions */
 int /*<<< orphan*/  MEMCELLSIZE ; 
 int MEM_Blob ; 
 int MEM_Dyn ; 
 int MEM_Ephem ; 
 int MEM_Static ; 
 int MEM_Str ; 
 int SQLITE_OK ; 
 scalar_t__ VdbeMemDynamic (TYPE_1__*) ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  memcpy (TYPE_1__*,TYPE_1__ const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sqlite3VdbeMemIsRowSet (TYPE_1__ const*) ; 
 int sqlite3VdbeMemMakeWriteable (TYPE_1__*) ; 
 int /*<<< orphan*/  vdbeMemClearExternAndSetNull (TYPE_1__*) ; 

int sqlite3VdbeMemCopy(Mem *pTo, const Mem *pFrom){
  int rc = SQLITE_OK;

  assert( !sqlite3VdbeMemIsRowSet(pFrom) );
  if( VdbeMemDynamic(pTo) ) vdbeMemClearExternAndSetNull(pTo);
  memcpy(pTo, pFrom, MEMCELLSIZE);
  pTo->flags &= ~MEM_Dyn;
  if( pTo->flags&(MEM_Str|MEM_Blob) ){
    if( 0==(pFrom->flags&MEM_Static) ){
      pTo->flags |= MEM_Ephem;
      rc = sqlite3VdbeMemMakeWriteable(pTo);
    }
  }

  return rc;
}