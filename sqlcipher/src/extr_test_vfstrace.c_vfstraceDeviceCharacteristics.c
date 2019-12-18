#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_5__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  zVfsName; } ;
typedef  TYPE_2__ vfstrace_info ;
struct TYPE_8__ {TYPE_5__* pReal; int /*<<< orphan*/  zFName; TYPE_2__* pInfo; } ;
typedef  TYPE_3__ vfstrace_file ;
typedef  int /*<<< orphan*/  sqlite3_file ;
struct TYPE_9__ {TYPE_1__* pMethods; } ;
struct TYPE_6__ {int (* xDeviceCharacteristics ) (TYPE_5__*) ;} ;

/* Variables and functions */
 int stub1 (TYPE_5__*) ; 
 int /*<<< orphan*/  vfstrace_printf (TYPE_2__*,char*,int,...) ; 

__attribute__((used)) static int vfstraceDeviceCharacteristics(sqlite3_file *pFile){
  vfstrace_file *p = (vfstrace_file *)pFile;
  vfstrace_info *pInfo = p->pInfo;
  int rc;
  vfstrace_printf(pInfo, "%s.xDeviceCharacteristics(%s)",
                  pInfo->zVfsName, p->zFName);
  rc = p->pReal->pMethods->xDeviceCharacteristics(p->pReal);
  vfstrace_printf(pInfo, " -> 0x%08x\n", rc);
  return rc;
}