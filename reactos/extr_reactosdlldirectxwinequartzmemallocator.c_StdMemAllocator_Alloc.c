#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_13__ {int dwPageSize; } ;
struct TYPE_12__ {int /*<<< orphan*/  listentry; } ;
struct TYPE_9__ {int cbAlign; int cbBuffer; int cbPrefix; int cBuffers; } ;
struct TYPE_10__ {int /*<<< orphan*/  free_list; TYPE_1__ props; } ;
struct TYPE_11__ {TYPE_2__ base; scalar_t__ pMemory; } ;
typedef  TYPE_3__ StdMemAllocator ;
typedef  TYPE_4__ StdMediaSample2 ;
typedef  TYPE_5__ SYSTEM_INFO ;
typedef  int LONG ;
typedef  int /*<<< orphan*/  IMemAllocator ;
typedef  int /*<<< orphan*/  HRESULT ;
typedef  int /*<<< orphan*/  BYTE ;

/* Variables and functions */
 int /*<<< orphan*/  E_OUTOFMEMORY ; 
 int /*<<< orphan*/  GetSystemInfo (TYPE_5__*) ; 
 int /*<<< orphan*/  MEM_COMMIT ; 
 int /*<<< orphan*/  PAGE_READWRITE ; 
 int /*<<< orphan*/  S_OK ; 
 int /*<<< orphan*/  StdMediaSample2_Construct (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,TYPE_4__**) ; 
 TYPE_3__* StdMemAllocator_from_IMemAllocator (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  VFW_E_BADALIGN ; 
 scalar_t__ VirtualAlloc (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add_head (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_empty (int /*<<< orphan*/ *) ; 

__attribute__((used)) static HRESULT StdMemAllocator_Alloc(IMemAllocator * iface)
{
    StdMemAllocator *This = StdMemAllocator_from_IMemAllocator(iface);
    StdMediaSample2 * pSample = NULL;
    SYSTEM_INFO si;
    LONG i;

    assert(list_empty(&This->base.free_list));

    /* check alignment */
    GetSystemInfo(&si);

    /* we do not allow a courser alignment than the OS page size */
    if ((si.dwPageSize % This->base.props.cbAlign) != 0)
        return VFW_E_BADALIGN;

    /* FIXME: each sample has to have its buffer start on the right alignment.
     * We don't do this at the moment */

    /* allocate memory */
    This->pMemory = VirtualAlloc(NULL, (This->base.props.cbBuffer + This->base.props.cbPrefix) * This->base.props.cBuffers, MEM_COMMIT, PAGE_READWRITE);

    if (!This->pMemory)
        return E_OUTOFMEMORY;

    for (i = This->base.props.cBuffers - 1; i >= 0; i--)
    {
        /* pbBuffer does not start at the base address, it starts at base + cbPrefix */
        BYTE * pbBuffer = (BYTE *)This->pMemory + i * (This->base.props.cbBuffer + This->base.props.cbPrefix) + This->base.props.cbPrefix;
        
        StdMediaSample2_Construct(pbBuffer, This->base.props.cbBuffer, iface, &pSample);

        list_add_head(&This->base.free_list, &pSample->listentry);
    }

    return S_OK;
}