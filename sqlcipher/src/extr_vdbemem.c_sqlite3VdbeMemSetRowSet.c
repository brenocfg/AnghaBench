#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  sqlite3 ;
struct TYPE_5__ {char* z; int flags; int /*<<< orphan*/  xDel; int /*<<< orphan*/ * db; } ;
typedef  int /*<<< orphan*/  RowSet ;
typedef  TYPE_1__ Mem ;

/* Variables and functions */
 int MEM_Blob ; 
 int MEM_Dyn ; 
 int SQLITE_NOMEM ; 
 int SQLITE_OK ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  sqlite3RowSetDelete ; 
 int /*<<< orphan*/ * sqlite3RowSetInit (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sqlite3VdbeMemIsRowSet (TYPE_1__*) ; 
 int /*<<< orphan*/  sqlite3VdbeMemRelease (TYPE_1__*) ; 

int sqlite3VdbeMemSetRowSet(Mem *pMem){
  sqlite3 *db = pMem->db;
  RowSet *p;
  assert( db!=0 );
  assert( !sqlite3VdbeMemIsRowSet(pMem) );
  sqlite3VdbeMemRelease(pMem);
  p = sqlite3RowSetInit(db);
  if( p==0 ) return SQLITE_NOMEM;
  pMem->z = (char*)p;
  pMem->flags = MEM_Blob|MEM_Dyn;
  pMem->xDel = sqlite3RowSetDelete;
  return SQLITE_OK;
}