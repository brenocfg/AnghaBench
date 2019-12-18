#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ i64 ;
struct TYPE_8__ {scalar_t__ r; scalar_t__ i; } ;
struct TYPE_10__ {int flags; TYPE_1__ u; TYPE_2__* db; } ;
struct TYPE_9__ {int /*<<< orphan*/  mutex; } ;
typedef  TYPE_3__ Mem ;

/* Variables and functions */
 int EIGHT_BYTE_ALIGNMENT (TYPE_3__*) ; 
 scalar_t__ LARGEST_INT64 ; 
 int /*<<< orphan*/  MEM_Int ; 
 int MEM_Real ; 
 int /*<<< orphan*/  MemSetTypeFlag (TYPE_3__*,int /*<<< orphan*/ ) ; 
 scalar_t__ SMALLEST_INT64 ; 
 int /*<<< orphan*/  assert (int) ; 
 scalar_t__ doubleToInt64 (scalar_t__) ; 
 int /*<<< orphan*/  sqlite3VdbeMemIsRowSet (TYPE_3__*) ; 
 scalar_t__ sqlite3_mutex_held (int /*<<< orphan*/ ) ; 

void sqlite3VdbeIntegerAffinity(Mem *pMem){
  i64 ix;
  assert( pMem->flags & MEM_Real );
  assert( !sqlite3VdbeMemIsRowSet(pMem) );
  assert( pMem->db==0 || sqlite3_mutex_held(pMem->db->mutex) );
  assert( EIGHT_BYTE_ALIGNMENT(pMem) );

  ix = doubleToInt64(pMem->u.r);

  /* Only mark the value as an integer if
  **
  **    (1) the round-trip conversion real->int->real is a no-op, and
  **    (2) The integer is neither the largest nor the smallest
  **        possible integer (ticket #3922)
  **
  ** The second and third terms in the following conditional enforces
  ** the second condition under the assumption that addition overflow causes
  ** values to wrap around.
  */
  if( pMem->u.r==ix && ix>SMALLEST_INT64 && ix<LARGEST_INT64 ){
    pMem->u.i = ix;
    MemSetTypeFlag(pMem, MEM_Int);
  }
}