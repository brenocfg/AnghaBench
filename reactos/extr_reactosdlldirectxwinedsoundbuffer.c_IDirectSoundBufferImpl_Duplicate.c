#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_19__   TYPE_3__ ;
typedef  struct TYPE_18__   TYPE_2__ ;
typedef  struct TYPE_17__   TYPE_1__ ;

/* Type definitions */
struct TYPE_19__ {int /*<<< orphan*/  driver; } ;
struct TYPE_18__ {int ref; int numIfaces; struct TYPE_18__* pwfx; TYPE_1__* buffer; int /*<<< orphan*/  entry; struct TYPE_18__* tmp_buffer; int /*<<< orphan*/  lock; int /*<<< orphan*/  buflen; int /*<<< orphan*/ * iks; int /*<<< orphan*/ * ds3db; TYPE_3__* device; scalar_t__ nrofnotifies; int /*<<< orphan*/ * notifies; int /*<<< orphan*/ * notify; scalar_t__ sec_mixpos; scalar_t__ buf_mixpos; int /*<<< orphan*/  state; scalar_t__ hwbuf; } ;
struct TYPE_17__ {int /*<<< orphan*/  ref; int /*<<< orphan*/  buffers; } ;
typedef  int /*<<< orphan*/  LPVOID ;
typedef  TYPE_2__ IDirectSoundBufferImpl ;
typedef  scalar_t__ HRESULT ;
typedef  TYPE_3__ DirectSoundDevice ;

/* Variables and functions */
 int /*<<< orphan*/  CopyMemory (TYPE_2__*,TYPE_2__*,int) ; 
 scalar_t__ DSERR_OUTOFMEMORY ; 
 TYPE_2__* DSOUND_CopyFormat (TYPE_2__*) ; 
 int /*<<< orphan*/  DSOUND_MixToTemporary (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DSOUND_RecalcFormat (TYPE_2__*) ; 
 scalar_t__ DS_OK ; 
 scalar_t__ DirectSoundDevice_AddBuffer (TYPE_3__*,TYPE_2__*) ; 
 scalar_t__ FAILED (scalar_t__) ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  GetProcessHeap () ; 
 TYPE_2__* HeapAlloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  HeapFree (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_2__*) ; 
 scalar_t__ IDsDriver_DuplicateSoundBuffer (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  RtlDeleteResource (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  RtlInitializeResource (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  STATE_STOPPED ; 
 int /*<<< orphan*/  TRACE (char*,...) ; 
 int /*<<< orphan*/  WARN (char*,...) ; 
 int /*<<< orphan*/  list_add_head (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_remove (int /*<<< orphan*/ *) ; 

HRESULT IDirectSoundBufferImpl_Duplicate(
    DirectSoundDevice *device,
    IDirectSoundBufferImpl **ppdsb,
    IDirectSoundBufferImpl *pdsb)
{
    IDirectSoundBufferImpl *dsb;
    HRESULT hres = DS_OK;
    TRACE("(%p,%p,%p)\n", device, ppdsb, pdsb);

    dsb = HeapAlloc(GetProcessHeap(),0,sizeof(*dsb));
    if (dsb == NULL) {
        WARN("out of memory\n");
        *ppdsb = NULL;
        return DSERR_OUTOFMEMORY;
    }
    CopyMemory(dsb, pdsb, sizeof(*dsb));

    dsb->pwfx = DSOUND_CopyFormat(pdsb->pwfx);
    if (dsb->pwfx == NULL) {
        HeapFree(GetProcessHeap(),0,dsb);
        *ppdsb = NULL;
        return DSERR_OUTOFMEMORY;
    }

    if (pdsb->hwbuf) {
        TRACE("duplicating hardware buffer\n");

        hres = IDsDriver_DuplicateSoundBuffer(device->driver, pdsb->hwbuf,
                                              (LPVOID *)&dsb->hwbuf);
        if (FAILED(hres)) {
            WARN("IDsDriver_DuplicateSoundBuffer failed (%08x)\n", hres);
            HeapFree(GetProcessHeap(),0,dsb->pwfx);
            HeapFree(GetProcessHeap(),0,dsb);
            *ppdsb = NULL;
            return hres;
        }
    }

    dsb->buffer->ref++;
    list_add_head(&dsb->buffer->buffers, &dsb->entry);
    dsb->ref = 1;
    dsb->numIfaces = 1;
    dsb->state = STATE_STOPPED;
    dsb->buf_mixpos = dsb->sec_mixpos = 0;
    dsb->notify = NULL;
    dsb->notifies = NULL;
    dsb->nrofnotifies = 0;
    dsb->device = device;
    dsb->ds3db = NULL;
    dsb->iks = NULL; /* FIXME? */
    dsb->tmp_buffer = NULL;
    DSOUND_RecalcFormat(dsb);
    DSOUND_MixToTemporary(dsb, 0, dsb->buflen, FALSE);

    RtlInitializeResource(&dsb->lock);

    /* register buffer */
    hres = DirectSoundDevice_AddBuffer(device, dsb);
    if (hres != DS_OK) {
        RtlDeleteResource(&dsb->lock);
        HeapFree(GetProcessHeap(),0,dsb->tmp_buffer);
        list_remove(&dsb->entry);
        dsb->buffer->ref--;
        HeapFree(GetProcessHeap(),0,dsb->pwfx);
        HeapFree(GetProcessHeap(),0,dsb);
        dsb = NULL;
    }

    *ppdsb = dsb;
    return hres;
}