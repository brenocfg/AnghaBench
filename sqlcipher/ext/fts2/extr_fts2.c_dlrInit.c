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
struct TYPE_4__ {char const* pData; int nData; scalar_t__ iDocid; scalar_t__ nElement; int /*<<< orphan*/  iType; } ;
typedef  int /*<<< orphan*/  DocListType ;
typedef  TYPE_1__ DLReader ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  dlrStep (TYPE_1__*) ; 

__attribute__((used)) static void dlrInit(DLReader *pReader, DocListType iType,
                    const char *pData, int nData){
  assert( pData!=NULL && nData!=0 );
  pReader->iType = iType;
  pReader->pData = pData;
  pReader->nData = nData;
  pReader->nElement = 0;
  pReader->iDocid = 0;

  /* Load the first element's data.  There must be a first element. */
  dlrStep(pReader);
}