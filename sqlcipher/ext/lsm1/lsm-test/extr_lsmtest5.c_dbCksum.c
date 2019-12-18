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
typedef  scalar_t__ u8 ;
typedef  int u32 ;

/* Variables and functions */
 int /*<<< orphan*/  unused_parameter (int) ; 

__attribute__((used)) static void dbCksum(
  void *pCtx,                     /* IN/OUT: Pointer to u32 containing cksum */
  void *pKey, int nKey,           /* Database key. Unused. */
  void *pVal, int nVal            /* Database value. Checksum this. */
){
  u8 *aVal = (u8 *)pVal;
  u32 *pCksum = (u32 *)pCtx;
  u32 cksum = *pCksum;
  int i;

  unused_parameter(pKey);
  unused_parameter(nKey);

  for(i=0; i<nVal; i++){
    cksum += (cksum<<3) + (int)aVal[i];
  }

  *pCksum = cksum;
}