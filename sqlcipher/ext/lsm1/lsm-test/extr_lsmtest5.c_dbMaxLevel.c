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
struct TYPE_3__ {int nKey; int nFanout; } ;
typedef  TYPE_1__ DbParameters ;

/* Variables and functions */

__attribute__((used)) static int dbMaxLevel(DbParameters *pParam){
  int iMax;
  int n = 1;
  for(iMax=0; n<pParam->nKey; iMax++){
    n = n * pParam->nFanout;
  }
  return iMax;
}