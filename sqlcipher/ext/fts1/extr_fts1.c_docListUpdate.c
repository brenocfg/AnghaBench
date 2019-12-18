#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {scalar_t__ iType; int /*<<< orphan*/  nData; int /*<<< orphan*/  pData; } ;
typedef  int /*<<< orphan*/  DocListReader ;
typedef  TYPE_1__ DocList ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  docListSpliceElement (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  firstDocid (TYPE_1__*) ; 
 int /*<<< orphan*/  readerInit (int /*<<< orphan*/ *,TYPE_1__*) ; 

__attribute__((used)) static void docListUpdate(DocList *d, DocList *pUpdate){
  DocListReader reader;

  assert( d!=NULL && pUpdate!=NULL );
  assert( d->iType==pUpdate->iType);

  readerInit(&reader, d);
  docListSpliceElement(&reader, firstDocid(pUpdate),
                       pUpdate->pData, pUpdate->nData);
}