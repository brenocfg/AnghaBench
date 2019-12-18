#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  void* sqlite_int64 ;
struct TYPE_4__ {int iHeight; int /*<<< orphan*/  term; int /*<<< orphan*/ * last; int /*<<< orphan*/ * first; void* iLastChildBlock; void* iOpeningChildBlock; } ;
typedef  TYPE_1__ InteriorWriter ;
typedef  int /*<<< orphan*/  InteriorBlock ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT_VALID_INTERIOR_BLOCK (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  CLEAR (TYPE_1__*) ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  dataBufferInit (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * interiorBlockNew (int,void*,char const*,int) ; 

__attribute__((used)) static void interiorWriterInit(int iHeight, const char *pTerm, int nTerm,
                               sqlite_int64 iChildBlock,
                               InteriorWriter *pWriter){
  InteriorBlock *block;
  assert( iHeight>0 );
  CLEAR(pWriter);

  pWriter->iHeight = iHeight;
  pWriter->iOpeningChildBlock = iChildBlock;
#ifndef NDEBUG
  pWriter->iLastChildBlock = iChildBlock;
#endif
  block = interiorBlockNew(iHeight, iChildBlock, pTerm, nTerm);
  pWriter->last = pWriter->first = block;
  ASSERT_VALID_INTERIOR_BLOCK(pWriter->last);
  dataBufferInit(&pWriter->term, 0);
}