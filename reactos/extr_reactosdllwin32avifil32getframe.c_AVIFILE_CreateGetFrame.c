#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/ * lpVtbl; } ;
struct TYPE_6__ {int ref; int lCurrentFrame; TYPE_1__ IGetFrame_iface; int /*<<< orphan*/ * pStream; } ;
typedef  TYPE_1__* PGETFRAME ;
typedef  int /*<<< orphan*/ * PAVISTREAM ;
typedef  TYPE_2__ IGetFrameImpl ;

/* Variables and functions */
 int /*<<< orphan*/  GetProcessHeap () ; 
 int /*<<< orphan*/  HEAP_ZERO_MEMORY ; 
 TYPE_2__* HeapAlloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  IAVIStream_AddRef (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  igetframeVtbl ; 

PGETFRAME AVIFILE_CreateGetFrame(PAVISTREAM pStream)
{
  IGetFrameImpl *pg;

  /* check parameter */
  if (pStream == NULL)
    return NULL;

  pg = HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY, sizeof(IGetFrameImpl));
  if (pg != NULL) {
    pg->IGetFrame_iface.lpVtbl = &igetframeVtbl;
    pg->ref           = 1;
    pg->lCurrentFrame = -1;
    pg->pStream       = pStream;
    IAVIStream_AddRef(pStream);
  }

  return &pg->IGetFrame_iface;
}