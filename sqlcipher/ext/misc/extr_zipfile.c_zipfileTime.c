#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u32 ;
struct TYPE_5__ {int iVersion; int /*<<< orphan*/  (* xCurrentTime ) (TYPE_1__*,double*) ;int /*<<< orphan*/  (* xCurrentTimeInt64 ) (TYPE_1__*,int*) ;} ;
typedef  TYPE_1__ sqlite3_vfs ;
typedef  int i64 ;

/* Variables and functions */
 TYPE_1__* sqlite3_vfs_find (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (TYPE_1__*,int*) ; 
 int /*<<< orphan*/  stub2 (TYPE_1__*,double*) ; 

__attribute__((used)) static u32 zipfileTime(void){
  sqlite3_vfs *pVfs = sqlite3_vfs_find(0);
  u32 ret;
  if( pVfs->iVersion>=2 && pVfs->xCurrentTimeInt64 ){
    i64 ms;
    pVfs->xCurrentTimeInt64(pVfs, &ms);
    ret = (u32)((ms/1000) - ((i64)24405875 * 8640));
  }else{
    double day;
    pVfs->xCurrentTime(pVfs, &day);
    ret = (u32)((day - 2440587.5) * 86400);
  }
  return ret;
}