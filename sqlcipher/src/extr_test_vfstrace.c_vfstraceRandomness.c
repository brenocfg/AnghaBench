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
struct TYPE_7__ {int (* xRandomness ) (TYPE_2__*,int,char*) ;scalar_t__ pAppData; } ;
typedef  TYPE_2__ sqlite3_vfs ;

/* Variables and functions */
 int stub1 (TYPE_2__*,int,char*) ; 
 int /*<<< orphan*/  vfstrace_printf (TYPE_1__*,char*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int vfstraceRandomness(sqlite3_vfs *pVfs, int nByte, char *zBufOut){
  vfstrace_info *pInfo = (vfstrace_info*)pVfs->pAppData;
  sqlite3_vfs *pRoot = pInfo->pRootVfs;
  vfstrace_printf(pInfo, "%s.xRandomness(%d)\n", pInfo->zVfsName, nByte);
  return pRoot->xRandomness(pRoot, nByte, zBufOut);
}