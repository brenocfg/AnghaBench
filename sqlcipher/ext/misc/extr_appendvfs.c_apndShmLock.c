#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {TYPE_1__* pMethods; } ;
typedef  TYPE_2__ sqlite3_file ;
struct TYPE_7__ {int (* xShmLock ) (TYPE_2__*,int,int,int) ;} ;

/* Variables and functions */
 TYPE_2__* ORIGFILE (TYPE_2__*) ; 
 int stub1 (TYPE_2__*,int,int,int) ; 

__attribute__((used)) static int apndShmLock(sqlite3_file *pFile, int offset, int n, int flags){
  pFile = ORIGFILE(pFile);
  return pFile->pMethods->xShmLock(pFile,offset,n,flags);
}