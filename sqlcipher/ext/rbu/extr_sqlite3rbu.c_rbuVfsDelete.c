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
struct TYPE_5__ {int (* xDelete ) (TYPE_1__*,char const*,int) ;} ;
typedef  TYPE_1__ sqlite3_vfs ;
struct TYPE_6__ {TYPE_1__* pRealVfs; } ;
typedef  TYPE_2__ rbu_vfs ;

/* Variables and functions */
 int stub1 (TYPE_1__*,char const*,int) ; 

__attribute__((used)) static int rbuVfsDelete(sqlite3_vfs *pVfs, const char *zPath, int dirSync){
  sqlite3_vfs *pRealVfs = ((rbu_vfs*)pVfs)->pRealVfs;
  return pRealVfs->xDelete(pRealVfs, zPath, dirSync);
}