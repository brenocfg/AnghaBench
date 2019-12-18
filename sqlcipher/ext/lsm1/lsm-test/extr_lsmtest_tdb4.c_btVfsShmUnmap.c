#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  bt_file ;
struct TYPE_6__ {int /*<<< orphan*/  pFile; TYPE_2__* pVfs; TYPE_1__* pBt; } ;
struct TYPE_5__ {int (* xShmUnmap ) (int /*<<< orphan*/ ,int) ;} ;
struct TYPE_4__ {scalar_t__ bCrash; } ;
typedef  TYPE_3__ BtFile ;

/* Variables and functions */
 int SQLITE4_IOERR ; 
 int stub1 (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int btVfsShmUnmap(bt_file *pFile, int bDelete){
  BtFile *p = (BtFile*)pFile;
  if( p->pBt && p->pBt->bCrash ) return SQLITE4_IOERR;
  return p->pVfs->xShmUnmap(p->pFile, bDelete);
}