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
struct TYPE_6__ {int /*<<< orphan*/  zVfsName; TYPE_2__* pRootVfs; } ;
typedef  TYPE_1__ vfstrace_info ;
struct TYPE_7__ {void* (* xDlOpen ) (TYPE_2__*,char const*) ;scalar_t__ pAppData; } ;
typedef  TYPE_2__ sqlite3_vfs ;

/* Variables and functions */
 void* stub1 (TYPE_2__*,char const*) ; 
 int /*<<< orphan*/  vfstrace_printf (TYPE_1__*,char*,int /*<<< orphan*/ ,char const*) ; 

__attribute__((used)) static void *vfstraceDlOpen(sqlite3_vfs *pVfs, const char *zPath){
  vfstrace_info *pInfo = (vfstrace_info*)pVfs->pAppData;
  sqlite3_vfs *pRoot = pInfo->pRootVfs;
  vfstrace_printf(pInfo, "%s.xDlOpen(\"%s\")\n", pInfo->zVfsName, zPath);
  return pRoot->xDlOpen(pRoot, zPath);
}