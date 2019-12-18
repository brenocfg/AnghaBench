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
struct TYPE_6__ {int (* xSetSystemCall ) (TYPE_2__*,char const*,int /*<<< orphan*/ ) ;scalar_t__ pAppData; } ;
typedef  TYPE_2__ sqlite3_vfs ;
typedef  int /*<<< orphan*/  sqlite3_syscall_ptr ;

/* Variables and functions */
 int stub1 (TYPE_2__*,char const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int vfstraceSetSystemCall(
  sqlite3_vfs *pVfs,
  const char *zName,
  sqlite3_syscall_ptr pFunc
){
  vfstrace_info *pInfo = (vfstrace_info*)pVfs->pAppData;
  sqlite3_vfs *pRoot = pInfo->pRootVfs;
  return pRoot->xSetSystemCall(pRoot, zName, pFunc);
}