#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int (* xSleep ) (TYPE_1__*,int) ;scalar_t__ pAppData; } ;
typedef  TYPE_1__ sqlite3_vfs ;

/* Variables and functions */
 int stub1 (TYPE_1__*,int) ; 

__attribute__((used)) static int asyncSleep(sqlite3_vfs *pAsyncVfs, int nMicro){
  sqlite3_vfs *pVfs = (sqlite3_vfs *)pAsyncVfs->pAppData;
  return pVfs->xSleep(pVfs, nMicro);
}