#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u8 ;
struct TYPE_3__ {int iSDParm; scalar_t__ nSdst; scalar_t__ iSdst; scalar_t__ zAffSdst; scalar_t__ eDest; } ;
typedef  TYPE_1__ SelectDest ;

/* Variables and functions */

void sqlite3SelectDestInit(SelectDest *pDest, int eDest, int iParm){
  pDest->eDest = (u8)eDest;
  pDest->iSDParm = iParm;
  pDest->zAffSdst = 0;
  pDest->iSdst = 0;
  pDest->nSdst = 0;
}