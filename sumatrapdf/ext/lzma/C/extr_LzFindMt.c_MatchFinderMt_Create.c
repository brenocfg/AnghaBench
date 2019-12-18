#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int UInt32 ;
struct TYPE_9__ {int historySize; int* hashBuf; int* btBuf; int /*<<< orphan*/  btSync; int /*<<< orphan*/  hashSync; int /*<<< orphan*/ * MatchFinder; } ;
struct TYPE_8__ {scalar_t__ (* Alloc ) (TYPE_1__*,int) ;} ;
typedef  int /*<<< orphan*/  SRes ;
typedef  TYPE_1__ ISzAlloc ;
typedef  TYPE_2__ CMatchFinderMt ;
typedef  int /*<<< orphan*/  CMatchFinder ;

/* Variables and functions */
 int /*<<< orphan*/  BtThreadFunc2 ; 
 int /*<<< orphan*/  HashThreadFunc2 ; 
 int /*<<< orphan*/  MatchFinder_Create (int /*<<< orphan*/ *,int,int,int,int,TYPE_1__*) ; 
 int /*<<< orphan*/  MtSync_Create (int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RINOK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SZ_ERROR_MEM ; 
 int /*<<< orphan*/  SZ_ERROR_PARAM ; 
 int /*<<< orphan*/  SZ_OK ; 
 int kBtBufferSize ; 
 int kHashBufferSize ; 
 int kMtBtBlockSize ; 
 int /*<<< orphan*/  kMtBtNumBlocks ; 
 scalar_t__ kMtHashBlockSize ; 
 int /*<<< orphan*/  kMtHashNumBlocks ; 
 scalar_t__ stub1 (TYPE_1__*,int) ; 

SRes MatchFinderMt_Create(CMatchFinderMt *p, UInt32 historySize, UInt32 keepAddBufferBefore,
    UInt32 matchMaxLen, UInt32 keepAddBufferAfter, ISzAlloc *alloc)
{
  CMatchFinder *mf = p->MatchFinder;
  p->historySize = historySize;
  if (kMtBtBlockSize <= matchMaxLen * 4)
    return SZ_ERROR_PARAM;
  if (p->hashBuf == 0)
  {
    p->hashBuf = (UInt32 *)alloc->Alloc(alloc, (kHashBufferSize + kBtBufferSize) * sizeof(UInt32));
    if (p->hashBuf == 0)
      return SZ_ERROR_MEM;
    p->btBuf = p->hashBuf + kHashBufferSize;
  }
  keepAddBufferBefore += (kHashBufferSize + kBtBufferSize);
  keepAddBufferAfter += kMtHashBlockSize;
  if (!MatchFinder_Create(mf, historySize, keepAddBufferBefore, matchMaxLen, keepAddBufferAfter, alloc))
    return SZ_ERROR_MEM;

  RINOK(MtSync_Create(&p->hashSync, HashThreadFunc2, p, kMtHashNumBlocks));
  RINOK(MtSync_Create(&p->btSync, BtThreadFunc2, p, kMtBtNumBlocks));
  return SZ_OK;
}