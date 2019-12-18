#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {scalar_t__ nZero; } ;
struct TYPE_7__ {int flags; int n; TYPE_2__* db; TYPE_1__ u; } ;
struct TYPE_6__ {int* aLimit; } ;
typedef  TYPE_3__ Mem ;

/* Variables and functions */
 int MEM_Blob ; 
 int MEM_Str ; 
 int MEM_Zero ; 
 size_t SQLITE_LIMIT_LENGTH ; 
 int /*<<< orphan*/  assert (int) ; 

int sqlite3VdbeMemTooBig(Mem *p){
  assert( p->db!=0 );
  if( p->flags & (MEM_Str|MEM_Blob) ){
    int n = p->n;
    if( p->flags & MEM_Zero ){
      n += p->u.nZero;
    }
    return n>p->db->aLimit[SQLITE_LIMIT_LENGTH];
  }
  return 0; 
}