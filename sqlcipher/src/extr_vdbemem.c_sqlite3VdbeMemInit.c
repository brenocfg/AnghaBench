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
typedef  int u16 ;
typedef  int /*<<< orphan*/  sqlite3 ;
struct TYPE_3__ {int flags; scalar_t__ szMalloc; int /*<<< orphan*/ * db; } ;
typedef  TYPE_1__ Mem ;

/* Variables and functions */
 int MEM_TypeMask ; 
 int /*<<< orphan*/  assert (int) ; 

void sqlite3VdbeMemInit(Mem *pMem, sqlite3 *db, u16 flags){
  assert( (flags & ~MEM_TypeMask)==0 );
  pMem->flags = flags;
  pMem->db = db;
  pMem->szMalloc = 0;
}