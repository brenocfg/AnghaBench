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
typedef  int /*<<< orphan*/  UInt64 ;
typedef  int /*<<< orphan*/  UInt32 ;
typedef  int /*<<< orphan*/  SRes ;
typedef  int /*<<< orphan*/  ISzAlloc ;
typedef  int /*<<< orphan*/  CSzData ;
typedef  int /*<<< orphan*/  CSzArEx ;
typedef  int /*<<< orphan*/  Byte ;

/* Variables and functions */
 int /*<<< orphan*/  IAlloc_Free (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SzReadHeader2 (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ **,int /*<<< orphan*/ **,int /*<<< orphan*/ **,int /*<<< orphan*/ **,int /*<<< orphan*/ **,int /*<<< orphan*/ **,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static SRes SzReadHeader(
    CSzArEx *p,
    CSzData *sd,
    ISzAlloc *allocMain,
    ISzAlloc *allocTemp)
{
  UInt64 *unpackSizes = 0;
  Byte *digestsDefined = 0;
  UInt32 *digests = 0;
  Byte *emptyStreamVector = 0;
  Byte *emptyFileVector = 0;
  Byte *lwtVector = 0;
  SRes res = SzReadHeader2(p, sd,
      &unpackSizes, &digestsDefined, &digests,
      &emptyStreamVector, &emptyFileVector, &lwtVector,
      allocMain, allocTemp);
  IAlloc_Free(allocTemp, unpackSizes);
  IAlloc_Free(allocTemp, digestsDefined);
  IAlloc_Free(allocTemp, digests);
  IAlloc_Free(allocTemp, emptyStreamVector);
  IAlloc_Free(allocTemp, emptyFileVector);
  IAlloc_Free(allocTemp, lwtVector);
  return res;
}