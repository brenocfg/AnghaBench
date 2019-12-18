#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u8 ;
struct TYPE_2__ {scalar_t__ cksum1; int /*<<< orphan*/  cksum2; int /*<<< orphan*/  nRow; } ;
typedef  TYPE_1__ Cksum ;

/* Variables and functions */

__attribute__((used)) static void scanCksumDb(
  void *pCtx, 
  void *pKey, int nKey,
  void *pVal, int nVal
){
  Cksum *p = (Cksum *)pCtx;
  int i;

  p->nRow++;
  for(i=0; i<nKey; i++){
    p->cksum1 += ((u8 *)pKey)[i];
    p->cksum2 += p->cksum1;
  }
  for(i=0; i<nVal; i++){
    p->cksum1 += ((u8 *)pVal)[i];
    p->cksum2 += p->cksum1;
  }
}