#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {scalar_t__ magic; TYPE_1__* db; } ;
typedef  TYPE_2__ Vdbe ;
struct TYPE_6__ {int errMask; } ;

/* Variables and functions */
 int SQLITE_OK ; 
 scalar_t__ VDBE_MAGIC_HALT ; 
 scalar_t__ VDBE_MAGIC_RUN ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  sqlite3VdbeDelete (TYPE_2__*) ; 
 int sqlite3VdbeReset (TYPE_2__*) ; 

int sqlite3VdbeFinalize(Vdbe *p){
  int rc = SQLITE_OK;
  if( p->magic==VDBE_MAGIC_RUN || p->magic==VDBE_MAGIC_HALT ){
    rc = sqlite3VdbeReset(p);
    assert( (rc & p->db->errMask)==rc );
  }
  sqlite3VdbeDelete(p);
  return rc;
}