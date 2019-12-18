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
typedef  int /*<<< orphan*/  ILookInStream ;
typedef  int /*<<< orphan*/  CSzData ;
typedef  int /*<<< orphan*/  CSzAr ;
typedef  int /*<<< orphan*/  CBuf ;
typedef  int /*<<< orphan*/  Byte ;

/* Variables and functions */
 int /*<<< orphan*/  IAlloc_Free (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SzAr_Free (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SzAr_Init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SzReadAndDecodePackedStreams2 (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ **,int /*<<< orphan*/ **,int /*<<< orphan*/ **,int /*<<< orphan*/ *) ; 

__attribute__((used)) static SRes SzReadAndDecodePackedStreams(
    ILookInStream *inStream,
    CSzData *sd,
    CBuf *outBuffer,
    UInt64 baseOffset,
    ISzAlloc *allocTemp)
{
  CSzAr p;
  UInt64 *unpackSizes = 0;
  Byte *digestsDefined = 0;
  UInt32 *digests = 0;
  SRes res;
  SzAr_Init(&p);
  res = SzReadAndDecodePackedStreams2(inStream, sd, outBuffer, baseOffset,
    &p, &unpackSizes, &digestsDefined, &digests,
    allocTemp);
  SzAr_Free(&p, allocTemp);
  IAlloc_Free(allocTemp, unpackSizes);
  IAlloc_Free(allocTemp, digestsDefined);
  IAlloc_Free(allocTemp, digests);
  return res;
}