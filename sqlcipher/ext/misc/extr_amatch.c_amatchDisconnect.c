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
typedef  int /*<<< orphan*/  sqlite3_vtab ;
struct TYPE_3__ {scalar_t__ nCursor; } ;
typedef  TYPE_1__ amatch_vtab ;

/* Variables and functions */
 int SQLITE_OK ; 
 int /*<<< orphan*/  amatchFree (TYPE_1__*) ; 
 int /*<<< orphan*/  assert (int) ; 

__attribute__((used)) static int amatchDisconnect(sqlite3_vtab *pVtab){
  amatch_vtab *p = (amatch_vtab*)pVtab;
  assert( p->nCursor==0 );
  amatchFree(p);
  return SQLITE_OK;
}