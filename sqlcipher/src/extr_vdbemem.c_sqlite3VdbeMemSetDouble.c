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
struct TYPE_5__ {double r; } ;
struct TYPE_6__ {int /*<<< orphan*/  flags; TYPE_1__ u; } ;
typedef  TYPE_2__ Mem ;

/* Variables and functions */
 int /*<<< orphan*/  MEM_Real ; 
 int /*<<< orphan*/  sqlite3IsNaN (double) ; 
 int /*<<< orphan*/  sqlite3VdbeMemSetNull (TYPE_2__*) ; 

void sqlite3VdbeMemSetDouble(Mem *pMem, double val){
  sqlite3VdbeMemSetNull(pMem);
  if( !sqlite3IsNaN(val) ){
    pMem->u.r = val;
    pMem->flags = MEM_Real;
  }
}