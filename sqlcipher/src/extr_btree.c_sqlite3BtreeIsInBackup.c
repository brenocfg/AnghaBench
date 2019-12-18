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
struct TYPE_7__ {scalar_t__ nBackup; TYPE_1__* db; } ;
struct TYPE_6__ {int /*<<< orphan*/  mutex; } ;
typedef  TYPE_2__ Btree ;

/* Variables and functions */
 int /*<<< orphan*/  assert (TYPE_2__*) ; 
 TYPE_2__* sqlite3_mutex_held (int /*<<< orphan*/ ) ; 

int sqlite3BtreeIsInBackup(Btree *p){
  assert( p );
  assert( sqlite3_mutex_held(p->db->mutex) );
  return p->nBackup!=0;
}