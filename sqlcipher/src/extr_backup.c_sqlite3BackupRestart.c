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
struct TYPE_7__ {int iNext; TYPE_2__* pSrc; struct TYPE_7__* pNext; } ;
typedef  TYPE_3__ sqlite3_backup ;
struct TYPE_6__ {TYPE_1__* pBt; } ;
struct TYPE_5__ {int /*<<< orphan*/  mutex; } ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sqlite3_mutex_held (int /*<<< orphan*/ ) ; 

void sqlite3BackupRestart(sqlite3_backup *pBackup){
  sqlite3_backup *p;                   /* Iterator variable */
  for(p=pBackup; p; p=p->pNext){
    assert( sqlite3_mutex_held(p->pSrc->pBt->mutex) );
    p->iNext = 1;
  }
}