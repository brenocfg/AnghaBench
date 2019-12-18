#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int i64 ;
typedef  int /*<<< orphan*/  CkptBuffer ;

/* Variables and functions */
 int /*<<< orphan*/  ckptSetValue (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int*) ; 

__attribute__((used)) static void ckptAppend64(CkptBuffer *p, int *piOut, i64 iVal, int *pRc){
  int iOut = *piOut;
  ckptSetValue(p, iOut++, (iVal >> 32) & 0xFFFFFFFF, pRc);
  ckptSetValue(p, iOut++, (iVal & 0xFFFFFFFF), pRc);
  *piOut = iOut;
}