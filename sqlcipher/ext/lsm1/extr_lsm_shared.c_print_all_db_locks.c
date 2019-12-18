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
struct TYPE_7__ {struct TYPE_7__* pNext; TYPE_1__* pDatabase; } ;
typedef  TYPE_2__ lsm_db ;
struct TYPE_6__ {TYPE_2__* pConn; } ;

/* Variables and functions */
 int /*<<< orphan*/  print_db_locks (TYPE_2__*) ; 
 int /*<<< orphan*/  printf (char*,char*,TYPE_2__*) ; 

void print_all_db_locks(lsm_db *db){
  lsm_db *p;
  for(p=db->pDatabase->pConn; p; p=p->pNext){
    printf("%s connection %p ", ((p==db)?"*":""), p);
    print_db_locks(p);
  }
}