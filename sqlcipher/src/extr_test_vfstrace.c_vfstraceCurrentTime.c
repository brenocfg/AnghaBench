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
struct TYPE_5__ {TYPE_2__* pRootVfs; } ;
typedef  TYPE_1__ vfstrace_info ;
struct TYPE_6__ {int (* xCurrentTime ) (TYPE_2__*,double*) ;scalar_t__ pAppData; } ;
typedef  TYPE_2__ sqlite3_vfs ;

/* Variables and functions */
 int stub1 (TYPE_2__*,double*) ; 

__attribute__((used)) static int vfstraceCurrentTime(sqlite3_vfs *pVfs, double *pTimeOut){
  vfstrace_info *pInfo = (vfstrace_info*)pVfs->pAppData;
  sqlite3_vfs *pRoot = pInfo->pRootVfs;
  return pRoot->xCurrentTime(pRoot, pTimeOut);
}