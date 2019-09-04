#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/ * notify; int /*<<< orphan*/ * ds3db; int /*<<< orphan*/ * iks; int /*<<< orphan*/  numIfaces; } ;
typedef  TYPE_1__ IDirectSoundBufferImpl ;
typedef  int /*<<< orphan*/  HRESULT ;

/* Variables and functions */
 int /*<<< orphan*/  IDirectSound3DBufferImpl_Destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IDirectSoundNotifyImpl_Destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IKsBufferPropertySetImpl_Destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  InterlockedIncrement (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  S_OK ; 
 int /*<<< orphan*/  TRACE (char*,TYPE_1__*) ; 
 int /*<<< orphan*/  WARN (char*) ; 
 int /*<<< orphan*/  secondarybuffer_destroy (TYPE_1__*) ; 

HRESULT IDirectSoundBufferImpl_Destroy(
    IDirectSoundBufferImpl *pdsb)
{
    TRACE("(%p)\n",pdsb);

    /* This keeps the *_Destroy functions from possibly deleting
     * this object until it is ready to be deleted */
    InterlockedIncrement(&pdsb->numIfaces);

    if (pdsb->iks) {
        WARN("iks not NULL\n");
        IKsBufferPropertySetImpl_Destroy(pdsb->iks);
        pdsb->iks = NULL;
    }

    if (pdsb->ds3db) {
        WARN("ds3db not NULL\n");
        IDirectSound3DBufferImpl_Destroy(pdsb->ds3db);
        pdsb->ds3db = NULL;
    }

    if (pdsb->notify) {
        WARN("notify not NULL\n");
        IDirectSoundNotifyImpl_Destroy(pdsb->notify);
        pdsb->notify = NULL;
    }

    secondarybuffer_destroy(pdsb);

    return S_OK;
}