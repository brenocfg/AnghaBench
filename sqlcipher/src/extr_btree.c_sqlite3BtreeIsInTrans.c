#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {scalar_t__ inTrans; TYPE_1__* db; } ;
struct TYPE_4__ {int /*<<< orphan*/  mutex; } ;
typedef  TYPE_2__ Btree ;

/* Variables and functions */
 scalar_t__ TRANS_WRITE ; 
 int /*<<< orphan*/  assert (int) ; 
 scalar_t__ sqlite3_mutex_held (int /*<<< orphan*/ ) ; 

int sqlite3BtreeIsInTrans(Btree *p){
  assert( p==0 || sqlite3_mutex_held(p->db->mutex) );
  return (p && (p->inTrans==TRANS_WRITE));
}