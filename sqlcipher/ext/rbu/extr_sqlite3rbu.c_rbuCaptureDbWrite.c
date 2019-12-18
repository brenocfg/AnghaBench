#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u32 ;
struct TYPE_5__ {int nFrame; int pgsz; TYPE_1__* aFrame; } ;
typedef  TYPE_2__ sqlite3rbu ;
typedef  int i64 ;
struct TYPE_4__ {scalar_t__ iDbPage; } ;

/* Variables and functions */
 int SQLITE_OK ; 

__attribute__((used)) static int rbuCaptureDbWrite(sqlite3rbu *pRbu, i64 iOff){
  pRbu->aFrame[pRbu->nFrame-1].iDbPage = (u32)(iOff / pRbu->pgsz) + 1;
  return SQLITE_OK;
}