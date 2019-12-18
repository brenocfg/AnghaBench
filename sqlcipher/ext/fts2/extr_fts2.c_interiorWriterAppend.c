#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_6__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ sqlite_int64 ;
struct TYPE_11__ {int nData; } ;
struct TYPE_10__ {int nData; char const* pData; } ;
struct TYPE_9__ {TYPE_6__ data; struct TYPE_9__* next; } ;
struct TYPE_8__ {scalar_t__ iLastChildBlock; scalar_t__ iOpeningChildBlock; TYPE_3__* last; TYPE_4__ term; int /*<<< orphan*/  iHeight; } ;
typedef  TYPE_1__ InteriorWriter ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT_VALID_INTERIOR_BLOCK (TYPE_3__*) ; 
 int INTERIOR_MAX ; 
 scalar_t__ INTERIOR_MIN_TERMS ; 
 int VARINT_MAX ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  dataBufferAppend2 (TYPE_6__*,char*,int,char const*,int) ; 
 int /*<<< orphan*/  dataBufferReplace (TYPE_4__*,char const*,int) ; 
 int /*<<< orphan*/  dataBufferReset (TYPE_4__*) ; 
 TYPE_3__* interiorBlockNew (int /*<<< orphan*/ ,scalar_t__,char const*,int) ; 
 int putVarint (char*,int) ; 

__attribute__((used)) static void interiorWriterAppend(InteriorWriter *pWriter,
                                 const char *pTerm, int nTerm,
                                 sqlite_int64 iChildBlock){
  char c[VARINT_MAX+VARINT_MAX];
  int n, nPrefix = 0;

  ASSERT_VALID_INTERIOR_BLOCK(pWriter->last);

  /* The first term written into an interior node is actually
  ** associated with the second child added (the first child was added
  ** in interiorWriterInit, or in the if clause at the bottom of this
  ** function).  That term gets encoded straight up, with nPrefix left
  ** at 0.
  */
  if( pWriter->term.nData==0 ){
    n = putVarint(c, nTerm);
  }else{
    while( nPrefix<pWriter->term.nData &&
           pTerm[nPrefix]==pWriter->term.pData[nPrefix] ){
      nPrefix++;
    }

    n = putVarint(c, nPrefix);
    n += putVarint(c+n, nTerm-nPrefix);
  }

#ifndef NDEBUG
  pWriter->iLastChildBlock++;
#endif
  assert( pWriter->iLastChildBlock==iChildBlock );

  /* Overflow to a new block if the new term makes the current block
  ** too big, and the current block already has enough terms.
  */
  if( pWriter->last->data.nData+n+nTerm-nPrefix>INTERIOR_MAX &&
      iChildBlock-pWriter->iOpeningChildBlock>INTERIOR_MIN_TERMS ){
    pWriter->last->next = interiorBlockNew(pWriter->iHeight, iChildBlock,
                                           pTerm, nTerm);
    pWriter->last = pWriter->last->next;
    pWriter->iOpeningChildBlock = iChildBlock;
    dataBufferReset(&pWriter->term);
  }else{
    dataBufferAppend2(&pWriter->last->data, c, n,
                      pTerm+nPrefix, nTerm-nPrefix);
    dataBufferReplace(&pWriter->term, pTerm, nTerm);
  }
  ASSERT_VALID_INTERIOR_BLOCK(pWriter->last);
}